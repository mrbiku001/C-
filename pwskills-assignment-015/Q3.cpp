// Q3. Write a function that returns the largest and the smallest number out of 3 given numbers.
//     The main function should call this function to get the largest and smallest number and print
//     the output.
//     Input: 3 4 10
//     Output: 10 3

#include <iostream>
using namespace std;
void
findSmallestAndLargest (int *ptrL, int *ptrS, int x, int y, int z)
{
  //findLargest
  if (x < y)
	{
	  if (z < y)
		{
		  *ptrL = y;
		}
	  else
		{
		  *ptrL = z;
		}
	}
  else
	{
	  if (z < x)
		{
		  *ptrL = x;
		}
	  else
		{
		  *ptrL = z;
		}
	}
  //findSmallest
  if (x < y)
	{
	  if (x < z)
		{
		  *ptrS = x;
		}
	  else
		{
		  *ptrS = z;
		}
	}
  else
	{
	  if (y < z)
		{
		  *ptrS = y;
		}
	  else
		{
		  *ptrS = z;
		}
	}
}

int main ()
{
  int x, y, z;
  int largest, smallest;
  int *ptrL = &largest, *ptrS = &smallest;
  cout << "enter integer x: ";
  cin >> x;
  cout << "enter integer y: ";
  cin >> y;
  cout << "enter integer z: ";
  cin >> z;

  findSmallestAndLargest (ptrL, ptrS, x, y, z);

  cout << "Largest: " << *ptrL << endl;
  cout << "Smallest: " << *ptrS << endl;
}
