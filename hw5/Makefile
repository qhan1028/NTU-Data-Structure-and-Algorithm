target = system
CPP_FLAG = -O3 -std=c++11

all: $(target)

system: system.cpp binomial_heap.h
	g++ $(CPP_FLAG) system.cpp -o system

clean:
	rm -rf system
	rm -rf 1.out
	rm -rf 2.out 
	rm -rf 3.out

run: system
	./system

test: 1.in 2.in 3.in system
	./system < 1.in > 1.out
	./system < 2.in > 2.out
	./system < 3.in > 3.out