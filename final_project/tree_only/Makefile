CPPFLAG = -std=c++11 -O3

all:
	g++ $(CPPFLAG) main.cpp all.cpp md5.cpp advise.cpp -o final_project

run:
	g++ $(CPPFLAG) main.cpp all.cpp md5.cpp advise.cpp -o final_project
	./final_project

clean:
	rm -rf final_project
	rm -rf maker
	rm -rf test.out
	rm -rf test.in

maker: 
	g++ $(CPPFLAG) maker.cpp -o maker
	./maker 200000 > test.in

test:
	g++ $(CPPFLAG) main.cpp all.cpp md5.cpp advise.cpp -o final_project
	./final_project < test.in > test.out