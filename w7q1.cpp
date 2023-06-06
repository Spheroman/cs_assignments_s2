#include <iostream>
#include <string>
using namespace std;

class Date {
private:
    char date[8]{};
    string month[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct",
                        "Nov", "Dec"};
public:
    void set_year(int in){
        this->date[0] = in / 1000 % 10 + '0';
        this->date[1] = in / 100 % 10 + '0';
        this->date[2] = in / 10 % 10 + '0';
        this->date[3] = in % 10 + '0';
    }
    void set_month(int in){
        this->date[4] = in / 10 % 10 + '0';
        this->date[5] = in % 10 + '0';
    }
    void set_day(int in){
        this->date[6] = in / 10 % 10 + '0';
        this->date[7] = in % 10 + '0';
    }
    int get_year() const{
        return (this->date[0] - '0') * 1000 + (this->date[1] - '0') * 100 + (this->date[2] - '0') * 10 + (this->date[3] - '0');
    }
    int get_month() const{
        return (this->date[4] - '0') * 10 + (this->date[5] - '0');
    }
    int get_day() const{
        return (this->date[6] - '0') * 10 + (this->date[7] - '0');
    }
    void print_date() const{
        cout << this->month[this->get_month() - 1] << " " << this->get_day() << ", " << this->get_year();
    }
};