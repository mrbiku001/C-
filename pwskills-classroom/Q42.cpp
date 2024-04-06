// Q42.Given a number n. Find the increasing sequence from  to n without using any loop.
//     Input n=4
//     Output 1 2 3 4

//     Input n=2
//     Output 1 2

#include <iostream>
using namespace std;
void rF(int n){
    if(n<1){
        return;
    }
    rF(n-1);
    cout<<n<<" ";
}
int main(){
    int n;
    cout<<"Enter n: ";
    cin>>n;
    rF(n);
    return 0;
}