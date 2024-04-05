#include <iostream>
using namespace std;
int rF(int p, int q){
    if(q == 0){
        return 1;
    }
    if(q%2){
        int result = rF(p, (q-1)/2);
        return p*result*result;
    }
    else{
        int result = rF(p,q/2);
        return result*result;
    }
}
int main(){
    int p, q;
    cout<<"Enter p & q";
    cin>> p>>q;

    cout<<rF(p,q);
    return 0;
}