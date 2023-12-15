#include "AC.h"

unsigned short H=h, L=l;

int main(){
    ifstream fin("text.txt", ios::binary);
    if(!fin.is_open()){cout<<"error"; return 0;}
    ofstream fout("Encode.txt", ios::binary);
    if(!fout.is_open()){cout<<"error"; return 0;}

    map<char,int>m;
    list<Range> t;
    char c;
    unsigned long long len=0;
    for(fin.get(c);!fin.eof();fin.get(c)) m[c]++;
    fin.clear();
    fin.seekg(0);

    t=CreateList(m);
    PrintList(t);

    int k=m.size();
    fout.write((char*)&k, sizeof(k));
    for(auto it = m.begin(); it!= m.end(); it++)
    {
        fout.write((char*)&it-> first, sizeof(it-> first)); fout.write((char*)&it -> second,sizeof(it -> second));
    }

    list<Range>::iterator it;
    
    int delitel=t.back().R;
	int bits_to_follow = 0;
	char tmp = 0;
    int count=0;
    char s; 
    while(fin.get(s)){  
        for(it=t.begin(); it->c!=s; it++);  
        int d=H-L+1;
        H = L + it->R * d/delitel-1;
		L = L + it->L * d/delitel;
        for(;;){
            if(H<Half){
                count++;
		if (count == 8)
		{
			fout.put(tmp);
			tmp = 0;
			count = 0;
		}
		for (; bits_to_follow > 0; bits_to_follow--)
		{
			tmp = tmp | (1 << (7 - count));
                        count++;
			if (count == 8)
			{
				fout.put(tmp);
				tmp = 0;
				count = 0;
			}
		}	
            }
            else if(L>=Half){
                tmp = tmp | (1 << (7 - count));
			count++;
			if (count == 8)
			{
				fout.put(tmp);
				tmp = 0;
				count = 0;
			}
			for (; bits_to_follow > 0; bits_to_follow--)
			{
                    count++;
				if (count == 8)
				{
					fout.put(tmp);
					tmp = 0;
					count = 0;
				}
				}
                L-= Half; H-= Half;

            }
            else if((L>=First_qtr)&&(H<Thride_qtr)){
                bits_to_follow++;
		L -= First_qtr; H -= First_qtr;
            }
            else break;
            L <<= 1;
		    H <<= 1;
            H++;
        }
    }
    
 
    fin.close();
    fout.close();
}


