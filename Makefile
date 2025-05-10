CXX = clang++
CXXFLAGS = -std=c++20 -Wall -fsanitize=address -g -Iinclude 

SRC = main.cpp
OUT = main

all: $(OUT)

$(OUT): $(SRC)
		$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC)

clean:
		rm -f $(OUT)