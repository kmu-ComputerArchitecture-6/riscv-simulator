// simulator.cpp
#include "simulator.h"

// 담당: 2번
int run(CPU& cpu, Memory& mem) {
    // TODO(2번): 실행 루프
    //   반복:
    //     fetchPC = cpu.pc
    //     inst = fetchWord(mem, fetchPC)
    //     execute(cpu, mem, inst)가 false면 finish(mem, fetchPC, inst) 후 0 반환
    //     실행 개수가 MAX_STEPS를 넘으면 stderr에 메시지, 0이 아닌 값 반환
    (void)cpu;
    (void)mem;
    return 1;
}

// 담당: 미정
void finish(const Memory& mem, uint32_t fetchPC, uint32_t inst) {
    // TODO: 종료 처리
    //   1. printf("PC 0x%08x invalid instruction 0x%08x\n", fetchPC, inst);
    //   2. mem.data 1024바이트를 "data.out"에 바이너리 모드로 저장 (덮어쓰기)
    (void)mem;
    (void)fetchPC;
    (void)inst;
}
