#include"main.hpp"

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
	string date_str;
	string name;
	money value;
	cin>>date_str>>name>>value;

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

void calc_rate(){
	money all=0;
	money suball=0;
	money zandaka=0;

	map<string,money>name_value_map;

	for(auto data:master.data){
		if(name_value_map.find(data.name)==end(name_value_map)){
			name_value_map[data.name]=data.value;
		}else{
			name_value_map[data.name]+=data.value;
		}

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



int graph(){ 
	FILE *fp = popen("gnuplot", "w"); 
	if (fp == NULL) return -1; 
	fputs("set mouse\n", fp); 
	fputs("set size ratio -1\n",fp);
	fputs("set xrange[-1:1]\n",fp);
	fputs("set yrange[-1:1]\n", fp);
	fputs("unset key\nunset border\nunset xtics\nunset ytics\n",fp);
	fputs("set angles degrees\n",fp);
	fputs("set style fill transparent solid 0.4 border lc rgb \"black\"\n",fp);
	fputs("set style lines 1 lc rgb \"yellow\"\n",fp);
	fputs("set style lines 2 lc rgb \"cyan\"\n",fp);
	fputs("set style lines 3 lc rgb \"brown\"\n",fp);
	fputs("set style lines 4 lc rgb \"magenta\"\n",fp);
	fputs("set style lines 5 lc rgb \"gray\"\n",fp);
	fputs("angle_conv(x) = -x +90.0\n",fp);
	fputs("plot \"data.dat\"using (0):(0):(1):(angle_conv($3)):(angle_conv($2)):($0+1) with circles lc var,\"\"using(0.7*cos(((angle_conv($2)+angle_conv($3))/2.0))):(0.7*sin(((angle_conv($2)+angle_conv($3))/2.0))):1 with labels\n",fp);
	fflush(fp); 
	cin.get(); 
	pclose(fp); 
	return 0; 
} 
int calc_rate_graph(){
	accout_book master;

	string koumoku[100];
	float  sisyutu[100];
	float wariai[100];
	float  outall;
	int i;
	float hinan;
	int graph();
	map<string, money> name_value_map;

	outall=0;
	for(auto data:master.data){
		if(data.value<0){
			outall-=data.value;
		}

		if(name_value_map.find(data.name) != name_value_map.end()){
			name_value_map.insert(make_pair(data.name,name_value_map.at(data.name) + data.value));
		}else{
			name_value_map.insert(make_pair(data.name, data.value));
		}
	}
	ofstream file("data.dat");
	for(auto value:name_value_map){
		file << value->first <<endl;
	}

	cout << name_value_map.at("a") << endl;


	int value = name_value_map.at("a");
	for(i=0;i<5;i++){
		wariai[i]=sisyutu[i]/outall;
	}

	hinan=0;

	ofstream file("data.dat");

	for(i=0;i<5;i++){

		file << koumoku[i] ;
		file<< " "<< hinan ;
		file<< " "<< hinan+wariai[i]*360 <<endl;
		hinan=hinan+wariai[i]*360;
	}
	graph();


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
		}else if(command.find("rate")==0){
			calc_rate();
		}else if(command.find("graph")==0){
			calc_rate_graph();
		}else{
			cout<<": '"<<command<<"' is not a command. See ' -h'."<<endl;
		}
	}
}
