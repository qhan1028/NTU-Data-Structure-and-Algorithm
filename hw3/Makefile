target = hw3_1
C_flag = -O3 -Wall
CPP_flag = -O3 -std=c++11 -Wall

all: $(target)

%: %.c
	gcc $(C_flag) $< -o $@

%: %.cpp
	g++ $(CPP_flag) $< -o $@

hw3_1: hw3_1.cpp hw3_1.h
	g++ $(CPP_flag) hw3_1.cpp -o $@

hw3_2: hw3_2.cpp hw3_2.h
	g++ $(CPP_flag) hw3_2.cpp -o $@

clean:
	rm $(target)

run:
	./$(target)