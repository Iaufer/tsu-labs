#include "class_BinTree.h"

list<Uzel*> BinTree::tree_walk(){
    list<Uzel*> r;
    r.push_back(root);
    list<Uzel*>::iterator h = r.begin();
    while(h != r.end()){
        if((*h) -> left) r.push_back((*h) -> left);
        if((*h) -> right) r.push_back((*h) -> right);
        cout << (*h) -> key << " ";
        h++;
    }
    return r;
}


void BinTree::LRK(){
    LRK(root);
}

void BinTree::LRK(Uzel* r){
    if(r -> left) LRK(r -> left);
    cout << r -> key << " ";
    if(r -> right) LRK(r -> right);
}

void BinTree::_del(int k){
    Uzel* curr = root;
    Uzel* parent = NULL;
    while (curr && curr -> key != k){
        parent = curr;
        if(curr -> key > k){
            curr = curr -> left;
        }else{
            curr = curr -> right;
        }
    }
    if(!curr) return;
    if(curr -> left == NULL){
        if(parent && parent  -> left == curr) parent -> left = curr -> right;
        if(parent && parent  -> right == curr) parent -> right = curr -> right;
        delete curr;
        return;
    } 
    if(curr -> right == NULL){
        if(parent && parent -> left == curr) parent -> left = curr -> left;
        if(parent && parent -> right == curr) parent -> right = curr -> left;
        delete curr;
        return;
    }

    Uzel *temp = curr -> right;
    Uzel *r = NULL;
    if(temp -> left == NULL){
        curr -> key = temp -> key;
        curr -> right = temp -> right;
        delete temp;
        return;
    }else{
        while(temp -> left != NULL){
            r = temp;
            temp = temp -> left;
        }
        curr -> key = temp -> key;
        r -> left = temp -> right;
        delete temp;
        return;
    }


}

int BinTree::KRL(int *a){
    int k = 0;
    inarray(root, a, k);
    return k;
}

void BinTree::inarray(Uzel*q, int*a, int&k){
    if(q == NULL) return;
    a[k++] = q -> key;
    inarray(q -> right, a, k);
    inarray(q -> left, a, k);
}
    
BinTree::BinTree(const vector<int> &arr){
    if(arr.size() > 0){
        Uzel *q = new Uzel(arr[0]);

        int _k = 0, size_arr = arr.size();

        vector<int>::iterator i;

        for (size_t i = 1; i < size_arr; i++){
            _k = arr[i];
            
            Uzel* p = q;
            Uzel* g = p;

            while (p != NULL) {
                if (_k < p->key) {
                    g = p;
                    p = p -> left;
                }
                else {
                    g = p;
                    p = p -> right;
                }
            }

            p = new Uzel(_k);
            if (_k < g -> key) {
                g -> left = p;
            }
            else {
                g -> right = p;
            }
        }
        root = q;
    }else{
        root = NULL;
    }
}

BinTree::BinTree(const int *arr, int N){
    if(N > 0){
        Uzel *q = new Uzel(arr[0]);

        int _k = 0, size_arr = N;

        for (size_t i = 1; i < size_arr; i++){
            _k = arr[i];
            
            Uzel* p = q;
            Uzel* g = p;

            while (p != NULL) {
                if (_k < p->key) {
                    g = p;
                    p = p -> left;
                }
                else {
                    g = p;
                    p = p -> right;
                }
            }

            p = new Uzel(_k);
            if (_k < g -> key) {
                g -> left = p;
            }
            else {
                g -> right = p;
            }
        }
        root = q;
    }else{
        root = NULL;
    }
}


BinTree::~BinTree()
{
    rec_del(root); root = NULL;
}

BinTree BinTree::operator=(const BinTree& BT){
    if(this == &BT) return *this;
    this -> ~BinTree();
    if(BT.root == NULL) root = NULL;
    else{
        root = new Uzel(BT.root -> key);
        root -> left = CopyTree(BT.root -> left);
        root -> right = CopyTree(BT.root -> right);
    }

    return *this;
}


BinTree::BinTree(const BinTree &BN){
    if(BN.root == NULL) root = NULL;
    else{
        root = new Uzel(BN.root -> key);
        root -> left = CopyTree(BN.root -> left);
		root -> right = CopyTree(BN.root -> right);
    }
}


Uzel* BinTree::CopyTree(Uzel *q){
    if(q == NULL) return NULL;
    Uzel *p = new Uzel(q -> key);
    p -> left = CopyTree(q -> left);
    p -> right = CopyTree(q -> right);
    return p;
}



void rec_del(Uzel* q){
    if(q == NULL) return;
    if(q -> left) rec_del(q -> left);
    if(q -> right) rec_del(q -> right);
    delete q;
}


BinTree::BinTree(int n){
    if(root == 0) root = NULL;

    Uzel* q = new Uzel(rand() % 100);
    int k;
    for (int i = 1; i < n; i++) {
        k = rand() % 100;
        Uzel* p = q;//
        Uzel* g = p;
        while (p != NULL) {
            if (k < p -> key) {
                g = p;
                p = p -> left;
            }
            else {
                g = p;
                p = p -> right;
            }
        }
        p = new Uzel(k);
        if (k < g -> key) {
            g -> left = p;
        }
        else {
            g -> right = p;
        }//
    }
    root = q;
}
Uzel* BinTree::find_k(int k){
    Uzel *tmp = root;
    
    while(tmp != NULL && tmp -> key != k){
        if(k < tmp -> key) tmp = tmp -> left;
        if(k > tmp -> key) tmp = tmp -> right;
    }

    return tmp;
}
void BinTree::add(int k){
    Uzel* tmp = new Uzel(k);

    if(root == NULL){
        root = tmp;
        return;
    }

    Uzel* q = root;

    while(true){
        if(tmp -> key < q -> key){
            if(q -> left == NULL) break;
            q = q -> left; 
        }else{
            if(q -> right == NULL) break;
            q = q -> right;
        }
    }

    if( tmp -> key < q -> key) q -> left = tmp;
    else q -> right = tmp;

    return;
}
void BinTree::print_tree(Uzel *q, int k){
    if(q == NULL) return;

    print_tree(q -> left, k + 3);

    for (size_t i = 0; i < k; i++) cout << " ";
        cout.width(2);

    cout << q -> key << endl;

    print_tree(q -> right, k + 3);
    
}
int BinTree::min(){
    if(root == NULL){
        cout << "Дерево пустое" << endl;
        return -1;
    }

    Uzel* min = root;

    while(min -> left != NULL) min = min -> left;

    return min -> key;
}

void BinTree::print(ostream& out, int spaces, Uzel* node) const{
    if (node == NULL) {
        return;
    }
    print(out, spaces+4, node->right);

    for (int i = 0; i < spaces; i++) {
        out << " ";
    }
    out << node->key << endl;

    print(out, spaces+4, node->left);
}

int BinTree::max(){
    if(root == NULL){
        cout << "tree is empty!" << endl;
        return - 1;
    }
    
    Uzel* max = root;
    while(max -> right != NULL) max = max -> right;

    return max -> key;
}

ostream& operator<<(ostream& out, const BinTree& BT) {
    BT.print(out, 0, BT.root);
    return out;
}