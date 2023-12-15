#include "class_BigNum.cpp"
#include <algorithm>
#include <map>

vector<BigNum> BigNum::fact(){

    BigNum n(*this), dk, dkPrev, two(BASE(2));
    vector<BigNum> p;

    if(fermat_test(10)){
        p.push_back(*this);
        return p;
    }

    while(n % BASE(2) == BASE(0)){
        p.push_back(two);
        n /= BASE(2);
    }

    int t = 0, k = 1;

    if(n == BASE(1)) return p;

    auto ds = n.sqrt();
    int f = 0;

    while(dk < ds && n != BASE(1)){
        if(t != k){
            switch (k)
            {
            case 1:
                dk = BASE(3);
                break;

            case 2:
                dkPrev = dk;
                dk = BASE(5);
                break;

            case 3:
                dkPrev = dk;
                dk = BASE(7);
                break;
            default:
                auto tmp = dk;
                dk = dkPrev + BASE(6);
                dkPrev = tmp;
                break;
            }
        }

        auto q = n / dk, 
        r = n % dk;

        if(r == BASE(0)){
            p.push_back(dk);
            n = q;
            t = k;
        }else if (q > dk){
            k++;
        }else{
            p.push_back(n);
            break;
        }
        
    }

    return p;
}

BigNum BigNum::methodAlway(BigNum d){
    if(fermat_test(10)) return *this;
    if(*this % BASE(2) == BASE(0)) throw invalid_argument("n must be odd");

    BigNum r1, r2, q, s, r;
    
    r1 = *this % d;
    r2 = *this %(d - 2);

    q = ((*this / (d - BASE(2)) - (*this / d))) * BASE(4);
    s = sqrt();

    while(true){
        d += BASE(2);

        if(d > s){std::cout << "no divisor" << std::endl; return BASE(0);}

        if ((r1 * BASE(2) + q) >= r2){
            r = r1 * BASE(2) + q - r2;
			r2 = r1;
			r1 = r;
        }else{
            r = r1 * BASE(2) + q + d - r2;
			r2 = r1;
			r1 = r;
            q += BASE(4);
        }

        while(r1 >= d){
            r1 -= d;
            q -= BASE(4);
        }

        if(r1 == 0) return d;
    }
}

pair<BigNum, BigNum> BigNum::methodFermat(){
    if(fermat_test(10)) {std::cout << "n is prime" << std::endl; return make_pair(*this, *this);}
    if(*this % BASE(2) == 0) {std::cout << "n 4etnoe " << std::endl; return make_pair(*this, *this);}

    BigNum x, z, y;

    x = sqrt();

    if(x.FastSqr() == *this) return make_pair(x, x);

    while(true){
        x += BASE(1);
        
        if(x == (*this + BASE(1) / BASE(2))){
            std::cout << "n is prime number" << std::endl;
            return make_pair(*this, *this);
        }else{
            z = x.FastSqr() - *this;
            y = z.sqrt();
        }
        
        if(y.FastSqr() == z) return make_pair(x + y, x - y);
    }
}

BigNum BigNum::Polard(){
    BigNum a(BASE(2)), b(BASE(2)), d, one(BASE(1));
    
    while(true){

        a = f_Polard(a);
        b = f_Polard(f_Polard(b));

        if (a == b) { std::cout << "Выход без результата" << std::endl; return BASE(1); }

        if (a < b) d = gcd(b - a, *this);
        else d = gcd(a - b, *this);

        if (d != one) return d;
        }

}

BigNum BigNum::gcd(BigNum a, BigNum b){
    while(a != BASE(0) && b != BASE(0)){
        if(a > b) a %= b;
        else b %= a;
    }
    return a+b;
}

BigNum BigNum::f_Polard(BigNum x){
    return (x.FastSqr() + BASE(1)) % *this;
}

BigNum BigNum::Gelfond(BigNum g, BigNum a){
    map <BigNum, BASE> u;
    map <BigNum, BASE>::iterator it;
    vector <BigNum> v;
    BigNum x;

    BigNum h = sqrt() + BASE(1);
    BigNum b = g.pow_mod(h, *this);

    for (BASE i = (BASE)1; h >= i; i += (BASE)1) {
        u.insert(make_pair(b.pow_mod(i, *this), i));
    }
    BASE i = BASE(1);
    while (h > i) {
        v.push_back((a * g.Pow(i)) % *this);
        it = u.find(v[i - (BASE)1]);
        if (it == u.end()) i+= (BASE)1;
        else{
            x = h * it->second - i;
            break;
        }
    }
    return x % *this;
}



// BigNum BigNum::Gelfond(BigNum g, BigNum a){
//     BigNum h, b;
//     vector<BigNum> u, v, _u;
//     pair<BASE, BASE> _pair;


//     h = sqrt() + BASE(1);
//     b = g.pow_mod(h, *this);

    
//     //отсортировать u
//     for(BASE i = 1; h >= i; i++){
//         u.push_back(b.pow_mod(i, *this));
//         _u.push_back(b.pow_mod(i, *this));

//         //v.push_back((a * g.Pow(i)) % *this);
//     }

//     std::sort(u.begin(), u.end());
    
//     int f = 1, i = 0;
//     int left = 0, right = u.size() - 1, middle = 0;

//     while(f){
//         v.push_back((a * g.Pow(i + 1)) % *this);

//         left = 0;
//         right = u.size() - 1;

//         while(true){
//             middle = (left + right) / 2;

//             if(u[middle] > v[i]) right = middle -1;
//             else if(u[middle] < v[i]) left = middle + 1;
//             else {f = 0 ; break;}

//             if(left > right){
//                 //f = 0;
//                 break;
//                 // std::cout << "Границы сомкнулись" << std::endl;
//                 // f = 0;
//                 // break;
//             }
//         }
//         i++;
//     }

//     int j = 0;
//     for(j = 0; j < _u.size(); j++)
//         if(u[middle] == _u[j]) break;

//     return (h * (j + 1) - i) % *this;
// }


BigNum BigNum::log(BigNum q) {
    if (q == BASE(0) || *this == (BASE)0) {
        cout << "Error!";
        exit(1);
    }

    BigNum x(*this);
    BigNum x0 = q;
    BigNum log = (BASE)0;
    while (x0 <= x){
        x0 *= q;
        log += (BASE)1;
    }

return log;
}
    
BigNum BigNum::Polard2(){
    if(fermat_test(10)) return *this;
    
    BigNum a, B, e, d, q;
    B.DecInput("10000");

    while(true){
        a = BASE(rand());
        if(a >= BASE(2) && a <= *this - BASE(2)) break;
    }

    d = gcd(a, *this);

    if(d > BASE(1)) return d;


    for(q = BASE(2); q <= B; q += BASE(1)){
        if(!q.fermat_test(10)) continue;

        e = log(q);
        a = a.pow_mod(q.Pow(e), *this);

        if(a == BASE(1)){
            while(true){
                a = BASE(rand());
                if(a >= BASE(2) && a <= *this - BASE(2)) break;
            }
        }else d = gcd(a - BASE(1), *this);

        if(d == BASE(1)) B += BASE(1);
        else return d;
    }

    return BASE(1);
}