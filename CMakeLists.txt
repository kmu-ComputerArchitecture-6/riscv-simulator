cmake_minimum_required(VERSION 3.16)
project(riscv_sim CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SRCS CONFIGURE_DEPENDS src/*.cpp)
add_executable(riscv_sim ${SRCS})
target_include_directories(riscv_sim PRIVATE include)
