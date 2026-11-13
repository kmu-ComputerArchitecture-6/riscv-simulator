// cpu.h
// CPU 상태(레지스터, PC)와 명령어 실행
#pragma once

#include <cstdint>
#include "memory.h"

// CPU 상태. 담당: 1번 (구조)
struct CPU {
    uint32_t pc = TEXT_BASE;     // 프로그램 카운터
    uint32_t reg[32] = {0};      // x0 ~ x31, 각 32비트
};

// 레지스터 쓰기. x0에 쓰는 값은 무시한다. 담당: 1번
void setReg(CPU& cpu, uint32_t rd, uint32_t value);

// 지원하는 14개 명령어 중 하나인지 판별만 한다 (실행하지 않음). 담당: 3번
// 실행 한도(100만 개)에 도달한 뒤 다음 명령어를 실행하지 않고 판별할 때 사용
// execute도 내부에서 이 판별을 같은 기준으로 해야 한다
bool isSupported(uint32_t inst);

// 명령어 하나를 해독하고 실행한다. 담당: 3번
// - 지원하는 명령어: 실행하고, cpu.pc를 다음 PC로 바꾼 뒤 true
//   (분기 성립: fetch PC + imm, 그 외: fetch PC + 4)
// - invalid 명령어: 아무것도 바꾸지 않고 false
bool execute(CPU& cpu, Memory& mem, uint32_t inst);
