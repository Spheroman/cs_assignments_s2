#include <iostream>
#include <cmath>
#include <string>

using namespace std;

char key[26] = {'A', 0, 0, 0, '3', 0, 0, 'H', 'I', 'L', 0, 'J', 'M', 0, 'O', 0, 0, 0,  '2', 'T', 'U', 'V', 'W', 'X', 'Y', '5'};
char nums[9] = {'1', 'S', 'E', 0, 'Z', 0, 0, '8', 0};

int main(){
    string s;
    while(cin >> s){
        bool isPalindrome = true, isMirrored = true;
        int len = s.length();
        for(int i = 0; i < len / 2; i++){
            if (s[i] != s[len - i - 1]){
                isPalindrome = false;
                break;
            }
        }
        for(int i = 0; i < len / 2 + 1; i++){
            char c = s[i];
            if (c >= 'A' && c <= 'Z')
                c = key[c - 'A'];
            else
                c = nums[c - '1'];
            if (c == 0 || c != s[len - i - 1]){
                isMirrored = false;
                break;
            }
        }
        cout << s << " -- is ";
        if (!isPalindrome && !isMirrored)
            cout << "not a palindrome.";
        else if (isPalindrome && !isMirrored)
            cout << "a regular palindrome.";
        else if (!isPalindrome)
            cout << "a mirrored string.";
        else
            cout << "a mirrored palindrome.";
        cout << endl << endl;
        if (cin.eof())
            break;
    }
}