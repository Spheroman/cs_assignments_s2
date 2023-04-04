#include <iostream>
#include <string>

std::string intToBin(int i, std::string s){
    s = std::to_string((i & 1)).append(s);
    i >>= 1;
    if (i == 0)
        return s;
    else
        return intToBin(i, s);
}


int main(){
    int i;
    std::cin >> i;
    std::cout << intToBin(i, "");
}
