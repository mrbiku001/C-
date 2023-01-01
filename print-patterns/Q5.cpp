// Q5. Print pattern.
//        *
//       ***
//      *****
//     *******
#include<iostream>
using namespace std;
int main(){
    int stages;
    cout<<"enter stages: ";
    cin>>stages;
    for(int i=1; i<=stages; i++){
        for(int j=1; j<=2*stages-1; j++){
            if((j>stages-i)&&(j<stages+i)){
                cout<<"*";
            }
            else{
                cout<<" ";
            }
        }
        cout<<endl;
    }
    return 0;
}