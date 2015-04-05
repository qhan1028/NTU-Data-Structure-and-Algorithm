#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
using namespace std;
#define MAX 150000000
#define URL_MAX 30
#define PRINT 1
#define GET_RATIO 2

class DATA_USER {
public:
	vector<int> Click;
	vector<int> Impression;
	vector<string> URL;
	vector<int> Ad;
	vector<int> Advertiser;
	vector<int> Depth;
	vector<int> Position;
	vector<int> Query;
	vector<int> Keyword;
	vector<int> Title;
	vector<int> Description;
};

class DATA_AD {
public:
	vector<int> Click;
	vector<int> Impression;
	vector<string> URL;
	vector<int> Advertiser;
	vector<int> Depth;
	vector<int> Position;
	vector<int> Query;
	vector<int> Keyword;
	vector<int> Title;
	vector<int> Description;
	vector<int> User;
};

class DATA {
public:
	DATA();
	~DATA();

	void Read();

	double Get(int&, int&, int&, int&, int&, int);
	void Clicked(int&);
	void Impressed(int&, int&);
	void Profit(int&, int&);
	void Quit();

	DATA_USER *USER;
	DATA_AD *AD;
};

DATA::DATA()
{
	USER = new DATA_USER[MAX];
	AD = new DATA_AD[MAX];
}


DATA::~DATA()
{
	delete [] USER;
	delete [] AD;
}

void DATA::Read()
{
	FILE *ptr = fopen("/tmp2/KDDCup2012/track2/kddcup2012track2.txt", "r");
	int click, imp, ad, adv, depth, pos, query, key, title, des, usr;
	char url[URL_MAX];
	while (fscanf(ptr, "%d", &click) != EOF) {
		fscanf(ptr, "%d", &imp);
		fscanf(ptr, "%s", url);
		fscanf(ptr, "%d%d%d", &ad, &adv, &depth);
		fscanf(ptr, "%d%d%d", &pos, &query, &key);
		fscanf(ptr, "%d%d%d", &title, &des, &usr);

		string s_url(url);
		
		USER[usr].Click.push_back(click);
		USER[usr].Impression.push_back(imp);
		USER[usr].URL.push_back(s_url);
		USER[usr].Ad.push_back(ad);
		USER[usr].Advertiser.push_back(adv);
		USER[usr].Depth.push_back(depth);
		USER[usr].Position.push_back(pos);
		USER[usr].Query.push_back(query);
		USER[usr].Keyword.push_back(key);
		USER[usr].Title.push_back(title);
		USER[usr].Description.push_back(des);

		AD[ad].Click.push_back(click);
		AD[ad].Impression.push_back(imp);
		AD[ad].URL.push_back(s_url);
		AD[ad].Advertiser.push_back(adv);
		AD[ad].Depth.push_back(depth);
		AD[ad].Position.push_back(pos);
		AD[ad].Query.push_back(query);
		AD[ad].Keyword.push_back(key);
		AD[ad].Title.push_back(title);
		AD[ad].Description.push_back(des);
		AD[ad].User.push_back(usr);
	}
	fclose(ptr);
}

double DATA::Get(int& user, int& ad, int& query, int& pos, int& depth, int function)
{
	double sum_click = 0, sum_impression = 0;
	for (int i = 0 ; i < USER[user].Click.size() ; i++) {
		if (USER[user].Ad[i] == ad &&
			USER[user].Query[i] == query &&
			USER[user].Position[i] == pos &&
			USER[user].Depth[i] == depth) {
			sum_click += USER[user].Click[i];
			sum_impression += USER[user].Impression[i];
		}
	}
	switch (function) {
		case PRINT : 
		printf("********************\n");
		printf("%d %d\n", sum_click, sum_impression);
		printf("********************\n");
		break;
		case GET_RATIO :
		return (sum_click/sum_impression);
		default:;
	}
	return 0;
}

typedef struct temp1{
	int Ad;
	int Query;
} Ck_output;

int compare1(const void *a, const void *b)
{
	int ad1 = ((Ck_output*)a)->Ad;
	int ad2 = ((Ck_output*)b)->Ad;
	int query1 = ((Ck_output*)a)->Query;
	int query2 = ((Ck_output*)b)->Query;
	if ( ad1 > ad2 ) return 1;
	if ( ad1 < ad2 ) return -1;
	if ( ad1 == ad2 ) {
		if ( query1 > query2 ) return 1;
		if ( query1 < query2 ) return -1;
		if ( query1 == query2 ) return 0;
	}
}

void DATA::Clicked(int& user)
{
	int dataSize = USER[user].Click.size();
	int j = 0;
	Ck_output *output = new Ck_output[dataSize];
	for (int i = 0 ; i < dataSize ; i++) {
		if (USER[user].Click[i] >= 1) {
			output[j].Ad = USER[user].Ad[i];
			output[j].Query = USER[user].Query[i];
			j++;
		}
	}
	int size = j;
	qsort(output, size, sizeof(Ck_output), compare1);
	printf("********************\n");
	for (int i = 0 ; i < size ; i++) {
		printf("%d %d\n", output[i].Ad, output[i].Query);
	}
	printf("********************\n");
	delete [] output;
}

void DATA::Impressed(int& user1, int& user2)
{

}

void DATA::Profit(int& ad, int& ratio)
{

}

void DATA::Quit()
{
	cout << "# leave the program\n" << endl;
}

int main(void)
{
	DATA data;
	data.Read();

	return 0;
}