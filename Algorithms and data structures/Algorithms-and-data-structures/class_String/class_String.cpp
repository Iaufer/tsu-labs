#include <iostream>
#include <string.h>

using namespace std;

class String
{
    char *str;
    int len;

  public:
  
    String(int l = 0);
    String(const char *);
    String(String &);
    ~String()
    {
        if(str)
            delete []str;

        str = NULL;
    }
   
    int Len();//+

    String & operator = (const String &);//+

    char &operator [](int);//+

    bool operator == (String &);//+
    bool operator != (String &);//+
    
    String operator + (const String &);//+
    String & operator += (const String &);
    
    friend istream& operator >> (istream &, String &);
    friend ostream& operator << (ostream &, String &);//+
    
    int BMH_search(String &);
};

int String::BMH_search(String& s)
{
    int table[256];

    for(int i = 0; i < 255; i++)
    {
        table[i] = s.len;
    }
    
    for(int i = 0; i < s.len - 1; i++)
    {
        table[s.str[i]] = s.len - 1 - i;
    }

    for(int i = 0; i < s.len; i++)
    {
        cout << table[s.str[i]];
    }
    cout << "\n";

    int i = s.len - 1, j = s.len - 1, k = s.len - 1;

    cout << table[str[2]] << "\n";

    while(i < len)
    {
        if(j < 0) return i + 1 - s.len;

        k = i;
        j = s.len - 1;

        while(j >= 0)
        {
            if(str[k] == s.str[j])
            {
                j--;
                k--;
            }else
            {
                i = i + table[str[i]];
                j = s.len - 1;
                
                break;
            }
        }
    }

    if(j >= 0) return (-1);
    else return i + 1 - s.len;
}

String& String::operator+=(const String& s)
{
    int length = len + s.len;

    char *t = new char[length + 1];

    for(int i = 0; i < len; i++)
    {
        t[i] = str[i];
    }

    for(int i = 0; i < length; i++)
    {
        t[i + len] = s.str[i];
    }

    delete[] str;

    str = t;

    len = length;   

    return *this;
}

String String::operator+(const String& s)
{
    String str_plus(len + s.len + 1);

    for(int i = 0; i < len; i++)
    {
        str_plus[i] = str[i];
    }

    for(int i = 0; i < len + s.len; i++)
    {
        str_plus[i + len] = s.str[i];
    }

    return str_plus;
}

String& String::operator=(const String& s)
{
    cout << *this <<" | " << &s << "| " << this <<  "\n";
    if(this != &s)//
    {
        delete[] str;

        str = new char[(len = s.len) + 1];

        for(int i = 0; i < len; i++)
        {
            str[i] = s.str[i];
        }

        str[len] = '\0';
    }
    
    cout << *this << " | " << &s << "\n";

    return *this;
}

istream& operator>>(istream& in, String& s)
{
    in >> s.len;

    delete[] s.str;
    
    s.str = new char[s.len];
    for(int i = 0; i < s.len; i++)
    {
        in >> s.str[i];
    } 

    return in;
}

ostream& operator<<(ostream& out, String& s)
{
    for(int i = 0; i < s.len; i++)
    {
        out << s.str[i];
    }

    return out;
}

bool String::operator!=(String& s)
{
    if(len != s.len) return true;

    for(int i = 0; i < len; i++)
    {
        if(str[i] != s.str[i])
        {
            return true;
        }
    }

    return false;
}

bool String::operator==(String& s)
{
    if(len != s.len) return false;

    for(int i = 0; i < len; i++)
    {
        if(str[i] != s.str[i]) return false;
    }
    
    //cout << "tra";

    return true;
}

char& String::operator[](int i)
{
    return str[i];
}

int String::Len()
{
    int length = 0;

    while(str[length])
    {
        length++;
    }

    return length;
}

String::String(String& s)
{
    str = new char[s.len + 1];

    for(len = 0; str[len] = s.str[len]; len++);
}
String::String(const char* s)
{
    str = new char[strlen(s) + 1];

    for(len = 0; str[len] = s[len]; len++);
}

String::String(int l)
{
    str = new char[l];

    len = l;
    str[0] = '\0';
}

int main(int argc, char const *argv[])
{
    String s1("123hello23");
    String s2("hello");
    String s3;

    int k = s1.BMH_search(s2);

    cout << "\n" << k << "\n";


    //s1 += s2;
    //cout << s1 << "\n";

    /*if(s1 != s2)
    {
        cout << "true" << "\n";
    }else
    {
        cout << "false" << "\n";
    }*/

    /*if(s1 == s2)
    {
        cout << "true" << "\n";
    }else
    {
        cout << "false" << "\n";
    }*/

    //cout << s1[-1];
    //cout << s1.Len();
    
    return 0;
}

