// Q5 - Write a C++ program to find size of basic data types. (Medium)
// Size of fundamental data types :
// The sizeof(char) : 1 bytes
// 	The sizeof(short) : 2 bytes
// 	The sizeof(int) : 4 bytes
// 	The sizeof(long): 4 bytes
// 	The sizeof(long long) : 8 bytes
// 	The sizeof(float) : 4 bytes
// 	The sizeof(double) : 8 bytes
// 	The sizeof(long double) : 12 bytes
// 	The sizeof(bool) : 1 bytes
#include<iostream>
using namespace std;
int main(){
    cout<<"Size of fundamental data types :"<<endl;
    cout<<"The sizeof(char) : "<<sizeof(char)<<" bytes"<<endl;
    cout<<"The sizeof(short) : "<<sizeof(short)<<" bytes"<<endl;
    cout<<"The sizeof(int) : "<<sizeof(int)<<" bytes"<<endl;
    cout<<"The sizeof(long) : "<<sizeof(long)<<" bytes"<<endl;
    cout<<"The sizeof(long long) : "<<sizeof(long long)<<" bytes"<<endl;
    cout<<"The sizeof(float) : "<<sizeof(float)<<" bytes"<<endl;
    cout<<"The sizeof(double) : "<<sizeof(double)<<" bytes"<<endl;
    cout<<"The sizeof(long double) : "<<sizeof(long double)<<" bytes"<<endl;
    cout<<"The sizeof(bool) : "<<sizeof(bool)<<" bytes"<<endl;
    return 0;
}