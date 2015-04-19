#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#define MAX 30000000
using namespace std;

class AD{
public:
	vector<int> click;
	vector<int> impression;
	vector<string> displayurl;
	vector<int> adid;
	vector<int> advertiserid;
	vector<int> keywordid;
	vector<int> titleid;
	vector<int> descriptionid;
	vector<int> userid;

};
class USERSER{
public:
	vector<int> click;
	vector<int> impression;
	vector<int> queryid;
	vector<int> adid;
	vector<int> depth;
	vector<int> position;
};
class DATA{
public:
	DATA();
	~DATA();
	USERSER *userser;
	AD *ad;
	void Get(int,int,int,int,int);
	void Clicked(int);
	void Profit(int,double);
	void Impress(int,int);
};
DATA::DATA(){
	userser = new USERSER[MAX];
	ad = new AD[MAX];
}
DATA::~DATA(){
	delete [] userser;
	delete [] ad;
}
void DATA::Get(int u,int a,int q,int p,int d){
	int sum_click = 0 , sum_impression = 0;
	for(int i = 0 ; i < userser[u].click.size() ; i++){
		if((userser[u].adid[i] == a )&&(userser[u].queryid[i] == q)&&(userser[u].position[i] == p )&&(userser[u].depth[i] == d)){
			sum_click += userser[u].click[i];
			sum_impression += userser[u].impression[i];
		}
	}
	printf("*********************\n%d %d\n*********************\n",sum_click,sum_impression);
}
class output{
public:
	int ad;
	int qu;
};
int cmp(const void *a,const void*b){
	int ad1 = ((output*)a) -> ad;
	int ad2 = ((output*)b) -> ad;
	if(ad1 > ad2) return 1 ;
	else if(ad1 < ad2) return -2;
	else{
		int qu1 = ((output*)a) -> qu;
		int qu2 = ((output*)b) -> qu;
		if(qu1 > qu2) return 1 ;
		else if(qu1 < qu2) return -2;
		else return 0 ;
	}
}
void DATA::Clicked(int u){
	int tmp = 0;
	output *click_output = new output[userser[u].click.size()];
	for(int i = 0 ; i < userser[u].click.size(); i++){
		if(userser[u].click[i] >= 1){
			click_output[tmp].ad = userser[u].adid[i];
			click_output[tmp].qu = userser[u].queryid[i];
			tmp++;
		}
	}
	qsort(click_output,tmp,sizeof(output),cmp);
	printf("********************\n");
	printf("%d %d\n",click_output[0].ad,click_output[0].qu);
	for(int j = 1 ; j < tmp ; j++){
		if((click_output[j].ad == click_output[j-1].ad) && (click_output[j].qu == click_output[j-1].qu))
			continue;
		else 
			printf("%d %d\n",click_output[j].ad,click_output[j].qu);
	}
	printf("********************\n");
	delete [] click_output;
}

class profit_output{
public:
	int sum_click;
	int sum_impression;
};

