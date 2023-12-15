#include "BigNum.h"
#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

BigNum::BigNum(BASE num){
    maxLEN = 1;
    coef = new BASE[len =maxLEN];
    coef[0] = num;
}

BigNum::BigNum(int Len, bool k){
    maxLEN=Len;
    coef=new BASE[maxLEN];
    if(k==0){
        len=1;
        for(int i=0;i<Len;i++) coef[i]=0;
    }
    else if(k==1){
        len=Len;
        int a;
        for(int i=0;i<Len;i++) 
        for(int j=0;j<BASE_SIZE;j=j+8){
            a=rand()%256;
            coef[i]=coef[i]|(a<<j);
        }
        this->NormLen();
    }

}

BigNum::BigNum(const BigNum &LN){
    if(&LN!=this){
        maxLEN=LN.maxLEN;
        len=LN.len;
        coef=new BASE[maxLEN];
        for(int i=0;i<maxLEN;i++) coef[i]=LN.coef[i];
    }

}

BigNum& BigNum::operator = (const BigNum &LN){
    if(&LN!=this){
        maxLEN=LN.maxLEN;
        len=LN.len;
        delete[]coef;
        coef=new BASE[maxLEN];
        for(int i=0;i<maxLEN;i++) coef[i]=LN.coef[i];
        return *this;
    }
    return *this;
}

BigNum& BigNum::operator = (const BASE num){
    delete[]coef;
    len=1;
    maxLEN=len;
    coef=new BASE[len];
    coef[0]=num;
    return *this;
}

void BigNum::HexInput(const char *S){
    int BS=BASE_SIZE/4;
    int Slen=strlen(S);
    len=(Slen-1)/BS+1;
    maxLEN=len+1;
    delete[]coef;
    coef=new BASE[maxLEN];
    for(int i=0;i<maxLEN;i++) coef[i]=0;
    for(int i=Slen-1;i>=0;i--){
        char tmp=0;
        int iRev=Slen-1-i;
        if((S[i]>='0')&&(S[i]<='9')) tmp=S[i]-'0';
        else if((S[i]>='a')&&(S[i]<='f')) tmp=S[i]-'a'+10;
        else if((S[i]>='A')&&(S[i]<='F')) tmp=S[i]-'A'+10;
        else continue;
        coef[iRev/BS]=coef[iRev/BS]|(tmp<<((iRev%BS)*4)); 
    }
    this->NormLen();
}

void BigNum::HexOutput(){
    bool k=true;
    for(int i=len-1;i>=0;i--){
        for(int j=BASE_SIZE-4;j>=0;j=j-4){
            char tmp=((coef[i]&(0xF<<j))>>j);
            if(k&&(tmp==0)) continue;
            else k=false;
            if(tmp<10){
                tmp=tmp+'0';
                cout<<tmp;
            }
            else if(tmp<16){
                tmp=tmp+'a'-10;
                cout<<tmp;
            }
        }
    }
    if(k) cout<<0;
}

bool BigNum::operator == (const BigNum &LN) const{
    if(&LN==this) return 1;
    if(len!=LN.len) return 0;
    int i=len-1;
    while(i>=0){
        if(coef[i]==LN.coef[i]) i--;
        else return false;
    }
    return true;
}

bool BigNum::operator != (const BigNum &LN){
    if(&LN==this) return 0;
    if(len!=LN.len) return 1;
    int i=len-1;
    while(i>=0){
        if(coef[i]==LN.coef[i]) i--;
        else return true;
    }
    return false;
}

bool BigNum::operator >= (const BigNum &LN){
    if(&LN==this) return 1;
    if(len>LN.len) return 1;
    if(len<LN.len) return 0;
    int i=len-1;
    while(i>=0){
        if(coef[i]==LN.coef[i]) i--;
        else if(coef[i]>LN.coef[i]) return 1;
        else return 0;
    }
    return true;
}

bool BigNum::operator <= (const BigNum &LN){
    if(&LN==this) return 1;
    if(len>LN.len) return 0;
    if(len<LN.len) return 1;
    int i=len-1;
    while(i>=0){
        if(coef[i]==LN.coef[i]) i--;
        else if(coef[i]<LN.coef[i]) return 1;
        else return 0;
    }
    return true;
}

