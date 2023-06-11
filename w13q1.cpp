#include <iostream>
#include <cmath>
#include <string>

using namespace std;

class board{
private:
    bool*** perms;
    int size;
public:
    board(int s){
        size = s;
        perms = new bool**[4];
        for (int i = 0; i < 4; i++){
            perms[i] = new bool*[size];
            for (int j = 0; j < size; j++){
                perms[i][j] = new bool[size];
                for (int k = 0; k < size; k++){
                    perms[i][j][k] = false;
                }
            }
        }
    }

    void print(int a){
        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++){
                cout << perms[a][i][j];
            }
            cout << endl;
        }
    }

    void set(int x, int y, bool val){
        perms[0][x][y] = val;
        perms[1][y][size - x - 1] = val;
        perms[2][size - x - 1][size - y - 1] = val;
        perms[3][size - y - 1][x] = val;
    }

    bool equals(board b){
        for (int i = 0; i < 4; i++){
            bool same = true;
            for (int j = 0; j < size; j++){
                for (int k = 0; k < size; k++){
                    if (perms[0][j][k] != b.perms[i][j][k]){
                        same = false;
                        break;
                    }
                }
                if (!same)
                    break;
            }
            if (same)
                return true;
        }
        return false;
    };
};


int main(){
    int s;
    while(true){
        cin >> s;
        if (s == 0)
            break;
        board* boards[2*s];
        for (int i = 0; i < 2*s; i++){
            boards[i] = new board(s);
        }
        int i = 0;
        bool draw = true;
        while (i < 2*s && draw){
            int x, y;
            char a;
            cin >> x >> y >> a;
            for (int j = i; j < 2*s; j++)
                boards[j]->set(x-1, y-1, a=='+');
            i++;
        }
        for (int i = 0; i < 2*s; i++){
            for (int j = 0; j < i; j++){
                if (boards[i]->equals(*boards[j])){
                    cout << "Player " << ((i+1)%2)+1 << " wins on move " << i+1 << endl;
                    draw = false;
                    break;
                }
            }
            if (!draw)
                break;
        }
        if (draw)
            cout << "Draw" << endl;
    }
}