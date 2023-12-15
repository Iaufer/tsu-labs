#include "class_BinTree.cpp"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    int N = 12, _A[N]{46, 82, 56, 57, 93, 90, 95, 30, 35, 17, 15, 26};
    BinTree A(_A, N);
    cout << A; cout << endl;
    return 0;
}
