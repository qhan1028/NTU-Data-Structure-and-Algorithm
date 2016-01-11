#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include "all.h"
using namespace std;

bool sCompare(char *a, char *b) {return (strcmp(a, b) < 0);}

int main()
{
	ALL all;
	char cmd[20], cmd2[20], inID1[INMAX], inPW1[INMAX], inID2[INMAX], inPW2[INMAX], order[INMAX];
	int inMoney;
	int curIndex = -1, temp, now, exist, index, index1, index2, f_size, i, next, first, second;
	RESULT result;
	all.allpeople = 0;
	int count = 0;
	while (scanf("%s", cmd) != EOF) {
		inMoney = 0;
		switch (cmd[0]) {
			case 'l' :
				scanf("%s %s", inID1, inPW1);
				temp = all.login(inID1, inPW1);
				if (temp == -2) printf("wrong password\n");
				else if (temp == -1) printf("ID %s not found\n", inID1);
				else if (temp >= 0) {
					printf("success\n");
					curIndex = temp; 
				}
				break;
			case 'c' :
				scanf("%s %s", inID1, inPW1);
				now = all.translate(inID1[0]);
				exist = all.findTree(all.tree[now], inID1, 0, strlen(inID1)-1);
				if (exist >= 0) {
					printf("ID %s exists, ", inID1);
					all.adviseID(inID1);
				} else if (exist < 0) {
					all.allpeople++;
					all.create(inID1, inPW1);
					printf("success\n");
				}
				break;
			case 'd' :
				if (cmd[2] == 'l') {
					scanf("%s %s", inID1, inPW1);
					temp = all.login(inID1, inPW1);
					if (temp == -2) printf("wrong password\n");
					if (temp == -1) printf("ID %s not found\n", inID1);
					if (temp >= 0) {
						all.allpeople--;
						all.deletion(temp);
						printf("success\n");
					}
					break;
				} else if (cmd[2] == 'p') {
					scanf("%d", &inMoney);
					result = all.deposit(curIndex, inMoney);
					if (result.first) printf("success, %d dollars in current account\n", result.second);
					else printf("deposit fail\n");
					break;
				}
			case 'm' :
				scanf("%s %s", inID1, inPW1);
				scanf("%s %s", inID2, inPW2);
				index1 = all.login(inID1, inPW1);
				index2 = all.login(inID2, inPW2);
				if (index1 == -1) printf("ID %s not found\n", inID1);
				else if (index2 == -1) printf("ID %s not found\n", inID2);
				else if (index1 == -2) printf("wrong password1\n");
				else if (index2 == -2) printf("wrong password2\n");
				else if (index1 == index2) printf("success, %s have %d dollars\n", all.data[index1].id, all.data[index1].money);
				else if (index1 >= 0 && index2 >= 0) {
					result = all.merge(index1, index2);
					all.allpeople--;
					if (result.first) printf("success, %s has %d dollars\n",inID1, result.second);
					else printf("merge fail\n");
				}
				break;
			case 'w' :
				scanf("%d", &inMoney);
				result = all.withdraw(curIndex, inMoney);
				if (result.first) printf("success, %d dollars left in current account\n", result.second);
				else printf("fail, %d dollars only in current account\n", result.second);
				break;
			case 't' :
				scanf("%s %d", inID1, &inMoney);
				now = all.translate(inID1[0]);
				temp = all.findTree(all.tree[now], inID1, 0, strlen(inID1)-1);
				if (temp < 0) {
					printf("ID %s not found, ", inID1);
					all.violent_advise(inID1);
				} else {
					result = all.transfer(curIndex, temp, inMoney);
					if (result.first) printf("success, %d dollars left in current account\n", result.second);
					else printf("fail, %d dollars only in current account\n", result.second);
				}
				break;
			case 'f' :
				scanf("%s", order);
				first = all.translate(order[0]);
				second = all.translate(order[1]);
				all.found.clear();
				if (first >= 0) all.find2(all.tree[first], order, 0, strlen(order)-1);
				else if (first == -1) {
					all.find2(all.tree[second], order, 1, strlen(order)-1);
					for (next = 0 ; next < 62 ; next++) {
						all.find2(all.tree[next], order, 0, strlen(order)-1);
					}
				} else if (first == -2) {
					for (next = 0 ; next < 62 ; next++) {
						order[0] = all.antiTranslate(next);
						all.find2(all.tree[next], order, 0, strlen(order)-1);
					}
				}
				sort(all.found.begin(), all.found.end(), sCompare);
				f_size = all.found.size();
				if (f_size != 0) printf("%s", all.found[0]);
				for (i = 1 ; i < f_size ; i++) {
					if (strcmp(all.found[i-1], all.found[i]) != 0)printf(",%s", all.found[i]);
				}
				printf("\n");
				all.found.clear();
				break;
			case 's' :
				scanf("%s", inID1);
				all.search(inID1, curIndex);
				break;
			default: 
				if (strcmp(cmd, "account") == 0) all.status(1);
				if (strcmp(cmd, "history") == 0) all.status(2);
				if (strcmp(cmd, "help") == 0) all.status(3);
				if (strcmp(cmd, "help-find") == 0) all.status(4);
		}
		count++;
	}
	return 0;
}