#include <cstdio>
#include <cstdlib>
#include <ctime>

char trans(int input) {
	if (input >= 0 && input <= 9) return '0'+input;
	else if (input >= 10 && input <= 35) return 'A'+input-10;
	else return 'a'+input-36;
};

int main(int argc, char *argv[])
{
	srand(time(NULL));
	for (int i = 0 ; i < 62 ; i++) {
		char c = trans(i);
		int m = abs(rand() * rand() % 1000000000);
		printf("create %c %c\n", c, c);
		printf("login %c %c\n", c, c);
		printf("deposit %d\n", m);
	}
	printf("login 0 0\n");
	char now = '0';
	int max = atoi(argv[1]);
	for (int i = 0 ; i < max ; i++) {
		char c = trans(rand()%62);
		char d = trans(rand()%62);
		switch (rand()%8) {
			case 0 :
				printf("login %c %c\n", c, c);
				now = c;
				break;
			case 1 :
				printf("deposit %d\n", rand());
				break;
			case 2 :
				printf("withdraw %d\n", rand());
				break;
			case 3 :
				if(c != now) printf("transfer %c %d\n", c, rand());
				else i--;
				break;
			case 4 : 
				printf("search %c\n", c);
				break;
			case 5 : 
				printf("create %c %c\n", c, c);
				break;
			case 6 :
				if (now != c) printf("delete %c %c\n", c, c);
				else i--;
				break;
			case 7 :
				if (now != d) printf("merge %c %c %c %c\n", c, c, d, d);
				else i--;
				break;
			default: ;
		}
	}
	return 0;
}