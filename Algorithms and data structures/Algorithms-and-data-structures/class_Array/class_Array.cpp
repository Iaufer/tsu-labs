#include <iostream>
#include <cmath>
#include <ctime>
#include <chrono>


using namespace std;

class Array
{
    int *a, n;
  public:
    // конструктор 1
    // len – число элементов в массиве
    // t = 1 – неупорядоченный массив
    // t = 2 – массив, упорядоченный по неубыванию
    // t = 3 – массив, упорядоченный по невозрастанию
    // d – диапазон псевдослучайных чисел для неупорядоченного массива (при t = 1)
    Array(int len = 1, int t = 1, int d = 10);

    Array(int *, int); // конструктор 2: по массиву
    Array(Array &);
    ~Array()
    {
        if(a != nullptr)
            delete[] a;
    }
    Array& operator = (Array &);
    int &operator [](int);

    bool Test(); // проверка на упорядоченность по неубыванию
    bool operator == (const Array &); // равенство элементов массивов (но не порядка)

    void Shell_sort();
    void Heapsort();
    void Hoar_sort(int, int);
    void Bit_sort(int, int);
    friend istream & operator >> (istream &, Array &);
    friend ostream & operator << (ostream &, Array &);

    void sift(int, int);
};

Array::Array(int len, int t, int d)
{
    if(len > 0) n = len; //
    else n = 1;

    a = new int[n];

    if(t == 1)
    {
        for(int i = 0; i < n; i++)
        {
            a[i] = rand() % d;
        }
    }

    if(t == 2)
    {
        a[0] = rand() % d;

        for(int i = 1; i < n; i++)
        {
            a[i] = a[i - 1] + rand() % d;
        }
    }

    if(t == 3)
    {
        a[n - 1] = rand() % d;

        for(int i = n - 2; i >= 0; i--)
        {
            a[i] = a[i + 1] + rand() % d;
        }
    }
    /* for(int i = 0; i < len; i++)
    {
        cout << a[i];
    } */
}

Array::Array(int *A, int len)
{
    a = new int[len];
    n = len;

    for(int i = 0; i < len; i++)
    {
        a[i] = A[i];
    }
}

Array::Array(Array& A)
{
    //if(this != &A)
    //{
        n = A.n;
        a = new int[n];

        for(int i = 0; i < n; i++)
        {
            a[i] = A.a[i];
        }
    //}
}

Array& Array::operator=(Array& A)
{
    if(this != &A)
    {
        n = A.n;
        a = new int[n];
        for(int i = 0; i < A.n; i++)
        {
            a[i] = A.a[i];
        }
    }
    
    return *this;
    
}

int& Array::operator[](int i)
{
    if(i >= n || i < 0)
    {
        cout << "FAIL INDEX";
        exit(0);
    }else
    {
        return a[i];
    }
}


bool Array::Test()
{
    for(int i = 0; i < n - 1; i++)
    {
        if(a[i] > a[i + 1])
        {
            return false;
        }
    }
    
    return true;
}

bool Array::operator==(const Array& A)
{
    if(this != &A)
    {
        if(n == A.n)
        {
            int *arr = new int[n];

            for(int i = 0; i < n; i++) arr[i] = 1;

            for(int i = 0; i < n; i++)
            {
                for(int j = 0; j < A.n; j++)
                {
                    if((a[i] == A.a[j]) && (arr[j] == 1))
                    {
                        arr[j]--;
                    }
                }
            }

            for(int i = 0; i < n; i++)
            {
                if(arr[i] != 0) return false;
                return true;
            }
        }

        return false;
    }

    return true;
}

void Array::Shell_sort()
{
    int temp = 0, k = 0;

    for(int i = n / 2; i > 0; i /= 2)
    {
        //cout << i << "\n";
        for(int j = 0; j < i; j++)
        {
            for(int q = i + j; q < n; q += i)
            {
                temp = a[q];

                for(k = q - i; (k >= 0) && (a[k] > temp); k -= i)
                {
                    a[k + i] = a[k];
                }

                a[k + i] = temp;
            }
        }
        cout << i << "\n" << *this << "\n";
    }
}


