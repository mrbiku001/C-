// Q10. Find the max. value out of all the elements in the array.
#include<iostream>
using namespace std;
int main(){
    int array[]={5,3,5,8,9,2};
    int max=INT_MIN, size=sizeof(array)/sizeof(array[0]);
    for(int i=0; i<size; i++){
        if(max<array[i]) max=array[i];
    }
    cout<<"maximun : "<<max;
    return 0;
}