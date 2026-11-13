// loader.cpp
// 담당: 2번
#include "loader.h"

bool Loader::loadText(const std::string& path, Memory& mem) {
    // TODO(2번): 파일을 바이너리 모드로 열어 mem.instructions에 전부 읽기
    //   - 파일이 없음, 크기가 4의 배수가 아님 → stderr에 메시지, false
    return false;
}

bool Loader::loadData(const std::string& path, Memory& mem) {
    // TODO(2번): 파일을 바이너리 모드로 열어 mem.data 앞부분에 읽기
    //   - 파일이 없음, 1024바이트 초과 → stderr에 메시지, false
    //   - 0바이트 파일도 정상
    return false;
}
