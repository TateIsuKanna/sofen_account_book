#include"main.hpp"

accout_book::record::record(time_t a_date,string a_name,long long a_value){
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

void accout_book::add_record(){
}

accout_book master;

void signal_handler(int signal_n){
        if(signal_n==SIGINT){
        }
}

int main(){
        signal(SIGINT, signal_handler);
        while(true){
                string command;
                cin>>command;
                if(command.find("user")==0){
                        master.change_user("");
                }else if(command.find("add")==0){
                        master.add_record();
                }else if(command.find("search")==0){
                }
                //record test=record(1,"用途",50000);
                //accout_book_list.push_back(test);
        }
}
