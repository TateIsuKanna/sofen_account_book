#include"main.hpp"

accout_book::record::record(time_t a_date,string a_name,money a_value){
        date=a_date;
        name=a_name;
        value=a_value;
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

void accout_book::del_by_name(string name){
	  data.erase(remove_if(data.begin(), data.end(), 
		[name](record d){return d.name==name;}
				  ), data.end());
}

void accout_book::search_by_name(string name){
        auto found_data = find_if(data.begin(), data.end(), [name](accout_book::record x) {return x.name==name;});
        if (found_data != data.end()) {
                cout <<  (*found_data).name << (*found_data).value << endl;
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
			string date_str;
			string name;
			money value;
			cin>>date_str>>name>>value;

			time_t date=time(nullptr);
			tm* lt=localtime(&date);
			lt->tm_mday=stoi(date_str);
			date=mktime(lt);

                        master.add_record(date,name,value);
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
