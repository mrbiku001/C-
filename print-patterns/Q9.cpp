// Q9. Print pattern.
//     123456
//     1    6
//     1    6
//     123456
#include<iostream>
using namespace std;
int main(){
    int row,col;
    cout<<"enter rows: ";
    cin>>row;
    cout<<"enter columns: ";
    cin>>col;
    for(int i=1; i<=row; i++){
        for(int j=1; j<=col; j++){
            (i==1||j==1||i==row||j==col)?cout<<j:cout<<" ";
        }
        cout<<endl;
    }
    return 0;
}