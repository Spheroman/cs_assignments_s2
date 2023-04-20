#include <iostream>

using namespace std;

class Gate
{
public :
    Gate *input[2] ;
    virtual bool output() = 0 ;
    void setValue(Gate *, int) ;
    void setValue(bool, int) ;
} ;

class TRUE : public Gate
{
public :
    virtual bool output() { return 1 ; }
    void setValue(Gate *, int) {}
    void setValue(bool, int) {}
} ;

class FALSE : public Gate
{
public :
    virtual bool output() { return 0 ; }
    void setValue(Gate *, int) {}
    void setValue(bool, int) {}
} ;

TRUE t ;
FALSE f ;

void Gate::setValue(bool val, int pin)
{
    if(val) this -> input[pin] = &t ;
    else this -> input[pin] = &f ;
}

void Gate::setValue(Gate *gate, int pin) { this -> input[pin] = gate ; }

class NOT : public Gate
{
public :
    virtual bool output() { return !(this -> input[0] -> output()) ; }
    void setValue(bool val, int pin = 0)
    {
        if(val) this -> input[0] = &t ;
        else this -> input[0] = &f ;
    }
    void setValue(Gate* gate, int pin = 0) { this -> input[0] = gate ; }
} ;

class NAND : public Gate
{
public :
    virtual bool output() { return !(this -> input[0] -> output()) || !(this -> input[1] -> output()) ; }
} ;

class NOR : public Gate
{
public :
    virtual bool output() { return !(this -> input[0] -> output()) && !(this -> input[1] -> output()) ; }
} ;

class AND : public Gate
{
public :
    AND() : Gate() {}
    virtual bool output() { return this -> input[0] -> output() && this -> input[1] -> output() ;}
} ;

class OR : public Gate
{
public :
    OR() : Gate() {}
    virtual bool output() { return this -> input[0] -> output() || this -> input[1] -> output() ;}
} ;

class XOR : public Gate
{
public :
    XOR() : Gate() {}
    virtual bool output() { return this -> input[0] -> output() ^   this -> input[1] -> output() ;}
} ;

class Adder
{
public :
    virtual void setValue(bool, int) = 0 ;
    virtual void setValue(Gate *, int) = 0 ;
    virtual Gate *sum() = 0 ;
    virtual Gate *carryOut() = 0 ;
} ;

class OneBitHalfAdder : public Adder
{
public :
    OneBitHalfAdder() {
        component[0] = new XOR();
        component[1] = new AND();
    }
    virtual void setValue(bool val, int pin) {
        component[0] -> setValue(val, pin);
        component[1] -> setValue(val, pin);
    }
    virtual void setValue(Gate *gate, int pin) {
        component[0] -> setValue(gate, pin);
        component[1] -> setValue(gate, pin);
    }
    virtual Gate *sum() {
        return component[0];
    }
    virtual Gate *carryOut() {
        return component[1];
    }
private :
    Gate *component[2] ;
} ;

class OneBitFullAdder : public Adder
{
public :
    OneBitFullAdder() {
        a[0] = new OneBitHalfAdder() ;
        a[1] = new OneBitHalfAdder() ;
        carry = new OR() ;
        a[1] -> setValue(&f, 1) ;
    }
    virtual void setValue(bool val, int pin) {
        //cout << "pin = " << pin << " with val " << val <<endl;
        if (pin == 2) a[1] -> setValue(val, 1) ;
        else a[0] -> setValue(val, pin) ;
    }
    virtual void setValue(Gate *gate, int pin) {
        if (pin == 2) a[1] -> setValue(gate, 1) ;
        else a[0] -> setValue(gate, pin) ;
    }
    virtual Gate *sum() {
        a[1] -> setValue(a[0] -> sum(), 0) ;
        return a[1] -> sum() ;
    }
    virtual Gate *carryOut() {
        a[1] -> setValue(a[0] -> sum(), 0) ;
        //cout << "a[0] -> sum() = " << a[0] -> sum() -> output() << endl;
        carry -> setValue(a[0] -> carryOut(), 0) ;
        //cout << "a[0] -> carryOut() = " << a[0] -> carryOut() -> output() << endl;
        carry -> setValue(a[1] -> carryOut(), 1) ;
        //cout << "a[1] -> carryOut() = " << a[1] -> carryOut() -> output() << endl;
        return carry;
    }
private :

