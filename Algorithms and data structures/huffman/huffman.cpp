#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <stdbool.h>
#include <iterator>
#include <fstream>

using namespace std;

class Uzel{
    public:
    char s;
    int key;
    Uzel *l, *r;
    Uzel();
    Uzel(char , int );
    Uzel(Uzel *, Uzel *);
};

class MapKey{
    public:
    map<char, int> MK;
    void create_map(ifstream& );
    void print_map();
    Uzel* create_list();
    unsigned long long head_reader(ifstream& );
    static bool comp(Uzel *l,Uzel *r){
    return r->key>l->key;
}
};


Uzel::Uzel(){
    l=NULL; r=NULL;
}

Uzel::Uzel(char c, int k){
    s=c; key=k;
    l=NULL; r=NULL;
}

Uzel::Uzel(Uzel *left, Uzel *right){
    key=left->key+right->key;
    r=right; l=left;
}

void MapKey::create_map(ifstream& fin){
    char c;
    for(fin.get(c);!fin.eof();fin.get(c)) MK[c]++;
    fin.clear();
    fin.seekg(0);
}


Uzel* MapKey::create_list(){
    list<Uzel*> List;
    for(auto it=MK.begin();it!=MK.end();it++){
        Uzel *p=new Uzel(it->first,it->second);
        List.push_back(p);
    }
    while(List.size()!=1){
        List.sort(comp);
        Uzel *r=List.front();
        List.pop_front();
        Uzel *l=List.front();
        List.pop_front();
        Uzel *p=new Uzel(l,r);
        List.push_back(p);
    }
    return List.front();
}

void MapKey::print_map(){

    for(auto it = MK.begin(); it!= MK.end(); it++)
    {
        cout << it-> first << " - " << it -> second << endl;
        
    }
}

unsigned long long MapKey::head_reader(ifstream& fin){
    int key, q;
    unsigned long long len=0;
    fin.read((char*)&q,sizeof(q));
    char s;
    for(int i=0;i<q;i++){
        fin.read((char*)&s, sizeof(s)); fin.read((char*)&key,sizeof(key));
        MK[s]=key;
        len+=key;
    }

    return len;
}



vector<bool>code;

void create_table(Uzel *T, map<char, vector<bool>>&buff)
{
    if(T->l){
        code.push_back(0);
        create_table(T->l,buff);
    }
    if(T->r){
        code.push_back(1);
        create_table(T->r,buff);
    }
    if(((T->r) == NULL) && ((T->l) == NULL))
    {
        buff[T->s]=code;   
    }
    if(!code.empty()) code.pop_back();
}



void print_vector(vector<bool>code){
    for(auto it=code.begin();it!=code.end();it++){
        cout<<*it;
    }
    cout<<endl;
}

void print_table(map<char, vector<bool>>&buff){
    for(auto it = buff.begin(); it!= buff.end(); it++)
    {
        cout << it-> first << " - " ;
        print_vector(it->second);
    }
}


void print_file(const char *PATH){
    ifstream fin(PATH);
    char s;
    while(fin>>s){
        for(int i=0;i<8;i++){
            int b=(s&(1<<(7-i)))>>(7-i);
            cout<<b;
        }
    }
    fin.close();
}