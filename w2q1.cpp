#include <iostream>
#include <string>

int romanNumeralsToDecimal(std::string romanNumeral){
    int decimal = 0;
    for (int i = 0; i < romanNumeral.length(); i++){
        if (romanNumeral[i] == 'I'){
            if (romanNumeral[i + 1] == 'V'){
                decimal += 4;
                i++;
            }
            else if (romanNumeral[i + 1] == 'X'){
                decimal += 9;
                i++;
            }
            else
                decimal += 1;
        }
        else if (romanNumeral[i] == 'V')
            decimal += 5;
        else if (romanNumeral[i] == 'X'){
            if (romanNumeral[i + 1] == 'L'){
                decimal += 40;
                i++;
            }
            else if (romanNumeral[i + 1] == 'C'){
                decimal += 90;
                i++;
            }
            else
                decimal += 10;
        }
        else if (romanNumeral[i] == 'L')
            decimal += 50;
        else if (romanNumeral[i] == 'C'){
            if (romanNumeral[i + 1] == 'D'){
                decimal += 400;
                i++;
            }
            else if (romanNumeral[i + 1] == 'M'){
                decimal += 900;
                i++;
            }
            else
                decimal += 100;
        }
        else if (romanNumeral[i] == 'D')
            decimal += 500;
        else if (romanNumeral[i] == 'M')
            decimal += 1000;
    }
    return decimal;
}

int main(){
    std::string i;
    std::cin >> i;
    std::cout << romanNumeralsToDecimal(i);
}

