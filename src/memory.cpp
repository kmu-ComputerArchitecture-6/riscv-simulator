// memory.cpp
// 담당: 1번 (구조)
#include "memory.h"

#include <cstdio>
#include <cstdlib>

// 바이트 4개 → 32비트 값 (little-endian)
// 예: p[0..3] = 78 56 34 12  →  0x12345678
static uint32_t bytesToWord(const uint8_t* p) {
    return (uint32_t)p[0]
         | ((uint32_t)p[1] << 8)
         | ((uint32_t)p[2] << 16)
         | ((uint32_t)p[3] << 24);
}

// 32비트 값 → 바이트 4개 (little-endian, 낮은 바이트가 낮은 주소)
static void wordToBytes(uint32_t value, uint8_t* p) {
    p[0] = value & 0xFF;
    p[1] = (value >> 8) & 0xFF;
    p[2] = (value >> 16) & 0xFF;
    p[3] = (value >> 24) & 0xFF;
}

uint32_t fetchWord(const Memory& mem, uint32_t addr) {
    if (addr < TEXT_BASE) return 0;
    uint32_t idx = addr - TEXT_BASE;
    if (idx + 4 > mem.text.size()) return 0;
    return bytesToWord(&mem.text[idx]);
}

// lw, sw 주소가 data 영역 안에 4바이트 전부 들어가는지 확인
// 명세상 채점 입력은 항상 범위 안이므로, 벗어나면 진단 후 비정상 종료
static uint32_t dataIndex(uint32_t addr) {
    if (addr < DATA_BASE || addr - DATA_BASE + 4 > DATA_SIZE) {
        fprintf(stderr, "error: data access out of range: 0x%08x\n", addr);
        exit(1);
    }
    return addr - DATA_BASE;
}

uint32_t loadWord(const Memory& mem, uint32_t addr) {
    return bytesToWord(&mem.data[dataIndex(addr)]);
}

void storeWord(Memory& mem, uint32_t addr, uint32_t value) {
    wordToBytes(value, &mem.data[dataIndex(addr)]);
}
