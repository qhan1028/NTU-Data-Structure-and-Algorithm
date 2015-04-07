#include <iostream> //cin cout
#include <cstdio> //printf scanf fscanf FILE
#include <cstdlib> //qsort
#include <ctime>
#include <vector> //vector
#include <string> //string compare
using namespace std;
#define USER_MAX 25000000
#define AD_MAX 25000000
#define URL_MAX 30

#define TEST7
#define READ
#define INIT

// Read OK
// Get OK
// Profit OK

class DATA_USER { //user branch
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

class DATA_AD { //ad branch
public:
	vector<int> Click;
	vector<int> Impression;
	vector<int> User;
};

class DATA { //root of all data
public:
	DATA();
	~DATA();

	void Read();

	void Get(int&, int&, int&, int&, int&);
	void Clicked(int&);
	void Impressed(int&, int&);
	void Profit(int&, double&);
	void Quit();

	DATA_USER *USER;
	DATA_AD *AD;
	int max_usr;
	int max_ad;
};

DATA::DATA()
{
	USER = new DATA_USER[USER_MAX];
	AD = new DATA_AD[AD_MAX];
#ifdef INIT
	printf("initialization success\t%fsecs\n", (double)clock()/CLOCKS_PER_SEC);
#endif
}

DATA::~DATA()
{
	delete [] USER;
	delete [] AD;
}

void DATA::Read()
{
	//char file[1000];
	//scanf("%s", file);
	FILE *ptr = fopen("/tmp2/KDDCup2012/track2/kddcup2012track2.txt", "r");
	int click, imp, ad, adv, depth, pos, query, key, title, des, usr, count = 0;
	char url[URL_MAX];
	max_usr = max_ad = 0;
#ifdef READ
	printf("file open success\t%fsecs\n", (double)clock()/CLOCKS_PER_SEC);
#endif
	while (!feof(ptr)) {
		fscanf(ptr, "%d%d%s%d%d%d%d%d%d%d%d%d",&click, &imp, &url, &ad, &adv, &depth, &pos, &query, &key, &title, &des, &usr);
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
		AD[ad].User.push_back(usr);
		if (usr > max_usr) max_usr = usr;
		if (ad > max_ad) max_ad = ad;	
#ifdef TEST7
		count++;
		if (count == 1000000) break;
#endif
	}
#ifdef READ
	printf("read success\t%fsecs\n",(double)clock()/CLOCKS_PER_SEC);
	printf("biggest usr = %d\n", max_usr);
	printf("biggest ad = %d\n", max_ad);
#endif
	fclose(ptr);
}

void DATA::Get(int& user, int& ad, int& query, int& pos, int& depth)
{
	int sum_click = 0, sum_impression = 0;
	for (int i = 0 ; i < USER[user].Ad.size() ; i++) {
		if (USER[user].Ad[i] == ad &&
			USER[user].Query[i] == query &&
			USER[user].Position[i] == pos &&
			USER[user].Depth[i] == depth) {
			sum_click += USER[user].Click[i];
			sum_impression += USER[user].Impression[i];
		}
	}
	printf("********************\n");
	printf("%d %d\n", sum_click, sum_impression);
	printf("********************\n");
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
	int outputSize = j;
	qsort(output, outputSize, sizeof(Ck_output), compare1);
	printf("********************\n");
	for (int i = 0 ; i < outputSize ; i++) {
		printf("%d %d\n", output[i].Ad, output[i].Query);
	}
	printf("********************\n");
	delete [] output;
}

typedef struct temp2 {
	int Ad;
	int usr;
	int usr_index;
} Imp_output;

int compare2(const void *a, const void *b)
{
	int ad1 = ((Imp_output*)a)->Ad;
	int ad2 = ((Imp_output*)b)->Ad;
	return ad1 - ad2;
}

void DATA::Impressed(int& user1, int& user2)
{

}
/*
void DATA::Impressed(int& user1, int& user2)
{
	int size1 = USER[user1].Click.size();
	int size2 = USER[user2].Click.size();
	Imp_output *temp_ad = new Imp_output[size1+size2];
	int tmp = 0;
	for (int i = 0 ; i < size1 ; i++) {
		for (int j = 0 ; j < size2 ; j++) {
			if (USER[user1].Ad[i] == USER[user2].Ad[j]) {
				temp_ad[tmp].Ad = USER[user1].Ad[i];
				temp_ad[tmp].usr = user1;
				temp_ad[tmp].usr_index = i;
				tmp++;
				temp_ad[tmp].Ad = USER[user2].Ad[j];
				temp_ad[tmp].usr = user2;
				temp_ad[tmp].usr_index = j;
				tmp++;
			}
		}
	}
	qsort(temp_ad, tmp, sizeof(Imp_output), compare2);
	printf("********************\n");
	printf("%d\n", temp_ad[0].Ad);
	for (int i = 0 ; i < tmp ; i++) {
		if (temp_ad[i].Ad != temp_ad[i-1].Ad && i > 0) {
			printf("%d\n", temp_ad[i].Ad);
		}
		cout << "\t" << USER[temp_ad[i].usr].URL[temp_ad[i].usr_index];
		cout << " " << USER[temp_ad[i].usr].Advertiser[temp_ad[i].usr_index];
		cout << " " << USER[temp_ad[i].usr].Keyword[temp_ad[i].usr_index];
		cout << " " << USER[temp_ad[i].usr].Title[temp_ad[i].usr_index];
		cout << " " << USER[temp_ad[i].usr].Description[temp_ad[i].usr_index] << endl;
	}
	printf("********************\n");
	delete [] temp_ad;
}
*/

typedef struct temp3 {
	int Click;
	int Impression;
} Pro_output;

void DATA::Profit(int& ad, double& std_ratio)
{
	int size = AD[ad].Click.size();
	Pro_output *temp_usr = new Pro_output[max_usr];
	for (int i = 0 ; i < size ; i++) {
		temp_usr[AD[ad].User[i]].Click += AD[ad].Click[i];
		temp_usr[AD[ad].User[i]].Impression += AD[ad].Impression[i];
	}
	double usr_ratio = 0;
	printf("********************\n");
	for (int i = 0 ; i < max_usr ; i++) {
		if (temp_usr[i].Click == 0 || temp_usr[i].Impression == 0) continue;
		usr_ratio = (double)temp_usr[i].Click/(double)temp_usr[i].Impression;
		if (usr_ratio >= std_ratio) cout << i << endl;
	}
	printf("********************\n");
	delete [] temp_usr;
}

void DATA::Quit(){ cout << "# leave the program" << endl;}

int main(void)
{
	DATA data;
	data.Read();
	string input;
	int ad, depth, pos, query, usr1, usr2;
	double ratio;
	cin >> input;
	while(input.compare("quit") != 0) {
		if (input.compare("get") == 0) {
			scanf("%d%d%d%d%d", &usr1, &ad, &query, &pos, &depth);
			data.Get(usr1, ad, query, pos, depth);
		}
		if (input.compare("clicked") == 0) {
			scanf("%d", &usr1);
			data.Clicked(usr1);
		}
		if (input.compare("impressed") == 0) {
			scanf("%d%d", &usr1, &usr2);
			data.Impressed(usr1, usr2);
		}
		if (input.compare("profit") == 0) {
			scanf("%d%lf", &ad, &ratio);
			data.Profit(ad, ratio);
		}
		cin >> input;
	}
	data.Quit();
	return 0;
}