#include<stdio.h>
#include <iostream> 
#include <cstdio> 
#include<fstream>
#include"main.hpp"
#include<map>
using namespace std; 

int main(){
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
	for(auto value:name_value_map){
		cout<<value->
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

int graph()
{ 
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
