#include"main.hpp"
#include<map>
#include<cmath>

using namespace std;

accout_book::record::record(time_t a_date,string a_name,money a_value){
        date=a_date;
        name=a_name;
        value=a_value;
}
accout_book master;
int main(){
	money all=0;
	money suball=0;
	money zandaka=0;

	master.data.push_back(accout_book::record(1,"給料",123123123));
	master.data.push_back(accout_book::record(1,"給料",123123123));
	master.data.push_back(accout_book::record(1,"食費",-9123123));
	map<string,money>name_value_map;

	for(auto data:master.data){
		if(name_value_map.find(data.name)==end(name_value_map)){
			name_value_map[data.name]=data.value;
		}else{
			name_value_map[data.name]+=data.value;
		}

		if(data.value>0){
			all+=data.value;
		}else{
			suball+=abs(data.value);
		}
		zandaka+=data.value;
	}

	cout << endl << "総収入割合" << endl;
	for(auto data:name_value_map){
		if(data.second>0){
			cout<<data.first<<"  "<<data.second<<"円  "<<(int)round((float)data.second/(float)all*100)<<"％"<<endl;
		}
	}

	cout << endl << "支出割合" << endl;
	for(auto data:name_value_map){
		if(data.second<0){
			cout<<data.first<<"  "<<data.second<<"円  "<<(int)round(-(float)data.second/(float)suball*100)<<"％"<<endl;
		}
	}

	cout << endl << "残高  " << zandaka <<"円"<<endl;
	if(zandaka > 0){
		cout << "黒字" << endl;
	}else{
		cout << "赤字！！" << endl;
	}
}





