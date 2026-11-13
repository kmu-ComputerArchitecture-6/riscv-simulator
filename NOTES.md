# RISC-V 시뮬레이터 정리

## 과제 요약
- text.bin, data.bin을 읽어 RV32I 명령어 14개를 실행하는 시뮬레이터
- 명령어: add sub addi and or andi ori lui lw sw beq bne blt bge
- 시작 PC / text 시작: 0x00040000
- data 시작: 0x10000000, 1024바이트 (0x10000000 ~ 0x100003FF)
- 바이트 순서: little-endian (명령어, 데이터 모두)
- 지원하지 않는 명령어를 fetch하면 실행하지 않고 종료
- 종료 출력 (표준 출력 한 줄, fetch 당시 PC):
  `PC 0x00040014 invalid instruction 0x00000000`
- data.out: 0x10000000부터 정확히 1024바이트, 바이너리
- 실행 한도: 명령어 1,000,000개
- 실행: `<실행파일> text.bin data.bin`
- 점수: 팀 60 + 개인 40 (기말 때 인쇄한 제출본 코드만 보고 개별 시험)
- 채점: 표준 출력과 data.out 바이트 비교, 비공개 테스트 있음

## 결정 사항
- 팀 3명, 언어 C++
- 구현은 병렬이 아니라 순서대로
- 제출물(D)과 시험 대비(E)는 다 같이
- 제어 신호(ALUSrc 등)는 만들 필요 없음. ISA 수준 결과만 맞추면 됨
- jal, jalr, auipc, slli 등 목록에 없는 명령어는 invalid로 종료

## 분담 (초안)
| 담당 | 내용 | 작업 번호 |
|---|---|---|
| 1번 (본인) | 구조: 파일·함수 뼈대, 메모리, 레지스터, read32/write32 | 1, 3, 5 |
| 2번 | 입력 읽기, data 적재, 잘못된 입력 에러 처리, 실행 루프 (fetch → CPU로 넘기기) | 2, 6, 16, 17 |
| 3번 | CPU: 기계어를 받아 해독 + 연산 | 8~15 |

아직 담당이 정해지지 않은 것:
- 7 종료 처리 (출력 한 줄, data.out 저장) + 4 data.out 쓰기
- 어셈블러 (테스트 도구, 처음에 팀원 한 명이 맡기로 했던 것)

2번 ↔ 3번 인터페이스 (정함):
- `bool execute(CPU& cpu, Memory& mem, uint32_t inst)`
- 3번이 cpu.pc를 직접 다음 PC로 바꿈. 반환값은 정상(true) / invalid(false)
- invalid면 아무것도 바꾸지 않음. 2번이 fetchPC를 따로 저장해 두고 finish에 넘김
- `bool isSupported(uint32_t inst)` (3번): 실행하지 않고 판별만. 100만 개 실행 후 다음 명령어 판단에 사용

실행 루프 주의:
- 입력은 줄 단위 텍스트가 아님. PC 위치에서 4바이트씩 읽음
- 파일 순서대로 넘기면 안 됨. 분기 때문에 매번 PC가 가리키는 명령어를 fetch

## 명세 해석
### text.bin은 기계어 바이트
명세서에 "text.bin은 기계어다"라는 문장이 직접 있지는 않고, 아래에서 나오는 결론.
- 7장 예시: 기계어 열 `0x100000b7` ↔ text.bin 바이트 `b7 00 00 10` (little-endian)
- 4장: 헤더 없는 바이너리 파일, ASCII 문자열이나 16진수 텍스트 파일이 아님
- 5.1장: 명령어 값 = 입력 바이트 4개를 little-endian으로 해석한 32비트 값

### 어셈블러는 테스트 도구
- 시뮬레이터 실행에는 필요 없음 (입력이 이미 기계어)
- 자체 테스트용 text.bin을 만드는 데 사용
- 8장 제출물 "자체 테스트 입출력: ... 테스트 목적 또는 생성 코드"로 제출 가능
- 학습목표 ① (인코딩과 해독), 시험 대비에 도움

## 폴더 구조 (2026-11-13 뼈대 생성)
```
RISCV/
├── README.md
├── Makefile / CMakeLists.txt
├── src/
│   ├── main.cpp            인자 처리, 적재, run 호출                  (2번)
│   ├── memory.h / .cpp     Memory 구조체, fetchWord/loadWord/storeWord (1번, 구현 완료)
│   ├── loader.h / .cpp     loadText, loadData                         (2번)
│   ├── simulator.h / .cpp  run (실행 루프), finish (종료 처리)         (run 2번, finish 미정)
│   ├── cpu.h / .cpp        CPU 구조체(pc, reg), setReg, execute        (setReg 1번 완료, execute 3번)
│   └── decoder.h / .cpp    해독                                       (3번, 설계도 3번)
├── tests/
│   ├── tools/              어셈블러 / 테스트 바이너리 생성
│   ├── cases/              테스트별 폴더 (text.bin, data.bin, 기대 출력, 설명)
│   └── run_tests           전체 테스트 실행 + 비교
└── report/                 보고서, AI 사용 메모, 사진
```
빌드: `g++ -std=c++17 -O2 -o riscv_sim src/*.cpp`

