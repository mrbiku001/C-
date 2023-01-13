// Q11. Search of the given element id present in the array or not and find the index. if not present then return the index as -1 (Linear search).
#include<iostream>
using namespace std;
int main(){
    int array[]={1,2,3,4,5,6,7,8,9}, find;
    cout<<"search for: ";
    cin>>find;
    int size=sizeof(array)/sizeof(array[0]);
    for(int index=0; index<size; index++){
        if(find==array[index]){
            cout<<index;
            return 0;
        }
    }
    cout<<"-1";
    return 0;
}