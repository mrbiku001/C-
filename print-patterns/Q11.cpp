// Q11. Print pattern.
//        1
//       121
//      12321
//     1234321
#include<iostream>
using namespace std;
int main(){
    int stages;
    cout<<"enter stages: ";
    cin>>stages;

    for(int i=1; i<=stages; i++){
        for(int j=1; j<=stages-i; j++){
            cout<<" ";
        }
        for(int j=1; j<=i; j++){
            cout<<j;
        }
        for(int j=i-1; j>=1; j--){
            cout<<j;
        }
        cout<<endl;
    }
    return 0;
}