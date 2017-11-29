#include"main.hpp"
#include <sys/ioctl.h>
#include <unistd.h>

accout_book::record::record(tm a_date,string a_name,money a_value){
	date=a_date;
	name=a_name;
	value=a_value;
}

ostream& operator << (ostream& os, const accout_book::record& r){
        os<<r.date.tm_year+1900<<"/"<<r.date.tm_mon+1<<"/"<<r.date.tm_mday<<" "<<r.name<<" "<<r.value;//HACK:マジックナンバーでは
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
		//HACK:流石にちょっと気持ち悪い実装かも
		string token[3];
		istringstream token_stream(line);
		for(int c_i=0;c_i<3;++c_i){
			getline(token_stream,token[c_i],',');
		}
		tm date;
		string name;
		money value;

                strptime(token[0].c_str(), "%Y/%m/%d", &date);
		name=token[1];
		value=stoll(token[2]);
		data.push_back(accout_book::record(date,name,value));
	}
}

void accout_book::add_record(tm date,string name,money value){
	data.push_back(accout_book::record(date,name,value));
}

void accout_book::del_by_name(string name){
	data.erase(remove_if(data.begin(), data.end(), 
				[name](record d){return d.name==name;}
			    ), data.end());
}

void accout_book::search_by_date_and_name(tm date,string name){
	for(
			auto search_iter=data.begin();
			(search_iter = find_if(search_iter, data.end(), 
					       [date,name](record d){
                                                       bool is_date_eq=
                                                                d.date.tm_year==date.tm_year&&
                                                               d.date.tm_mon==date.tm_mon&&
                                                               d.date.tm_mday==date.tm_mday;
;
                                                       if(date.tm_year==0&&date.tm_mon==0&&date.tm_mday==0){
                                                               is_date_eq=true;
                                                       }
                                                       regex comp_re(R"((-?[<>])(\d+))");
                                                       sregex_token_iterator rend;
                                                       sregex_token_iterator comp_it=sregex_token_iterator(begin(name), end(name), comp_re, 1);
                                                       sregex_token_iterator value_it=sregex_token_iterator(begin(name), end(name), comp_re, 2);
                                                       if(comp_it!=rend&&comp_it->str()!=""){//HACK:多分
                                                               bool is_inner_range=true;
                                                               if(comp_it->str()==">"){
                                                                       is_inner_range=d.value>stoi(value_it->str());
                                                               }else if(comp_it->str()=="<"){
                                                                       is_inner_range=d.value>0 && d.value<stoi(value_it->str());
                                                               }else if(comp_it->str()=="->"){
                                                                       is_inner_range=d.value<-stoi(value_it->str());
                                                               }else if(comp_it->str()=="-<"){
                                                                       is_inner_range=d.value<0 && d.value>-stoi(value_it->str());
                                                               }
                                                               return is_date_eq&&is_inner_range;
                                                       }
                                                       return is_date_eq && (name=="*"||d.name.find(name)!=string::npos);
						}
					      ))!=data.end();
			search_iter++
	   ){
		cout<<(*search_iter)<<endl;

	}
}

void accout_book::save(){
	ofstream file_stream(current_username);
	for(auto r:data){
		file_stream<<r.date.tm_year+1900<<"/"<<r.date.tm_mon+1<<"/"<<r.date.tm_mday<<","<<r.name<<","<<r.value<<endl;//HACK:マジックナンバーでは
	}
}

accout_book master;

void signal_handler(int signal_n){
	if(signal_n==SIGINT){
		master.save();
		exit(1);
	}
}

tm* complement_date(string date_str){
	time_t now=time(nullptr);
	tm* date=localtime(&now);

        //HACK:好ましい実装では無い
        if(date_str=="*"){
                date->tm_year=0;
                date->tm_mon=0;
                date->tm_mday=0;
                return date;
        }
	if(date_str!="."){
		try{
			//日付補完．今日の日付を元に，入力した部分だけ置き換えする．
			//例えば，2011/11/12 で入力が 11 なら 2011/11/11 にする．

			regex date_re(R"((((\d{4,})/)?([1-9]|1[0-2])/)?([1-3]\d|[1-9]))");
			sregex_token_iterator rend;
			sregex_token_iterator it;
			it=sregex_token_iterator(begin(date_str), end(date_str), date_re, 3);
			if(it!=rend&&it->str()!=""){//HACK:多分
				date->tm_year=stoi(it->str())-1900;//HACK:マジックナンバーでは
			}
			it=sregex_token_iterator(begin(date_str), end(date_str), date_re, 4);
			if(it!=rend&&it->str()!=""){//HACK:多分
				date->tm_mon=stoi(it->str())-1;//HACK:マジックナンバーでは
			}
			it=sregex_token_iterator(begin(date_str), end(date_str), date_re, 5);
			if(it!=rend&&it->str()!=""){//HACK:多分
				date->tm_mday=stoi(it->str());
			}
		}catch(const invalid_argument& e){
			cerr<<e.what()<<endl;
		}
	}
	return date;
}

void into_addmode(){
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
		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			continue;
		}

		tm* date=complement_date(date_str);
		
		master.add_record(*date,name,value);
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
			cout<<data.first<<"  "<<-data.second<<"円  "<<(int)round(-(float)data.second/(float)suball*100)<<"％"<<endl;
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
                cout<<left<<setw(value.second/outall*(terminal_width-10)+1)<<label;
	}
        cout<<endl;
        cout<<"|";
	for(auto value:name_value_map){
                cout<<string(value.second/outall*(terminal_width-10), '-')+"|";
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
		"		search {* | . | [[年/]月/]日 } {* | 項目名 | [-]{><}金額}\n"
		"		* は全ての項目を指定します．\n"
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
			return -1;
		}
		if(command=="user"){
			string user;
			cin>>user;
			master.change_user(user);
		}else if(command=="add"){
			into_addmode();
		}else if(command=="del"){
			string name;
			cin>>name;
			master.del_by_name(name);
		}else if(command=="search"){
			string date_str;
			string name;
			cin>>date_str>>name;
			tm* date=complement_date(date_str);
			master.search_by_date_and_name(*date,name);
		}else if(command=="rate"){
			calc_rate();
		}else if(command=="graph"){
			calc_rate_graph();
		}else{
			cout<<"nn: '"<<command<<"' is not a nn command. See 'nn -h'."<<endl;
		}
	}
}