void Array::sift(int i, int n)
{
    int j = 2 * i + 1, x = a[i], f = 1;

    while(j <= n && f)
    {
        if(j + 1 <= n)
        {
            if(a[j + 1] > a[j])
            {
                j = j + 1;
            }
        }

        if(a[j] > x)
        {
            a[i] = a[j];
            i = j;
            j = 2 * i + 1;
        }else
        {
            f = 0;
        }
    }

    a[i] = x;
}



void Array::Heapsort()
{
    int temp = 0;

    for(int i = (n / 2) - 1; i >= 0; i--)
    {
        sift(i, n);
    }

    for(int i = n - 1; i >= 1; i--)
    {
        temp = a[0];
        a[0] = a[i];
        a[i] = temp;

        sift(0, i - 1);
    }
}


void Array::Hoar_sort(int l, int r)
{
    if(l < r){;
    
        int i = l, j = r, xm = a[(l + r) / 2], temp = 0;

        while(i < j)
        {
            
            while((i <= j) && (a[i] < xm)) i++;
            while((j >= i) && (a[j] > xm)) j--;

            if(i <= j)
            {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
                i++;
                j--;
            }
        }
        cout << xm << " " << j << " " << i << " " << "\n";
        //cout << &a;
        Hoar_sort(l, j);
        Hoar_sort(i, r);
    }
}

ostream& operator<<(ostream& out, Array& A)
{
    //cout << A.n <<  "\n";
    for(int i = 0; i < A.n; i++)
    {
        out << A.a[i] << " ";
    }
    cout << "\n";

    return out;
}

istream& operator>>(istream& in, Array& A)
{
    in >> A.n;

    if(A.a != nullptr) delete[] A.a;

    A.a = new int[A.n];

    for(int i = 0; i < A.n; i++)
    {
        in >> A.a[i];
    }

    return in;
}


int main(int argc, char const *argv[])
{   
    using namespace std::chrono;
    srand(time(0));

    Array A(15, 1, 10), B(10000000, 1, 10), C(10000000, 1, 10), D(10, 1, 10), E(100, 1, 10);

    //cout << A;
    auto start_shell_sort = high_resolution_clock::now();
    A.Shell_sort();
    auto stop_shell_sort = high_resolution_clock::now();
    auto duration_shell_sort = duration_cast<microseconds>(stop_shell_sort - start_shell_sort);
    cout << "shell sorting time: " << duration_shell_sort.count() << "\n";
    //cout << A;
    

    //cout << B;
    /* auto start_heapsort = high_resolution_clock::now();
    B.Heapsort();
    auto stop_heapsort = high_resolution_clock::now();
    auto duration_heapsort = duration_cast<microseconds>(stop_heapsort - start_heapsort);
    cout << "Heapsort: " << duration_heapsort.count() << "\n"; */
    //cout << B;
    
    //cout << C;
    /* auto start_Hoar_sort = high_resolution_clock::now();
    C.Hoar_sort(0, 10000000 - 1);//второй аргумент размер массива - 1
    auto stop_Hoar_sort = high_resolution_clock::now();
    auto duration_Hoar_sort = duration_cast<microseconds>(stop_Hoar_sort - start_Hoar_sort);
    cout << "Hoar_sort: " << duration_Hoar_sort.count() << "\n"; */
    //cout << C;

    /* cout << D;
    C.Bit_sort(0, 10 - 1);
    cout << D; */

    /* if(A == B)
        cout << 1;
    else
        cout << 0;
    */
    //cout << A.Test();

    //cout << A[10];
    /* A = C;
    cout << "A: " << A;
    */
    return 0;
}
