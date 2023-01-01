// Q10. Print pattern.
//     1
//     12
//     123
//     1234
#include<iostream>
using namespace std;
int main(){
    int order;
    
    cout<<"enter order: ";
    cin>>order;

    for(int i=1; i<=order; i++){
        for(int j=1; j<=i; j++){
            cout<<j;
        }
        cout<<endl;
    }

    return 0;
}