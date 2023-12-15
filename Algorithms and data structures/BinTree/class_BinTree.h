#include <iostream>
#include <ctime>
#include <vector>
#include <list>

using namespace std;

class Uzel{
private:
    int key;
    Uzel *left, *right;

    Uzel(int k = 0, Uzel *l = NULL, Uzel *r = NULL)
    {key = k; left = l; right = r;}

    friend void rec_del(Uzel*);
    friend class BinTree;
};

class BinTree
{
private:
    Uzel *root;
    int count_uzel = 0;
public:
    BinTree(){root = NULL;}//пустое дерево
    BinTree(int n);
    BinTree(const BinTree&);
    BinTree(const vector<int>&);
    BinTree(const int *arr, int N);
    ~BinTree();

    Uzel *BTree(int n);
    Uzel* get_root(){return root;}
    Uzel* find_k(int k);
    
    Uzel* CopyTree(Uzel*);

    BinTree operator =(const BinTree&);

    int find__k(int k);
    
    void add(int k);
    void del(int k);
    void _del(int k);

    int min();
    int min_r(Uzel *q);

    int KRL(int *a);
    void LRK(Uzel* r);
    void LRK();
    void inarray(Uzel* q, int* a,int& k);
    
    int max();
    void print_level(Uzel* t, int k);
    list<Uzel*> tree_walk();
    //del_elem, два обхода(по уровню и глубины)
    //два обхода(по уровню и глубины)

    void print_tree(Uzel*, int k);
    void print(ostream& os, int, Uzel*) const;
    friend ostream & operator << (ostream&, const BinTree&);
};