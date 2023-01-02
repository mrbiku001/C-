// Q4. find the sum of the following series.
//     1-2+3-4......n
#include<iostream>
using namespace std;
int main(){
    int n,sum=0;
    cout<<"enter number: ";
    cin>>n;

    for(int i=1; i<=n; i++){
         (i%2)?sum+=i:sum-=i;
    }
    cout<<"sum of the series = "<<sum;
    return 0;
}