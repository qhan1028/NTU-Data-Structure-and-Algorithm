all:
	g++ -O3 hw2-4.cpp -o demo
	./demo /tmp2/KDDCup2012/track2/kddcup2012track2.txt

clean:
	rm demo
