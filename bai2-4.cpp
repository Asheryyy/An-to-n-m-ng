#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

char keyMatrix[5][5];
bool used[26];
char alphab[5][5] = {
    {'A','B','C','D','E'},
    {'F','G','H','I','K'},
    {'L','M','N','O','P'},
    {'Q','R','S','T','U'},
    {'V','W','X','Y','Z'}
    
};
void generateKeyMatrix(string key)
{
    memset(used, false, sizeof(used));
    int row = 0, cowl = 0;

    for(char c: key)
    {
        if(c == 'J') c = 'I';
        if(!used[c-'A'])
        {
            keyMatrix[row][cowl++] = c;
            used[c - 'A'] = true;

            if(cowl == 5)
            {
                cowl =0; 
                row ++;
            }
        }

    }
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        {
            if(!used[alphab[i][j] - 'A'])
            {
                keyMatrix[row][cowl++] = alphab[i][j];
                used[alphab[i][j] - 'A'] = true;
                if(cowl ==5)
                {
                    cowl = 0;
                    row++;
                }
            }
        }
    }
}

string prepareText(string text) {
    string result = "";

    for (char c : text) {
        if (c >= 'a' && c <= 'z') c -= 32;
        if (c == 'J') c = 'I';
        if (c >= 'A' && c <= 'Z')
            result += c;
    }

    for (int i = 0; i < result.length(); i += 2) {
        if (i + 1 == result.length()) {
            result += 'X';
        } else if (result[i] == result[i + 1]) {
            result.insert(i + 1, "X");
        }
    }

    return result;
}
void findPosition(char cha, int& r, int& c)
{
    if(cha == 'J') cha = 'I';

    for(int row=0; row<5; row++)
    {
        for(int cowl=0; cowl<5; cowl++)
        {
            if(keyMatrix[row][cowl]==cha) 
            {
                r=row;
                c=cowl;
                return;
            }
        }
    }

}
string encrypt(string text)
{
    string cipher = "";
    for(int i = 0; i< text.length(); i+=2)
    {
        int r1,r2,c1,c2;
        findPosition(text[i],r1,c1);
        findPosition(text[i+1],r2,c2);

       if(r1==r2)
        {
            cipher+=keyMatrix[r1][(c1+1)%5];
            cipher+=keyMatrix[r2][(c2+1)%5];
        }
        else if(c1==c2)
        {
            cipher+=keyMatrix[(r1+1)%5][c1];
            cipher+=keyMatrix[(r2+1)%5][c2];
        }
        else
        {
            cipher += keyMatrix[r1][c2];
            cipher += keyMatrix[r2][c1];
        }

    }
    return cipher;
}
string decrypt(string cipher) {
    string text = "";

    for (int i = 0; i < cipher.length(); i += 2) {
        int r1, c1, r2, c2;

        findPosition(cipher[i], r1, c1);
        findPosition(cipher[i + 1], r2, c2);

        if (r1 == r2) {
            text += keyMatrix[r1][(c1 + 4) % 5];
            text += keyMatrix[r2][(c2 + 4) % 5];
        }
        else if (c1 == c2) {
            text += keyMatrix[(r1 + 4) % 5][c1];
            text += keyMatrix[(r2 + 4) % 5][c2];
        }
        else {
            text += keyMatrix[r1][c2];
            text += keyMatrix[r2][c1];
        }
    }

    return text;
}

int main()
{
    do
    {
        int x;
        cout << "CHUONG TRINH MA HOA HOAC GIAI MA"<<endl;
        cout << "1. MA HOA"<< endl;
        cout << "2. GIAI MA"<< endl;
        cout << "3. THOAT"<<endl;
        cout << "CHOOSE: ";
        cin >> x;
        if(x==1)
        {
            string key, plaintext;;
            cout << "Nhap Key: ";
            cin >> key;
            generateKeyMatrix(key);
            cout << "Nhap plaintext: ";
            cin >> plaintext;

            
            for(int i=0; i<5; i++)
            {
                for(int j=0; j<5; j++)
                {
                cout << keyMatrix[i][j] << " ";
                }
                cout << endl;
            }

            string prepared = prepareText(plaintext);
            string cipher = encrypt(prepared);
        

            cout << "Ciphertext: " << cipher << endl;
        }
        if(x==2)
        {
            string cipherText;
            cout<< "Nhap ciphertext: ";
            cin >> cipherText;
            string decrypted = decrypt(cipherText);
            cout << "Decrypted: " << decrypted << endl;
        }
        if(x==3) break;
      
    }while(1);
   

    

    return 0;

}