bool BigNum::operator > (const BigNum &LN) const{
    if(&LN==this) return 0;
    if(len>LN.len) return 1;
    if(len<LN.len) return 0;
    int i=len-1;
    while(i>=0){
        if(coef[i]==LN.coef[i]) i--;
        else if(coef[i]>LN.coef[i]) return true;
        else return false;
    }
    return false;
}

bool BigNum::operator < (const BigNum &LN) const{
    if(&LN==this) return 0;
    if(len>LN.len) return 0;
    if(len<LN.len) return 1;
    int i=len-1;
    while(i>=0){
        if(coef[i]==LN.coef[i]) i--;
        else if(coef[i]<LN.coef[i]) return true;
        else return false;
    }
    return false;
}

BigNum BigNum::operator+ (const BigNum &LN){
        int min,max;
        BASE *MaxCoef;
        bool k=0;
        TMP tmp;
        if(len>LN.len) {min=LN.len; max=len+1; MaxCoef=coef;}
        else {min=len; max=LN.len+1; MaxCoef=LN.coef;}
        BigNum A(max,0);
        for(int i=0;i<min;i++){
            tmp=(TMP)LN.coef[i]+(TMP)coef[i]+k;
            A.coef[i]=(BASE)tmp;
            k=(bool)(tmp>>BASE_SIZE);
        }
        for(int i=min;i<max-1;i++){
            tmp=(TMP)MaxCoef[i]+k;
            A.coef[i]=(BASE)tmp;
            k=(bool)(tmp>>BASE_SIZE);
        }
        A.coef[max-1]=k;
        A.NormLen();
        return A;
    }

BigNum BigNum::operator+ (const BASE num){
    TMP tmp=0;
    bool k=0;
    int Len=maxLEN;
    if(len+1>maxLEN) Len=len+1;
    BigNum A(Len,0);
    tmp=(TMP)coef[0]+(TMP)num+k;
    k=(bool)(tmp>>BASE_SIZE);
    A.coef[0]=tmp;
    for(int i=1;i<len;i++){
        tmp=coef[i]+k;
        k=bool(tmp>>BASE_SIZE);
        A.coef[i]=tmp;
    }
    A.coef[len]=k;
    A.NormLen();
    return A;
}

BigNum& BigNum::operator+= (const BASE num){
    *this=*this+num;
    return *this;
}

BigNum& BigNum::operator+= (const BigNum &LN){
    *this=*this+LN;
    return *this;
}

BigNum BigNum::operator - (const BASE num){
    if (*this < num) {
    throw invalid_argument("first value should be bigger than second to subtract");
    }
    TMP tmp;
    bool k=0;
    BigNum A(*this);
    tmp=A.coef[0]+MAX_BASE-num;
    A.coef[0]=(BASE)tmp;
    k=!((tmp)>>BASE_SIZE);
    for(int i=A.len;k&&i<=A.len;i++){
        tmp=A.coef[i]+MAX_BASE-k;
        A.coef[i]=(BASE)tmp;
        k=!((tmp)>>BASE_SIZE);
    }
    A.NormLen();
    return A;
}

BigNum& BigNum::operator -= (const BASE num){
    *this=*this-num;
    return *this;
}

BigNum BigNum::operator - (const BigNum &LN){
    if (*this < LN) {
    throw std::invalid_argument("first value should be bigger than second to subtract");
    }
    TMP tmp;
    bool k=0;
    BigNum A(*this);
    for(int i=0;i<LN.len;i++){
        tmp=A.coef[i]+MAX_BASE-LN.coef[i]-k;
        A.coef[i]=(BASE)tmp;
        k=!((tmp)>>BASE_SIZE);
    }
    for(int i=LN.len;k&&i<=A.len;i++){
        tmp=A.coef[i]+MAX_BASE-k;
        A.coef[i]=(BASE)tmp;
        k=!((tmp)>>BASE_SIZE);
    }
    A.NormLen();
    return A;
}

BigNum& BigNum::operator -= (const BigNum &LN){
    if (*this < LN) {
    throw invalid_argument("first value should be bigger than second to subtract");
    }
    int min;
    bool k=0;
    TMP tmp;
    for(int i=0;i<LN.len;i++){
        tmp=coef[i]+MAX_BASE-LN.coef[i]-k;
        k=!((tmp)>>BASE_SIZE);
        coef[i]=(BASE)tmp;
    }
    for(int i=LN.len;k&&i<=len;i++){
        tmp=coef[i]+MAX_BASE-k;
        k=!((tmp)>>BASE_SIZE);
        coef[i]=(BASE)tmp;
    }
    this->NormLen();
    return *this;
}

