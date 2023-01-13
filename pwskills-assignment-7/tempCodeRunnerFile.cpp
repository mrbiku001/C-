    for(int i=1; i<n-1; i++){
        if((arr[i]>maxLeft(arr,n,i))&&(arr[i]<minRight(arr,n,i))){
            cout<<arr[i];
            break;
        }
    }
    cout<<"no such element found";