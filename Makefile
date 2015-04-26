target = hw3
C_flag = -O3 -Wall
CPP_flag = -O3 -std=c++11 -Wall

all: $(target)

%: %.c
	gcc $(C_flag) $< -o $@

%: %.cpp
	g++ $(CPP_flag) $< -o $@

hw3: hw3_1.cpp hw3_1.h hw3_2.cpp hw3_2.h
	g++ $(CPP_flag) hw3_1.cpp -o 3_4_1.out
	g++ $(CPP_flag) hw3_2.cpp -o 3_4_2.out

clean:
	rm $(target)

run:
	./$(target)