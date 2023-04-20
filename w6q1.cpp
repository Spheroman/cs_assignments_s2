#include <iostream>
#include <string>

using namespace std;

static string registers[8] = {"01000", "01001", "01010", "01011", "01100", "01101", "01110", "01111"};

string argParse(string args){
    string ret = "";
    int nums[3];
    int idx = 0;
    for(int i = 0; i < args.length(); i++){
        if(args[i] == '$'){
            nums [idx] = args[i+2] - '0';
            idx++;
        }
    }
    ret += registers[nums[1]];
    ret += registers[nums[2]];
    ret += registers[nums[0]];
    return ret;
}

string toBinary(unsigned int n){
    string r;
    while(n!=0) {r=(n%2==0 ?"0":"1")+r; n/=2;}
    while (r.length() < 16){
        r = "0" + r;
    }
    return r;
}

string addFun(string args){
    string ret = "000000";
    ret += argParse(args);
    ret += "00000100000";
    return ret;
}

string subFun(string args){
    string ret = "000000";
    ret += argParse(args);
    ret += "00000100010";
    return ret;
}

string orFun(string args){
    string ret = "000000";
    ret += argParse(args);
    ret += "00000100101";
    return ret;
}

string andFun(string args){
    string ret = "000000";
    ret += argParse(args);
    ret += "00000100100";
    return ret;
}

string addiFun(string args){
    string ret = "001000";
    string a, b;
    int idx = 0, num;
    while (args[idx] != '$') idx++;
    a = registers[args[idx+2] - '0'];
    idx ++;
    while (args[idx] != '$') idx++;
    b = registers[args[idx+2] - '0'];
    idx += 4;
    num = stoi(args.substr(idx));
    ret += a;
    ret += b;
    string bin = toBinary(num);
    ret += bin;
    return ret;
}
int main(){
    string input;
    while (getline(cin, input)){
        string op = input.substr(0, input.find(' '));
        string args = input.substr(input.find(' '));
        if (op == "add") cout << addFun(args) << endl;
        else if (op == "sub") cout << subFun(args) << endl;
        else if (op == "or") cout << orFun(args) << endl;
        else if (op == "and") cout << andFun(args) << endl;
        else if (op == "addi") cout << addiFun(args) << endl;
    }
    return 0;
}