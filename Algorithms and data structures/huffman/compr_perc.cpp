#include <iostream>
#include <fstream>

using namespace std;


int main(){
    fstream file_test("Test.txt");
    fstream file_encode("encode.txt");

    int size_test = 0;
    int size_encode = 0;

    file_test.seekg(0, ios::end);
    file_encode.seekg(0, ios::end);
    
    size_test = file_test.tellg();
    size_encode = file_encode.tellg();

    cout << "Файл test весит: " << size_test << " байт" << endl;
    cout << "Файл encode весит: " << size_encode << " байт" << endl;
    file_test.close();
    file_encode.close();

    double temp = size_test - size_encode;
    double compr_perc = (temp / size_test) * 100;

    cout << "Процент сжатия равен: " << compr_perc << "%" <<  endl;

    return 0;
}