#ifndef Complex_hpp
#define Complex_hpp

#include "Real.hpp"

class Complex : public Real
{
private:
    double imagNum;
    
public:
    Complex(double real, double imag);
    
    ~Complex(){};
    
    double getImageryNum() const;
    
    void setImageryNum(double newImagNum);
    
    double findMagnitude() const;
    
    Complex operator+(const Real &num) const;
    
    Complex operator-(const Real &num) const;

    Complex operator*(const Real &num) const;
    
    Complex operator/(const Real &num) const;
    
    bool operator<(const Real &num) const;
    
    bool operator>(const Real &num) const;
    
    bool operator==(const Real &num) const;
    
    friend ostream& operator<<(ostream &out, const Complex num); // for printing
    
    friend istream& operator>>(istream &in, Complex num); // for inserting
};

#endif
