#include <iostream>
#include <string>

using namespace std;

int main()
{
    int k;
    cout << "Nhap khoa k (so buoc dich chuyen): "; 
    cin >> k;
    cin.ignore();

    string n;
    cout << "Nhap doan ma can GIAI MA: ";
    getline(cin, n);

    cout << "Ket qua sau khi giai ma: ";
    for(int i = 0; i < n.size(); i++)
    {
        char chu = n[i];
        
        if(chu >= 'a' && chu <= 'z')
        {
            int index = (chu - 'a' - k + 26) % 26;
            cout << (char)('a' + index);
        }
        else if(chu >= 'A' && chu <= 'Z')
        {
            int index = (chu - 'A' - k + 26) % 26;
            cout << (char)('A' + index);
        }
        else
        {
            cout << chu;
        }
    }
    cout << endl;
    return 0;
}