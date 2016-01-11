#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string.h>
#include <cstdlib>
#include <math.h>
#include <vector>
#include "all.h"
bool fuck_compare(char *a,char *b){
	return (strcmp(a,b)<0);
}
int ALL::score(char *ID_1,char *ID_2)
{
	int length_diff = (strlen(ID_2)-strlen(ID_1));
	int slen = (length_diff > 0)? strlen(ID_1) : strlen(ID_2);
	length_diff = fabs(length_diff);
	int string_sum = 0;
	for (int i = 1 ; i <= slen ; i++) {
		if (ID_1[slen-i] != ID_2[slen-i]) string_sum += i; 
	}
	int length_sum=(length_diff*(length_diff+1))/2;
	return length_sum + string_sum;
}
int ALL::string_score(char *ID_1,char *ID_2)
{
	int string_score_diff=0;
	if(strlen(ID_1)<=strlen(ID_2)){
		for(int i=0;i<strlen(ID_1);i++){
			if(ID_1[ (strlen(ID_1)-i-1) ]!=ID_2[ (strlen(ID_1)-i-1) ]){
				//cout<<"ID_1: "<<ID_1[ (strlen(ID_1)-i-1) ]<<"ID_2: "<<ID_2[ (strlen(ID_1)-i-1) ]<<endl;
				string_score_diff+=i+1;
			}
		}
	}
	else{//strlen(ID_1)<=strlen(ID_2)
		for(int i=0;i<strlen(ID_2);i++){
			if(ID_1[ (strlen(ID_2)-i-1) ]!=ID_2[ (strlen(ID_2)-i-1) ]){
				string_score_diff+=i+1;
			}
		}
	}	
	
	return string_score_diff;
}
void ALL::print_function(vector<int>& record_array,char *advise_string,int flag){
	if(flag>=record_array.size()){return;}
	for(int i=0;i<=61;i++){
		advise_string[ record_array[flag] ]=antiTranslate(i);
		print_function(record_array,advise_string,flag+1);
		int now=translate(advise_string[0]);
		TREE *temp = findTree(tree[now],advise_string,0,strlen(advise_string)-1);
		if(temp == nullptr || temp->data.back().exist < 0 ){
			char *tmp=new char[101];
			strcpy(tmp,advise_string);
			TEN.push_back(tmp);
		}
	}
	return;
}
void ALL::order_function(const int string_length,const int& length_dis,const int ID_length,vector<int>& record_array,int string_score_remain,int flag){
	if(string_score_remain==0){
		char advise_string[101];
		strncpy(advise_string,save_used_ID,string_length);
		advise_string[string_length]='\0';
		//cout<<"advise_string="<<advise_string<<endl;
		int now=translate(advise_string[0]);
		if(record_array.size()==0){
			TREE *temp = findTree(tree[now],advise_string,0,strlen(advise_string)-1);
			if( (temp == nullptr || temp->data.back().exist < 0) && strcmp(advise_string," ")!=0){
				char *tmp = new char [101];
				strcpy(tmp, advise_string);
				TEN.push_back(tmp);
			}
		}
		print_function(record_array,advise_string,0);
		return;
	}
	//cout<<"string_length= "<<string_length<<"   "<<"flag= "<<flag<<endl;
	//cout<<"string_score_remain="<<string_score_remain<<endl;
	if(flag>=string_length){return;}
	//===============================
	if(string_score_remain>=(string_length-flag)){
		//cout<<"enter if and  "<<"string_length= "<<string_length<<"   "<<"flag= "<<flag<<endl;
		for(flag;flag<string_length;flag++){
			/*cout<<"string_score_remain="<<string_score_remain<<"   ";
			cout<<"flag= "<<flag<<endl;
			cout<<"string_length-flag="<<string_length-flag<<endl;*/
			record_array.push_back(flag);
			order_function(string_length,length_dis,ID_length,record_array,string_score_remain-(string_length-flag),flag+1);
			record_array.pop_back();
		}
	}
	else{
		//cout<<"enter else"<<endl;
		order_function(string_length,length_dis,ID_length,record_array,string_score_remain,flag+1);
	}
	//================================
	return;
}
void ALL::order_function_big(const int string_length,const int& length_dis,const int ID_length,vector<int>& record_array,int string_score_remain,int flag){
	if(string_score_remain==0){	
		char advise_string[101];
		//cout<<"string_length="<<string_length<<endl;
		strncpy(advise_string,save_used_ID,ID_length);
		advise_string[string_length]='\0';
		//cout<<"advise_string="<<advise_string<<endl;
		int i;
		for(i=ID_length;i<string_length;i++){
			//cout<<"flag="<<flag<<" "<<endl;
			record_array.push_back(i);
		}
		print_function(record_array,advise_string,0);
		for(i;i>ID_length;i--){record_array.pop_back();}
		return;
	}
	if(flag>=string_length){return;}
	//===============================
	if(string_score_remain>=(ID_length-flag)){
		for(flag;flag<ID_length;flag++){
			record_array.push_back(flag);
			order_function_big(string_length,length_dis,ID_length,record_array,string_score_remain-(ID_length-flag),flag+1);
			record_array.pop_back();
		}
	}
	else{
		order_function_big(string_length,length_dis,ID_length,record_array,string_score_remain,flag+1);
	}
	//================================
	
	return;	
}
void ALL::adviseID(char *used_ID){
	strcpy(save_used_ID,used_ID);
	int length_element;
	int string_element;
	int record_length=0;
	int string_score_remain;
	int count_to_ten=0;
	//vector<char*> top_ten;
	for(int SCORE=1;SCORE<=5050;SCORE++){
		//vector<char*> TEN;
		//inside this loop has the same SCORE
		//cout<<"score="<<SCORE<<endl;
		TEN.clear();
		for(int j=record_length ;(j*(j+1))/2<=SCORE;j++){
			record_length=j;//record records the longest length which can be from the used_ID
			//cout<<"record_length="<<record_length<<endl;
		}
		for(int j=record_length;j>=record_length*(-1);j--){//we have to seek account from the smallest length
		//j is the distance between strings
			vector<int> record_array;
			record_array.clear();
			if(j>=0){
				string_score_remain=SCORE-(j*(j+1))/2;//string_score_remain is the score which minus length
				//cout<<"string_score_remain="<<string_score_remain<<endl;
				if(strlen(used_ID)>j){
					//start to do string_score_remain
					order_function(strlen(used_ID)-j,j,strlen(used_ID),record_array,string_score_remain,0);}
			}
			else{
				string_score_remain=SCORE-(j*(-1)*(j*(-1)+1))/2;//string_score_remain is the score which minus length
				if(strlen(used_ID)-j<=100){
					order_function_big(strlen(used_ID)-j,(-1)*j,strlen(used_ID),record_array,string_score_remain,0);
				}
			}
		//cout<<record<<endl;
		}
		if(TEN.size()!=0){
			sort(TEN.begin(),TEN.end(),fuck_compare);
			for(int times=0;times<10&&times<TEN.size();times++){
				cout<<TEN[times];
				count_to_ten++;
				if(count_to_ten<10){cout<<",";}
				else{break;}
			}
		}
		if(count_to_ten>=10){break;}
	}
	cout<<endl;
	return;
}
/*void ALL::print_function(vector<int>& record_array,int& count_within_ten,char *advise_string,int flag){
	if(count_within_ten>=10){return;}
	if(flag>=record_array.size()){return;}
	for(int i=0;i<=61;i++){
		advise_string[ record_array[flag] ]=antiTranslate(i);
		print_function(record_array,count_within_ten,advise_string,flag+1);
		if(count_within_ten>=10){return;}
		int now=translate(advise_string[0]);
		if( findTree(tree[now],advise_string,0,strlen(advise_string)-1)<0 ){
			count_within_ten++;
			cout<<advise_string;
			if(count_within_ten<10){cout<<",";}
		}
		if(count_within_ten>=10){return;}
	}
	return;
}
void ALL::order_function(const int string_length,const int& length_dis,const int& SCORE,const int ID_length,vector<int>& record_array,int string_score_remain,int& count_within_ten,int flag){
	if(count_within_ten>=10){return;}
	if(string_score_remain==0){
		char advise_string[101];
		strncpy(advise_string,save_used_ID,string_length);
		advise_string[string_length]='\0';
		//cout<<"advise_string="<<advise_string<<endl;
		int now=translate(advise_string[0]);
		if(record_array.size()==0){
			if(findTree(tree[now],advise_string,0,strlen(advise_string)-1)<0&& strcmp(advise_string," ")!=0){
				cout<<advise_string;
				count_within_ten++;
				if(count_within_ten<10){cout<<",";}
			}
		}
		print_function(record_array,count_within_ten,advise_string,0);
		return;
	}
	//cout<<"string_length= "<<string_length<<"   "<<"flag= "<<flag<<endl;
	//cout<<"string_score_remain="<<string_score_remain<<endl;
	if(flag>=string_length){return;}
	//===============================
	if(string_score_remain>=(string_length-flag)){
		//cout<<"enter if and  "<<"string_length= "<<string_length<<"   "<<"flag= "<<flag<<endl;
		for(flag;flag<string_length;flag++){
			//cout<<"string_score_remain="<<string_score_remain<<"   ";
			//cout<<"flag= "<<flag<<endl;
			//cout<<"string_length-flag="<<string_length-flag<<endl;
			record_array.push_back(flag);
			order_function(string_length,length_dis,SCORE,ID_length,record_array,string_score_remain-(string_length-flag),count_within_ten,flag+1);
			record_array.pop_back();
		}
	}
	else{
		//cout<<"enter else"<<endl;
		order_function(string_length,length_dis,SCORE,ID_length,record_array,string_score_remain,count_within_ten,flag+1);
	}
	//================================
	return;
}
void ALL::order_function_big(const int string_length,const int& length_dis,const int& SCORE,const int ID_length,vector<int>& record_array,int string_score_remain,int& count_within_ten,int flag){
	if(count_within_ten>=10){return;}
	if(string_score_remain==0){	
		char advise_string[101];
		//cout<<"string_length="<<string_length<<endl;
		strncpy(advise_string,save_used_ID,ID_length);
		advise_string[string_length]='\0';
		//cout<<"advise_string="<<advise_string<<endl;
		int i;
		for(i=ID_length;i<string_length;i++){
			//cout<<"flag="<<flag<<" "<<endl;
			record_array.push_back(i);
		}
		print_function(record_array,count_within_ten,advise_string,0);
		for(i;i>ID_length;i--){record_array.pop_back();}
		return;
	}
	if(flag>=string_length){return;}
	//===============================
	if(string_score_remain>=(ID_length-flag)){
		for(flag;flag<ID_length;flag++){
			record_array.push_back(flag);
			order_function_big(string_length,length_dis,SCORE,ID_length,record_array,string_score_remain-(ID_length-flag),count_within_ten,flag+1);
			record_array.pop_back();
		}
	}
	else{
		order_function_big(string_length,length_dis,SCORE,ID_length,record_array,string_score_remain,count_within_ten,flag+1);
	}
	//================================
	
	return;	
}
void ALL::adviseID(char *used_ID){
	strcpy(save_used_ID,used_ID);
	int count_within_ten=0;
	int length_element;
	int string_element;
	int record_length=0;
	int string_score_remain;
	//vector<char*> top_ten;
	for(int SCORE=1;SCORE<=5050;SCORE++){
		//inside this loop has the same SCORE
		//cout<<"score="<<SCORE<<endl;
		for(int j=record_length ;(j*(j+1))/2<=SCORE;j++){
			record_length=j;//record records the longest length which can be from the used_ID
			//cout<<"record_length="<<record_length<<endl;
		}
		for(int j=record_length;j>=record_length*(-1);j--){//we have to seek account from the smallest length
		//j is the distance between strings
			vector<int> record_array;
			record_array.clear();
			if(j>=0){
				string_score_remain=SCORE-(j*(j+1))/2;//string_score_remain is the score which minus length
				//cout<<"string_score_remain="<<string_score_remain<<endl;
				if(strlen(used_ID)>j){
					//start to do string_score_remain
					order_function(strlen(used_ID)-j,j,SCORE,strlen(used_ID),record_array,string_score_remain,count_within_ten,0);}
			}
			else{
				string_score_remain=SCORE-(j*(-1)*(j*(-1)+1))/2;//string_score_remain is the score which minus length
				if(strlen(used_ID)-j<=100){
					order_function_big(strlen(used_ID)-j,(-1)*j,SCORE,strlen(used_ID),record_array,string_score_remain,count_within_ten,0);
				}
			}
		//cout<<record<<endl;
			if(count_within_ten>=10){break;}
		}
		if(count_within_ten>=10){break;}
		
	}
	cout<<endl;
	return;
}
void ALL::transfer_adviseID(char *used_ID){
	strcpy(save_used_ID,used_ID);
	int count_within_ten=0;
	int length_element;
	int string_element;
	int record_length=0;
	int string_score_remain;
	//vector<char*> top_ten;
	for(int SCORE=1;SCORE<=5050;SCORE++){
		//inside this loop has the same SCORE
		//cout<<"score="<<SCORE<<endl;
		for(int j=record_length ;(j*(j+1))/2<=SCORE;j++){
			record_length=j;//record records the longest length which can be from the used_ID
			//cout<<"record_length="<<record_length<<endl;
		}
		for(int j=record_length;j>=record_length*(-1);j--){//we have to seek account from the smallest length
		//j is the distance between strings
			vector<int> record_array;
			record_array.clear();
			if(j>=0){
				string_score_remain=SCORE-(j*(j+1))/2;//string_score_remain is the score which minus length
				//cout<<"string_score_remain="<<string_score_remain<<endl;
				if(strlen(used_ID)>j){
					//start to do string_score_remain
					transfer_order_function(strlen(used_ID)-j,j,SCORE,strlen(used_ID),record_array,string_score_remain,count_within_ten,0);}
			}
			else{
				string_score_remain=SCORE-(j*(-1)*(j*(-1)+1))/2;//string_score_remain is the score which minus length
				if(strlen(used_ID)-j<=100){
					transfer_order_function_big(strlen(used_ID)-j,(-1)*j,SCORE,strlen(used_ID),record_array,string_score_remain,count_within_ten,0);
				}
			}
		//cout<<record<<endl;
			if(count_within_ten>=10||count_within_ten>=allpeople){break;}
		}
		if(count_within_ten>=10||count_within_ten>=allpeople){break;}
		
	}
	cout<<endl;
	return;
}
void ALL::transfer_print_function(vector<int>& record_array,int& count_within_ten,char *advise_string,int flag){
	if(count_within_ten>=10||count_within_ten>=allpeople){return;}
	if(flag>=record_array.size()){return;}
	for(int i=0;i<=61;i++){
		advise_string[ record_array[flag] ]=antiTranslate(i);
		transfer_print_function(record_array,count_within_ten,advise_string,flag+1);
		if(count_within_ten>=10||count_within_ten>=allpeople){return;}
		int now=translate(advise_string[0]);
		if( findTree(tree[now],advise_string,0,strlen(advise_string)-1)>=0 ){
			count_within_ten++;
			cout<<advise_string;
			if(allpeople<10){
				if(count_within_ten<allpeople){
					cout<<",";}
			}
			else if(count_within_ten<10){cout<<",";}
		}
		if(count_within_ten>=10||count_within_ten>=allpeople){return;}
	}
	return;
}
void ALL::transfer_order_function(const int string_length,const int& length_dis,const int& SCORE,const int ID_length,vector<int>& record_array,int string_score_remain,int& count_within_ten,int flag){
	if(count_within_ten>=10){return;}
	if(string_score_remain==0){
		char advise_string[101];
		strncpy(advise_string,save_used_ID,string_length);
		advise_string[string_length]='\0';
		//cout<<"advise_string="<<advise_string<<endl;
		int now=translate(advise_string[0]);
		if(record_array.size()==0){
			if(findTree(tree[now],advise_string,0,strlen(advise_string)-1)>=0&& strcmp(advise_string," ")!=0){
				cout<<advise_string;
				count_within_ten++;
				if(allpeople<10){
					if(count_within_ten<allpeople){
						cout<<",";}
				}
				else if(count_within_ten<10){cout<<",";}
				
			}
		}
		transfer_print_function(record_array,count_within_ten,advise_string,0);
		return;
	}
	//cout<<"string_length= "<<string_length<<"   "<<"flag= "<<flag<<endl;
	//cout<<"string_score_remain="<<string_score_remain<<endl;
	if(flag>=string_length){return;}
	//===============================
	if(string_score_remain>=(string_length-flag)){
		//cout<<"enter if and  "<<"string_length= "<<string_length<<"   "<<"flag= "<<flag<<endl;
		for(flag;flag<string_length;flag++){
			//cout<<"string_score_remain="<<string_score_remain<<"   ";
			//cout<<"flag= "<<flag<<endl;
			//cout<<"string_length-flag="<<string_length-flag<<endl;
			record_array.push_back(flag);
			transfer_order_function(string_length,length_dis,SCORE,ID_length,record_array,string_score_remain-(string_length-flag),count_within_ten,flag+1);
			record_array.pop_back();
		}
	}
	else{
		//cout<<"enter else"<<endl;
		transfer_order_function(string_length,length_dis,SCORE,ID_length,record_array,string_score_remain,count_within_ten,flag+1);
	}
	//================================
	return;
}
void ALL::transfer_order_function_big(const int string_length,const int& length_dis,const int& SCORE,const int ID_length,vector<int>& record_array,int string_score_remain,int& count_within_ten,int flag){
	if(count_within_ten>=10){return;}
	if(string_score_remain==0){	
		char advise_string[101];
		//cout<<"string_length="<<string_length<<endl;
		strncpy(advise_string,save_used_ID,ID_length);
		advise_string[string_length]='\0';
		//cout<<"advise_string="<<advise_string<<endl;
		int i;
		for(i=ID_length;i<string_length;i++){
			//cout<<"flag="<<flag<<" "<<endl;
			record_array.push_back(i);
		}
		transfer_print_function(record_array,count_within_ten,advise_string,0);
		for(i;i>ID_length;i--){record_array.pop_back();}
		return;
	}
	if(flag>=string_length){return;}
	//===============================
	if(string_score_remain>=(ID_length-flag)){
		for(flag;flag<ID_length;flag++){
			record_array.push_back(flag);
			transfer_order_function_big(string_length,length_dis,SCORE,ID_length,record_array,string_score_remain-(ID_length-flag),count_within_ten,flag+1);
			record_array.pop_back();
		}
	}
	else{
		transfer_order_function_big(string_length,length_dis,SCORE,ID_length,record_array,string_score_remain,count_within_ten,flag+1);
	}
	//================================
	
	return;	
}*/