BigNum BigNum::operator* (const BigNum &LN){
    TMP tmp;
    BASE k;
    BigNum A(len+LN.len,0);
    for(int i=0;i<len;i++){
        k=0;
        for(int j=0;j<LN.len;j++){
            tmp=(TMP)LN.coef[j]*(TMP)coef[i]+A.coef[i+j]+k;
            k=(tmp>>BASE_SIZE);
            A.coef[i+j]=tmp;
        }
        A.coef[LN.len+i]+=k;
    }
    A.NormLen();
    return A;
}

BigNum BigNum::operator* (const BASE num){
    TMP tmp=0;
    BASE k=0;
    BigNum A(len+1,0);
    for(int i=0;i<len;i++){
        tmp=(TMP)coef[i]*(TMP)num+k;
        k=(tmp>>BASE_SIZE);
        A.coef[i]=(BASE)tmp;
    }
    A.coef[len]=k;
    A.NormLen();
    return A;
}

BigNum& BigNum::operator*= (const BASE num){
    *this=*this*num;
    return *this;
}
        
BigNum& BigNum::operator *= (const BigNum &LN){
    *this=*this*LN;
    return *this;
}

BigNum BigNum::operator/(const BASE num){
    TMP tmp,k=0;
    BigNum A(len,0);
    for(int i=len-1;i>=0;i--){
        tmp=(k<<BASE_SIZE)+coef[i];
        k=tmp%num;
        A.coef[i]=(tmp)/num;
    }
    A.NormLen();
    return A;
}

BigNum& BigNum::operator/=(const BASE num){
    *this=*this/num;
    return *this;
}

BASE BigNum::operator%(const BASE num) const{
    TMP tmp,k=0;
    for(int i=len-1;i>=0;i--){
        tmp=(k<<BASE_SIZE)+coef[i];
        k=tmp%num;
    }
    return k;
}

BigNum& BigNum::operator%=(const BASE num){
    *this=*this%num;
    return *this;
}

BigNum BigNum::operator/(const BigNum &LN){
    if((LN.len==1)&&(LN.coef[0]!=0)){BigNum q=*this/LN.coef[0]; return q;}   
    if((LN.len==1)&&(LN.coef[0]==0)){BigNum q(1,0); q.coef[0]=0; return q;}   
    if(*this==LN){BigNum q(1,0); q.coef[0]=1; return q;}
    if(*this<LN){BigNum q; return q;}
    BigNum q(len-LN.len+1, 0);
    TMP b=MAX_BASE;
    //D1
    TMP d=b/((TMP)LN.coef[LN.len-1]+1);
    BigNum dU(*this);
    BigNum dV(LN);
    dU*=d;
    dV*=d;   
        if(len==dU.len){
        if(dU.len==dU.maxLEN){
            dU.ExpMaxLen(1);
        }
        dU.coef[len]=0;
        dU.len=len+1;
    }   
    //D2
    for(int j=len-LN.len;j>=0;j--){//D7(Цикл по j)
        //D3
        int _j=j+LN.len;
        TMP ff=((TMP)dU.coef[_j]<<BASE_SIZE)+dU.coef[_j-1];
        TMP _q=(ff/dV.coef[LN.len-1]);
        TMP _r=(ff%dV.coef[LN.len-1]);
        if((_q==b)||((_q*dV.coef[LN.len-2])>(b*_r+dU.coef[_j-2]))){
            _q--; _r=_r+dV.coef[LN.len-1];
            if((_r<b)&&((_q==b)||(_q*dV.coef[LN.len-2]>b*_r+dU.coef[_j-2]))){
                _q--; _r=_r+dV.coef[LN.len-1];
            }
        }
        //D5
        q.coef[j]=_q;   
        //D4
        int k=dU.SubLN( dV*_q,j);
        if(k){
            //D6
            q.coef[j]--;
            dU.AddLN(dV,j);
        }
    }
    //D8
    q.NormLen();
    return q;
}

BigNum& BigNum::operator/=(const BigNum &LN){
    *this=*this/LN;
    return *this;
}

