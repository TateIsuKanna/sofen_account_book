#include"main.hpp"
#include <sys/ioctl.h>
#include <unistd.h>

accout_book::record::record(time_t a_date,string a_name,money a_value){
	date=a_date;
	name=a_name;
	value=a_value;
}

ostream& operator << (ostream& os, const accout_book::record& r){
	tm* lt=localtime(&r.date);
	os<<lt->tm_year+1900<<"/"<<lt->tm_mon+1<<"/"<<lt->tm_mday<<" "<<r.name<<" "<<r.value;//HACK:マジックナンバーでは
	return os;
}

void accout_book::change_user(string user_name){
	save();
	current_username=user_name;
	ifstream file_stream;
	file_stream.open(current_username);
	string line;
	data.clear();
	while(getline(file_stream,line)){
		//HACK:流石にちょっと気持ち悪い実装
		string token[3];
		istringstream token_stream(line);
		for(int c_i=0;c_i<3;++c_i){
			getline(token_stream,token[c_i],',');
		}
		time_t date;
		string name;
		money value;
		date=stoi(token[0]);
		name=token[1];
		value=stoll(token[2]);
		data.push_back(accout_book::record(date,name,value));
	}
}

void accout_book::add_record(time_t date,string name,money value){
	data.push_back(accout_book::record(date,name,value));
}

void accout_book::del_by_name(string name){
	data.erase(remove_if(data.begin(), data.end(), 
				[name](record d){return d.name==name;}
			    ), data.end());
}

void accout_book::search_by_name(string name){
	for(
			auto search_iter=data.begin();
			(search_iter = find_if(search_iter, data.end(), 
					       [name](record d){return d.name==name;}
					      ))!=data.end();
			search_iter++
	   ){
		cout<<(*search_iter)<<endl;

	}
}

void accout_book::save(){
	ofstream file_stream(current_username);
	for(auto r:data){
		file_stream<<r.date<<","<<r.name<<","<<r.value<<endl;
	}
}

accout_book master;

void signal_handler(int signal_n){
	if(signal_n==SIGINT){
		master.save();
		exit(1);
	}
}

void add_command(){
	while(true){
                cout<<">";
		string date_str;
		string name;
		money value;
		cin>>date_str;
		if(date_str=="q"){
			return;
		}
		cin>>name>>value;
		//日付補完．今日の日付を元に，入力した部分だけ置き換えする．
		//例えば，2011/11/12 で入力が 11 なら 2011/11/11 にする．
		time_t date=time(nullptr);
		tm* lt=localtime(&date);

		regex date_re(R"((((\d{4,})/)?([1-9]|1[0-2])/)?([1-3]\d|[1-9]))");
		sregex_token_iterator it;
		it=sregex_token_iterator(begin(date_str), end(date_str), date_re, 3);
		if(it->str()!=""){//HACK:多分
			lt->tm_year=stoi(it->str())-1900;//HACK:マジックナンバーでは
		}
		it=sregex_token_iterator(begin(date_str), end(date_str), date_re, 4);
		if(it->str()!=""){//HACK:多分
			lt->tm_mon=stoi(it->str())-1;//HACK:マジックナンバーでは
		}
		it=sregex_token_iterator(begin(date_str), end(date_str), date_re, 5);
		if(it->str()!=""){//HACK:多分
			lt->tm_mday=stoi(it->str());
		}

		date=mktime(lt);

		master.add_record(date,name,value);
	}
}

void calc_rate(){
	money all=0;
	money suball=0;
	money zandaka=0;

	map<string,money>name_value_map;

	for(auto data:master.data){
                name_value_map[data.name]+=data.value;

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

void calc_rate_graph(){
        map<string, money> name_value_map;

	float  outall=0;
	for(auto data:master.data){
		if(data.value<0){
			outall-=data.value;
			name_value_map[data.name]-=data.value;
		}
	}

        struct winsize ws;
        int terminal_width=50;
        if(ioctl(STDOUT_FILENO,TIOCGWINSZ, &ws ) != -1 ) {
                terminal_width  = ws.ws_col;
        }

	for(auto value:name_value_map){
		string label;
		label=value.first+" "+to_string(value.second);
                cout<<label+string(value.second/outall*(terminal_width-5)-label.length()+1, ' ');
	}
        cout<<endl;
        cout<<"|";
	for(auto value:name_value_map){
                cout<<string(value.second/outall*(terminal_width-5), '-')+"|";
	}
        cout<<endl;
}

int main(int argc,char* argv[]){
	if(argc>=2 && string(argv[1])=="-h"){
		cout<<
		"usage: nn [-h]\n"
		"-h	このヘルプを表示します．\n"
		"\n"
		"内部コマンド\n"
		"	ユーザー名指定\n"
		"		user ユーザー名\n"
		"	追加\n"
		"		add {. | [[年/]月/]日} 項目名 金額\n"
		"		年，月は省略すると現在の日付が使われます．\n"
		"		. は現在の日時を指定します．\n"
		"	削除\n"
		"		del 項目名\n"
		"	検索\n"
		"		search 項目名 \n"
		"	項目別収支\n"
		"		rate\n"
		"	項目別支出グラフ描画\n"
		"		graph"
		<<endl;
		return 0;
	}
	signal(SIGINT, signal_handler);
	while(true){
		string command;
		cin>>command;
		if (cin.fail()) {
			cin.clear();
			continue;
		}
		if(command.find("user")==0){
			string user;
			cin>>user;
			master.change_user(user);
		}else if(command.find("add")==0){
			add_command();
		}else if(command.find("del")==0){
			string name;
			cin>>name;
			master.del_by_name(name);
		}else if(command.find("search")==0){
			string name;
			cin>>name;
			master.search_by_name(name);
		}else if(command.find("rate")==0){
			calc_rate();
		}else if(command.find("graph")==0){
			calc_rate_graph();
		}else{
			cout<<"nn: '"<<command<<"' is not a nn command. See 'nn -h'."<<endl;
		}
	}
}
