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
class Memory {
public:
    std::vector<uint8_t> instructions;  // text segment: text.bin 내용 (명령어)
    uint8_t data[DATA_SIZE] = {0};      // data segment, 0으로 초기화

    // text segment에서 pc 위치의 명령어 4바이트를 읽는다 (fetch용)
    // 범위를 벗어나면 0을 돌려준다 (0x00000000은 invalid 명령어)
    uint32_t fetchWord(uint32_t pc) const;

    // data segment에서 4바이트를 읽는다 (lw용)
    uint32_t loadWord(uint32_t addr) const;

    // data segment에 4바이트를 쓴다 (sw용)
    void storeWord(uint32_t addr, uint32_t value);
};
