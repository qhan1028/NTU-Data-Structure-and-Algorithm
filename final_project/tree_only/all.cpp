#include <cstdio>
#include <cstring>
#include <algorithm>
#include <regex>
#include <vector>
#include "all.h"
#include "md5.h"

// return nullptr : node not exist or been deleted or merged
TREE *ALL::findTree(TREE *node, char *input, int n, int max) 
{
	int now = translate(input[n]);
	if (now < 0 || node == nullptr || n > max) return nullptr; 		
	else if (node != nullptr) {
		if (n == max && node->exist == 1) return node;
		else if (n < max) {
			int next = translate(input[n+1]);
			return findTree(node->tree[next], input, n+1, max);
		}
	} 
	return nullptr;
}

void ALL::deleteTree(TREE *node, char *del_id, int n, int max)
{
	if (node != nullptr && n == max) {
		node->data.back().exist = -1;
		node->data.back().money = -1;
	}
	else if (node != nullptr && n < max) {
		int next = translate(del_id[n+1]);
		deleteTree(node->tree[next], del_id, n+1, max);
	}
}

void ALL::addTree(TREE *node, char *newID, int n, int max, string pw) 
{
	int now = translate(newID[n]);
	if (n == max) {
		node->exist = 1;
		DATA newData(pw);
		node->data.push_back(newData);
		strcpy(node->id, newID);
	} else if (n < max) {
		int next = translate(newID[n+1]);
		if (node->tree[next] == nullptr) node->tree[next] = new TREE;
		addTree(node->tree[next], newID, n+1, max, pw);
	}
}

// return nullptr : been deleted or merged or wrong password
TREE *ALL::login(char *inID, char *inPW) 
{
	string s(inPW);
	string in_pw = md5(s);
	int now = translate(inID[0]);
	TREE *node = findTree(tree[now], inID, 0, strlen(inID)-1);
	if (node == nullptr || node->data.back().exist < 0) {
		printf("ID %s not found\n", inID);
		return nullptr;
	}
	else if (node->data.back().exist == 1){
		if (node->data.back().pw.compare(in_pw) == 0) return node;
		else {
			printf("wrong password\n");
			return nullptr;
		}
	}
	return nullptr;
} 

void ALL::create(char *newID, char *newPW)
{
	string s(newPW);
	string hash_s = md5(s);
	int now = translate(newID[0]);
	if (tree[now] == nullptr) tree[now] = new TREE;
	if (strlen(newID) > 1) 
		addTree(tree[now], newID, 0, strlen(newID)-1, hash_s);
	else {
		DATA newData(hash_s);
		tree[now]->exist = 1;
		tree[now]->data.push_back(newData);
		strcpy(tree[now]->id, newID);
	}
}

RESULT ALL::deposit(TREE *node, int inMoney)
{
	RESULT result;
	if (node->data.back().exist == 1) {
		node->data.back().money += inMoney;
		result.first = true;
		result.second = node->data.back().money;
	} else {
		result.first = false;
	}
	return result;
}

RESULT ALL::withdraw(TREE *node, int inMoney)
{
	RESULT result;
	if (node->data.back().exist == 1 && node->data.back().money >= inMoney) {
		node->data.back().money -= inMoney;
		result.first = true;
		result.second = node->data.back().money;
	} else if (node->data.back().exist == 1){
		result.first = false;
		result.second = node->data.back().money;
	} else {
		result.first = false;
	}
	return result;
}

RESULT ALL::transfer(TREE *from, TREE *to, int money)
{
	RESULT result;
	if (from->data.back().money >= money) { 						// transfer success
		from->data.back().money -= money;
		to->data.back().money += money;
		if (strcmp(from->id, to->id) != 0) {
			HISTORY new_his(money);
			strcpy(new_his.from, from->id);
			strcpy(new_his.to, to->id);
			from->data.back().record.push_back(history.size());		// add record
			to->data.back().record.push_back(history.size());		// add record
			history.push_back(new_his);	
		}
		result.first = true;
		result.second = from->data.back().money;
	} else if (from->data.back().money < money) {					// transfer fail
		result.first = false;
		result.second = from->data.back().money;
	}
	return result;
}

