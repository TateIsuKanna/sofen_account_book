//担当->内訳,残高  accout_book_list[]  .data/.name/.value

#include <stdio.h>
#include <iostream>
#include<math.h>
#include<stdlib.h>
#include<string.h>

#define check(x) printf("OK%d\n",x)

#define list accout_book_list
#define data(x) accout_book_list[x].data
#define name(x) accout_book_list[x].name
#define value(x) accout_book_list[x].value
#define listmax 20

int all, zandaka, utiwake[listmax], size, i;
float percent[listmax];

struct DATA {
	int data;
	char name[listmax];
	int value;
}accout_book_list[listmax];

using namespace std;

int main(){
	
	all=zandaka=0;
	for(i=0; i<5; i++) utiwake[i]=0;
	
	for(i=1; i<listmax; i++){
		value(i)=-(300*i); //pow(x,y)-->x^y
		if(i%7==0){ strcpy(name(i),"給料"); value(i)=1000*i;}
		else if(i%15==0){ strcpy(name(i),"臨時収入"); value(i)=3000*i;}
		else if(i%4==0) strcpy(name(i),"食費");
		else if(i%4==1) strcpy(name(i),"交通費");
		else if(i%4==2) strcpy(name(i),"光熱費");
		else if(i%4==3) strcpy(name(i),"その他");
		cout << data(i) << " , " << name(i) << " , " << value(i) << endl;
	}
	
	
	size = listmax;//sizeof(list) / sizeof(list[0]);
		for(i=0; i<size; i++){
			if(strcmp(name(i),"給料")==0){
				all+=value(i);
				utiwake[0]+=value(i);
			}
			else if(strcmp(name(i),"臨時収入")==0){
				all+=value(i);
				utiwake[1]+=value(i);
			}
			else if(strcmp(name(i),"食費")==0){
				all-=abs(value(i));
				utiwake[2]+=abs(value(i));
			}
			else if(strcmp(name(i),"交通費")==0){
				all-=abs(value(i));
				utiwake[3]+=abs(value(i));
			}
			else if(strcmp(name(i),"光熱費")==0){
				all-=abs(value(i));
				utiwake[4]+=abs(value(i));
			}
			else if(strcmp(name(i),"その他")==0){
				all-=abs(value(i));
				utiwake[5]+=abs(value(i));
			}
			else printf("ERROR%d",i);
			zandaka+=value(i);
		}
		
		for(i=0;i<6;i++){
			percent[i]=100.0*(float)utiwake[i]/(float)all;
			cout << utiwake[i] << " , " << percent[i] << endl;
		}
		
		cout << zandaka << endl;
}





