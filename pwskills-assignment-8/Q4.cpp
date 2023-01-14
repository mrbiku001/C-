// Q4 - Given a vector arr[] sorted in increasing order. Return an array of squares of each number sorted in increasing order. Where size of vector 1<size<101.(Medium)
//     Input:[0,1,2,3]
//     Output:[0,1,4,9]
//     Input:[-5,-4,-3,-2,-1]
//     Output:[1,4,9,16,25]
//     Input:[-4,-3,-1,0,2,10]
//     Output:[0,2,4,9,16,100]
#include<iostream>
#include<vector>
using namespace std;
void sqshortarr(int arr[], int size){
        for(int i=0; i<size; i++){
            for(int j=i+1; j<size; j++){
                if(arr[i]>arr[j]){
                    int temp=arr[i];
                    arr[i]=arr[j];
                    arr[j]=temp;
                }
            }
        }
        int sqarr[size];
        for(int i=0; i<size; i++){
            sqarr[i]=arr[i]*arr[i];
        }
        cout<<"[";
        for(int i=0; i<size; i++){
            cout<<sqarr[i];
            if(i<size-1){
                cout<<",";
            }
        }
        cout<<"]";
    }
int main(){
    vector<int> v={-4,-3,-1,0,2,10};
    int arr[v.size()];
    for(int i=0; i<v.size(); i++){
        if(v[i]<0){
            arr[i]=-v[i];
        }
        else{
            arr[i]=v[i];
        }
    }
    sqshortarr(arr,v.size());
    return 0;
}