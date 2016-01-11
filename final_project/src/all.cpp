#include <cstdio>
#include <cstring>
#include <algorithm>
#include <regex>
#include <vector>
#include "all.h"
#include "md5.h"

// return -1 : id not found
// return -2 : id been deleted
int ALL::findTree(TREE *node, char *input, int n, int max) 
{
	int now = translate(input[n]);
	if (now < 0 || node == nullptr || n > max) return -1; 		
	else if (node != nullptr) {
		if (n == max) {
			return (node->exist == 1)? node->index : -1;
		} else if (n < max) {
			int next = translate(input[n+1]);
			return findTree(node->tree[next], input, n+1, max);
		}
	} 
	return -1;
}

// exist = -1
void ALL::deleteTree(TREE *node, char *del_id, int n, int max)
{
	if (node != nullptr && n == max) {
		node->exist = -1;
		node->index = -1;
	}
	else if (node != nullptr && n < max) {
		int next = translate(del_id[n+1]);
		deleteTree(node->tree[next], del_id, n+1, max);
	}
}

// exist = 1
void ALL::addTree(TREE *node, char *newID, int n, int max, int index) 
{
	int now = translate(newID[n]);
	if (n == max) {
		node->exist = 1;
		node->index = index;
	} else if (n < max) {
		int next = translate(newID[n+1]);
		if (node->tree[next] == nullptr) node->tree[next] = new TREE;
		addTree(node->tree[next], newID, n+1, max, index);
	}
}

// return -1 : no exist account
// return -2 : wrong password
int ALL::login(char *inID, char *inPW) 
{
	string s(inPW);
	string in_pw = md5(s);
	int now = translate(inID[0]);
	int index = findTree(tree[now], inID, 0, strlen(inID)-1);
	if (index < 0) return -1;
	else return (data[index].pw.compare(in_pw) == 0)? index : -2;
} 

void ALL::create(char *newID, char *newPW)
{
	int now = translate(newID[0]);
	if (now < 0) {
		printf("invalid id\n");
		return;
	} else {
		if (tree[now] == nullptr) tree[now] = new TREE;
		if (strlen(newID) > 1) 
			addTree(tree[now], newID, 0, strlen(newID)-1, data.size());
		else {
			tree[now]->index = data.size();
			tree[now]->exist = 1;
		}
	}

	DATA newData;
	string s(newPW);
	strcpy(newData.id, newID);
	newData.pw = md5(s);
	newData.money = 0;
	newData.exist = 1;
	data.push_back(newData);
}

void ALL::deletion(int del_index)
{
	int now = translate(data[del_index].id[0]);
	deleteTree(tree[now], data[del_index].id, 0, strlen(data[del_index].id)-1);
	data[del_index].money = 0;
	data[del_index].exist = -1;
}

RESULT ALL::deposit(int index, int inMoney)
{
	RESULT result;
	if (index >= 0) {
		data[index].money += inMoney;
		result.first = true;
		result.second = data[index].money;
	} else {
		result.first = false;
	}
	return result;
}

RESULT ALL::withdraw(int index, int inMoney)
{
	RESULT result;
	if (index >= 0 && data[index].money >= inMoney) {
		data[index].money -= inMoney;
		result.first = true;
		result.second = data[index].money;
	} else if (index >= 0){
		result.first = false;
		result.second = data[index].money;
	} else {
		result.first = false;
	}
	return result;
}

RESULT ALL::transfer(int from, int to, int money)
{
	RESULT result;
	if (data[from].money >= money) { 					// transfer success
		data[from].money -= money;
		data[to].money += money;
		if (from != to) {
			HISTORY new_his(from, to, money);
			data[from].record.push_back(history.size());	// add record
			data[to].record.push_back(history.size());		// add record
			history.push_back(new_his);						// new history
		}
		result.first = true;
		result.second = data[from].money;
	} else if (data[from].money < money) {				// transfer fail
		result.first = false;
		result.second = data[from].money;
	}
	return result;
}

