#include <vector>
#include <utility>
#include <string>
#include "md5.h"
using namespace std;
#define INMAX 102
#define MONEYMAX 1000000000

typedef pair<bool, int> RESULT;

class DATA {
public:
	DATA(string newPW) {
		money = 0;
		exist = 1;
		pw = newPW;
	}
	string pw;
	int exist; // exist : -1(deleted, not found), 1(exist)
	int money;
	vector<int> record;
};

class TREE {
public:
	TREE() {
		exist = -1;
		for (int i = 0 ; i < 62 ; i++) tree[i] = nullptr;
	}
	vector<DATA> data;
	int exist; 		// exist : -1(deleted, not found), 1(exist)
	char id[INMAX]; 
	TREE *tree[62];
};

class HISTORY { 
public:
	HISTORY(int c) {
		from_exist = 1;
		to_exist = 1;
		trans_money = c;
	};
	~HISTORY(){trans_money = 0;}
	char from[INMAX];
	int from_exist;
	char to[INMAX];
	int to_exist;
	int trans_money;
};

class ALL {
public:
	ALL() {
		for (int i = 0 ; i < 62 ; i++) tree[i] = nullptr;
	}

	TREE *tree[62];
	vector<HISTORY> history;
	vector<char*> found;
	vector<pair<char*, int> > vf;
	int allpeople;

	TREE *login(char*, char*);
	void create(char*, char*);
	RESULT deposit(TREE*, int);
	RESULT withdraw(TREE*, int);
	RESULT transfer(TREE*, TREE*, int);
	RESULT merge(TREE*, TREE*);
	void find2(TREE*, char*, int, int);
	void search(TREE*, TREE*);					// search history
	void status(int);

	// 0~9 : 0~9
	// A~Z : 10~35
	// a~z : 36~61
	int translate(char word){
		if (word >= '0' && word <= '9') return word-'0';
		else if (word >= 'A' && word <= 'Z') return word-'A'+10;
		else if (word >= 'a' && word <= 'z') return word-'a'+36;
		else if (word == '*') return -1;
		else if (word == '?') return -2;
		else return -3;
	};
	char antiTranslate(int input) {
		if (input >= 0 && input <= 9) return '0'+input;
		else if (input >= 10 && input <= 35) return 'A'+input-10;
		else return 'a'+input-36;
	};

	int score(char*,char*);
	int string_score(char*,char*);
	void order_function(const int,const int&,const int,vector<int>&,int,int);
	void order_function_big(const int,const int&,const int,vector<int>&,int,int);
	void print_function(vector<int>&,char*,int);
	char save_used_ID[100];
	void adviseID(char *);
	vector<char*> TEN;

	TREE *findTree(TREE*, char*, int, int);
	void deleteTree(TREE*, char*, int, int);
	void addTree(TREE*, char*, int, int, string);

	void violent_advise(char*);
	void tree_traverse(TREE*, char*);
};
