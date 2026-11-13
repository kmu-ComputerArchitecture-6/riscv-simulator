// main.cpp
// 사용법: riscv_sim <text.bin> <data.bin>
// 담당: 2번
#include "cpu.h"
#include "loader.h"
#include "memory.h"
#include "simulator.h"

int main(int argc, char* argv[]) {
    // TODO(2번): 인자 개수 확인 (2개가 아니면 stderr에 사용법, 종료 코드 1)

    Memory mem;
    CPU cpu;

    // TODO(2번): loadText(argv[1], mem), loadData(argv[2], mem) 호출, 실패하면 종료 코드 1

    return run(cpu, mem);
}
