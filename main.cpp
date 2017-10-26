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
        ifstream file_stream;
        file_stream.open(user_name,ios::in);
        while(!file_stream.eof()){
                string line;
                getline(file_stream,line);
        }
}

void accout_book::add_record(time_t date,string name,money value){
	data.push_back(accout_book::record(date,name,value));
}

string lambda_is_equal_by_name_name_arg;
bool lambda_is_equal_by_name(accout_book::record d){
        return d.name==lambda_is_equal_by_name_name_arg;
}

void accout_book::del_by_name(string name){
        lambda_is_equal_by_name_name_arg=name;
        data.erase(remove_if(data.begin(), data.end(), 
                                lambda_is_equal_by_name
                            ), data.end());
}

void accout_book::search_by_name(string name){
        lambda_is_equal_by_name_name_arg=name;
        auto found_data = find_if(data.begin(), data.end(), lambda_is_equal_by_name);
        if (found_data != data.end()) {
		cout<<(*found_data)<<endl;
        }
}

void accout_book::save(){
}
void accout_book::load(string user){
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

	time_t date=time(NULL);
	tm* lt=localtime(&date);
	lt->tm_mday=stoi(date_str);
	date=mktime(lt);

	master.add_record(date,name,value);
}

int main(){
        signal(SIGINT, signal_handler);
        while(true){
                string command;
                cin>>command;
                if(command.find("user")==0){
			string user;
			cin>>user;
                        master.change_user("");
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
                }else if(command.find("-h")==0){
			//TODO:ヘルプ書く
                }else{
			cout<<": '"<<command<<"' is not a command. See ' -h'."<<endl;
		}
        }
}
