#include <iostream>
#include <string>
using namespace std ;

int main()
{
    int in;
    while (cin >> in) {
        if (!(in >= 1 && in <= 2147483647))
            break;

        int count = 0;
        string out;

        while (in != 0) {
            if (in % 2 == 1) {
                count++;
                out.insert(out.begin(), '1');
            } else {
                out.insert(out.begin(), '0');
            }
            in /= 2;
        }

        cout << "The parity of " << out << " is " << count << " (mod 2)." << endl;
    }
    return 0;
}