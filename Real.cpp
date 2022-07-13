#include "Real.hpp"

template<typename Base, typename T>
inline bool instanceof(const T*) {
   return is_base_of<Base, T>::value;
}

Real::Real(double num)
{
    realNum = num;
}

double Real::getRealNum() const
{
    return realNum;
}

void Real::setRealNum(double newRealNum)
{
    realNum = newRealNum;
}

Real Real::operator+(const Real &num) const
{
    return Real(getRealNum() + num.getRealNum());
}

Real Real::operator-(const Real &num) const
{
    return Real(getRealNum() - num.getRealNum());
}

Real Real::operator*(const Real &num) const
{
    
    return Real(getRealNum() * num.getRealNum());
}

Real Real::operator/(const Real &num) const
{
    return Real(getRealNum() / num.getRealNum());
}

bool Real::operator<(const Real &num) const
{
    return getRealNum() < num.getRealNum();
}

bool Real::operator>(const Real &num) const
{
    return getRealNum() > num.getRealNum();
}

bool Real::operator==(const Real &num) const
{
    return getRealNum() == num.getRealNum();
}

// For printing objects
ostream& operator<<(ostream &out, const Real num)
{
    out << num.getRealNum() << endl;
    
    return out;
}

// For inserting values into objects
istream& operator>>(istream &in, Real num)
{
    double real;
    in >> real;
    num.setRealNum(real);
    
    return in;
}
