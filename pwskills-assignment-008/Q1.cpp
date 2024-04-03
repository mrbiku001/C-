// Q1 - Given two vectors arr1[] and arr2[] of size m and n sorted in increasing order. Merge the two arrays into a single sorted array of size m+n.(Easy)
//     Input:arr1=[1,2,3] arr2=[4,5,6]
//     Output:arr=[1,2,3,4,5,6]
//     Input:arr1=[1,3,5] arr2=[2,4,6]
//     Output:arr=[1,2,3,4,5,6]
#include<iostream>
using namespace std;
void merge(int arr1[], int sizearr1, int arr2[], int sizearr2, int arr[]){
    int indexarr1=0, indexarr2=0, indexarr=0;
    while(indexarr1<sizearr1 && indexarr2<sizearr2){
        (arr1[indexarr1]<arr2[indexarr2])?arr[indexarr++]=arr1[indexarr1++]:arr[indexarr++]=arr2[indexarr2++];
    }
    while(indexarr1<sizearr1){
        arr[indexarr++]=arr1[indexarr1++];
    }
    while(indexarr2<sizearr2){
        arr[indexarr++]=arr2[indexarr2++];
    }
    cout<<"arr=[";
    for(int i=0; i<sizearr1+sizearr2; i++){
        cout<<arr[i];
        if(i<sizearr1+sizearr2-1){
            cout<<",";
        }
    }
    cout<<"]";
}
int main(){
    int arr1[]={1,2,3}, arr2[]={4,5,6};
    int sizearr1=sizeof(arr1)/sizeof(arr1[0]), sizearr2=sizeof(arr2)/sizeof(arr2[0]);
    int arr[sizearr1+sizearr2];
    merge(arr1, sizearr1, arr2, sizearr2, arr);
    return 0;
}