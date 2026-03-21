#include <iostream>
#include <string>
using namespace std;
int main()
{
    string st;
    getline(cin,st);
    for(int i=0; i< st.size(); i++)
    {
        if(st[i]=='a'||st[i]=='A') st[i] = 'x';
        else if(st[i]=='b'||st[i]=='B') st[i] = 'y';
        else if(st[i]=='c'||st[i]=='C') st[i] = 'z';
        else if(st[i]=='d'||st[i]=='D') st[i] = 'f';
        else if(st[i]=='e'||st[i]=='E') st[i] = 'v';
        else if(st[i]=='f'||st[i]=='F') st[i] = 'u';
        else if(st[i]=='g'||st[i]=='G') st[i] = 't';
        else if(st[i]=='h'||st[i]=='H') st[i] = 'h';
        else if(st[i]=='i'||st[i]=='I') st[i] = 'r';
        else if(st[i]=='j'||st[i]=='J') st[i] = 'x';
        else if(st[i]=='k'||st[i]=='K') st[i] = 'p';
        else if(st[i]=='l'||st[i]=='L') st[i] = 'a';
        else if(st[i]=='m'||st[i]=='M') st[i] = 'n';
        else if(st[i]=='n'||st[i]=='N') st[i] = 'm';
        else if(st[i]=='o'||st[i]=='O') st[i] = 'l';
        else if(st[i]=='p'||st[i]=='P') st[i] = 'k';
        else if(st[i]=='q'||st[i]=='Q') st[i] = 'j';
        else if(st[i]=='r'||st[i]=='R') st[i] = 'i';
        else if(st[i]=='s'||st[i]=='S') st[i] = 's';
        else if(st[i]=='t'||st[i]=='T') st[i] = 'g';
        else if(st[i]=='u'||st[i]=='U') st[i] = 'w';
        else if(st[i]=='v'||st[i]=='V') st[i] = 'e';
        else if(st[i]=='w'||st[i]=='W') st[i] = 'd';
        else if(st[i]=='x'||st[i]=='X') st[i] = 'c';
        else if(st[i]=='y'||st[i]=='Y') st[i] = 'b';
        else if(st[i]=='z'||st[i]=='Z') st[i] = 'o';
        else continue;
 
    }
    cout << st;
}