    Adder *a[2] ;
    Gate *carry = &f;
} ;

class Decoder {
public :
    virtual void setValue(bool, int) = 0;

    virtual void setValue(Gate *, int) = 0;

    virtual void setEnable(bool) = 0;

    virtual void setEnable(Gate *) = 0;

    virtual int output() = 0;

    virtual Gate *operator[](int) = 0;

protected :
    Gate *enable;
};

class Decoder2_4 : public Decoder {
public :
    Decoder2_4() : Decoder2_4(0) {}

    Decoder2_4(bool val) {
        if (val) this->enable = &t;
        else this->enable = &f;
        for (int i = 0; i < 2; i++)
            component[i] = new NOT;
        for (int i = 2; i < 6; i++)
            component[i] = new AND;
        for (int i = 0; i < 4; i++)
            enables[i] = new AND;
    }

    virtual void setEnable(bool val) {
        if (val) this->enable = &t;
        else this->enable = &f;
    }

    virtual void setEnable(Gate *gate) { this->enable = gate; }

    virtual void setValue(Gate *gate, int i) { component[i % 2]->input[0] = gate; }

    virtual void setValue(bool val, int i) {
        if (val) component[i % 2]->input[0] = &t;
        else component[i % 2]->input[0] = &f;
    }

    virtual Gate *operator[](int n) {
        _out();
        switch (n) {
            case 0 :
                return enables[0];
            case 1 :
                return enables[1];
            case 2 :
                return enables[2];
            case 3 :
                return enables[3];
            default :
                return nullptr;
        }
    }

    friend ostream &operator<<(ostream &out, Decoder2_4 dec) {
        for (int i = 3; i >= 0; i--)
            out << dec[i]->output() << " ";
        return out;
    }

    virtual int output() {
        for (int i = 0; i < 4; i++)
            if (enables[i]->output()) return i;
    }

private :
    Gate *component[6];
    Gate *enables[4];

    void _out() {
        component[2]->input[0] = component[0];
        component[2]->input[1] = component[1];

        component[3]->input[0] = component[0]->input[0];
        component[3]->input[1] = component[1];

        component[4]->input[0] = component[0];
        component[4]->input[1] = component[1]->input[0];

        component[5]->input[0] = component[0]->input[0];
        component[5]->input[1] = component[1]->input[0];

        for (int i = 0; i < 4; i++) {
            enables[i]->input[0] = this->enable;
            enables[i]->input[1] = component[i + 2];
        }
    }
};

class Decoder4_16 : public Decoder {
public :
    Decoder4_16() {
        for (int i = 0; i < 5; i++)
            dec2_4[i] = new Decoder2_4;
    }

    Decoder4_16(bool val) {
        for (int i = 0; i < 5; i++)
            dec2_4[i] = new Decoder2_4(val);
        if (val) enable = &t;
        else enable = &f;
    }

    virtual void setEnable(bool val) {
        if (val) enable = &t;
        else enable = &f;
    }

    virtual void setEnable(Gate *gate) {
        enable = gate;
    }

    virtual void setValue(bool val, int pin) {
        if (pin == 0 || pin == 1) {
            dec2_4[0]->setValue(val, pin);
            dec2_4[1]->setValue(val, pin);
            dec2_4[2]->setValue(val, pin);
            dec2_4[3]->setValue(val, pin);
        } else dec2_4[4]->setValue(val, pin - 2);
    }

    virtual void setValue(Gate *gate, int pin) {
        if (pin == 0 || pin == 1) {
            dec2_4[0]->setValue(gate, pin);
            dec2_4[1]->setValue(gate, pin);
            dec2_4[2]->setValue(gate, pin);
            dec2_4[3]->setValue(gate, pin);
        } else dec2_4[4]->setValue(gate, pin - 2);
    }

