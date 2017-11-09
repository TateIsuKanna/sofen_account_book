//担当->内訳,残高  accout_book_list[]  .data/.name/.value

#include <stdio.h>
#include <iostream>
#include<math.h>
#include<stdlib.h>
#include<string.h>

#define check(x) printf("OK%d\n",x)

#define list accout_book_list
#define data(x,y) accout_book_list[x].data[y]
#define name(x) accout_book_list[x].name
#define value(x) accout_book_list[x].value
#define listmax 20

int all, suball, zandaka, utiwake[listmax], size, i;
float percent[listmax], subpercent[listmax];
char name[listmax];

struct DATA {
	int data[3];
	char name[listmax];
	int value;
}accout_book_list[listmax];

using namespace std;

int main(){
	
	all=zandaka=0;
	for(i=0; i<5; i++) utiwake[i]=0;
	
	for(i=1; i<listmax; i++){
		data(i,0) = 2000 + i;
		data(i,1) = (i*5)%12;
		data(i,2) = (i*3)%31;
		value(i)=-(500*i); //pow(x,y)-->x^y
		if(i%7==0){ strcpy(name(i),"給料"); value(i)=1000*i;}
		else if(i%15==0){ strcpy(name(i),"臨時収入"); value(i)=3000*i;}
		else if(i%4==0) strcpy(name(i),"食費");
		else if(i%4==1) strcpy(name(i),"交通費");
		else if(i%4==2) strcpy(name(i),"光熱費");
		else if(i%4==3) strcpy(name(i),"その他");
		printf("%5d年 %2d月 %2d日 , %-12s ,%7d \n",data(i,0),data(i,1),data(i,2),name(i),value(i));
	}
	
	
	size = listmax;//sizeof(list) / sizeof(list[0]);
		for(i=1; i<size; i++){
			if(strcmp(name(i),"給料")==0){
				all+=value(i);
				utiwake[0]+=value(i);
			}
			else if(strcmp(name(i),"臨時収入")==0){
				all+=value(i);
				utiwake[1]+=value(i);
			}
			else if(strcmp(name(i),"食費")==0){
				all+=abs(value(i));
				suball+=abs(value(i));
				utiwake[2]+=abs(value(i));
			}
			else if(strcmp(name(i),"交通費")==0){
				all+=abs(value(i));
				suball+=abs(value(i));
				utiwake[3]+=abs(value(i));
			}
			else if(strcmp(name(i),"光熱費")==0){
				all+=abs(value(i));
				suball+=abs(value(i));
				utiwake[4]+=abs(value(i));
			}
			else if(strcmp(name(i),"その他")==0){
				all+=abs(value(i));
				suball+=abs(value(i));
				utiwake[5]+=abs(value(i));
			}
			else printf("ERROR %d \n",i);
			zandaka+=value(i);
		}
		
		cout << endl << "総収支割合" << endl;
		for(i=0;i<6;i++){
			switch(i){
				case 0:
				strcpy(name,"給料　　");
				break;
				
				case 1:
				strcpy(name,"臨時収入");
				break;
				
				case 2:
				strcpy(name,"食費　　");
				break;
				
				case 3:
				strcpy(name,"交通費　");
				break;
				
				case 4:
				strcpy(name,"光熱費　");
				break;
				
				case 5:
				strcpy(name,"その他　");
				break;
			}
			percent[i]=100.0*(float)utiwake[i]/(float)all;
			printf("%-12s %6d円 ,%3d％ \n",name,utiwake[i],(int)round(percent[i]));
		}
		
		cout << endl << "支出割合" << endl;
		for(i=2;i<6;i++){
			switch(i){
				case 2:
				strcpy(name,"食費　　");
				break;
				
				case 3:
				strcpy(name,"交通費　");
				break;
				
				case 4:
				strcpy(name,"光熱費　");
				break;
				
				case 5:
				strcpy(name,"その他　");
				break;
			}
			subpercent[i]=100.0*(float)utiwake[i]/(float)suball;
			printf("%-12s %6d円 ,%3d％ \n",name,utiwake[i],(int)round(subpercent[i]));
		}
		
		cout << endl << "残高  " << zandaka;
		if(zandaka > 0) cout << "円 , 黒字" << endl;
		else cout << " , 赤字！！" << endl;
}





