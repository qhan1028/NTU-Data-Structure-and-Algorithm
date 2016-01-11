#include <vector>
#include <utility>
#include "md5.h"
#include <map>
using namespace std;
#define INMAX 110
#define MONEYMAX 1000000000

typedef pair<bool, long long int> RESULT;

class DATA {
public:
	DATA() {
		money = 0;
		exist = -1;
	}
	char id[INMAX];
	string pw;
	int exist;
	// exist : -1(deleted), 0(not found), 1(exist)
	long long int money;
	vector<int> record;
};

class TREE {
public:
	TREE() {
		index = exist = -1;
		for (int i = 0 ; i < 62 ; i++) tree[i] = nullptr;
	}
	int index;
	int exist; 
	// exist : -1(deleted), 0(not found), 1(exist)
	TREE *tree[62];
};

class HISTORY { 
public:
	HISTORY(int a, int b, long long int c) {
		from = a;
		from_exist = 1;
		to = b;
		to_exist = 1;
		trans_money = c;
	};
	~HISTORY(){from = to = trans_money = 0;}
	int from;
	int from_exist;
	int to;
	int to_exist;
	long long int trans_money;
};

class ALL {
public:
	/*ALL() {
		for (int i = 0 ; i < 62 ; i++) tree[i] = nullptr;
	}*/
	vector<DATA> data;
	//TREE *tree[62];
	vector<HISTORY> history;
	vector<char*> found;
	int allpeople;

	int login(char*, char*);
	void create(char*, char*, int);
	void deletion(int);
	RESULT deposit(int, long long int);
	RESULT withdraw(int, long long int);
	RESULT transfer(int, int, long long int);
	RESULT merge(int, int);
	void find(char*);
	void search(char*, int);					// search history
	void status(int);
	int findVector(char*);
	int findindex(char*);
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
	void order_function(const int,const int&,const int&,const int,vector<int>&,int,int);
	void order_function_big(const int,const int&,const int&,const int,vector<int>&,int,int);
	void print_function(vector<int>&,char*,int);
	char save_used_ID[100];
	void adviseID(char *);
	vector<char*> TEN;

	int findTree(TREE*, char*, int, int);
	void deleteTree(TREE*, char*, int, int);
	void addTree(TREE*, char*, int, int, int);

	void violent_advise(char*);
};
