#include <iostream>
#include <cmath>
#include <stdbool.h>
#include <string.h>
#include <array>

using namespace std;

class BoolV
{
    unsigned int *v;
    int nbit, m; // nbit – количество бит вектора, m – количество элементов массива v
    
  public:

    BoolV(int nn = 1); // формируется булев вектор из nn бит; все биты со значениями 0
    BoolV(const char*); // формируется булев вектор по строке из нулей и единиц
    BoolV(const BoolV &);
    ~BoolV();

    void Set1(int); // устанавливает указанный бит в 1
    void Set0(int); // устанавливает указанный бит в 0
    
    int operator[](int);
    
    BoolV& operator = (const BoolV &);
    bool operator == (const BoolV &); // равенство векторов
    BoolV operator | (const BoolV &);
    BoolV operator & (const BoolV &);
    BoolV operator ~ ();

    friend ostream& operator << (ostream &, const BoolV &);

    friend istream& operator >> (istream &, BoolV &);

    // Дополнительно (не обязательно)
    int weight(); //вес вектора
    BoolV operator << (int); //сдвиг на k бит влево
    BoolV operator >> (int); //сдвиг на k бит вправо
};


BoolV::BoolV(int nn)
{
    nbit = nn;
    m = ((nbit - 1) / 32) + 1;

    v = new unsigned int[m];

    for(int i = 0; i < m; i++)
    {
        v[i] = 0;
    }
}

BoolV::BoolV(const char *_v)
{
    nbit = strlen(_v);
    m = ((nbit - 1) / 32) + 1;
    
    v = new unsigned int[m];

    for(int i = 0; i < m; i++)
    {
        v[i] = 0;
    }

    for(int i = 0; i < nbit; i++)
    {
        if(_v[i] != '0')
        {
            v[i / 32] = v[i / 32] | (1 << (i % 32));
        }
    }
}


BoolV::BoolV(const BoolV& _b)
{
    nbit = _b.nbit;
    m = _b.m;

    for(int i = 0; i < m; i++)
    {
        v[i] = _b.v[i];
    }
}


BoolV::~BoolV()
{
    delete[] v;
}


void BoolV::Set1(int k)
{
    if(k >= nbit || k < 0)
    {
        cout << "Index Fail" << "\n";
    }else
    {
        unsigned int mask = 1 << k;
        v[k / 32] = v[k / 32] | mask;
    }
}

void BoolV::Set0(int k)
{
    if(k >= nbit && k < 0)
    {
        cout << "Index fail" << "\n";
    }else
    {
        unsigned int mask = ~(1 << k);
        v[k / 32] = v[k / 32] & mask;   
    }
}

int BoolV::operator[](int k)
{
    if(k >= nbit && k < 0)
    {
        cout << "Index fail" << "\n";
        
        return -1;
    }else
    {
        unsigned int mask = (1 << k);
        if((v[k / 32] & mask) == 0)
        {
            return 0;
        }else
        {
            return 1;
        }
    }
} 

BoolV& BoolV::operator=(const BoolV& vec)
{
    if(this != &vec)
    {
        m = vec.m;  
        nbit = vec.nbit;
        
        delete[] v;
        
        v = new unsigned int[m];
        
        for(int i = 0; i < m; i++)
        {
            v[i] = vec.v[i];
        }
    }
    
    return *this;
}

bool BoolV::operator==(const BoolV& vec)
{
    if(this != &vec)
    {
        if(nbit == vec.nbit)
        {
            for(int i = 0; i < m; i++)
            {
                for(int j = 0; j < m; j++)
                {
                    if(v[i] != v[j])
                    {
                        return false;
                    }
                }
            }

            return true;
        }else
        {
            return false;
        }
    }

    return true;
}



ostream& operator<<(ostream& out, const BoolV& _b)
{
    for(int i = 0; i < _b.nbit; i++)
        if((_b.v[i / 32] & (1 << (i % 32))) == 0) out << 0;
        else out << 1;

    return out;
}


int main()
{
    BoolV a("1010101"), b("1010101"), c("10101011010101101010110101011010101");

    /* cout << a << "\n";
    a.Set1(1);
    cout << a; */

    /* cout << b << "\n";
    b.Set0(0);
    cout << b << "\n"; */

    /* cout << c[33] << "\n"; */

    /* a = b;
    cout << a << "\n"; */

    /* if(a == b)
    {
        cout << 1;
    }else
    {
        cout << 0;
    } */

    return 0;
}
