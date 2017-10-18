#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <signal.h>

using money=long long;

using namespace std;
class accout_book{
        public:
                class record{
                        public:
                                time_t date;
                                string name;
                                money value;
                                record(time_t a_date,string a_name,money a_value);
                };
                vector<record> data;
                void change_user(string user);
                void add_record(time_t date,string name,money value);
                void del_by_name(string name);
                void search_by_name(string name);
                void save();
                void load(string user);
};
