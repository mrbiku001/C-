// Q3 - Given a m*n integer matrix. If an element of the matrix is 0 then set the complete row and column of that element to 0. Make the changes inplace and print the matrix.(Hard)
//     m=3
//     n=3
//     arr[]={{1,2,3},{1,0,1},{5,6,7}}
//     Output: {{1,0,3},{0,0,0},{5,0,7}}
//     arr[]={{0,1,2,0},{3,4,5,2},{1,3,1,5}}
//     Output:{{0,0,0,0},{0,4,5,0},{0,3,1,0}
//Exp:- first store all the cell position (i,j) in a vectop of pair which has the value 0; then we traverse through the vector and make the row and columns corrosponding to that cell(i,j) as 0
#include<iostream>
#include<vector>
using namespace std;
int main(){
    //taking input matrix
    int m,n;
    cin>>m>>n;
    int arr[m][n];
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            cin>>arr[i][j];
        }
    }
    //solve
    vector<pair<int,int>> ans; //we are shorting all the cells which have valur 0
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(arr[i][j]==0){
                ans.push_back({i,j});
            }
        }
    }
    //traversing the ans vector and making row and column of that cell to 0
    for(int i=0; i<ans.size(); i++){
        int x=ans[i].first;
        int y=ans[i].second;
        int row=0;
        int col=0;
        while(row<m){
            arr[row][y]=0;
            row++;
        }
        while(col<n){
            arr[x][col]=0;
            col++;
        }
    }cout<<endl;
    //printing the updated matrix
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            cout<<arr[i][j]<<" ";
        }cout<<endl;
    }
    return 0;
}