RESULT ALL::merge(int in1, int in2)
{
	data[in1].money += data[in2].money;
	data[in2].money = 0;
	int m_size = data[in2].record.size();
	for (int i = 0 ; i < m_size ; i++) {
		if (history[data[in2].record[i]].to != in1 && 
			history[data[in2].record[i]].from != in1) {
			data[in1].record.push_back(data[in2].record[i]); 			// give record to in1
			if (history[data[in2].record[i]].from == in2)
				history[data[in2].record[i]].from = in1;
			if (history[data[in2].record[i]].to == in2)
				history[data[in2].record[i]].to = in1;
		} else {
			if (history[data[in2].record[i]].from == in2) {				// in2 become inexist
				history[data[in2].record[i]].from_exist--;	
				history[data[in2].record[i]].from = in1;	
			}	
			if (history[data[in2].record[i]].to == in2) {
				history[data[in2].record[i]].to_exist--;
				history[data[in2].record[i]].to = in1;
			}
		}
	}
	deletion(in2);
	data[in2].record.clear();
	RESULT result;														// result
	result.first = true;
	result.second = data[in1].money;
	return result;
}

void ALL::find2(TREE* node, char* input, int in, int inmax)
{
	if (node == nullptr) return;
	if (in < inmax) {
		int now = translate(input[in]);
		if (now >= 0) {
			int next = translate(input[in+1]);
			if (next >= 0) find2(node->tree[next], input, in+1, inmax);	// next recursion
			else if (next == -1 || next == -2) find2(node, input, in+1, inmax);
		} else if (now == -1) {
			int next = translate(input[in+1]);
			find2(node->tree[next], input, in+1, inmax);
			for (next = 0 ; next < 62 ; next++) {
				find2(node->tree[next], input, in, inmax);	// next recursion with *
			}
		} else if (now == -2) {
			for (int next = 0 ; next < 62 ; next++) {
				find2(node->tree[next], input, in+1, inmax);		// next recursion
			}
		} else return;
	} else if (in == inmax) {
		int now = translate(input[in]);
		if (now >= 0) {
			if (node->exist == 1) found.push_back(data[node->index].id);					// found
		} else if (now == -1) {
			if (node->exist == 1) found.push_back(data[node->index].id);					// found
			for (int i = 0 ; i < 62 ; i++) {
				find2(node->tree[i], input, in, inmax);		// next recursion
			}
		} else if (now == -2) {
			for (int i = 0 ; i < 62 ; i++) {
				if (node->tree[i] != nullptr && node->tree[i]->exist == 1) 
					found.push_back(data[node->tree[i]->index].id);								// found
			}
		}
	} else return;
}

void ALL::search(char *s, int curIndex)
{
	int rec_size = data[curIndex].record.size();
	int have_record = 0;
	sort(data[curIndex].record.begin(), data[curIndex].record.end());
	if (strcmp(s, data[curIndex].id) != 0) {
		for (int i = 0 ; i < rec_size ; i++) {
			int from = history[data[curIndex].record[i]].from;
			int to = history[data[curIndex].record[i]].to;
			int money = history[data[curIndex].record[i]].trans_money;
			if (strcmp(data[from].id, s) == 0 && to == curIndex) {
				have_record = 1;
				printf("From %s %d\n", data[from].id, money);
			} else if (from == curIndex && strcmp(data[to].id, s) == 0) {
				have_record = 1;
				printf("To %s %d\n", data[to].id, money);
			} 
		}
	} else if (strcmp(s, data[curIndex].id) == 0) {
		for (int i = 0 ; i < rec_size ; i++) {
			int from = history[data[curIndex].record[i]].from;
			int from_exist = history[data[curIndex].record[i]].from_exist;
			int to = history[data[curIndex].record[i]].to;
			int to_exist = history[data[curIndex].record[i]].to_exist;
			int money = history[data[curIndex].record[i]].trans_money;
			if (from == to) {
				have_record = 1;
				if (from_exist > to_exist) {
					printf("To %s %d\n", data[curIndex].id, money);
					printf("From %s %d\n", data[curIndex].id, money);
				} else {
					printf("From %s %d\n", data[curIndex].id, money);
					printf("To %s %d\n", data[curIndex].id, money);
				}
			}
		}
	}
	if(!have_record) printf("no record\n");
}

