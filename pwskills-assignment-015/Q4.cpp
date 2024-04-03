// Q4. Implement the swap function using pointers.
//     Input:
//     Output:
//     35 23
//     23 35

#include <iostream>

using namespace std;
void swap(int * ptrX, int * ptrY) {
  int temp = * ptrX;
  * ptrX = * ptrY;
  * ptrY = temp;
}
int main() {
  int x, y;
  int * ptrX = & x, * ptrY = & y;
  // input
  cout << "enter integer x: ";
  cin >> x;
  cout << "enter integer y: ";
  cin >> y;

  // call swap function
  swap(ptrX, ptrY);

  //Output
  cout << "x: " << * ptrX << endl;
  cout << "y: " << * ptrY << endl;

  return 0;
}