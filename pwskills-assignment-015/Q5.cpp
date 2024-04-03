// Q5. Write a function that returns the first character, last character and the number of
//     occurrences of ‘t’ in a string input by user.
//     Input:
//     Output:
//     twitter
//     t r 3

#include <iostream>

using namespace std;

void operation(string s, char ch, char * ptrFirstChar, char * ptrLastChar, int * ptrCount) {
  for (int i = 0; i < s.size(); i++) {
    if (i == 0) {
      * ptrFirstChar = s[i];
    }
    if (i == s.size() - 1) {
      * ptrLastChar = s[i];
    }
    if (s[i] == ch) {
      * ptrCount = * ptrCount + 1;
    }

  }
}
int main() {
  string s = "twitter";
  char ch = 't';
  int count = 0;
  char firstChar;
  char lastChar;
  int * ptrCount = & count;
  char * ptrFirstChar = & firstChar;
  char * ptrLastChar = & lastChar;

  //call function
  operation(s, ch, ptrFirstChar, ptrLastChar, ptrCount);

  // Output

  cout << firstChar << " " << lastChar << " " << count << endl;

  return 0;
}