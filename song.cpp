#include <iostream>
#include <cstdio>
using namespace std;
int min(int a ,int b){
	return (a < b)? a:b;
} 
int max(int a ,int b){
	return (a > b)? a:b;
} 
void swap(int* a ,int* b){
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
void GCD_BY_REVERSE_SEARCH(int a , int b){
	int count = 0;
	for(int i = min(a,b);i >= 1; i -- ){
		count ++;
		if((a % i == 0) && (b % i == 0)){
		 printf("Case (%d, %d): GCD-By-Reverse-Search = %d, taking %d iterations\n",a,b,i,count); 
		 return;
		}
	
	}

}
int GCD_BY_FILTER(int a , int b){
	int count = 0;
	for(int i = 2;i <= min(a,b); i ++){
		count ++;
		if((a % i == 0) && (b % i == 0)){
			return i * GCD_BY_FILTER(a/i, b/i);
		}
	
	}
	return 1 ;

}
int GCD_BY_FILTER_count(int a , int b){
	int count = 0;
	for(int i = 2;i <= min(a,b); i ++){
		count ++;
		if((a % i == 0) && (b % i == 0)){
			return count + GCD_BY_FILTER_count(a/i, b/i);
		}
	
	}
	return count ;

}
int GCD_BY_FILTER_FASTER(int a , int b , int s){
	int count = 0;
	for(int i = s;i <= min(a,b); i ++){
		count ++;
		if((a % i == 0) && (b % i == 0)){
			return i * GCD_BY_FILTER_FASTER(a/i, b/i, i);
		}
	
	}
	return 1 ;

}
int GCD_BY_FILTER_FASTER_count(int a , int b , int s){
	int count = 0;
	for(int i = s;i <= min(a,b); i ++){
		count ++;
		if((a % i == 0) && (b % i == 0)){
			return count + GCD_BY_FILTER_FASTER_count(a/i, b/i, i);
		}
	
	}
	return count ;
}
void GCD_By_Binary(int a,int b){
	int n,m,ans,count = 0;
	n = min(a,b);
	m = max(a,b);
	ans = 1;
	while(n*m != 0){
		count ++ ;
		if((n % 2 == 0) && (m % 2 == 0)){
			ans = ans * 2;
			n = n / 2 ;
			m = m / 2 ; 
		}
		else if(n % 2 == 0 && m % 2 != 0)
			n = n / 2 ;
		else if(m % 2 == 0 && n % 2 != 0)
			m = m / 2 ;
		if (n > m)
			swap(&n,&m);
		m = m - n;
	}
	printf("Case (%d, %d): GCD-By-Binary = %d, taking %d iterations\n" , a , b , n * ans , count);
}
void GCD_By_Euclid(int a,int b){
	int n,m,temp,count = 0;
	n = min(a,b);
	m = max(a,b);
	while(m % n != 0){
		count++ ;
		temp = n ;
		n = m % n ;
		m = temp ;
	}
	printf("Case (%d, %d): GCD-By-Euclid = %d, taking %d iterations\n" , a , b , n ,count);
}
int main(){
    int a,b;
	cin >> a >> b ;
	while(a != 0){
		 GCD_BY_REVERSE_SEARCH(a,b);

		 int ans = GCD_BY_FILTER(a,b);
		 printf("Case (%d, %d): GCD-By-Filter = %d, taking %d iterations\n",a,b,ans,GCD_BY_FILTER_count(a,b));

		 int ans2 = GCD_BY_FILTER_FASTER(a,b,2);
		 printf("Case (%d, %d): GCD-By-Filter-Faster = %d, taking %d iterations\n",a,b,ans2,GCD_BY_FILTER_FASTER_count(a,b,2));

		 GCD_By_Binary(a,b);
		 GCD_By_Euclid(a,b);

		 cin >> a >> b;
	} 

	return 0 ;
}

