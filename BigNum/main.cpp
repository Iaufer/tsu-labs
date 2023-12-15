#include "NT_class.cpp"

void test_fact(){
    BigNum n, tmp;
    tmp.DecInput("1");
    n.DecInput("99971");

    vector<BigNum> p = n.fact();

    for(int i = 0; i < p.size(); i++){
        p[i].DecOutput();
        std::cout << " ";
        tmp *= p[i];
    }

    if(tmp == n) std::cout << "SUCCES";
    else std::cout << "ERROR";
}

void test_alway(){
    BigNum n, d, res;

    n.DecInput("256590620791");
    d = n.cbrt() * BASE(2) + BASE(1);


    res = n.methodAlway(d);
    res.DecOutput();
}

void test_methodFermat(){
    BigNum n;

    n.DecInput("88169891");

    pair<BigNum, BigNum> p = n.methodFermat();

    p.first.DecOutput();
    std::cout << " ";
    p.second.DecOutput();

    if(n == p.first * p.second) std::cout << std::endl << "SUCCES";
    else std::cout << std::endl << "ERROR";
}

void test_Polard(){
    BigNum n;
    n.DecInput("1840312331");
    n.Polard().DecOutput();
    
}

void test_Gelfond(){
    BigNum a, n, g;

    a.DecInput("647");
    n.DecInput("1571");
    g.DecInput("52");

    n.Gelfond(g, a).DecOutput();
}

void Polard2(){
    BigNum n;
    // n.DecInput("1840312331");
    n.DecInput("1840312331");

    n.Polard2().DecOutput();
}

int main(int argc, char const *argv[])
{

    srand(time(NULL));
    //test_fact();
    //test_alway();
    //test_methodFermat();
    //test_Polard();
    test_Gelfond();

    //Polard2();


    // BigNum x;
    // x.DecInput("31");

    // x.log().DecOutput();

    return 0;
}
