#include <iostream>
#include <cmath>

using namespace std;


class Complex
{
    double re, im; 

    public:

    Complex (){}
  
    Complex (double re = 0, double im = 0)
    {
        this -> re = re;
        this -> im = im;
    }
  
    Complex (const Complex &c)
    {
        re = c.re;
        im = c.im;
    }
  
    ~Complex (){}
 
    double getRe()
    {
        return re;
    }

    void setRe(double value = 0)
    {
        this -> re = value;
    }

    double getIm()
    {
        return im;
    }
    void setIm(double value)
    {
        this -> im = value;
    }
 
    friend bool operator == (const Complex& first, const Complex& second)
    {
        if(first.re == second.re && first.im == second.im)
        {
            return true;
        }else
        {
            return false;
        }
    }
    friend bool operator != (const Complex& first, const Complex& second)
    {
        if(first.re != second.re && first.im != second.im)
        {
            return false;
        }else
        {
            return true;
        }
    } 
 
    double mod(); 

    Complex& operator= (const Complex &x);
    Complex operator+ (const Complex &x); 
    Complex operator- (const Complex &x); 
    Complex operator* (const Complex &x) const; 
    Complex operator/ (const Complex &x);
    //Complex operator/ (double divider);
 
    void Output();     
    void Input();       
 
    friend ostream&operator <<(ostream& out, const Complex &x); 
    friend istream&operator >>(istream& in, const Complex &x); 

    /*Complex operator-()const
    {
        return Complex(re, im * -1);
    }*/
};

inline double Complex::mod()
{
    return sqrt(re * re + im * im);
}

istream&operator >>(istream& in, Complex &x)
{
    double re = x.getRe();
    double im = x.getIm();

    in >> re >> im;


    return in;
}

ostream& operator<<(ostream& out, Complex& x)
{
    double re = x.getRe();
    double im = x.getIm();

    char sign_plus = '+';
    //char sign_munis = "-";

    out << re;

    if(im > 0)
    {
        out << sign_plus << im << "i";
    }else
    {
        out << im << "i";
    }

    out << "\n";

    return out;
}

Complex& Complex::operator=(const Complex &x)
{
    this->re = x.re;
    this->im = x.im;
    return *this;
}


/*inline Complex Complex::operator/(double divisible)
{
    Complex result(*this);
    result.re /= divisible;
    result.im /= divisible;
    return result;
}

inline Complex Complex::operator/(const Complex& x)
{
    double denominator = (x * (-x)).re;
    Complex result(*this);
    result = result * (-x);
    result = result / denominator;  
    //Complex result((re * x.re + im * x.im) / (x.re * x.re + x.im * x.im), (im * x.re + re * x.im) / (x.re * x.re + x.im * x.im));
    
    return result;
}*/

inline Complex Complex::operator/(const Complex& x)
{
    Complex result((re * x.re + im * x.im) / (x.re * x.re + x.im * x.im), (x.re * im - re * x.im) / (x.re * x.re + x.im * x.im));

    return result;
}

inline Complex Complex::operator*(const Complex &x) const
{
    Complex result(re * x.re - im * x.im, re * x.im + im * x.re);

    return result;
}

inline Complex Complex::operator-(const Complex &x)
{
    Complex result(re - x.re, im - x.im);

    return result;
}

inline Complex Complex::operator+(const Complex &x)
{
    Complex result(re + x.re, im + x.im);

    return result;
}

inline void Complex::Output()
{
    cout << re;

    if(im > 0)
    {
        cout << "+" << im << "i";
    }else
    {
        cout << im << "i";
    }
    cout << "\n";
}


int main(int argc, char const *argv[])
{
    Complex cmpx_1(112, 32), cmpx_2(123, 10);

    //cout << cmpx_1;

    //cmpx_1.setRe(4);
    //cmpx_1.setIm(9);

    Complex result = cmpx_1 / cmpx_2;
    cout << "div: " << result;

    //if(cmpx_1 != cmpx_2)
    //{
    //    cout << "1" << "\n";
    //}else
    //{
    //    cout << "2" << "\n";
    //}

    //cout << cmpx_1.mod();

    //cin >> cmpx_1;

    //cmpx_1.Output();
    //cmpx_2.Output();

    // Complex sum = cmpx_1 + cmpx_2;
    // cout << "Sum: ";
    // sum.Output();

    // Complex min = cmpx_1 - cmpx_2;
    // cout << "min: ";
    // min.Output();

    // Complex mult = cmpx_1 * cmpx_2;
    // cout << "mult: ";
    // mult.Output();

    //Complex result = cmpx_1 / cmpx_2;
    //cout << "division(/): ";
    //result.Output();

    return 0;
}
