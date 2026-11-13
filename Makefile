CXX      = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra
TARGET   = riscv_sim
SRCS     = $(wildcard src/*.cpp)

$(TARGET): $(SRCS) $(wildcard src/*.h)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET) $(TARGET).exe

.PHONY: clean
