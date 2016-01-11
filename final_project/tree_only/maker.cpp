#include <cstdio>
#include <cstdlib>
#include <ctime>

#define LOGIN 0
#define DEPOSIT 1
#define WITHDRAW 2
#define TRANSFER 3
#define SEARCH 4
#define CREATE 5
#define DELETE 6
#define MERGE 7

char trans(int input) {
	if (input >= 0 && input <= 9) return '0'+input;
	else if (input >= 10 && input <= 35) return 'A'+input-10;
	else return 'a'+input-36;
}

int main(int argc, char *argv[])
{
	int exist[62];
	srand(time(NULL));
	for (int i = 0 ; i < 62 ; i++) {
		char c = trans(i);
		int m = rand()%10;
		exist[i] = 1;
		printf("create %c %c\n", c, c);
		printf("login %c %c\n", c, c);
		printf("deposit %d\n", m);
	}
	printf("login 0 0\n");
	char now = '0';
	for (int i = 0 ; i < atoi(argv[1]) ; i++) {
		int a = rand()%62;
		int b = rand()%62;
		char c = trans(a);
		char d = trans(b);
		switch (rand()%8) {
			case LOGIN :
				if (exist[a] != 0) {
					printf("login %c %c\n", c, c);
					now = c;
				}
				else i--;
				break;
			case DEPOSIT :
				printf("deposit %d\n", rand()%10);
				break;
			case WITHDRAW :
				printf("withdraw %d\n", rand()%10);
				break;
			case TRANSFER :
				if(c != now) printf("transfer %c %d\n", c, rand()%10);
				else i--;
				break;
			case SEARCH : 
				printf("search %c\n", c);
				break;
			case CREATE : 
				printf("create %c %c\n", c, c);
				break;
			case DELETE :
				if (now != c) {
					printf("delete %c %c\n", c, c);
					exist[a] = 0;
				}
				else i--;
				break;
			case MERGE :
				if (now != d && d != c) {
					printf("merge %c %c %c %c\n", c, c, d, d);
					exist[b] = 0;
				}
				else i--;
				break;
			default: ;
		}
	}
	return 0;
}