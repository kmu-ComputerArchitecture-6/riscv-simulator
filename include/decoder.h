// decoder.h
// 명령어 해독: 필드 추출, 즉시값 조립과 부호 확장, 명령어 판별
// 담당: 3번 (멤버와 해독 결과 형식은 3번이 설계)
#pragma once

#include <cstdint>

class Decoder {
public:
    // TODO(3번): 해독 결과 형식과 멤버 함수 선언
    //   필드: opcode [6:0], rd [11:7], funct3 [14:12],
    //         rs1 [19:15], rs2 [24:20], funct7 [31:25]
    //   즉시값: I형 [31:20]
    //           S형 [31:25] + [11:7]
    //           B형 [31] [7] [30:25] [11:8] + 0
    //           U형 [31:12] << 12
    //   판별: opcode + funct3 + funct7로 14개 중 하나, 아니면 invalid
};
