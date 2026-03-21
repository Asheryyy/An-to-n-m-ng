#include <iostream>
#include <string>
using namespace std;

// mod theo kiểu CrypTool (1..26)
int mod26(int x) {
    int r = x % 26;
    if (r <= 0) r += 26;
    return r;
}

// A=1,...,Z=26
int charToNum(char c) {
    return c - 'A' + 1;
}

// 1..26 -> A..Z
char numToChar(int x) {
    return char(x - 1 + 'A');
}

// Chuẩn hóa chuỗi
string normalize(string s) {
    string res = "";
    for (char c : s) {
        if (isalpha(c)) res += toupper(c);
    }
    if (res.length() % 2 != 0) res += 'X';
    return res;
}

// Mã hóa
string encrypt(string text, int key[2][2]) {
    string result = "";

    for (int i = 0; i < text.length(); i += 2) {
        int a = charToNum(text[i]);
        int b = charToNum(text[i+1]);

        int c1 = mod26(key[0][0]*a + key[0][1]*b);
        int c2 = mod26(key[1][0]*a + key[1][1]*b);

        result += numToChar(c1);
        result += numToChar(c2);
    }
    return result;
}

// tìm nghịch đảo mod 26
int modInverse(int a) {
    a = mod26(a);
    for (int x = 1; x <= 26; x++) {
        if ((a * x) % 26 == 1) return x;
    }
    return -1;
}

// Giải mã
string decrypt(string text, int key[2][2]) {
    int det = key[0][0]*key[1][1] - key[0][1]*key[1][0];
    det = mod26(det);

    int invDet = modInverse(det);
    if (invDet == -1) return "Key khong nghich dao!";

    int invKey[2][2];
    invKey[0][0] = mod26( key[1][1] * invDet);
    invKey[0][1] = mod26(-key[0][1] * invDet);
    invKey[1][0] = mod26(-key[1][0] * invDet);
    invKey[1][1] = mod26( key[0][0] * invDet);

    string result = "";

    for (int i = 0; i < text.length(); i += 2) {
        int a = charToNum(text[i]);
        int b = charToNum(text[i+1]);

        int p1 = mod26(invKey[0][0]*a + invKey[0][1]*b);
        int p2 = mod26(invKey[1][0]*a + invKey[1][1]*b);

        result += numToChar(p1);
        result += numToChar(p2);
    }

    return result;
}

int main() {
    int key[2][2];

    cout << "Nhap key 2x2:\n";
    cout << "Nhap dong so thu nhat: ";
    cin >> key[0][0] >> key[0][1];
    cout << "Nhap dong so hai nhat: ";
    cin >> key[1][0] >> key[1][1];
    cin.ignore();

    string text;
    cout << "Nhap van ban: ";
    getline(cin, text);

    string clean = normalize(text);

    cout << "Text chuan hoa: " << clean << endl;

    string enc = encrypt(clean, key);
    cout << "Encrypt: " << enc << endl;

    string dec = decrypt(enc, key);
    cout << "Decrypt: " << dec << endl;

    return 0;
}