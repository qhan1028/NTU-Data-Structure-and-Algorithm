#include <cstdio>
#include <cstring>
#include <iostream>
#include "binomial_heap.h"
#define INMAX 10

class CMD {
public:
	int id;
	int p;
	bool operator > (const CMD& cmd) {
		if (p > cmd.p) return true;
		else if (p == cmd.p && id < cmd.id) return true;
		else return false;
	}
};

int main()
{
	int cm1 = 0, cm2 = 0;
	int c = 0, w = 0;
	printf("Input the number of computers and w : ");
	scanf("%d%d", &c, &w);
	BinomialHeap<CMD> *computer = new BinomialHeap<CMD> [c];
	char input[INMAX];
	while (scanf("%s", input) != EOF) {
		CMD temp;
		if (strcmp(input, "assign") == 0) {
			scanf("%d%d%d", &cm1, &temp.id, &temp.p);
			computer[cm1].insert(temp);
			printf("There are %d tasks on computer %d.\n", computer[cm1].size, cm1);
		}
		if (strcmp(input, "execute") == 0) {
			scanf("%d", &cm1);
			temp = computer[cm1].pop();
			printf("Computer %d execute task %d.\n", cm1, temp.id);
			while (computer[cm1].size != 0 && computer[cm1].max_p() == temp.p) {
				temp = computer[cm1].pop();
				printf("Computer %d execute task %d.\n", cm1, temp.id);
			}
		}
		if (strcmp(input, "merge") == 0) {
			scanf("%d%d", &cm1, &cm2);
			if (computer[cm2].size >= w) {
				computer[cm1].merge(computer[cm2]);
				printf("The largest priority number is now %d on %d.\n", computer[cm1].max_p(), cm1);
			} else printf("Merging reuest failed.\n");
		}
	}
	return 0;
}