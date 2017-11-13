#include <iostream> 
#include <cstdio>
#include <cstdlib> 
#include <string> 
using namespace std; 

int main() 
{ 
  FILE *fp = popen("gnuplot", "w"); 
  if (fp == NULL)  return -1; 
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
  fputs("plot \"circle-data0.dat\"using (0):(0):(1):(angle_conv($3)):(angle_conv($2)):($0+1) with circles lc var,\"\"using(0.7*cos(((angle_conv($2)+angle_conv($3))/2.0))):(0.7*sin(((angle_conv($2)+angle_conv($3))/2.0))):1 with labels\n",fp);
  fflush(fp);  
  cin.get();
  pclose(fp);   
  return 0; 
  } 
