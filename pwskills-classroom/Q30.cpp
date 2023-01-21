// Q30. WAP to print plus pattern.
//       *
//       *
//     *****
//       *
//       *
// Note:- input is always odd and also should be greater then or equal to 3
#include<iostream>
using namespace std;
int main(){
    int n;
    cin>>n;

    /* for(int i = 1; i <= n; i++) {
        if(i == (n+1)/2) {
            for(int j = 1; j <= n; j++) {
                cout<<"*";
            }cout<<endl;
        }
        else{
            for(int k = 1; k <= n; k++) {
                if(k == (n+1)/2) {
                    cout<<"*";
                }
                else{
                    cout<<" ";
                }
            }cout<<endl;
        }
    } */
    for(int line = 0; line < n; line++) {
        for(int i = 0; i < n; i++){
            if(i == n/2) cout<<"*";
            else if(line == n/2) cout<<"*";
            else cout<<" ";
        }cout<<endl;
    }
    return 0;
}