// simulator.h
// 실행 루프와 종료 처리
#pragma once

#include <cstdint>
#include "cpu.h"
#include "memory.h"

const uint64_t MAX_STEPS = 1000000;  // 정상 명령어 최대 실행 개수

// 실행 루프. 담당: 2번
// PC 위치에서 명령어를 fetch → execute에 넘김 → false면 종료 처리
// 반환값: 프로그램 종료 코드 (정상 종료 0, 실행 한도 초과 등은 0이 아닌 값)
int run(CPU& cpu, Memory& mem);

// 종료 처리. 담당: 미정
// 표준 출력 한 줄 + data.out 저장
void finish(const Memory& mem, uint32_t fetchPC, uint32_t inst);
