all:
	g++ -O3 hw2-4.cpp -o demo
	./demo /tmp2/KDDCup2012/track2/kddcup2012track2.txt < get.in > get.out
	./demo /tmp2/KDDCup2012/track2/kddcup2012track2.txt < clicked.in > clicked.out
	./demo /tmp2/KDDCup2012/track2/kddcup2012track2.txt < impressed.in > impressed.out
	./demo /tmp2/KDDCup2012/track2/kddcup2012track2.txt < profit.in > profit.out

clean:
	rm demo
	rm get.out
	rm clicked.out
	rm impressed.out
	rm profit.out
