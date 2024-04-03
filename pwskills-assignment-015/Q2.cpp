// Q2. Write a program to find the product of 2 numbers using pointers
//     Input1:
//     3 10
//     output1:
//     30
//     Input2:
//     6 80
//     Output2:
//     480

#include <iostream>

using namespace std;
int main() {
  int x, y;
  cout << "enter integer x: ";
  cin >> x;
  cout << "enter integer y: ";
  cin >> y;

  int * ptrx = & x, * ptry = & y;
  cout << ( * ptrx) * ( * ptry);

}