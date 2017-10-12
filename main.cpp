#include<iostream>
#include<string>
#include<iomanip>
#include<sstream>
#include<vector>
using namespace std;

class accout_book{
        class record{
                public:
                        time_t date;
                        string name;
                        long long value;

                        record(time_t a_date,string a_name,long long a_value){
                                date=a_date;
                                name=a_name;
                                value=a_value;
                        }
        };
        public:
                vector<record> data;
                void change_user(string user){
                        ifstream file_stream;
                        file_stream.open(user,ios::in);
                        while(!file_stream.eof()){
                                string line;
                                getline(file_stream,line);
                        }
                }

                void add_record(){
                }
};


accout_book master;

int main(){
        while(true){
                string command;
                cin>>command;
                if(command.find("user")==0){
                        master.change_user();
                }else if(command.find("add")==0){
                        master.add_record();
                }else if(command.find("search")==0){
                }
                //record test=record(1,"用途",50000);
                //accout_book_list.push_back(test);
        }
}
