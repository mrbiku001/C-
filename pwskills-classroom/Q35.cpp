// Q35. WAP to find sum of digits of number recursively.
//     ex. input 1234
//         output 10
#include <iostream>
using namespace std;
int rF(int n)
{
    if (n >= 0 && n <= 9)
    {
        return n;
    }
    return rF(n / 10) + n % 10;
}
int main(int argc, char const *argv[])
{
    int n;
    cout << "enter number: ";
    cin >> n;
    int result = rF(n);
    cout << result << endl;
    return 0;
}