    virtual Gate *operator[](int n) {
        if (!enable->output()) return &f;
        _update();
        return dec2_4[n / 4]->operator[](n % 4);
    }

    friend ostream &operator<<(ostream &out, Decoder4_16 dec) {
        for (int i = 15; i >= 0; i--) {
            out << dec[i]->output() << " ";

        }
        return out;
    }

    int output() {
        _update();
        for (int i = 0; i < 16; i++)
            if (dec2_4[i / 4]->operator[](i % 4)->output()) return enable->output() ? i : 0;
    }

private :
    void _update() {
        for (int i = 0; i < 4; i++) {
            dec2_4[i]->setEnable(dec2_4[4]->operator[](i));
        }
    }

    Decoder *dec2_4[5];
};

class Decoder5_32 : public Decoder {
public :
    Decoder5_32() {
        dec4_16 = new Decoder4_16(&t);
        for (int i = 0; i < 5; i++)
            dec4_16->setValue(&f, i);
    }

    Decoder5_32(bool val) {
        dec4_16 = new Decoder4_16(val);
        if (val) enable = &t;
        else enable = &f;
    }

    virtual void setEnable(bool val) {
        if (val) enable = &t;
        else enable = &f;
    }

    virtual void setEnable(Gate *gate) {
        enable = gate;
    }

    virtual void setValue(bool val, int pin) {
        if (pin == 0 || pin == 1 || pin == 2 || pin == 3) dec4_16->setValue(val, pin);
        else if (val) carry = &t;
        else carry = &f;
    }

    virtual void setValue(Gate *gate, int pin) {
        if (pin == 0 || pin == 1 || pin == 2 || pin == 3) {
            dec4_16->setValue(gate, pin);
        } else carry=gate;
    }

    virtual Gate *operator[](int n) {
        if (n < 16 && !carry->output()) return dec4_16->operator[](n);
        if (n >= 16 && carry->output()) return dec4_16->operator[](n-16);
        else return &f;
    }

    friend ostream &operator<<(ostream &out, Decoder5_32 dec) {
        for (int i = 31; i >= 0; i--) {
            out << dec[i]->output() << " ";
        }
        return out;
    }

    int output() {
        for (int i = 0; i < 32; i++)
            if (operator[](i)->output()) return i;
    }

private :
    Decoder *dec4_16;
    Gate* carry;
};

class FourBitsRippleAdder : public Adder {
public :
    FourBitsRippleAdder() {
        for (int i = 0; i < 4; i++) {
            a[i] = new OneBitFullAdder();
        }
        a[0]->setValue(&f, 2);
    }

    virtual void setValue(bool val, int pin) {
        //cout << "setValue on pin " << pin % 2 << " on adder " << pin / 2 << " as " << val << endl;
        a[pin / 2]->setValue(val, pin % 2);
    }

    virtual void setValue(Gate *gate, int pin) {
        //cout << "setValue on pin" << pin % 2 << " on adder " << pin / 2 << " as " << gate->output() << endl;
        a[pin / 2]->setValue(gate, pin % 2);
    }

    virtual Gate *sum() {
        //cout << "sum" << endl;
        _update();
        return a[3]->sum();
    }

    virtual Gate *carryOut() {
        //cout << "carryOut" << endl;
        _update();
        return a[3]->carryOut();
    }

    void print() {
        cout << "print" << endl;
        _update();
        for (int i = 4; i >= 0; i--) {
            cout << this->operator[](i)->output() << " ";
        }
        cout << endl;
    }

    virtual Gate *operator[](int n) {
        _update();
        if (n == 4) return a[3]->carryOut();
        else return a[n]->sum();
    }

private :
    void _update() {
        for (int i = 0; i < 3; i++) {
            //cout << "adder " << i << " with carry " << a[i] -> carryOut() -> output() << " and sum " << a[i] -> sum() -> output() << endl;
            a[i + 1]->setValue(a[i]->carryOut(), 2);
        }
    }

    Adder *a[4];
};

