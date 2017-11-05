#include"main.hpp"

accout_book::record::record(time_t a_date,string a_name,money a_value){
        date=a_date;
        name=a_name;
        value=a_value;
}

ostream& operator << (ostream& os, const accout_book::record& r){
	tm* lt=localtime(&r.date);
	os<<lt->tm_year+1900<<"/"<<lt->tm_mon+1<<"/"<<lt->tm_mday<<" "<<r.name<<" "<<r.value;
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
                date=stof(token[0]);
                name=token[1];
                value=stof(token[2]);
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
        auto search_iter=data.begin();
        while(
                (search_iter = find_if(search_iter, data.end(), 
                        [name](record d){return d.name==name;}
                ))!=data.end()
        ){
                cout<<(*search_iter)<<endl;
                search_iter++;
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
	string date_str;
	string name;
	money value;
	cin>>date_str>>name>>value;

	time_t date=time(nullptr);
	tm* lt=localtime(&date);
	lt->tm_mday=stoi(date_str);
	date=mktime(lt);

	master.add_record(date,name,value);
}


int main(int argc,char* argv[]){
        if(argc==2 && string(argv[1])=="-h"){
                cout<<"usage"<<endl;
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
                }else{
			cout<<": '"<<command<<"' is not a command. See ' -h'."<<endl;
		}
        }
}
