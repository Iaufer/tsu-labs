#include <iostream>

using namespace std;
 
/* Works only if a >= 0 and b >= 0 */
int pow(int a, int b)
{
    if (b == 0)
        return 1;
    int answer = a;
    int increment = a;
    int i, j;
    for(i = 1; i < b; i++)
    {
        for(j = 1; j < a; j++)
        {
            answer += increment;
        }
        increment = answer;
    }
    return answer;
}
 
// Driver Code
int main()
{
    cout << pow(5, 6);
    return 0;
}