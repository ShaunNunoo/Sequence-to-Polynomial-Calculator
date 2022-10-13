#include <iostream>
#include <vector>
using namespace std;

//matrix to store vraibles to be solved for
vector<vector<double>>variableMatrix;

//Stores points of the derivative of the elements
vector<vector<double>>elementDerivatives;

//Gets initials of the derivitaves of the element
void getInitalDerivative(vector<double>elements)
{
    //stores derivative of a matrix to find next derivative
    vector<double>derivative;

    //number of elements
    long unsigned elementCount = elements.size();

    //loop fills the matriz with a pascal's triangle data equivalent
    for (long unsigned i = 0; i < elementCount; i++)
    {
        for (long unsigned j = 0; j < elementCount - i; j++)
            if (i == 0)
                derivative.push_back(elements[j]);
            else
                derivative.push_back(elements[j + 1] - elements[j]);

        elements = derivative;
        elementDerivatives.push_back(derivative);
        derivative.clear();
    }
};

//flips a row a a matrix
vector<double> flipRow(vector<double>Row)
{
    vector<double>flipedVector;

    for (long i = Row.size() - 1; i >= 0; i--)
        flipedVector.push_back(Row[i]);
    return flipedVector;
}

//prints values of a matrix to the screen
void displayMatrix(vector<vector<double>>Matrix)
{
    for (long unsigned i = 0; i < Matrix.size(); i++)
    {
        for (long unsigned j = 0; j < Matrix[i].size(); j++)
            cout << Matrix[i][j] << " ";
        cout << endl;
    }
}


//prints values of a row of a matrix to the screen
void displayRow(vector<double>Row)
{
    for (long unsigned i = 0; i < Row.size(); i++)
        cout << Row[i] << " ";
    cout << endl;
}

//calculates factorial
long unsigned factorial(long unsigned num)
{
    long unsigned count = num;

    if (count > 0)
    {
        for (long unsigned i = count - 1; i > 1; i--)
            num *= i;    
        return num;
    }
    else
        return 1;
}


//function stores variables in a matrix
void storeVariables(long unsigned degree)
{
    //place holder vector
    variableMatrix.clear();
    vector<double>subvariables;

    for (long unsigned n = 0; n < degree; n++)
    {
        for (long unsigned i = 1; i <= degree - n; i++)
            subvariables.push_back(double(factorial(n + i)) / double(factorial(i) * factorial(n)));

        variableMatrix.push_back(flipRow(subvariables));
        subvariables.clear();
    }
}

//Returns a vector contining next degree of elements to be caculated
vector<double> getVariables(vector<double>polynomial, double initial)
{
    //degree of elements
    double degree = polynomial.size();

    //stores algorimetric values in matrix
    storeVariables(degree);

    //place holder to solve variables
    vector<double>solvedVariables;

    for (long i = 0; i < degree; i++)
        solvedVariables.push_back(1);

    for (long i = degree - 1; i >= 0; i--)
    {
        //sum
        double sum = 0;
        //result
        double result = 0;
        long  var_n = degree - 1 - i;

        for (long n = 0; n < var_n + 1; n++)
            variableMatrix[i][n] *= solvedVariables[n];

        for (long j = 0; j < var_n; j++)
            sum += variableMatrix[i][j];
        
        result = (polynomial[i] - sum) / variableMatrix[i][var_n];
        solvedVariables[var_n] = result;
    }

    solvedVariables.push_back(initial);
    return flipRow(solvedVariables);
}

//returns a + symbole when not 0

string symbol(long i, float num)
{
    if (i > 0 && num > 0)
        return "+";
    else
        return "";
}

//returns an "x^" string under a condition
string x_component(long degree)
{
    if (degree > 1)
        return "x^";
    else
        if (degree == 1)
            return "x";
        else
            return "";
}

//returns a vector of polynomial constants
vector<double> getPolynomialConstants()
{
    long elementSize = elementDerivatives.size();
    vector<double>polynomialIntegral = elementDerivatives[elementSize - 1];

    for (long i = elementSize - 1; i > 0; i--)
    {

        polynomialIntegral = getVariables(polynomialIntegral, elementDerivatives[i - 1][0]);

    }

    return polynomialIntegral;
}

void displayPolynomial()
{
    vector<double>polynomial = getPolynomialConstants();

    long count = 0;

    long size = polynomial.size();

    cout << "f(x)= ";

    for (long i = size - 1; i >= 0; i--)
    {
        if (polynomial[i] != 0)
        {
            //if(polynomial[i]>1.000)
            cout << symbol(count, polynomial[i]) << polynomial[i] << x_component(i);

            if (i > 1)
            {
                cout << i;
            }
            count++;
        }
        cout << " ";
    }
}


int main() {

    //FILL IN POINTS Y-VALUES FOR THE POLYNOMIAL YOU WANT HERE---->:
    vector<double>elements{ 0,1,2,0,-1,-2,0,1,2};
    //<------

    cout << "Copy and Paste the Coordinates of the Polynomial\nand its Funtion into a graphing caculator!\n\n*Points Should Align on Graph*" << endl << endl;
    cout << "Cordinates on Polynomial: " << endl;

    for (unsigned long i = 0; i < elements.size(); i++)
    {
        cout << "(" << i << "," << elements[i] << ")";
        if (i < elements.size() - 1)
            cout << ", ";
    }
    cout << endl << endl << "Polynomial of Coordinates: " << endl;
    //Points on Function to be created

    //Fills elementDerivative Matrix
    getInitalDerivative(elements);

    displayPolynomial();

    return 0;
}