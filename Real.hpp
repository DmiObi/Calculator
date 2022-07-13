#ifndef Real_hpp
#define Real_hpp
#include <iostream>

using namespace std;

class Real
{
private:
    double realNum;
    
public:
    Real(double realNum);
    
    virtual ~Real() {};
    
    double getRealNum() const;
        
    void setRealNum(double newRealNum);
    
    Real operator+(const Real &num) const;
        
    Real operator-(const Real &num) const;

    Real operator*(const Real &num) const;
    
    Real operator/(const Real &num) const;
    
    virtual bool operator<(const Real &num) const;
    
    virtual bool operator>(const Real &num) const;
    
    virtual bool operator==(const Real &num) const;
    
    friend ostream& operator<<(ostream &out, const Real num); // For printing

    friend istream& operator>>(istream &in, Real num); // For inserting
};

#endif