BigNum BigNum::operator%(const BigNum &LN) const{
    if((LN.len==1)&&(LN.coef[0]!=0)){BigNum r(1,0); r.coef[0]=*this%LN.coef[0]; return r;}   
    if((LN.len==1)&&(LN.coef[0]==0)){BigNum r(*this); return r;}
    if(*this==LN){BigNum r(1,0); return r;}
    if(*this<LN){BigNum r(*this); return r;}
    BigNum r(LN.len-1, 0);
    TMP b=MAX_BASE;
    TMP d=b/((TMP)LN.coef[LN.len-1]+1);
    BigNum dU(*this);
    BigNum dV(LN);
    dU*=d;
    dV*=d;
    if(len==dU.len){
        if(dU.len==dU.maxLEN){
            dU.ExpMaxLen(1);
        }
        dU.coef[len]=0;
        dU.len=len+1;
    }   
    for(int j=len-LN.len;j>=0;j--){
        int _j=j+LN.len;
        TMP ff=((TMP)dU.coef[_j]<<BASE_SIZE)+dU.coef[_j-1];
        TMP _q=(ff/dV.coef[LN.len-1]);
        TMP _r=(ff%dV.coef[LN.len-1]);
        if((_q==b)||((_q*dV.coef[LN.len-2])>(b*_r+dU.coef[_j-2]))){
            _q--; _r=_r+dV.coef[LN.len-1];
            if((_r<b)&&((_q==b)||(_q*dV.coef[LN.len-2]>b*_r+dU.coef[_j-2]))){
                _q--; _r=_r+dV.coef[LN.len-1];
            }
        }
        int k=dU.SubLN( dV*_q,j);
        if(k){
            //D6
            //q.coef[j]--;
            dU.AddLN(dV,j);
        }
    }
    dU.len=LN.len;
    r=dU/d;
    
    //r.NormLen();
    return r;
}

BigNum& BigNum::operator%=(const BigNum &LN) {
    *this=*this%LN;
    return *this;
}

void BigNum::DecInput(const char *S){
    TMP tmp=0;
    BASE k=0;
    int BS=BASE_SIZE/4;
    int Slen=strlen(S);
    maxLEN=(Slen-1)/BS+2;
    len=1;
    delete[]coef;
    coef=new BASE[maxLEN];
    for(int i=0;i<maxLEN;i++) coef[i]=0;
    
    for(int i=0;i<Slen;i++){
        char s=0;
        if((S[i]>='0')&&(S[i]<='9')) s=S[i]-'0';
        else continue;
        (*this*=10)+=s;
    }
    NormLen();
}

void BigNum::DecOutput(){
    if(len==1&&coef[0]==0) cout<<0;
    else{
    BigNum A(*this);
    int SLen=len*10;
    int k=0;
    //unsigned char tmp;
    char* S=new char[SLen];
    while(A.coef[0]!=0||A.len>1){
        S[k]=(A%10)+'0';
        //cout<<S[k]<<' ';
        A/=10;
        k++;
    }
    k--;
    for(;k>=0;k--) cout<<S[k];
    delete[]S;
    }
}   

int BigNum::SubLN(const BigNum &LN, int j){
    TMP tmp;
    bool k=0;
    for(int i=0;i<LN.len;i++){
        //cout<<i+j<<" "<<len<<endl;
        tmp=(TMP)coef[i+j]+MAX_BASE-LN.coef[i]-k;
        coef[i+j]=(BASE)tmp;
        k=!((tmp)>>BASE_SIZE);
    }
    for(int i=LN.len;k&&(i+j)<len;i++){
        //cout<<i+j<<" "<<len<<endl;
        tmp=(TMP)coef[i+j]+MAX_BASE-k;
        coef[i+j]=(BASE)tmp;
        k=!((tmp)>>BASE_SIZE);
    }
    NormLen();
    return k;
}

void BigNum::AddLN(const BigNum &LN, int j){
        bool k=0;
        for(int i=0;i<LN.len;i++){
            TMP tmp=(TMP)coef[i+j]+LN.coef[i]+k;
            k=bool(tmp>>BASE_SIZE);
            coef[i+j]=tmp;
        }
        for(int i=LN.len;k&&(i+j)<len;i++){
            TMP tmp=(TMP)coef[i+j]+k;
            k=bool(tmp>>BASE_SIZE);
            coef[i+j]=tmp;
        }
        //NormLen();
    }

BigNum BigNum::DivBN(const BASE num, int j){
    TMP tmp,k=0;
    BigNum A(j+1,0);
    for(int i=j;i>=0;i--){
        tmp=(k<<BASE_SIZE)+coef[i];
        k=tmp%num;
        A.coef[i]=(tmp)/num;
    }
    A.NormLen();
    return A;
}

