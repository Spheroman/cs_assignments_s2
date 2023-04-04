#include <iostream>
#include <string>

std::string decimalToRomanNumerals(int decimal){
    std::string romanNumeral;
    while (decimal > 0){
        if (decimal >= 1000){
            romanNumeral += "M";
            decimal -= 1000;
        }
        else if (decimal >= 900){
            romanNumeral += "CM";
            decimal -= 900;
        }
        else if (decimal >= 500){
            romanNumeral += "D";
            decimal -= 500;
        }
        else if (decimal >= 400){
            romanNumeral += "CD";
            decimal -= 400;
        }
        else if (decimal >= 100){
            romanNumeral += "C";
            decimal -= 100;
        }
        else if (decimal >= 90){
            romanNumeral += "XC";
            decimal -= 90;
        }
        else if (decimal >= 50){
            romanNumeral += "L";
            decimal -= 50;
        }
        else if (decimal >= 40){
            romanNumeral += "XL";
            decimal -= 40;
        }
        else if (decimal >= 10){
            romanNumeral += "X";
            decimal -= 10;
        }
        else if (decimal >= 9){
            romanNumeral += "IX";
            decimal -= 9;
        }
        else if (decimal >= 5){
            romanNumeral += "V";
            decimal -= 5;
        }
        else if (decimal >= 4){
            romanNumeral += "IV";
            decimal -= 4;
        }
        else {
            romanNumeral += "I";
            decimal -= 1;
        }
    }
    return romanNumeral;
}

int main(){
    int i;
    std::cin >> i;
    std::cout << decimalToRomanNumerals(i);
}

