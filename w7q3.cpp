class PokerCard
{
public:
    PokerCard(std::string s, int f)
    {
        suit = s;
        face = f;
    }
    friend std::ostream &operator<<(std::ostream &out, const PokerCard &p)
    {
        out<<"["<<p.face<<" of "<<p.suit<<"]";
        return out;
    }

    //Please finish the comparison operator override
    //compare face first, if the same then compare suit 
    //請完成比較運算子多載
    //先比較 face ， face 一樣再比較 suit
    //1 > 13 > 12 > 11 > 10 > 9 > 8 > 7 > 6 > 5 > 4 > 3 > 2
    //spade > heart > diamond > club

    std::string getSuit() const
    {
        return suit;
    }

    int getFace() const
    {
        return face;
    }

    bool operator>(const PokerCard& b) const
    {
        if (face == b.face)
            return suit > b.suit;
        else
        if (face == 1)
            return true;
        else if (b.face == 1)
            return false;
        else
            return (face > b.face);
    }

    bool operator<(const PokerCard& b) const
    {
        if (face == b.face)
            return suit < b.suit;
        else
        if (face == 1)
            return false;
        else if (b.face == 1)
            return true;
        else
            return (face < b.face);
    }

    bool operator==(const PokerCard& b) const
    {
        return suit == b.suit && face == b.face;
    }

private:
    std::string suit;
    int face;
};