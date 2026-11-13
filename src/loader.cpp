// loader.cpp
// 담당: 2번
#include "loader.h"

bool loadText(const std::string& path, Memory& mem) {
    // TODO(2번): 파일을 바이너리 모드로 열어 mem.text에 전부 읽기
    //   - 파일이 없음, 크기가 4의 배수가 아님 → stderr에 메시지, false
    (void)path;
    (void)mem;
    return false;
}

bool loadData(const std::string& path, Memory& mem) {
    // TODO(2번): 파일을 바이너리 모드로 열어 mem.data 앞부분에 읽기
    //   - 파일이 없음, 1024바이트 초과 → stderr에 메시지, false
    (void)path;
    (void)mem;
    return false;
}
