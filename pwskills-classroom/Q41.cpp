// Q41. WAP to check whether a given number is palindrome or not through recursion.
#include <iostream>
using namespace std;
bool rF(int num, int *temp)
{
    if (num >= 0 && num <= 9)
    {
        int lastDigitOfTemp = (*temp) % 10;
        (*temp) /= 10;
        return (num == lastDigitOfTemp);
    }
    bool result = (rF(num / 10, temp) && (num % 10) == ((*temp) % 10));
    (*temp) /= 10;
    return result;
}
int main()
{
    int num;
    cout<<"Enter number to check: ";
    cin>>num;
    int anotherNum = num;
    int *temp = &anotherNum;
    cout << rF(num, temp);
    return 0;
}