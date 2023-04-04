#include <iostream>

int main(){
    int i;
    std::cin >> i;
    if ((i > 0) && ((i & (i - 1)) == 0))
        std::cout << "Yes";
    else
        std::cout << "No";
}