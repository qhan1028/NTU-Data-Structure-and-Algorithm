#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include "all.h"
#include <map>
using namespace std;

bool sCompare(char *a, char *b) {return (strcmp(a, b) < 0);}

int main()
{
	ALL all;
	char cmd[20], cmd2[20], inID1[INMAX], inPW1[INMAX], inID2[INMAX], inPW2[INMAX], order[INMAX];
	long long int inMoney;
	int curIndex = -1, temp, now, exist, index, index1, index2, f_size, i, next, first, second;
	RESULT result;
	all.allpeople = 0;
	int count = 0;
	while (scanf("%s", cmd) != EOF) {
		inMoney = 0;
		switch (cmd[0]) {
			/*case 'z' :
				for(all.it_int=all.ID_map.begin();all.it_int!=all.ID_map.end();++all.it_int){
					cout<<all.it_int->first<<endl;
				}*/
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
				//cout<<"size="<<all.ID_map.size()<<endl;
				//now = all.translate(inID1[0]);
				/*if( all.ID_map.find(inID1)!=all.ID_map.end() ){
					cout<<"inID1="<<inID1<<endl;
					cout<<all.ID_map.find(inID1)->second<<endl;
					exist=1;
				}*/
				exist=all.findVector(inID1);
				//exist = all.findTree(all.tree[now], inID1, 0, strlen(inID1)-1);
				if (exist == 1) {
					printf("ID %s exists, ", inID1);
					all.adviseID(inID1);
				} else if (exist <= 0) {
					all.allpeople++;
					all.create(inID1, inPW1, exist);
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
					scanf("%lld", &inMoney);
					result = all.deposit(curIndex, inMoney);
					if (result.first) printf("success, %lld dollars in current account\n", result.second);
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
				else if (index1 == index2) printf("success, %s have %lld dollars\n", all.data[index1].id, all.data[index1].money);
				else if (index1 >= 0 && index2 >= 0) {
					result = all.merge(index1, index2);
					all.allpeople--;
					if (result.first) printf("success, %s has %lld dollars\n",inID1, result.second);
					else printf("merge fail\n");
				}
				break;
			case 'w' :
				scanf("%lld", &inMoney);
				result = all.withdraw(curIndex, inMoney);
				if (result.first) printf("success, %lld dollars left in current account\n", result.second);
				else printf("fail, %lld dollars only in current account\n", result.second);
				break;
			case 't' :
				scanf("%s %lld", inID1, &inMoney);
				//now = all.translate(inID1[0]);
				//temp = all.findTree(all.tree[now], inID1, 0, strlen(inID1)-1);
				if ( all.findVector(inID1)<=0 ) {
					printf("ID %s not found, ", inID1);
					all.violent_advise(inID1);
				} else {
					temp=all.findindex(inID1);
					result = all.transfer(curIndex, temp, inMoney);
					if (result.first) printf("success, %lld dollars left in current account\n", result.second);
					else printf("fail, %lld dollars only in current account\n", result.second);
				}
				break;
			case 'f' :
				scanf("%s", order);
				all.found.clear();
				all.find(order);
				f_size = all.found.size();
				sort(all.found.begin(), all.found.end(), sCompare);
				printf("%s", all.found[0]);
				for (i = 1 ; i < f_size ; i++) {
					if (strcmp(all.found[i], all.found[i-1]) != 0)printf(",%s", all.found[i]);
				}
				printf("\n");
				all.found.clear();
				break;
			case 's' :
				scanf("%s", inID1);
				all.search(inID1, curIndex);
				break;
			default: ;
		}
		count++;
	}
	return 0;
}
