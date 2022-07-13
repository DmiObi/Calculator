// Dmitrii Obideiko
//Net ID: DXO200006

#include <iostream>
#include <fstream>
#include <string>
#include "Real.hpp"
#include "Complex.hpp"

using namespace std;

enum Operation
{
    OP_INVALID, OP_PLUS, OP_MINUS, OP_MULT, OP_DIVIDE, OP_EQ, OP_LT, OP_GT
};

// Used for checking if an object is Complex or not
template<typename Base, typename T>
inline bool instanceof(const T* v) {
    return dynamic_cast<const Base*>(v) != nullptr;
}

// Looks for an operator in the string and initilizes its real number and imagery number
// startInd is the index of the first character in the string
// endInd is the index of last character in the string
static bool getNumber(string line, size_t startInd, size_t endInd, double &real, double &imag)
{
    bool hasDot = false;
    real = 0; imag = 0;
    
    for (size_t i = startInd; i <= endInd; i++)
    {
        const char symb = line.at(i);
        
        // Checks if the character is a digit
        if (isdigit(symb))
            continue;
        
        // Looks for a real number
        if (symb == '+' || symb == '-')
        {
            if (i > startInd)
            {
                real = stod(line.substr(startInd, i - startInd));
                startInd = i;
                hasDot = false;
            }
        }
        // Checks if an imagery number was found
        else if (symb == 'i')
        {
            if (i == endInd)
            {
                imag = stod(line.substr(startInd, i - startInd));
                return true;
            }
            else // Invalid format
                return false;
        }
        // Checks if there's 2 dots in a single number
        else if (symb == '.')
        {
            if (hasDot)
                return false;
            else
                hasDot = true;
        }
        // Checks if there're other characters besdies operations, i, digits, and .
        else if (symb != '.')
        {
            return false;
        }
    }
    
    // If a line only has a number, then the whole line is a real number
    real = stod(line.substr(startInd, endInd - startInd + 1));
    return true;
}

// Looks for an operation in a string and returns its type
static Operation getOpearation(string line)
{
    Operation oper = OP_INVALID;
 
    if (line.compare("+") == 0)
    {
        oper = OP_PLUS;
    }
    else if (line.compare("-") == 0)
    {
        oper = OP_MINUS;
    }
    else if (line.compare("*") == 0)
    {
        oper = OP_MULT;
    }
    else if (line.compare("/") == 0)
    {
        oper = OP_DIVIDE;
    }
    else if (line.compare("<") == 0)
    {
        oper = OP_LT;
    }
    else if (line.compare(">") == 0)
    {
        oper = OP_GT;
    }
    else if (line.compare("=") == 0)
    {
        oper = OP_EQ;
    }
    
    return oper;
}

// Parse single line from the file, initializes both operators, returns operation type
static Operation parseExpression(string line, double &r1, double &i1, double &r2, double &i2)
{
    Operation oper;
    
    size_t startInd = 0;
    size_t spaceIndex = line.find(' ');
    
    if (spaceIndex == string::npos)
        return OP_INVALID;

    // Finds the first operator
    if (!getNumber(line, startInd, spaceIndex - 1, r1, i1))
        return OP_INVALID;
    startInd = spaceIndex + 1;
    
    // Finds the operation
    spaceIndex = line.find(' ', startInd);
    
    // Checks if no space in the expression
    if (spaceIndex == string::npos)
        return OP_INVALID;
    
    // Get operation type
    oper = getOpearation(line.substr(startInd, spaceIndex - startInd));
    
    // Checks if there's no operation
    if (oper == OP_INVALID)
        return oper;
    startInd = spaceIndex + 1;
    
    // Finds the second operator
    if (!getNumber(line, startInd, line.size() - 1, r2, i2))
        return OP_INVALID;
    
    return oper;
}

// Craetes an object based on the real number and imagenery number
static Real* createObject(double r, double i)
{
    if (i == 0)
        return new Real(r);
    else
        return new Complex(r, i);
}

