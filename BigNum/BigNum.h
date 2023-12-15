#include <iostream>
#include <ctime>
#include <stdbool.h>
#include <string.h>
#include <type_traits> 
#include <string>
#include <bitset>
#include <vector>
#define BASE_SIZE (sizeof(BASE)*8)
#define MAX_BASE ((unsigned long long)1<<BASE_SIZE)

using namespace std;
typedef unsigned short BASE;
typedef unsigned long long EXT_BASE;
typedef conditional<BASE_SIZE<32,conditional<BASE_SIZE<16,unsigned short, unsigned int >::type, unsigned long long>::type TMP; 

class BigNum{
    public:
    BASE *coef;
    int maxLEN;
    int len;
        BigNum(BASE num = 0);
        BigNum(int, bool);
        BigNum(const BigNum &);
        ~BigNum(){delete[]coef; coef=NULL; len=0; maxLEN=0;}
        BigNum& operator = (const BigNum &);
        BigNum& operator = (const BASE);

        void HexInput(const char *);
        void HexOutput();

        bool operator == (const BigNum&) const;
        bool operator != (const BigNum&);
        bool operator >= (const BigNum&);
        bool operator <= (const BigNum&);
        bool operator > (const BigNum&) const;
        bool operator < (const BigNum&) const;

        BigNum operator + (const BigNum &);
        BigNum& operator += (const BigNum &);
        BigNum operator + (const BASE);
        BigNum& operator += (const BASE);

        BigNum operator - (const BASE);
        BigNum& operator -= (const BASE);
        BigNum operator - (const BigNum &);
        BigNum& operator -= (const BigNum &);

        BigNum operator * (const BigNum &);
        BigNum& operator *= (const BigNum &);
        BigNum operator * (const BASE);
        BigNum& operator *= (const BASE);

        BigNum operator /(const BASE);
        BigNum& operator /=(const BASE);
        BigNum operator /(const BigNum &);
        BigNum& operator /=(const BigNum &);

        BASE operator %(const BASE) const;
        BigNum& operator %=(const BASE) ;
        BigNum operator %(const BigNum &) const;
        BigNum& operator %=(const BigNum &) ;

        friend ostream& operator << (ostream &, const string&);
        //friend istream& operator >> (istream &, LargeNum&);

        BigNum FastSqr();
        BigNum Pow(BigNum&);
        BigNum Pow(BASE);
        BigNum StandardPow(BigNum&);
        BigNum StandardPow(BASE);
        BigNum BarretMod(BigNum&, BigNum&);
        BigNum pow_mod(const BigNum&, const BigNum&);
        bool fermat_test(BASE);
        bool solovay_strassen_test(BASE);
        bool miller_rabin_test(BASE);


        void DecInput(const char *);
        void DecOutput();
        void PrintCoef();
        bool isEven();
        BigNum phi();

        float eps_fermat();
        float eps_solovay_strassen();
        float eps_miller_rabin();

        BigNum sqrt();
        BigNum cbrt();
        
        vector<BigNum> fact();
        BigNum methodAlway(BigNum);
        pair<BigNum, BigNum> methodFermat();
        BigNum Polard();
        BigNum f_Polard(BigNum);
        BigNum gcd(BigNum, BigNum);

        BigNum Gelfond(BigNum, BigNum);

        BigNum log(BigNum);
        BigNum Polard2();
    private:
        void ExpMaxLen(int);
        void NormLen();
        BigNum ShiftR(int); 
        bool bit(BASE) const;
        BASE bits() const;  
        int SubLN(const BigNum&, int);
        void AddLN(const BigNum&, int);
        BigNum DivBN(const BASE , int);
};