#include <iostream> //cin cout
#include <cstdio> //printf scanf fscanf FILE
#include <cstdlib> //qsort
#include <ctime>
#include <vector> //vector
#include <string> //string compare
using namespace std;
#define USER_MAX 50000000
#define AD_MAX 25000000
#define URL_MAX 30

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
};

DATA::DATA()
{
	USER = new DATA_USER[USER_MAX];
	cout << "success1\n";
	AD = new DATA_AD[AD_MAX];
	cout << "success2\n";
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
	int click, imp, ad, adv, depth, pos, query, key, title, des, usr;
	char url[URL_MAX];
	max_usr = 0;
	printf("success3\t\t%fsecs\n", (double)clock()/CLOCKS_PER_SEC);
	while (!feof(ptr)) {
		fscanf(ptr, "%d%d%s%d%d%d%d%d%d%d%d%d",&click, &imp, url, &ad, &adv, &depth, &pos, &query, &key, &title, &des, &usr);
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
	}
	printf("fucking success~~\t%fsecs\n",(double)clock()/CLOCKS_PER_SEC);
	fclose(ptr);
}

void DATA::Get(int& user, int& ad, int& query, int& pos, int& depth)
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
	int usr1;
	int usr2;
} Imp_output;

int compare2(const void *a, const void *b)
{
	int ad1 = ((Imp_output*)a)->Ad;
	int ad2 = ((Imp_output*)b)->Ad;
	return ad1 - ad2;
}

void DATA::Impressed(int& user1, int& user2)
{
	int size1 = USER[user1].Click.size();
	int size2 = USER[user2].Click.size();
	Imp_output *temp_ad = new Imp_output[(size1 >= size2)? size1 : size2];
	int tmp = 0;
	for (int i = 0 ; i < size1 ; i++) {
		for (int j = 0 ; j < size2 ; j++) {
			if (USER[user1].Ad[i] == USER[user2].Ad[j] &&
				USER[user1].Impression[i] != 0 ||
				USER[user2].Impression[j] != 0) {
				temp_ad[tmp].Ad = USER[user1].Ad[i];
				temp_ad[tmp].usr1 = (USER[user1].Impression[i] > 0)? i : -1;
				temp_ad[tmp].usr2 = (USER[user2].Impression[j] > 0)? j : -1;
				tmp++;
			}
		}
	}
	qsort(temp_ad, tmp, sizeof(Imp_output), compare2);
	printf("********************\n");
	for (int i = 0 ; i < tmp ; i++) {
		if (temp_ad[i].Ad != temp_ad[i-1].Ad && i >= 1)
			printf("%d\n",temp_ad[i].Ad);
		if (temp_ad[i].usr1) 
			cout << "\t" << USER[user1].URL[temp_ad[i].usr1];
			printf(" %d %d %d %d\n",
			USER[user1].Advertiser[temp_ad[i].usr1],
			USER[user1].Keyword[temp_ad[i].usr1],
			USER[user1].Title[temp_ad[i].usr1],
			USER[user1].Description[temp_ad[i].usr1]);
		if (temp_ad[i].usr2) 
			cout << "\t" << USER[user2].URL[temp_ad[i].usr2];
			printf(" %d %d %d %d\n",
			USER[user2].Advertiser[temp_ad[i].usr2],
			USER[user2].Keyword[temp_ad[i].usr2],
			USER[user2].Title[temp_ad[i].usr2],
			USER[user2].Description[temp_ad[i].usr2]);	
	}
	printf("********************\n");
	delete [] temp_ad;
}

typedef struct temp3 {
	int User;
	int Click;
	int Impression;
} Pro_output;

int compare3(const void *a, const void *b)
{
	int usr1 = ((Pro_output*)a)->User;
	int usr2 = ((Pro_output*)b)->User;
	return usr1 - usr2;
}

void DATA::Profit(int& ad, double& std_ratio)
{
	int size = AD[ad].Click.size();
	Pro_output *temp_usr = new Pro_output[max_usr];
	for (int i = 0 ; i < size ; i++) {
		temp_usr[AD[ad].User[i]].User = AD[ad].User[i];
		temp_usr[AD[ad].User[i]].Click += AD[ad].Click[i];
		temp_usr[AD[ad].User[i]].Impression += AD[ad].Impression[i];
	}
	qsort(temp_usr, max_usr, sizeof(Pro_output), compare3);
	printf("********************\n");
	for (int i = 0 ; i < max_usr ; i++) {
		if (temp_usr[i].Click == 0 || temp_usr[i].Click) continue;
		int usr_ratio = (double)temp_usr[i].Click/(double)temp_usr[i].Impression;
		if (usr_ratio >= std_ratio) printf("%d\n", temp_usr[i].User);
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