class Mux
{
public :
    virtual void setData(bool, int) = 0 ;
    virtual void setData(Gate *, int) = 0 ;
    virtual void setSelect(bool, int) = 0 ;
    virtual void setSelect(Gate *, int) = 0 ;
    virtual void setEnable(bool) = 0 ;
    virtual void setEnable(Gate *) = 0 ;
    virtual Gate *output() = 0 ;
protected :
    Gate *enable ;
} ;

class Mux2_1 : public Mux
{
public :
    Mux2_1() : Mux2_1(0) {}
    Mux2_1(bool val)
    {
        if(val) this -> enable = &t ;
        else this -> enable = &f ;
        component[0] = new AND ;
        component[1] = new AND ;
        component[2] = new NOT ;
        component[3] = new OR ;
        component[4] = new AND ;
    }
    virtual void setData(bool val, int pin)
    {
        switch(pin)
        {
            case 0 : component[0] -> setValue(val, 0) ; break ;
            case 1 : component[1] -> setValue(val, 0) ; break ;
            default : ;
        }
    }
    virtual void setData(Gate *gate, int pin)
    {
        switch(pin)
        {
            case 0 : component[0] -> setValue(gate, 0) ; break ;
            case 1 : component[1] -> setValue(gate, 0) ; break ;
            default : ;
        }
    }
    virtual void setEnable(bool val)
    {
        if(val) this -> enable = &t ;
        else this -> enable = &f ;
    }
    virtual void setEnable(Gate *gate)
    {
        this -> enable = gate ;
    }
    virtual void setSelect(bool val, int pin = 0)
    {
        component[1] -> setValue(val, 1) ;
        component[2] -> setValue(val, 0) ;
        component[0] -> input[1] = component[2] ;
    }
    virtual void setSelect(Gate *gate, int pin = 0)
    {
        component[1] -> setValue(gate, 1) ;
        component[2] -> setValue(gate, 0) ;
        component[0] -> input[1] = component[2] ;
    }
    virtual Gate *output()
    {
        component[3] -> setValue(component[0], 0) ;
        component[3] -> setValue(component[1], 1) ;
        component[4] -> setValue(this -> enable, 0) ;
        component[4] -> setValue(component[3], 1) ;
        return component[4] ;
    }
private :
    Gate *component[5] ;
} ;

class Mux4_1 : public Mux
{
public :
    Mux4_1() : Mux4_1(0) {}
    Mux4_1(bool val) {
        if (val)
            this->enable = &t;
        else
            this->enable = &f;
        mux2_1[0] = new Mux2_1(val);
        mux2_1[1] = new Mux2_1(val);
        component[0] = new AND;
        component[1] = new OR;
        component[2] = new AND;
    }
    virtual void setData(bool val, int pin) {
        mux2_1[pin % 2]->setData(val, pin / 2);
    }
    virtual void setData(Gate *gate, int pin) {
        mux2_1[pin % 2]->setData(gate, pin / 2);
    }
    virtual void setSelect(bool val, int pin) {
        if (!pin){
            mux2_1[0]->setEnable(!val);
            mux2_1[1]->setEnable(val);
        }
        else{
            mux2_1[0]->setSelect(val, 0);
            mux2_1[1]->setSelect(val, 0);
        }
    }
    virtual void setSelect(Gate *gate, int pin) {
        if (gate == &t)
            this->setSelect(true, pin);
        else
            this->setSelect(false, pin);
    }
    virtual void setEnable(bool val) {
        if(val) this -> enable = &t ;
        else this -> enable = &f ;
        mux2_1[0]->setEnable(val);
        mux2_1[1]->setEnable(val);
    }
    virtual void setEnable(Gate *gate) {
        this -> enable = gate ;
        mux2_1[0]->setEnable(gate);
        mux2_1[1]->setEnable(gate);
    }
    virtual Gate *output() {
        component[1]->setValue(mux2_1[0]->output(), 0);
        component[1]->setValue(mux2_1[1]->output(), 1);
        component[2]->setValue(this->enable, 0);
        component[2]->setValue(component[1], 1);
        return component[2];
    }
private :
    Mux *mux2_1[2] ;
    Gate *component[3] ;
    bool select;
} ;