RESULT ALL::merge(TREE *in1, TREE *in2)
{
	in1->data.back().money += in2->data.back().money;
	in2->data.back().money = 0;
	int m_size = in2->data.back().record.size();
	char to[INMAX], from[INMAX], id1[INMAX], id2[INMAX];
	strcpy(id1, in1->id);
	strcpy(id2, in2->id);
	for (int i = 0 ; i < m_size ; i++) {
		int r_index = in2->data.back().record[i];
		strcpy(to, history[in2->data.back().record[i]].to);
		strcpy(from, history[in2->data.back().record[i]].from);
		if (strcmp(to, id1) != 0 && strcmp(from, id1) != 0) {
			in1->data.back().record.push_back(r_index);						// give record to in1
			if (strcmp(from, id2) == 0) {
				strcpy(history[in2->data.back().record[i]].from, id1);
			}
			if (strcmp(to, id2) == 0) {
				strcpy(history[in2->data.back().record[i]].to, id1);
			}
		} else {
			if (strcmp(from, id2) == 0) {								// in2 become inexist
				history[in2->data.back().record[i]].from_exist--;
				strcpy(history[in2->data.back().record[i]].from, id1);	
			}	
			if (strcmp(to, id2) == 0) {
				history[in2->data.back().record[i]].to_exist--;
				strcpy(history[in2->data.back().record[i]].to, id1);
			}
		}
	}
	in2->data.back().exist = -2;
	in2->data.back().record.clear();
	RESULT result;															// result
	result.first = true;
	result.second = in1->data.back().money;
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
			if (node->exist == 1 && node->data.back().exist == 1) 
				found.push_back(node->id);					// found
		} else if (now == -1) {
			if (node->exist == 1 && node->data.back().exist == 1) 
				found.push_back(node->id);					// found
			for (int i = 0 ; i < 62 ; i++) {
				find2(node->tree[i], input, in, inmax);		// next recursion
			}
		} else if (now == -2) {
			for (int i = 0 ; i < 62 ; i++) {
				if (node->tree[i] != nullptr && node->tree[i]->exist == 1
					&& node->tree[i]->data.back().exist == 1) 
					found.push_back(node->tree[i]->id);								// found
			}
		}
	} else return;
}

void ALL::search(TREE *s, TREE *cur)
{
	int r_size = cur->data.back().record.size();
	int have_record = 0;
	char from[INMAX], to[INMAX];
	sort(cur->data.back().record.begin(), cur->data.back().record.end());
	if (strcmp(s->id, cur->id) != 0) {
		for (int i = 0 ; i < r_size ; i++) {
			strcpy(from, history[cur->data.back().record[i]].from);
			strcpy(to, history[cur->data.back().record[i]].to);
			if (strcmp(from, s->id) == 0 && strcmp(to, cur->id) == 0) {
				have_record = 1;
				printf("From %s %d\n", from, history[cur->data.back().record[i]].trans_money);
			} else if (strcmp(from, cur->id) == 0 && strcmp(to, s->id) == 0) {
				have_record = 1;
				printf("To %s %d\n", to, history[cur->data.back().record[i]].trans_money);
			} 
		}
	} else if (strcmp(s->id, cur->id) == 0) {
		for (int i = 0 ; i < r_size ; i++) {
			strcpy(from, history[cur->data.back().record[i]].from);
			int from_exist = history[cur->data.back().record[i]].from_exist;
			strcpy(to, history[cur->data.back().record[i]].to);
			int to_exist = history[cur->data.back().record[i]].to_exist;
			int money = history[cur->data.back().record[i]].trans_money;
			if (strcmp(from, to) == 0) {
				have_record = 1;
				if (from_exist > to_exist) {
					printf("To %s %d\n", cur->id, money);
					printf("From %s %d\n", cur->id, money);
				} else {
					printf("From %s %d\n", cur->id, money);
					printf("To %s %d\n", cur->id, money);
				}
			}
		}
	}
	if(!have_record) printf("no record\n");
}

void ALL::tree_traverse(TREE *node, char *ne) 
{
	if (node == nullptr) return;
	if (node->exist == 1 && node->data.back().exist == 1) {
		int s = score(ne, node->id);
		pair<char*, int> temp;
		temp = make_pair(node->id, s);
		bool inserted = false;
		vector<pair<char*, int> >::iterator it = vf.begin();
		if (vf.size() == 0) vf.push_back(temp);
		else if (vf.size() < (unsigned int)10) {
			for (int j = 0 ; j < vf.size() ; j++) {
				if (vf[j].second > temp.second) {
					it += j;
					vf.insert(it, temp);
					inserted = true;
					break;
				} else if (vf[j].second == temp.second && 
					strcmp(vf[j].first, temp.first) > 0) {
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
						strcmp(vf[j].first, temp.first) > 0) {
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
	for (int i = 0 ; i < 62 ; i++) tree_traverse(node->tree[i], ne);
}

void ALL::violent_advise(char* ne)
{
	vf.clear();
	for (int i = 0 ; i < 62 ; i++) tree_traverse(tree[i], ne);
	if (vf.size() != 0) printf("%s", vf[0].first);
	for (int i = 1 ; i < vf.size() ; i++) printf(",%s", vf[i].first);
	printf("\n");
}