// Q36. Given 2 no. p & q, find the value of p^q using recursive function
#include <iostream>
using namespace std;
int rF(int p, int q)
{
    if (q == 0)
    {
        return 1;
    }
    return rF(p, q - 1) * p;
}
int main()
{
    int p, q;
    cout << "Enter p & q: ";
    cin >> p >> q;
    int result = rF(p, q);
    cout << result;
    return 0;
}