void ALL::violent_advise(char* ne)
{
	vector<pair<int, int> > vf;				// index, score
	pair<int, int> temp;
	for (int i = 0 ; i < data.size() ; i++) {
		if (data[i].exist != 1) continue;
		int s = score(ne, data[i].id);
		vector<pair<int, int> >::iterator it = vf.begin();
		temp = make_pair(i, s);
		bool inserted = false;

		if (vf.size() == 0) vf.push_back(temp);
		else if (vf.size() < (unsigned int)10) {
			for (int j = 0 ; j < vf.size() ; j++) {
				if (vf[j].second > temp.second) {
					it += j;
					vf.insert(it, temp);
					inserted = true;
					break;
				} else if (vf[j].second == temp.second && 
					strcmp(data[vf[j].first].id, data[temp.first].id) > 0) {
					it += j;
					vf.insert(it, temp);
					inserted = true;
					break;
				}
			}
			if (!inserted) vf.push_back(temp);
		} else {
			if (temp.second <= vf[9].second) {
				for (int j = 0 ; j < 10 ; j++) {
					if (vf[j].second > temp.second) {
						it += j;
						vf.insert(it, temp);
						inserted = true;
						break;
					} else if (vf[j].second == temp.second && 
						strcmp(data[vf[j].first].id, data[temp.first].id) > 0) {
						it += j;
						vf.insert(it, temp);
						inserted = true;
						break;
					}
				}
				if (inserted) vf.pop_back();
			}
		}
	}
	if (vf.size() != 0) printf("%s", data[vf[0].first].id);
	for (int i = 1 ; i < vf.size() ; i++) printf(",%s", data[vf[i].first].id);
	printf("\n");
}

void ALL::status(int f)
{
	if (f == 1) {
		for (int i = 0 ; i < data.size() ; i++) {
			printf("%d\t", i);
			if(data[i].exist == 1) printf("existed ");
			if(data[i].exist == -1) printf("deleted ");
			printf("id %s\t\t%d dollars\t%lu records\n", data[i].id, data[i].money, data[i].record.size());
		}
		printf("exist %d accounts\n", allpeople);
	}
	if (f == 2) {
		for (int i = 0 ; i < history.size() ; i++) {
			printf("%d\t%s to %s, %d dollars\n", i, data[history[i].from].id, data[history[i].to].id, history[i].trans_money);
		}
		printf("exist %lu histories\n", history.size());
	}
	if (f == 3) {
		printf("\tlogin [id] [pw]\t\t\tlogin id\n");
		printf("\tcreate [id] [pw]\t\tcreate new id\n");
		printf("\tdelete [id] [pw]\t\tdelete exist id\n");
		printf("\tdeposit [money]\t\t\tdeposit money into current account\n");
		printf("\twithdraw [money]\t\twithdraw money from current account\n");
		printf("\ttransfer [id] [money]\t\ttransfer money to id from current account\n");
		printf("\tmerge [id1] [pw1] [id2] [pw2]\tmerge id2 to id1\n");
		printf("\tfind [id]\t\t\ttype \"help-find\" to learn more about find\n");
		printf("\tsearch [id]\t\t\tsearch the transfer history between current account and id\n");
		printf("\taccount\t\t\t\tlist all exist, been deleted, been merged accounts\n");
		printf("\thistory\t\t\t\tlist all transfer history by timeline\n");
	}
	if (f == 4) {
		printf("\t* means there exist 0 or more characters\n");
		printf("\t? means there exist 1 character\n");
		printf("\tex : find a*b?c\n");
		printf("\tabec, a2egrb5c, abbcc, aabb1c... are all possible results\n");
	}
}