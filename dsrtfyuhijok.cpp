#include <string>

class PokerCard
{
public:
    PokerCard(std::string s, int f)
    {
        suit = s;
        face = f;
    }

    std::ostream& operator<<(std::ostream &out, const PokerCard &p)
    {
        out<<"["<<p.getFace()<<" of "<<p.getSuit()<<"]";
        return out;
    }

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