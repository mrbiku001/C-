// Q13. Print pattern.
//     *   *
//      * *
//       *
//      * *
//     *   *
#include<iostream>
using namespace std;
int main(){
    int order;
    cout<<"enter order: ";
    cin>>order;

    for(int i=1; i<=order; i++){
        for(int j=1; j<=order; j++){
            (j==i||j==order-i+1)?cout<<"*":cout<<" ";
        }
        cout<<endl;
    }
}