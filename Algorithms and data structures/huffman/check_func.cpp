#include <iostream>
#include <fstream>

using namespace std;

int count_text(){
    int count = 0;    

    ifstream fin_text;
    fin_text.open("Test.txt");

    if(!fin_text.is_open()){
        cout << "count_text: Файлы не открылся!" << endl;
    }else{
        char ch_text;
        while(fin_text.get(ch_text)){
            count++;
        }
    }
    fin_text.close();

    return count;
}

int count_decode(){
    int count = 0;    

    ifstream fin_decode;
    fin_decode.open("decode.txt");

    if(!fin_decode.is_open()){
        cout << "fin_decode: Файлы не открылся!" << endl;
    }else{
        char ch_decode;
        while(fin_decode.get(ch_decode)){
            count++;
        }
    }
    fin_decode.close();

    return count;
}


bool check_file(){
    int ct = count_text();
    int cd = count_decode();
    if(ct != cd) return false;

    ifstream fin_text;
    ifstream fin_decode;

    fin_text.open("Test.txt");
    fin_decode.open("decode.txt");

    if(!fin_text.is_open()) return false;
    if(!fin_decode.is_open()) return false;

    char ch_text, ch_decode;

    while(fin_text.get(ch_text) && fin_decode.get(ch_decode))
        if(ch_text != ch_decode) return false;

    return true;
}

int main(int argc, char const *argv[])
{
    cout << "Равенство файлов: " << check_file() << endl;
    
    cout << "количсество символов в файле text: " << count_text() << endl;
    cout << "количсество символов в файле decode:" << count_decode() << endl;
    return 0;
}
