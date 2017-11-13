#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <csignal>
#include <regex>

#include <iostream> 
#include <cstdio> 
#include <fstream>
#include <map>
#include <cmath>

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
                string current_username;
                void change_user(string user);
                void add_record(time_t date,string name,money value);
                void del_by_name(string name);
                void search_by_name(string name);
                void save();
};
