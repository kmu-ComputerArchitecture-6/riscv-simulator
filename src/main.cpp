// main.cpp
// 사용법: riscv_sim <text.bin> <data.bin>
// 실행 루프(run), 종료 처리(finish), main
#include <cstdint>
#include <cstdio>
#include "cpu.h"
#include "loader.h"
#include "memory.h"

const uint64_t MAX_STEPS = 1000000;  // 정상 명령어 최대 실행 개수

// 종료 처리
// invalid 명령어를 fetch했을 때 호출. 그 명령어는 실행하지 않은 상태
// 1. 표준 출력 한 줄: fetch 당시 PC와 명령어 값 (명세서 5.1)
// 2. data.out: data segment 1024바이트를 그대로 저장 (명세서 5.2)
void finish(const Memory& mem, uint32_t fetchPC, uint32_t inst) {
    printf("PC 0x%08x invalid instruction 0x%08x\n", fetchPC, inst);
    fflush(stdout);

    // "wb": 바이너리 모드 + 기존 파일 덮어쓰기
    // 텍스트 모드("w")로 쓰면 Windows에서 0x0a 바이트가 0x0d 0x0a로 바뀌어 파일이 망가진다
    FILE* fp = fopen("data.out", "wb");
    if (fp == nullptr) {
        fprintf(stderr, "error: cannot open data.out for writing\n");
        return;
    }
    if (fwrite(mem.data, 1, DATA_SIZE, fp) != DATA_SIZE) {
        fprintf(stderr, "error: failed to write data.out\n");
    }
    fclose(fp);
}

// 실행 루프. 담당: 2번
// PC 위치에서 명령어를 fetch → execute에 넘김 → false면 종료 처리
// 반환값: 프로그램 종료 코드 (정상 종료 0, 실행 한도 초과 등은 0이 아닌 값)
int run(CPU& cpu, Memory& mem) {
    // TODO(2번): 실행 루프
    //   반복:
    //     fetchPC = cpu.pc
    //     inst = mem.fetchWord(fetchPC)
    //     실행 개수가 MAX_STEPS에 도달했으면 (100만 개 실행 완료):
    //       보고서에 실행한도 초과로 비정상 종료 조건이 있기때문에 필요함
    //       cpu.isSupported(inst)가 false → finish(mem, fetchPC, inst) 후 0 반환 (정상 종료)
    //       cpu.isSupported(inst)가 true  → 실행하지 않고 stderr에 메시지, 0이 아닌 값 반환
    //     cpu.execute(mem, inst)가 false면 finish(mem, fetchPC, inst) 후 0 반환
    //     true면 실행 개수 + 1
    return 1;
}

// 담당: 2번
int main(int argc, char* argv[]) {
    // TODO(2번): 인자 개수 확인 (2개가 아니면 stderr에 사용법, 종료 코드 1)

    Memory mem;
    CPU cpu;
    Loader loader;

    // TODO(2번): loader.loadText(argv[1], mem), loader.loadData(argv[2], mem) 호출, 실패하면 종료 코드 1

    return run(cpu, mem);
}
