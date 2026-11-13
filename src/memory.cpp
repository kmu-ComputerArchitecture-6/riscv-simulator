// memory.cpp
// 담당: 1번 (구조)
#include "memory.h"

#include <cstdio>
#include <cstdlib>

// 메모리의 바이트 4개를 읽어 32비트 값으로 합친다 (little-endian)
// bytes: 읽기 시작할 메모리 위치
// 예: bytes[0..3] = 78 56 34 12  →  0x12345678
static uint32_t bytesToWord(const uint8_t* bytes) {
    return (uint32_t)bytes[0]
         | ((uint32_t)bytes[1] << 8)
         | ((uint32_t)bytes[2] << 16)
         | ((uint32_t)bytes[3] << 24);
}

// 32비트 값을 바이트 4개로 쪼개 메모리에 쓴다 (little-endian, 낮은 바이트가 낮은 주소)
// bytes: 쓰기 시작할 메모리 위치
static void wordToBytes(uint32_t value, uint8_t* bytes) {
    bytes[0] = value & 0xFF;
    bytes[1] = (value >> 8) & 0xFF;
    bytes[2] = (value >> 16) & 0xFF;
    bytes[3] = (value >> 24) & 0xFF;
}

uint32_t Memory::fetchWord(uint32_t pc) const {
    if (pc < TEXT_BASE) return 0;
    uint32_t idx = pc - TEXT_BASE;
    if (idx + 4 > instructions.size()) return 0;
    return bytesToWord(&instructions[idx]);
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

uint32_t Memory::loadWord(uint32_t addr) const {
    return bytesToWord(&data[dataIndex(addr)]);
}

void Memory::storeWord(uint32_t addr, uint32_t value) {
    wordToBytes(value, &data[dataIndex(addr)]);
}
