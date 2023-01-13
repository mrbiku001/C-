// Q9. Calculate the sum of all the element in the given array.
#include<iostream>
using namespace std;
int main(){
    int array[]={1,2,3,4,5,6};
    int sum=0, size=sizeof(array)/sizeof(array[0]);
    for(int i=0; i<size; i++){
        sum+=array[i];
    }
    cout<<"sum : "<<sum;
    return 0;
}