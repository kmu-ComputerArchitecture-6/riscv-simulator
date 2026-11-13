// cpu.cpp
#include "cpu.h"
#include "decoder.h"

// 담당: 1번 (구조)
void setReg(CPU& cpu, uint32_t rd, uint32_t value) {
    if (rd != 0) cpu.reg[rd] = value;
}

// 담당: 3번
bool execute(CPU& cpu, Memory& mem, uint32_t inst) {
    // TODO(3번): decoder로 명령어를 해독하고 14개 명령어를 실행
    //   add sub and or / addi andi ori / lui / lw sw / beq bne blt bge
    //   - 레지스터 쓰기는 setReg 사용 (x0 보호)
    //   - lw/sw는 loadWord / storeWord 사용
    //   - blt/bge는 (int32_t)로 캐스팅해서 비교
    //   - 실행 후 cpu.pc 갱신
    (void)cpu;
    (void)mem;
    (void)inst;
    return false;  // 지금은 모든 명령어를 invalid로 처리
}