## 메모리와 레지스터 표현
- 레지스터: `uint32_t reg[32]` (32비트 칸 32개, x0~x31)
  - x0은 쓰기 함수에서 무시
  - uint32_t라서 덧셈·뺄셈은 자동으로 하위 32비트만 남음
  - 부호가 필요한 곳(blt, bge)만 `(int32_t)`로 캐스팅
- 메모리: 바이트 배열 (주소 하나 = 1바이트)
  - text: `std::vector<uint8_t>` (text.bin 크기만큼)
  - data: `uint8_t data[1024]`, 0으로 초기화
  - 배열 인덱스 = 주소 - 시작 주소 (예: 0x10000008 → data[8])
  - 32비트 값은 4칸에 나눠 저장, 낮은 바이트가 낮은 주소 (little-endian)
  - `78 56 34 12` → `0x12345678`

## 핵심 개념
1. 바이트 순서: 메모리는 1바이트 단위, 32비트 값은 4바이트를 합치고 쪼갬 (fetch, lw, sw, 파일 입출력)
2. 명령어 해독: 비트를 잘라 opcode, rd, rs1, rs2, funct3, funct7, 즉시값 추출. S형·B형 즉시값 조립이 어려움
3. 부호 처리: `0xffffffff`는 부호 없이 약 42억, 부호 있게 -1. 즉시값 부호 확장, blt/bge
4. PC 갱신: 보통 PC+4, 분기 성립 시 fetch PC + imm, 종료 때 fetch 당시 PC 출력

## 구현 작업 (순서대로)
### memory.cpp
1. 메모리 배열 준비 (text, data)
2. 파일 적재: text.bin → 0x00040000부터, data.bin → 0x10000000부터 (0~1024바이트)
3. read32 / write32 (little-endian)
4. data.out 저장 (data 배열 1024바이트, 바이너리 모드)

### cpu.cpp
5. 레지스터 + setReg (rd == 0이면 무시)
6. 실행 루프: PC = 0x00040000, fetch (fetch 당시 PC 보관) → decode → invalid면 종료 / 아니면 execute, 실행 개수 카운트
7. 종료 처리: 출력 한 줄 + data.out 저장

### decoder.cpp
8. 필드 추출: opcode [6:0], rd [11:7], funct3 [14:12], rs1 [19:15], rs2 [24:20], funct7 [31:25]
9. 즉시값 조립 + 부호 확장
   - I형 (addi, andi, ori, lw): [31:20], 12비트
   - S형 (sw): [31:25] + [11:7], 12비트
   - B형 (beq, bne, blt, bge): [31] [7] [30:25] [11:8] + 끝에 0, 13비트
   - U형 (lui): [31:12] << 12
10. 명령어 판별 (opcode + funct3 + funct7), 14개 중 어디에도 해당하지 않으면 invalid

### cpu.cpp - execute
11. R형: add, sub, and, or
12. I형: addi, andi, ori
13. U형: lui
14. lw (rs1 + imm 주소에서 읽기), sw (rs1 + imm 주소에 쓰기)
15. beq, bne, blt, bge: blt/bge는 int32_t 비교, 성립 시 fetch PC + imm, 아니면 fetch PC + 4

### main.cpp
16. 인자 2개 확인 (text 경로, data 경로)
17. 적재 → 실행 루프 호출

## 테스트 작업 (나중에)
- C1 테스트 바이너리 생성 (어셈블러)
- C2 명세서 7장 예시 재현
- C3 명령어별 테스트 + 손으로 계산한 기대 결과
- C4 경계 테스트: 음수 즉시값, 오버플로, x0 쓰기, -1 vs 1 비교, 뒤로 가는 분기, 미지원 명령어
- C5 자동 비교 스크립트 (표준 출력 + data.out)
- C6 버그와 수정 내용 기록

## 같이 할 것
- 제출물: README(팀원, 언어·버전, 의존성, 빌드·실행 명령, 파일 배치), 보고서 PDF(필수 11개 항목), 기능별 구현 위치표, AI 활용표, 팀 사진, 새 환경 실행 확인, 명세서 11장 체크리스트
- 시험 대비: 전체 코드 같이 읽기, 예시 문항 연습, 제출본 코드 인쇄

## 주의
- AI 사용 내역은 그때그때 메모 (보고서에 영역별 등급 0~3, 반영 위치, 검증 근거)
- 디버그 출력은 stderr로만
- data.out은 바이너리 모드로 쓰기 (Windows 텍스트 모드는 바이트를 바꿈)
- 채점 환경이 Linux일 수 있으니 Windows 전용 기능 쓰지 않기
