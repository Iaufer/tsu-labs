#include <iostream>
#include <fstream>

using namespace std;

int main(){
    fstream file_test("text.txt");
    fstream file_encode("encode.txt");

    int size_test = 0;
    int size_encode = 0;

    file_test.seekg(0, ios::end);
    file_encode.seekg(0, ios::end);
    
    size_test = file_test.tellg();
    size_encode = file_encode.tellg();

    cout << "File weight test: " << size_test << " byte" << endl;
    cout << "File weight encode: " << size_encode << " byte" << endl;
    file_test.close();
    file_encode.close();

    double temp = size_test - size_encode;
    double compr_perc = (temp / size_test) * 100;

    cout << "The compression percentage is: " << compr_perc << "%" <<  endl;

    return 0;
}