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
    virtual bool output() { return true ; }
    void setValue(Gate *, int) {}
    void setValue(bool, int) {}
} ;

class FALSE : public Gate
{
public :
    virtual bool output() { return false ; }
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
private :
    Gate *component[2] ;
} ;

class OR : public Gate
{
public :
    OR() : Gate() {}
    virtual bool output() { return this -> input[0] -> output() || this -> input[1] -> output() ;}
private :
    Gate *component[2] ;
} ;

class XOR : public Gate
{
public :
    XOR() : Gate() {}
    virtual bool output() { return this -> input[0] -> output() ^ this -> input[1] -> output() ;}
private :
    Gate *component[2] ;
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
    Gate *component[2]{} ;
} ;

class OneBitFullAdder : public Adder
{
public :
    OneBitFullAdder() {
        a[0] = new OneBitHalfAdder() ;
        a[1] = new OneBitHalfAdder() ;
        carry = new OR() ;
    }
    virtual void setValue(bool val, int pin) {
        if (pin == 2) a[1] -> setValue(val, 1) ; //b
        else a[0] -> setValue(val, pin) ;
    }
    virtual void setValue(Gate *gate, int pin) {
        if (pin == 2) a[1] -> setValue(gate, 1) ; //b
        else a[0] -> setValue(gate, pin) ;
    }
    virtual Gate *sum() {
        a[1] -> setValue(a[0] -> sum(), 0) ; //a
        return a[1] -> sum() ;
    }
    virtual Gate *carryOut() {
        a[1] -> setValue(a[0] -> sum(), 0) ; //a
        carry -> setValue(a[0] -> carryOut(), 0) ; //a
        carry -> setValue(a[1] -> carryOut(), 1) ; //b
        return carry;
    }
private :
    Adder *a[2] ;
    Gate *carry = &f;
} ;