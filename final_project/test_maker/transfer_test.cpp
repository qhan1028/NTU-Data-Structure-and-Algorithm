#include<iostream>
#include<stdio.h>
#include<cstdio>
#include<stdlib.h>
#include<cstdlib>
#include<time.h>
using namespace std;

int main(){
	char c;
	for(int i=0;i<3;i++){
		c='a'+i;
		cout<<"create "<< c <<" fuck"<<endl;
		cout<<"login "<< c <<" fuck"<<endl;
		cout<<"deposit 10000000"<<endl;
	}
	char ID1,ID2;
	int money;
	srand(time(NULL));
	for(int i=0;i<100;i++){
		ID1='a'+rand()%3;
		ID2='a'+rand()%3;
		money=rand()%1000+1;
		cout<<"login "<< ID1<<" fuck"<<endl;
		cout<<"transfer "<<ID2<<" "<<money<<endl;
	}
	for(int i=1;i<3;i++){
		c='a'+i;
		cout<<"merge a fuck "<< c<<" fuck"<<endl;
	}
	cout<<"login a fuck\n";
	cout<<"search a\n";
	return 0;
}