void BigNum::ExpMaxLen(int b){
    maxLEN+=b;
    BASE *NewCoef=new BASE[maxLEN];
    for(int i=0;i<len;i++) NewCoef[i]=coef[i];
    for(int i=len;i<maxLEN;i++) NewCoef[i]=0;
    delete[]coef;
    coef=NewCoef;
}

void BigNum::NormLen(){
    for(len=maxLEN;coef[len-1]==0&&len>0;len--);
    if(len==0) len=1;
}

void BigNum::PrintCoef(){
    for(int i=len-1;i>=0;i--) cout<<bitset<8>(coef[i])<<" ";
    cout<<endl;

}

BASE BigNum::bits() const{
    for(int i = len-1; i >= 0; i--){
        for(int bit = BASE_SIZE-1; bit >= 0; bit--){
            if((coef[i] >> bit) & 1) return (i * BASE_SIZE + bit + 1);
        }
    }
    return 0;
}

bool BigNum::bit(BASE i) const{
    int pos = i/BASE_SIZE;
    return ((coef[pos] >> (i % BASE_SIZE)) & 1);
}

BigNum BigNum::ShiftR(int i){
    int new_len = (i>len) ? 0 : len - i;
    BigNum res(new_len, 0);
    res.len = new_len;
    for(int cf = 0; cf < new_len; cf++){
        res.coef[cf] = coef[cf + i];
    }
    return res;
}

bool BigNum::isEven(){
    return !(coef[0]&1);
}

BigNum BigNum::pow_mod(const BigNum &n, const BigNum &m){
    if(m == 1){
        return BigNum(0);
    }
    BigNum q = *this % m;

    BigNum z(1);
    if(n.coef[0]&1){
        z = BigNum(*this) % m;
    }

    BASE n_bits = n.bits();
    for(int i=1; i < n_bits; i++){
        q = q.FastSqr() % m;
        if(n.bit(i)) z = (z * q) % m;
    }
    return z; 
}   

BigNum generator_prime(BASE size)
    {
        BigNum prime;
        do{
            prime = BigNum(size, 1);
        }while(!prime.miller_rabin_test(100));
        return prime;
    }

BigNum BigNum::sqrt(){
    BigNum x(*this), x0, tmp;  

    x0 = x;
    x = (x0 + (*this / x0)) / 2;

    while(x < x0){
        x0 = x;
        x = (x0 + (*this / x0)) / 2;
    }

    return x;
}

// BigNum BigNum::sqrt()
// {
// 	BigNum x(*this), x0;
// 	do
// 	{
// 		x0 = x;
// 		x = (*this / x + x) / 2;
// 	} while (x < x0);
// 	return x0;
// }

BigNum BigNum::cbrt(){
    BigNum x(*this), x0, tmp;  

    x0 = x;
    x = (x0 * 2 + (*this / x0.Pow(2))) / BASE(3);

    while(x < x0){
        x0 = x;
        x = (x0 * 2 + (*this / x0.Pow(2))) / BASE(3);
    }

    return x;
}

BigNum BigNum::FastSqr(){
    BigNum res(2*len, 0);
    for(int i = 0; i < len; i++){
        EXT_BASE cuv = EXT_BASE(coef[i])*coef[i] + res.coef[2*i];
        res.coef[2*i] = cuv;
        //2)
        for(int j = i + 1; j < len; j++){
            cuv = EXT_BASE(2) * coef[i] * coef[j] + res.coef[i+j] + (cuv >> BASE_SIZE);
            res.coef[i+j] = cuv;
        }

        TMP* y = (TMP*) &res.coef[i+len];
        *y += cuv >> BASE_SIZE;
    }

    res.NormLen();
    return res;
}

BigNum BigNum::Pow(BigNum &n) {
    BigNum q(*this);
    BigNum z(1,0);
    if(n.coef[0]&1){
        z = BigNum(*this);
    }else{
        z+=1;
    }
    BASE n_bits = n.bits();
    for(int i=1; i < n_bits; i++){
        q = q.FastSqr();
        if(n.bit(i)) z *= q;
    }
    return z;       
}

BigNum BigNum::Pow(BASE n){
    BigNum q(*this);
    BigNum z(1,0);
    if(n&1){
        z = BigNum(*this);
    }else{
        z+=1;
    }
    n = n >> 1;
    while(n > 0){
        q = q.FastSqr();
        if(n&1) z *= q;
        n = n >> 1;
    }
    return z;
}

