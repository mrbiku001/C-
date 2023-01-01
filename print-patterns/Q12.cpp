// Q12. Print pattern.
//        1
//       2 2
//      3   3
//     4444444
#include<iostream>
using namespace std;
int main(){
    int stages;
    cout<<"enter stages";
    cin>>stages;
    for(int i=1; i<=stages; i++){
        for(int j=1; j<=stages-i; j++){
            cout<<" ";
        }
        cout<<i;
        if(i!=1&&i!=stages){
            for(int j=1; j<=i-1; j++){
                cout<<" ";
            }
            for(int j=i-2; j>=1; j--){
                cout<<" ";
            }
            cout<<i;
        }
        else if(i==stages){
            for(int j=1; j<=2*stages-1; j++){
                cout<<i;
            }
        }
        cout<<endl;
    }
    return 0;
}