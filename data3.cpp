//担当->内訳,残高  master[]  .data/.name/.value
#include"main.hpp"

#define num 10

int all, suball, zandaka, utiwake[num], size, i;
//all:収支総額格納 , suball:支出総額格納 , zandaka:残高格納 , utiwake:収支種類別金額格納 , size:accout_book_listの個数を格納
float percent[num], subpercent[num]; //percent:総収支割合格納 , subpercent:支出割合格納
string name;  //name:収支種類名格納

using namespace std;

accout_book::record::record(time_t a_date,string a_name,money a_value){
        date=a_date;
        name=a_name;
        value=a_value;
}
accout_book master;
int main(){
	master.data.push_back(accout_book::record(1,"給料",123123123));
	master.data.push_back(accout_book::record(1,"給料",123123123));
	all=suball=zandaka=0;
	for(i=0; i<num; i++) utiwake[i]=0;

	for(auto data:master.data){
		if(data.name=="給料"){
			all+=data.value;
			utiwake[0]+=data.value;
		}
		else if(data.name=="臨時収入"){
			all+=data.value;
			utiwake[1]+=data.value;
		}
		else if(data.name=="食費"){
			all+=abs(data.value);
			suball+=abs(data.value);
			utiwake[2]+=abs(data.value);
		}
		else if(data.name=="交通費"){
			all+=abs(data.value);
			suball+=abs(data.value);
			utiwake[3]+=abs(data.value);
		}
		else if(data.name=="光熱費"){
			all+=abs(data.value);
			suball+=abs(data.value);
			utiwake[4]+=abs(data.value);
		}
		else{
			all+=abs(data.value);
			suball+=abs(data.value);
			utiwake[5]+=abs(data.value);
		}
		zandaka+=data.value;
	}

	cout << endl << "総収支割合" << endl;
	for(i=0;i<num;i++){
		switch(i){
			case 0:
				name="給料　　";
				break;

			case 1:
				name="臨時収入";
				break;

			case 2:
				name="食費　　";
				break;

			case 3:
				name="交通費　";
				break;

			case 4:
				name="光熱費　";
				break;

			case 5:
				name="その他　";
				break;
		}
		percent[i]=100.0*(float)utiwake[i]/(float)all;
		//printf("%-12s %6d円 ,%3d％ \n",name,utiwake[i],(int)round(percent[i]));
		cout<<name<<"  "<<utiwake[i]<<"円  "<<(int)round(percent[i])<<"％"<<endl;
	}

	cout << endl << "支出割合" << endl;
	for(i=2;i<num;i++){
		switch(i){
			case 2:
				name="食費　　";
				break;

			case 3:
				name="交通費　";
				break;

			case 4:
				name="光熱費　";
				break;

			case 5:
				name="その他　";
				break;
		}
		subpercent[i]=100.0*(float)utiwake[i]/(float)suball;
		//printf("%-12s %6d円 ,%3d％ \n",name,utiwake[i],(int)round(subpercent[i]));
		cout<<name<<"  "<<utiwake[i]<<"円  "<<(int)round(subpercent[i])<<"％"<<endl;
	}

	cout << endl << "残高  " << zandaka;
	if(zandaka > 0) cout << "円 , 黒字" << endl;
	else cout << " , 赤字！！" << endl;
}





