#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
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
	int inMoney, now, now1, now2, exist, index, f_size, i, next, first, second;
	RESULT result;
	TREE *cur, *temp, *index1, *index2;
	string spw1, spw2, pw1, pw2;
	all.allpeople = 0;

	while (scanf("%s", cmd) != EOF) {
		inMoney = 0;
		switch (cmd[0]) {
			case 'l' :
				scanf("%s %s", inID1, inPW1);
				temp = all.login(inID1, inPW1);
				if (temp != nullptr) {
					printf("success\n");
					cur = temp; 
				}
				break;
			case 'c' :
				scanf("%s %s", inID1, inPW1);
				now = all.translate(inID1[0]);
				temp = all.findTree(all.tree[now], inID1, 0, strlen(inID1)-1);
				if (temp == nullptr || temp->data.back().exist < 0) {
					all.allpeople++;
					all.create(inID1, inPW1);
					printf("success\n");
				} else if (temp->data.back().exist == 1) {
					printf("ID %s exists, ", inID1);
					all.adviseID(inID1);
				}
				break;
			case 'd' :
				if (cmd[2] == 'l') {
					scanf("%s %s", inID1, inPW1);
					temp = all.login(inID1, inPW1);
					if (temp != nullptr) {
						all.allpeople--;
						int now = all.translate(inID1[0]);
						all.deleteTree(all.tree[now], inID1, 0, strlen(inID1)-1);
						printf("success\n");
					}
					break;
				} else if (cmd[2] == 'p') {
					scanf("%d", &inMoney);
					result = all.deposit(cur, inMoney);
					if (result.first) printf("success, %d dollars in current account\n", result.second);
					else printf("deposit fail\n");
					break;
				}
			case 'm' :
				scanf("%s %s", inID1, inPW1);
				scanf("%s %s", inID2, inPW2);
				now1 = all.translate(inID1[0]);
				now2 = all.translate(inID2[0]);
				index1 = all.findTree(all.tree[now1], inID1, 0, strlen(inID1)-1);
				index2 = all.findTree(all.tree[now2], inID2, 0, strlen(inID2)-1);
				pw1.assign(inPW1);
				pw2.assign(inPW2);
				spw1 = md5(pw1);
				spw2 = md5(pw2);
				if (index1 == nullptr || index1->data.back().exist < 0) printf("ID %s not found\n", inID1);
				else if (index2 == nullptr || index2->data.back().exist < 0) printf("ID %s not found\n", inID2);
				else if (spw1.compare(index1->data.back().pw) != 0) printf("wrong password1\n");
				else if (spw2.compare(index2->data.back().pw) != 0) printf("wrong password2\n");
				else {
					result = all.merge(index1, index2);
					all.allpeople--;
					if (result.first) printf("success, %s has %d dollars\n",inID1, result.second);
					else printf("merge fail\n");
				}
				break;
			case 'w' :
				scanf("%d", &inMoney);
				result = all.withdraw(cur, inMoney);
				if (result.first) printf("success, %d dollars left in current account\n", result.second);
				else printf("fail, %d dollars only in current account\n", result.second);
				break;
			case 't' :
				scanf("%s %d", inID1, &inMoney);
				now = all.translate(inID1[0]);
				temp = all.findTree(all.tree[now], inID1, 0, strlen(inID1)-1);
				if (temp == nullptr || temp->data.back().exist < 0) {
					printf("ID %s not found, ", inID1);
					all.violent_advise(inID1);
				} else {
					result = all.transfer(cur, temp, inMoney);
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
				now = all.translate(inID1[0]);
				temp = all.findTree(all.tree[now], inID1, 0, strlen(inID1)-1);
				if (temp != nullptr) all.search(temp, cur);
				else printf("no record\n");
				break;
			default: ;
		}
	}
	return 0;
}