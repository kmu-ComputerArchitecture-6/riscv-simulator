# RISC-V 시뮬레이터

RV32I 명령어 14개를 실행하는 기능 시뮬레이터.

## 팀원
- TODO

## 환경
- 언어: C++17
- 컴파일러: g++ (TODO: 최종 확인한 버전 기재)
- 외부 의존성: 없음

## 빌드
```bash
g++ -std=c++17 -O2 -o riscv_sim src/*.cpp
```
또는 `make`

## 실행
```bash
./riscv_sim text.bin data.bin
```
- 표준 출력: `PC 0x%08x invalid instruction 0x%08x`
- 현재 디렉터리에 `data.out` (1024바이트) 생성

## 파일 배치
| 파일 | 내용 |
|---|---|
| `src/main.cpp` | 인자 처리, 적재, 실행 시작 |
| `src/memory.h/.cpp` | 메모리 표현, little-endian 읽기/쓰기 |
| `src/loader.h/.cpp` | text.bin, data.bin 적재 |
| `src/simulator.h/.cpp` | 실행 루프, 종료 처리 |
| `src/cpu.h/.cpp` | CPU 상태(PC, 레지스터), 명령어 실행 |
| `src/decoder.h/.cpp` | 명령어 해독 |
| `tests/` | 자체 테스트 |
