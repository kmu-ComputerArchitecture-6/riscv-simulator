// loader.h
// 입력 파일(text.bin, data.bin)을 메모리에 적재
// 담당: 2번
#pragma once

#include <string>
#include "memory.h"

// text.bin 전체를 mem.text에 넣는다 (첫 바이트 = 0x00040000)
// 실패하면 stderr에 이유를 쓰고 false
bool loadText(const std::string& path, Memory& mem);

// data.bin을 mem.data 앞부분에 넣는다 (첫 바이트 = 0x10000000, 0~1024바이트)
// 실패하면 stderr에 이유를 쓰고 false
bool loadData(const std::string& path, Memory& mem);
