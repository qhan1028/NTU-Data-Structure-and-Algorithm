
/*
scanf("%s", order);
all.found.clear();
all.find(order);
f_size = all.found.size();
sort(all.found.begin(), all.found.end(), sCompare);
printf("%s", all.found[0]);
for (i = 1 ; i < f_size ; i++) printf(",%s", all.found[i]);
*/

void ALL::status(int f)
{
	if (f == 1) {
		for (int i = 0 ; i < data.size() ; i++) {
			if(data[i].exist == 1) printf("existed ");
			if(data[i].exist == -1) printf("deleted ");
			printf("id %s\t\t%lld dollars\t%lu records\n", data[i].id, data[i].money, data[i].record.size());
		}
	}
	if (f == 2) {
		printf("constructing...\n");
	}
	if (f == 3) {
		for (int i = 0 ; i < history.size() ; i++) {
			printf("%s to %s, %lld dollars\n", data[history[i].from].id, data[history[i].to].id, history[i].trans_money);
		}
	}
}

	void neFind(char*, vector<int>, int);
	void dividePoint(char*, vector<int>, int, int);
	void sFind(char*, int, int, int);
	void advise(char*);

#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include "all.h"
using namespace std;

char cfound[10][INMAX];
int fcount = 0;

bool sCompare2(char *a, char *b) {return (strcmp(a, b) < 0);}

void ALL::neFind(char *target, vector<int> divpos, int bound)
{
	if (divpos.size() == 0) {
		int now = translate(target[0]);
		if (findTree(tree[now], target, 0, strlen(target)-1) < 0) {
			char *temp = new char[INMAX];
			strcpy(temp, target);
			found.push_back(temp);
		}
	} else if (divpos.size() != 0) {
		int pos = bound-divpos.back();
		divpos.pop_back();
		for (int i = 0 ; i < 62 ; i++) {
			target[pos] = antiTranslate(i);
			neFind(target, divpos, bound);
		}
	}
}

void ALL::dividePoint(char *target, vector<int> divpos, int rest, int bound)
{
	if (rest > 0) {
		for (int i = 1 ; i <= rest ; i++) {
			if (!divpos.empty() && divpos.back() >= i) continue;
			divpos.push_back(i);
			dividePoint(target, divpos, rest-i, bound);
			divpos.pop_back();
		}
	} else if (rest == 0) {
		char temp[INMAX];
		strcpy(temp, target);
		neFind(temp, divpos, bound);
	} else return;
}

void ALL::sFind(char *e, int dL, int ws, int f)
{
	int len;
	char temp[INMAX];
	strcpy(temp, e);
	vector<int> divpos;
	if (f == 1 && len >= dL && dL > 0) {
		for (int i = 1 ; i <= dL ; i++) temp[len-i] = 0;
		if (ws == 0) neFind(temp, divpos, len-dL);
		else if (ws != 0) dividePoint(temp, divpos, ws, len-dL);
	} else if (f == 2 && ws > 0) dividePoint(e, divpos, ws, len);
	else if (f == 3 && dL > 0) {
		for (int i = 1 ; i <= dL ; i++) temp[len+i-1] = '?';
		if (ws == 0) neFind(temp, divpos, len);
		else if (ws != 0) dividePoint(temp, divpos, ws, len);
	}
}

void ALL::advise(char *ec)
{
	int score_sum, score_W, score_L, dL, fcount = 0;
	found.clear();
	for (int score_sum = 0 ; found.size() <= 10 ; score_sum++) {
		for (dL = 0, score_L = 0 ; (dL*dL+dL)/2 <= score_sum ; dL++) {
			score_L = (dL*dL+dL)/2;
			score_W = score_sum - score_L;
			for (int j = 1 ; j <= 3 ; j++) sFind(ec, dL, score_W, j);
		}
		sort(found.begin()+fcount, found.end(), sCompare2);
		if (found.size() >= (unsigned int)10) break;
		fcount = found.size();
	}
	printf("%s", found[0]);
	for (int i = 0 ; i < 10 ; i++) printf(",%s", found[i]);
	printf("\n"); 
}
	
void ALL::find(char order[])
{
	int dataSize = data.size();
	char *newOrder = new char[200];
	for (int i = 0, j = 0 ; i < strlen(order) ; i++) {
		if (translate(order[i]) >= 0 ) {
			newOrder[j] = order[i];
			j++;
		} else if (translate(order[i]) == -1) {
			newOrder[j] = '.';
			newOrder[j+1] = '*';
			j += 2;
		} else if (translate(order[i]) == -2) {
			newOrder[j] = '.';
			j++;
		}
	}
	string s_order(newOrder);
	for (int i = 0 ; i < dataSize ; i++) {
		string in(data[i].id);
		if (regex_match(in, regex(s_order)) && data[i].exist == 1) {
			found.push_back(data[i].id);
		}
	}
}