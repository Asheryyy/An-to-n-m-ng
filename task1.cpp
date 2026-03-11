#include <iostream>
#include <string>

using namespace std;

int main()
{
    int k;
    cout << "Nhập khóa k: "; 
    cin >> k;
    cin.ignore();

    string n;
    cout << "Nhập đoạn mã cần giải mã: ";
    getline(cin, n);

    cout << "Kết quả sau khi giải mã: ";
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