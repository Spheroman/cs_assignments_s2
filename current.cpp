#include <iostream>
#include <string>
using namespace std;

class variable{
    public:
    bool val = true;
    char name = 0;
    bool checkname(char check){
        return this->name == check;
    }
};

class operation{
    public:
    char op;
    operation* left = nullptr;
    operation* right = nullptr;
    int priority = 0;
    variable* var = nullptr;
    operation(char op){
        this->op = op;
        if (op == '&'){
            this->priority = 2;
        }
        else if (op == '|'){
            this->priority = 3;
        }
    }
    operation(variable* var, bool op){
        this->var = var;
        if (op){
            this->op = '!';
        }
        else{
            this->op = ' ';
        }
        this->priority = 1;
    }
    operation* add_to_heap(operation* in){
        if (in == nullptr){
            return this;
        }
        if (in->priority <= this->priority){
            if (this->left == nullptr){
                this->left = in;
                return this;
            }
            if (this->right == nullptr){
                this->right = in;
                return this;
            }
            if (this->left->priority < in->priority){
                this->left = in->add_to_heap(this->left);
                return this;
            }
            else{
                this->right = in->add_to_heap(this->right);
                return this;
            }

        }
        else{
            return in->add_to_heap(this);
        }
    }
    bool doops(){
        if (this->op == '!'){
            return !this->var->val;
        }
        else if (this->op == ' '){
            return this->var->val;
        }
        else if (this->op == '&'){
            return this->left->doops() && this->right->doops();
        }
        else if (this->op == '|'){
            return this->left->doops() || this->right->doops();
        }
        return false;
    }

    void printheap(){
        if (this->op == '!'){
            cout << "!" << this->var->name;
        }
        else if (this->op == ' '){
            cout << this->var->name;
        }
        else if (this->op == '&'){
            cout << "(";
            this->left->printheap();
            cout << "&";
            this->right->printheap();
            cout << ")";
        }
        else if (this->op == '|'){
            cout << "(";
            this->left->printheap();
            cout << "||";
            this->right->printheap();
            cout << ")";
        }
    }
};

int get_var_idx(variable* var, int varnum, char name){
    for (int i = 0; i < varnum; i++){
        if (var[i].checkname(name)){
            return i;
        }
    }
    return -1;
}

void print_bar(int num){
    cout << "+";
    for (int i = 0; i < num; i++){
        cout << "-";
    }
    cout << "+" << endl;
}

class equation{
    public:
    int varnum, numin = 0;
    variable* var;
    operation* op = nullptr;
    operation* last = nullptr;
    variable* buffer = nullptr;
    char bufferop = '&';
    bool notflag = false;
    string in = "";
    equation(string in, int varnum){
        this->varnum = varnum;
        this->var = new variable[varnum];
        this->in = in;
        int i;
        for (i = in.length()-1; in[i] != '=' && i >= 0; i--){
            if (in[i] == ' '){
                continue;
            }
            else if (in[i] == '\''){
                notflag = !notflag;
            }
            else if (in[i] == '+'){
                bufferop = '|';
            }
            else if (in[i] >= 'A' && in[i] <= 'Z'){
                int idx = get_var_idx(this->var, this->varnum, in[i]);
                if (idx == -1){
                    var[this->numin].name = in[i];
                    this->numin++;
                    if (this->numin > varnum){
                        cout << "ERROR";
                        exit(0);
                    }
                }
                idx = get_var_idx(this->var, this->varnum, in[i]);
                if (buffer != nullptr){
                    op = (new operation(bufferop))->add_to_heap(op); //and or
                }
                op = (new operation(&var[idx], notflag))->add_to_heap(op); //not
                notflag = false;
                bufferop = '&';
                buffer = &var[idx];
            }
        }
        if (i < 0 || this->numin == 0 || get_var_idx(this->var, this->varnum, in[0]) != -1){
            cout << "ERROR";
            exit(0);
        }
        this->varnum = this->numin;
    }
    void print_truth_table(){
        for (int i = 0; i < this->varnum; i++){
            cout << this->var[i].name << " | ";
        }
        cout << "F" << endl;
        for (int i = 0; i < (1 << this->varnum); i++){
            for (int j = 0; j < this->varnum; j++){
                this->var[j].val = (i >> j) & 1;
                cout << this->var[j].val << " | ";
            }
            cout << this->op->doops() << endl;
        }
    }
    void print_truth_table_alphabetical() {
        int varorder[this->varnum];
        for (int i = 0; i < this->varnum; i++) {
            varorder[i] = i;
        }
        for (int i = 0; i < this->varnum - 1; i++) {
            for (int j = i + 1; j < this->varnum; j++) {
                if (this->var[varorder[i]].name < this->var[varorder[j]].name) {
                    swap(varorder[i], varorder[j]);
                }
            }
        }
        cout << "| ";
        for (int j = this->varnum - 1; j >= 0; j--) {
            cout << this->var[varorder[j]].name << " ";
        }
        cout << "| " << this->in[0] << " |" << endl;
        print_bar(2 * this->varnum + 5);
        for (int i = 0; i < (1 << this->varnum); i++) {
            cout << "| ";
            for (int j = this->varnum - 1; j >= 0; j--) {
                this->var[varorder[j]].val = (i >> j) & 1;
                cout << this->var[varorder[j]].val << " ";
            }
            cout << "| " << this->op->doops() << " |" << endl;
        }
    }
};


int main (){
    int varnum = 0;
    cin >> varnum;
    cin.ignore();
    string input;
    getline(cin, input);
    if (varnum < 1 || varnum > 26){
        cout << "ERROR";
        exit(0);
    }
    equation eq(input, varnum);
    print_bar(2*eq.varnum+5);
    eq.print_truth_table_alphabetical();
    print_bar(2*eq.varnum+5);
}
