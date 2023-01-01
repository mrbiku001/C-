// Q7. Print pattern.
//     123456
//     123456
//     123456
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
            cout<<j;
        }
        cout<<endl;
    }
    return 0;
}