void DATA::Profit(int a,double theta){
	profit_output *output = new profit_output[24000000]; 
	for(int i = 0; i < ad[a].click.size(); i++){
		output[ ad[a].userid[i] ].sum_click += ad[a].click[i];
		output[ ad[a].userid[i] ].sum_impression += ad[a].impression[i];
	}
	printf("********************\n");
	for(int i = 0; i < 24000000; i++){
		if(output[i].sum_impression == 0 ){
			continue;	
		}
		else if(((double)output[i].sum_click / (double)output[i].sum_impression) >= theta)
			printf("%d\n",i);
	}
	printf("********************\n");
	delete [] output;
}
class impress_output{
public:
	string url_output;
	int advertiserid_output;
	int keywordid_output;
	int titleid_output;
	int descriptionid_output;
};
int cmp2(const void*a ,const void *b){
	int adv1 = ((impress_output*)a) -> advertiserid_output;
	int adv2 = ((impress_output*)b) -> advertiserid_output;

	int key1 = ((impress_output*)a) -> keywordid_output;
	int key2 = ((impress_output*)b) -> keywordid_output;

	int tit1 = ((impress_output*)a) -> titleid_output;
	int tit2 = ((impress_output*)b) -> titleid_output;

	int des1 = ((impress_output*)a) -> descriptionid_output;
	int des2 = ((impress_output*)b) -> descriptionid_output;

	string url1 = ((impress_output*)a) -> url_output;
	string url2 = ((impress_output*)b) -> url_output;

	return (url1.compare(url2) == 0)? (adv1 == adv2)? (key1 == key2)? (tit1 == tit2)? (des1 == des2)? 0:(des1 - des2):(tit1 - tit2): (key1 - key2):(adv1 - adv2):(url1.compare(url2));
}
void DATA::Impress(int use1,int use2){
	printf("********************\n");
	for(int i = 0 ; i <  23000000 ; i++ ){
		vector <int> tmp; 
		int found1 = 0,found2 = 0;
		for(int j = 0 ; j < ad[i].userid.size() ; j++){
    		if(ad[i].userid[j] == use1){
    			tmp.push_back(j);
    			found1 = 1;
    		}
    		if(ad[i].userid[j] == use2){
    			tmp.push_back(j);
    			found2 = 1;
    		}
		}
		if(found1 && found2 ){
			impress_output *output = new impress_output[ad[i].userid.size()];
			for(int k = 0 ; k < tmp.size(); k++){
				output[k].advertiserid_output = ad[i].advertiserid[k];
	 			output[k].keywordid_output = ad[i].keywordid[k];
	 			output[k].titleid_output = ad[i].titleid[k];
	 			output[k].descriptionid_output = ad[i].descriptionid[k];
	 			output[k].url_output = ad[i].displayurl[k];
			}
			qsort(output,tmp.size(),sizeof(impress_output),cmp2);
			printf("%d\n", i);
			cout << "\t" << output[0].url_output;
			printf(" %d %d %d %d\n", output[0].advertiserid_output,output[0].keywordid_output,output[0].titleid_output,output[0].descriptionid_output);
			for(int l = 1 ; l < tmp.size() ; l++){
				if(!(output[l].advertiserid_output == output[l-1].advertiserid_output && 
					output[l].keywordid_output == output[l-1].keywordid_output &&
					output[l].titleid_output == output[l-1].titleid_output &&  
					output[l].descriptionid_output == output[l-1].descriptionid_output &&
					output[l].url_output.compare(output[l-1].url_output)==0 )) {
					cout << "\t" << output[l].url_output;
					printf(" %d %d %d %d\n", output[l].advertiserid_output,output[l].keywordid_output,output[l].titleid_output,output[l].descriptionid_output);
				}
			}
		}
	}
	printf("********************\n");
}
int main(int argc , char const * argv[] ){
	DATA data;
	int Click;
	int Impression;
	char DisplayURL[25];
	int AdID;
	int AdvertiserID;
	int Depth;
	int Position;
	int QueryID;
	int KeywordID;
	int TitleID;
	int DescriptionID;
	int UserID;
	int u,a,q,p,d;
	char command[10];
	double theta;
	int use1,use2;
	FILE *brptr;
	brptr = fopen(argv[1],"r");
	while(1){
		fscanf(brptr,"%d",&Click);
		fscanf(brptr,"%d",&Impression);
		fscanf(brptr,"%s",&DisplayURL);
		fscanf(brptr,"%d",&AdID);
		fscanf(brptr,"%d",&AdvertiserID);
		fscanf(brptr,"%d",&Depth);
		fscanf(brptr,"%d",&Position);
		fscanf(brptr,"%d",&QueryID);
		fscanf(brptr,"%d",&KeywordID);
		fscanf(brptr,"%d",&TitleID);
		fscanf(brptr,"%d",&DescriptionID);
		fscanf(brptr,"%d",&UserID);
		if(feof(brptr)) break;
		string DisplayURLhaha(DisplayURL);
		data.userser[UserID].click.push_back(Click);
		data.userser[UserID].impression.push_back(Impression);
		data.userser[UserID].adid.push_back(AdID);
		data.userser[UserID].depth.push_back(Depth);
		data.userser[UserID].position.push_back(Position);
		data.userser[UserID].queryid.push_back(QueryID);
		data.ad[AdID].click.push_back(Click);
		data.ad[AdID].impression.push_back(Impression);
		data.ad[AdID].displayurl.push_back(DisplayURLhaha);
		data.ad[AdID].adid.push_back(AdID);
		data.ad[AdID].advertiserid.push_back(AdvertiserID);
		data.ad[AdID].keywordid.push_back(KeywordID);
		data.ad[AdID].titleid.push_back(TitleID);
		data.ad[AdID].descriptionid.push_back(DescriptionID);
		data.ad[AdID].userid.push_back(UserID);
	}
	cin >> command;
	while(strcmp(command,"quit") != 0){
		if(strcmp(command,"get") == 0){
			scanf("%d",&u);
			scanf("%d",&a);
			scanf("%d",&q);
			scanf("%d",&p);
			scanf("%d",&d);
			data.Get(u,a,q,p,d);
		}
		else if(strcmp(command,"clicked") == 0){
			scanf("%d",&u);
			data.Clicked(u);
		}
		else if(strcmp(command,"profit") == 0){
			scanf("%d",&u);
			scanf("%lf",&theta);
			data.Profit(u,theta);
		}
		else if(strcmp(command,"impressed" )== 0){
			scanf("%d",&use1);
			scanf("%d",&use2);
			data.Impress(use1,use2);
		}	
	cin >> command;
	}
	cout << "# leave the program\n";
	return 0;
}
