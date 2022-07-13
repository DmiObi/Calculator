#include "Complex.hpp"
#include <math.h>

// used for checking if an object is Complex or not
template<typename Base, typename T>
inline bool instanceof(const T* v) {
    return dynamic_cast<const Base*>(v) != nullptr;
}

Complex::Complex(double real, double imag) : Real(real)
{
    imagNum = imag;
    
}

double Complex::getImageryNum() const
{
    return imagNum;
}

void Complex::setImageryNum(double newImagNum)
{
    imagNum = newImagNum;
}

// Used for comparing a complex number and a real number
double Complex::findMagnitude() const
{
    return sqrt(pow(getRealNum(), 2) + pow(getImageryNum(), 2));
}

Complex Complex::operator+(const Real &num) const
{
    double newReal = 0;
    double newImag = 0;
    
    // Complex + Complex
    if (instanceof<Complex>(&num))
    {
        const Complex comp = (const Complex&) num;
        newReal = getRealNum() + comp.getRealNum();
        newImag = getImageryNum() + comp.getImageryNum();
    }
    else // Complex + Real
    {
        newReal = getRealNum() + num.getRealNum();
        newImag = getImageryNum();
    }
        
    return Complex(newReal, newImag);
}

Complex Complex::operator-(const Real &num) const
{
    double newReal = 0;
    double newImag = 0;
    
    // Complex - Complex
    if (instanceof<Complex>(&num))
    {
        const Complex comp = (const Complex&) num;
        newReal = getRealNum() - comp.getRealNum();
        newImag = getImageryNum() - comp.getImageryNum();
    }
    else // Complex - Real
    {
        newReal = num.getRealNum() - num.getRealNum();
        newImag = getImageryNum();
    }
        
    return Complex(newReal, newImag);
}

Complex Complex::operator*(const Real &num) const
{
    double newReal = 0;
    double newImag = 0;
    
    // Complex * Complex
    if (instanceof<Complex>(&num))
    {
        const Complex comp = (const Complex&) num;
        
        // Formula: (a + bi) * (c + di) = (ac - bd) + (ad + bc)
        double a = getRealNum();
        double b = getImageryNum();
        double c = comp.getRealNum();
        double d = comp.getImageryNum();
    
        newReal = a * c - b * d;
        newImag = a * d + b * c;
    }
    // Complex * Real
    else
    {
        newReal = getRealNum() * num.getRealNum();
        newImag = getImageryNum() * num.getRealNum();
    }
        
    return Complex(newReal, newImag);
}

Complex Complex::operator/(const Real &num) const
{
    double newReal = 0;
    double newImag = 0;
    
    // Complex / Complex
    if (instanceof<Complex>(&num))
    {
        const Complex comp = (const Complex&) num;
        
        // Formula: (a*c + bd) / (c^2 + d^2) + (bc - ad) / (c^2 + d^2) i
        double a = getRealNum();
        double b = getImageryNum();
        double c = comp.getRealNum();
        double d = comp.getImageryNum();
        
        newReal = (a * c + b * d) / (pow(c, 2) + pow(d, 2));
        newImag = (b * c - a * d) / (pow(c, 2) + pow(d, 2));
    }
    // Complex / Real
    else
    {
        newReal = getRealNum() / num.getRealNum();
        newImag = getImageryNum() / num.getRealNum();
    }
        
    return Complex(newReal, newImag);
}

bool Complex::operator<(const Real &num) const
{
    // Complex < Complex
    if (instanceof<Complex>(&num))
        return findMagnitude() < ((const Complex&)num).findMagnitude();
    else // Complex < Real
        return findMagnitude() < num.getRealNum();
}

bool Complex::operator>(const Real &num) const
{
    // Complex > Complex
    if (instanceof<Complex>(&num))
        return findMagnitude() > ((const Complex&)num).findMagnitude();
    else // Complex > Real
        return findMagnitude() > num.getRealNum();
}

bool Complex::operator==(const Real &num) const
{
    // Complex == Complex
    if (instanceof<Complex>(&num))
    {
        const Complex comp = (const Complex&) num;
        return getRealNum() == comp.getRealNum() &&
               getImageryNum() == comp.getImageryNum();
    }
    else // Complex == Real
        return findMagnitude() == num.getRealNum();
}

ostream& operator<<(ostream &out, const Complex num)
{
    // If real number is 0, it's not printed
    if (num.getRealNum() == 0)
    {
        out << num.getImageryNum() << "i" << endl;
    }
    else
    {
        // If real and imag are 0, then just 0 is printed
        if (num.getRealNum() == 0 && num.getImageryNum() == 0)
        {
            out << 0;
        }
        // If imagery number is 0, then only real number is printed
        else if (num.getImageryNum() == 0)
        {
            cout << num.getRealNum() << endl;
        }
        // If real number is 0, then imagery number is printed
        else if (num.getRealNum() == 0)
        {
            cout << num.getImageryNum();
        }
        else
        {
            // Prints both the real number and the imagery number
            if (num.getImageryNum() < 0)
            {
                out << num.getRealNum() << num.getImageryNum() << "i" << endl;
            }
            else
            {
                // adds + in the console between 2 numbers
                out << num.getRealNum() << "+" << num.getImageryNum() << "i" << endl;
            }
        }
    }
    
    return out;
}

// Gets a Comlex number and asks user for new real and imag numbers
istream& operator>>(istream &in, Complex &num)
{
    double real;
    double imag;
    
    in >> real;
    in >> imag;
    
    num.setRealNum(real);
    num.setImageryNum(imag);
    
    return in;
}
