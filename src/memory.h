// memory.h
// 메모리 표현과 4바이트 little-endian 읽기/쓰기
// 담당: 1번 (구조)
#pragma once

#include <cstdint>
#include <vector>

const uint32_t TEXT_BASE = 0x00040000;  // text segment 시작 주소 = 초기 PC
const uint32_t DATA_BASE = 0x10000000;  // data segment 시작 주소
const uint32_t DATA_SIZE = 1024;        // data 영역 크기 (0x10000000 ~ 0x100003FF)

// 메모리는 바이트 배열. 배열 인덱스 = 주소 - 시작 주소
struct Memory {
    std::vector<uint8_t> text;          // text.bin 내용 (명령어)
    uint8_t data[DATA_SIZE] = {0};      // data 영역, 0으로 초기화
};

// text 영역에서 명령어 4바이트를 읽는다 (fetch용)
// text 범위를 벗어나면 0을 돌려준다 (0x00000000은 invalid 명령어)
uint32_t fetchWord(const Memory& mem, uint32_t addr);

// data 영역에서 4바이트를 읽는다 (lw용)
uint32_t loadWord(const Memory& mem, uint32_t addr);

// data 영역에 4바이트를 쓴다 (sw용)
void storeWord(Memory& mem, uint32_t addr, uint32_t value);
