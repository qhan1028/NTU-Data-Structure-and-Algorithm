target = hw1_6 gcd_by_binary gcd_by_euclid
CFLAGS = -O2 -Wall
CPPFLAGS = -O2 -std=c++11 -Wall

all: $(target)

%: %.c
	gcc $(CFLAGS) $< -o $@

%: %.cpp
	g++ $(CPPFLAGS) $< -o $@

gcd_by_binary: gcd_by_binary.cpp biginteger_for_binary.cpp biginteger_for_binary.h
	g++ $(CPPFLAGS) gcd_by_binary.cpp biginteger_for_binary.cpp -o $@

gcd_by_euclid: gcd_by_euclid.cpp biginteger_for_euclid.cpp biginteger_for_euclid.h
	g++ $(CPPFLAGS) gcd_by_euclid.cpp biginteger_for_euclid.cpp -o $@

clean:
	rm -rf $(target)

run1_6:
	./hw1_6

run1_7_1:
	./gcd_by_binary

run1_7_2:
	./gcd_by_euclid