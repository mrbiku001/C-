// Q8. Print pattern
//     121212
//     212121
//     121212
//     212121
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
            if(i%2){
                (j%2)?cout<<"1":cout<<"2";
            }
            else{
                (j%2)?cout<<"2":cout<<"1";
            }
        }
        cout<<endl;
    }
    return 0;
}