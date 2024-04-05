// Q40. Remove all the occurrences of 'a' from strings
//     s="abcax"
#include <iostream>
using namespace std;
string rF(string &s, int idx, int n)
{
    if (idx == n)
        return "";
    string curr = "";
    curr += s[idx];
    return ((s[idx] == 'a') ? "" : curr) + rF(s, idx + 1, n);
}
int main()
{
    string s = "abcax";
    int n = 5;
    cout << rF(s, 0, n);
    return 0;
}