BigNum BigNum::StandardPow(BigNum &n) {
    BigNum res(*this);
    BigNum i;
    i = 1;
    for(;i<n;i+=1){
        res *= *this;
    }
    return res;
}

BigNum BigNum::StandardPow(BASE n) {
    BigNum res(*this);
    BASE i = 1;
    for(;i<n;i+=1){
        res *= *this;
    }
    return res;
}


BigNum BigNum::BarretMod(BigNum &m, BigNum &z){
    if(len > 2 * m.len) throw invalid_argument("This number is too big for this method");
    
    BigNum q = ShiftR(m.len-1);
    q*=z;
    q = ShiftR(m.len + 1);

    BigNum r1 = *this;
    BigNum r2 = q * m;
    BigNum r(m.len+2, 0);

    if(r1>=r2){
        r = (r1 - r2);
    } else{
        r.coef[m.len+1] = 1;
        r.len = m.len + 2;
        r += (r1-r2);
    }

    while(r>=m){
        r-=m;
    }
    
    return r;
}

bool BigNum::fermat_test(BASE t){
    if(*this == BigNum(3) || *this == BigNum(2)){
        return true;
    }
    if(isEven()){
        return false;
    }
    while(t){
        BigNum a(len, 1);
        a.coef[len-1] = a.coef[len-1] % coef[len-1];
        if(a < 2 || a > (*this-2)){
            continue;
        }
        BigNum r = a.pow_mod(*this-1, *this);
        if(r != 1){
            return false;
        }
        t--;
    }
    return true;
}

bool BigNum::miller_rabin_test(BASE t){
    if(*this == BigNum(3) || *this == BigNum(2)){
        return true;
    }
    if(isEven()){
        return false;
    }
    
    BigNum r = BigNum(*this - 1);
    BigNum s = 0;
    while(r.isEven()){
        r /= 2;
        s += 1;
    }
    while(t){
        BigNum b(len, 1);
        b.coef[len-1] = b.coef[len-1] % coef[len-1];
        if(b < 2 || b > (*this-2)){
            continue;
        }

        BigNum y = b.pow_mod(r, *this);
        
        BigNum nm(*this-1);

        if(y != 1 && y != nm){
            BigNum j = 1;
            while(j < s && y != nm){
                y = y.FastSqr()%(*this);
                if(y == 1){
                    return false;
                }
                j += 1;
            }
            if(y != nm){
                return false;
            }
        }
        t--;
    }
    return true;

}

BigNum generator_strong_prime(BASE size){
    BigNum s = generator_prime(size);
    BigNum t = generator_prime(size);
    
    BigNum i(1, 1);
    BigNum r = i * t * 2 + 1;
    while(!r.miller_rabin_test(100)){
        i += 1;
        r = i * t * 2 + 1;
    }

    BigNum p0 = s.pow_mod(r-2, r) * s * 2 - 1;

    BigNum j(1, 1);
    BigNum p = (j * r * s * 2) + p0;
    while(!p.miller_rabin_test(100)){
        j += 1;
        p = (j * r * s * 2) + p0;
    }
    return p;
}

BigNum BigNum::phi(){
    BigNum result = *this;
    BigNum n = *this;
    for (BigNum i = 2; i.FastSqr() <= n; i += 1) {
        if (n % i == 0) {
            do {
                n /= i;
            } while (n % i == 0);
            result -= result / i;
        }
    }

    if (n > 1)
        result -= result / n;

    return result;
}

float BigNum::eps_fermat(){
    BASE shift = 10000;
    BigNum eps_bn = (this->phi()*shift / ((*this)));
    float eps = eps_bn.coef[0];
    return eps / shift;
}

float BigNum::eps_solovay_strassen(){
    BASE shift = 10000;
    BigNum eps_bn = (this->phi()*shift / ((*this * 2)));
    float eps = eps_bn.coef[0];
    return eps / shift;
}

float BigNum::eps_miller_rabin(){
    BASE shift = 10000;
    BigNum eps_bn = (this->phi()*shift / ((*this * 4)));
    float eps = eps_bn.coef[0];
    return eps / shift;

}

float pow(float eps, BASE t){
    t--;
    while(t){
        eps*=eps;
        t--;
    }
    return eps;
}