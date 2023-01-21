// Q31. WAP to display multiplication of two matrices entered by user.
//     Input:
//     enter the no. of rows=3
//     enter the no. of column=3
//     enter the first matrix elements=
//     1 2 3 4 5 6 7 8 9
//     enter the second matrix elements=
//     1 2 3 4 5 6 7 8 9
//     Output:
//     multiply of the matrix=
//     30 36 42 
//     66 81 96 
//     102 126 150
#include<iostream>
using namespace std;
void multiply(int, int);
int main(){
    int row1, col1;
    cout<<"enter rows and columns of matrix-1: ";
    cin>>row1>>col1;
    int row2, col2;
    cout<<"enter rows and columns of matrix-2: ";
    cin>>row2>>col2;
    if(col1!=row2){
        //as if col1 is not equal to row2 then this signifies the multiplication opreation can not be performed
        cout<<"not acceptable inputs";
    }
    int mat1[row1][col1];
    for(int i = 0; i < row1; i++) {
        for (int j = 0; j < col1; j++) {
            cout<<"\n mat1["<<i<<"]["<<j<<"] : ";
            cin>>mat1[i][j];
        }
    }


    int mat2[row2][col2];
    for(int i = 0; i < row2; i++) {
        for (int j = 0; j < col2; j++) {
            cout<<"\n mat2["<<i<<"]["<<j<<"] : ";
            cin>>mat2[i][j];
        }
    }

    int ans[row1][col2];
    for(int i = 0; i < row1; i++) {
        for(int j = 0; j < col2; j++) {
            for (int k = 0; k < col1; k++) {
                if(k==0){
                    ans[i][j]=0;
                }
                ans[i][j]+=mat1[i][k]*mat2[k][j];
            }
        }
    }
    
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col2; j++) {
            cout<<ans[i][j]<<" ";
        }cout<<endl;
    }
    return 0;
}