// If needed, casts the objects into Complex and adds them up
static void plusFunc(const Real* op1, const Real* op2)
{
    if (instanceof<Complex>(op1))
    {
        const Complex* cop1 = (const Complex*)op1;
        cout << *cop1 + *op2;
    }
    else if (instanceof<Complex>(op2))
    {
        const Complex* cop2 = (const Complex*)op2;
        cout << *cop2 + *op1;
    }
    else
    {
        cout << *op1 + *op2;
    }
}

// If needed, casts the objects into Complex and finds the difference between them
static void minusFunc(const Real* op1, const Real* op2)
{
    if (instanceof<Complex>(op1))
    {
        const Complex* cop1 = (const Complex*)op1;
        cout << *cop1 - *op2;
    }
    else if (instanceof<Complex>(op2))
    {
        Complex cop1(op1->getRealNum(), 0);
        cout << cop1 - *op2;
    }
    else
    {
        cout << *op1 - *op2;
    }
}

// If needed casts the objects into Complex and multiples them
static void multiplyFunc(const Real* op1, const Real* op2)
{
    if (instanceof<Complex>(op1))
    {
        const Complex* cop1 = (const Complex*)op1;
        cout << *cop1 * *op2;
    }
    else if (instanceof<Complex>(op2))
    {
        const Complex* cop2 = (const Complex*)op2;
        cout << *cop2 * *op1;
    }
    else
    {
        cout << *op1 * *op2;
    }
}

// If needed casts the objects into Complex and divides them
static void divideFunc(const Real* op1, const Real* op2)
{
    if (instanceof<Complex>(op1))
    {
        const Complex* comp1 = (const Complex*)op1;
        cout << *comp1 / *op2;
    }
    else if (instanceof<Complex>(op2))
    {
        Complex cop1(op1->getRealNum(), 0);
        cout << cop1 / *op2;
    }
    else
    {
        cout << *op1 / *op2;
    }
}

// Print out true if the first object is less then then second object, false otherwise
static void LTFunc(const Real* op1, const Real* op2)
{
    cout << ((*op1 < *op2) ? "true" :  "false") << endl;
}

// Prints out true if the first object is greater than the second object, false otherwise
static void GTFunc(const Real* op1, const Real* op2)
{
    cout << ((*op1 > *op2) ? "true" :  "false") << endl;
}

// Prints out true if two objects are equal, false otherwise
static void EQFunc(const Real* op1, const Real* op2)
{
    cout << ((*op1 == *op2) ? "true" : "false") << endl;
}

// Reads the file and calls other functions that solve the expressions from the file
static void loadFile(ifstream &file)
{
    // Loops the file line by line until the end of file is reached
    while (!file.eof())
    {
        // Reads a line
        string line;
        getline(file, line);

        // If line is empty, ignore it
        if (line.size() != 0)
        {
            // r stands for a real number and i stands for an imagenery number
            double r1, i1, r2, i2;
            Operation oper;
            
            // gets real and imagenery numbers from the line
            oper = parseExpression(line, r1, i1, r2, i2);
            
            // Ignore the line if invalid
            if (oper == OP_INVALID)
                continue;
            
            // Create objects for operands
            const Real *op1 = createObject(r1, i1);
            const Real *op2 = createObject(r2, i2);
        
            cout << line << "\t";
            
            // An according function is called based on the operation
            switch (oper) {
                case OP_PLUS:
                    plusFunc(op1, op2);
                    break;
                case OP_MINUS:
                    minusFunc(op1, op2);
                    break;
                case OP_MULT:
                    multiplyFunc(op1, op2);
                    break;
                case OP_DIVIDE:
                    divideFunc(op1, op2);
                    break;
                case OP_LT:
                    LTFunc(op1, op2);
                    break;
                case OP_GT:
                    GTFunc(op1, op2);
                    break;
                case OP_EQ:
                    EQFunc(op1, op2);
                    break;
                default:
                    break;
            }
            
            delete op1;
            delete op2;
        }
    }
}

int main()
{
    // Rounds numbers to 2 decimals
    cout.setf(cout.fixed);
    cout.precision(2);

    // Prompts the user for file name and loads it
    string fileName;
    cin >> fileName;
    ifstream file(fileName);

    loadFile(file);
    
    return 0;
}
