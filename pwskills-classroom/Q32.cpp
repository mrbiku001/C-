// Q32. WAP to print the transpose of the matrix entered by the user.
//     Input:
//     row = 3
//     col = 3
//     arr[]={{1,2,3},{4,5,6},{7,8,9}}
//     Output: 1 4 7 2 5 8 3 6 9
#include<iostream>
using namespace std;
int main(){
    int m,n;
    cin>>m>>n;
    int arr[m][n];
    for (int i = 0; i < m; i++) {
        for ( int j = 0; j < n; j++) {
            cin>>arr[i][j];
        }
    }

    int transpose[n][m];
    for(int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            transpose[i][j]=arr[j][i];
        }
    }

    for(int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout<<transpose[i][j]<<" ";
        }cout<<endl;
    }
    return 0;
}