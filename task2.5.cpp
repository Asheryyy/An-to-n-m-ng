#include<bits/stdc++.h>

using namespace std;

void mahoa()
{
    string k;
    cout << "Nhập khóa k: ";
    cin >> k;
    int m = k.size();
    string n;
    cout << "Nhập đoạn mã cần mã hóa: ";
    cin.ignore();
    getline(cin, n);
    for(int i=0;i< n.size();i++)
    {
        int t = i% m;
        char chu = n[i];
        if(chu >= 'a' && chu <= 'z')
        {
            int idx = (chu - 'a' + (k[t] - 'a')) % 26;
            cout << (char)(idx + 'a');
        }
        else if(chu >= 'A' && chu <= 'Z')
        {
            int idx = (chu - 'A' + (k[t] - 'A')) % 26;
            cout << (char)(idx + 'A');
        }
        else
        {
            cout << chu;
        }
    }
}

void giaima()
{
    string k;
    cout << "Nhập khóa k: ";
    cin >> k;
    int m = k.size();
    cin.ignore();
    string n;
    cout << "Nhập đoạn mã cần giải mã: ";
    getline(cin, n);
    for(int i=0; i< n.size();i++)
    {
        int x = i % m;
        char chu = n[i];
        if(chu >= 'a' && chu <= 'z')
        {
            int index = (chu - 'a' -(k[x] - 'a') + 26) % 26;
            cout << (char)('a' + index);
        }
        else if(chu >= 'A' && chu <= 'Z')
        {
            int index = (chu - 'A' - (k[x] - 'A') + 26) % 26;
            cout << (char)('A' + index);
        }
        else
        {
            cout << chu;
        }
    }
}



int main()
{
    int chon;
    cout << "1. Mã hóa\n2. Giải mã\nChọn chức năng (1/2): ";
    cin >> chon;
    if(chon == 1)
    {
        mahoa();
    }
    else if(chon == 2)
    {
        giaima();
    }
    else
    {
        cout << "Lựa chọn không hợp lệ.\n";
    }
}