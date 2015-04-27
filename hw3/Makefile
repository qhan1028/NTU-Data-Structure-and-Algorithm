target = hw3
C_flag = -O3
CPP_flag = -O3 -std=c++11

all: $(target)

%: %.c
	gcc $(C_flag) $< -o $@

%: %.cpp
	g++ $(CPP_flag) $< -o $@

hw3: hw3_1.cpp hw3_1.h hw3_2.cpp hw3_2.h
	g++ $(CPP_flag) hw3_1.cpp -o 3_4_1.out
	g++ $(CPP_flag) hw3_2.cpp -o 3_4_2.out

clean1:
	rm 3_4_1.out

clean2:
	rm 3_4_2.out

clean:
	rm 3_4_1.out
	rm 3_4_2.out

run1:
	./3_4_1.out

run2:
	./3_4_2.out