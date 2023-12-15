#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

class Route
{
    int *r, n;
    
  public:
    
    Route(int num = 0);
    Route(const Route&);
    
    Route& operator = (const Route&);
    
    ~Route()
    {
        if(r) delete []r;
        r = NULL;
    }
    
    int Route_price(int **);
    bool next_Route();

    friend ostream & operator << (ostream&, const Route&);
};

ostream& operator<<(ostream& out, const Route& a)
{
    for(int i = 0; i < a.n + 1; i++) out << a.r[i] << " ";

    return out;
}

int Route::Route_price(int** m)
{
    int weight = 0;

    for(int i = 1; i <= n; i++) 
        weight = weight + m[r[i - 1] -1][r[i] - 1];
    
    return weight;
}

int** create_matrix(int n)
{
    int **matrix = nullptr;
    matrix = new int*[n];

    srand((0));

    for(int i = 0; i < n; i++)
    {
        matrix[i] = new int[n];

        for(int j = 0; j < n; j++)
        {
            if(i != j)
            {
                matrix[i][j] = 1 + rand() % 20;
            }else
            {
                matrix[i][j] = 0;
            }
        }
    }
    return matrix;
}

bool Route::next_Route()
{
    int i = n - 1, j = n, temp = 0, weight = 0, min_weight = 0xFFFFFFF;

    //cout << "\n";

    
    //weight = Route_price(create_matrix(n));
    //cout << "route cost: "<< weight << "\n";
     

    while(r[i] >= r[i + 1] && (i > 0)) i--;

    if(i == 0) return false;

    while(r[i] >= r[j] && (i < j)) j--;

    if(i != j)
    {
        temp = r[i];
        r[i] = r[j];
        r[j] = temp;
    }

    for(i = i + 1, j = n - 1; i < j; i++, j--)
    {
        temp = r[i];
        r[i] = r[j];
        r[j] = temp;
    }
    
    return true;
}

Route& Route::operator=(const Route& rr)
{
    if(n != rr.n)
    {
        n = rr.n;

        delete[] r;

        r = new int[n + 1];
    }

    for(int i = 0; i < n + 1; i++)
    {
        r[i] = rr.r[i];
    }

    return *this;
}

Route::Route(const Route& rr)
{
    n = rr.n;

    r = new int[n + 1];

    for(int i = 0; i < n + 1; i++)
    {
        r[i] = rr.r[i];
    }   
}

Route::Route(int num)
{
    n = num;

    r = new int[num + 1];

    for(int i = 0; i < num; i++)
    {
        r[i] = i + 1;
    }

    r[num] = 1;
}

int main(int argc, char const *argv[])
{
    bool _bool = true;
    int** matrix = nullptr;
    int n = 0, MIN_WEIGHT = 0xFFFFFFF, weight = 0;

    cout << "Enter the number of cities: ";
    cin >> n;

    //srand ( time(NULL) );
    matrix = create_matrix(n);

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "\n";

    Route A(n), B(n);

    while(_bool == true)
    {
        weight = A.Route_price(matrix);

        cout << A << " " << "route cost:  " << weight << "\n";
        if(weight < MIN_WEIGHT)
        {
            MIN_WEIGHT = weight;
            B = A;
        }

        _bool = A.next_Route();

    }

    cout << B << "minimum cost: " << MIN_WEIGHT << "\n";

    return 0;
}
