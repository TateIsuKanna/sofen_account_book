#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>
#include <fstream>
#include <sstream>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;
class accout_book{
        public:
                class record{
                        public:
                                time_t date;
                                string name;
                                long long value;
                                record(time_t a_date,string a_name,long long a_value);
                };
                vector<record> data;
                void change_user(string user);
                void add_record();
                void search_by_name(string name);
};
