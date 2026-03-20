#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cmath>

using namespace std;

const double ENGLISH_FREQ[26] = {
    0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015,
    0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749,
    0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758,
    0.00978, 0.02360, 0.00150, 0.01974, 0.00074
};

string clean_text(const string& text) {
    string cleaned = "";
    for (char c : text) {
        if (isalpha(c)) {
            cleaned += toupper(c);
        }
    }
    return cleaned;
}

double calculate_ic(const string& text) {
    int N = text.length();
    if (N <= 1) return 0.0;

    int counts[26] = { 0 };
    for (char c : text) {
        counts[c - 'A']++;
    }

    double ic = 0.0;
    for (int i = 0; i < 26; i++) {
        ic += counts[i] * (counts[i] - 1);
    }
    return ic / (N * (N - 1));
}

int find_key_length(const string& text, int max_len = 20) {
    int best_len = 1;
    double best_ic_diff = 1.0; 

    cout << "\n[*] B1: Phan tich Chi so trung hop (IC) de tim do dai khoa..." << endl;

    for (int len = 2; len <= max_len; len++) {
        double total_ic = 0.0;
        for (int i = 0; i < len; i++) {
            string column = "";
            for (size_t j = i; j < text.length(); j += len) {
                column += text[j];
            }
            total_ic += calculate_ic(column);
        }
        double avg_ic = total_ic / len;

        if (avg_ic > 0.055) {
            cout << "  -> Do dai = " << len << " | IC trung binh = " << avg_ic << endl;
        }

        double diff = abs(avg_ic - 0.066); // So sánh với IC chuẩn của tiếng Anh
        if (diff < best_ic_diff) {
            best_ic_diff = diff;
            best_len = len;
        }
    }
    return best_len;
}

double chi_squared(int counts[], int length) {
    double chi = 0;
    for (int i = 0; i < 26; i++) {
        double expected = length * ENGLISH_FREQ[i];
        if (expected > 0) {
            double diff = counts[i] - expected;
            chi += (diff * diff) / expected;
        }
    }
    return chi;
}

// Bước 2: Tìm từng ký tự của khóa dựa trên độ dài đã biết
string find_key(const string& text, int key_len) {
    string key = "";

    for (int i = 0; i < key_len; i++) {
        string column = "";
        for (size_t j = i; j < text.length(); j += key_len) {
            column += text[j];
        }

        double min_chi = 9999999.0;
        char best_char = 'A';

        // Thử dịch cột này đi độ dịch shift (0-25) và kiểm tra Chi-squared
        for (int shift = 0; shift < 26; shift++) {
            int counts[26] = { 0 };
            for (char c : column) {
                // Giải mã thử ký tự này với độ dịch 'shift'
                char dec = (c - 'A' - shift + 26) % 26 + 'A';
                counts[dec - 'A']++;
            }

            double chi = chi_squared(counts, column.length());
            if (chi < min_chi) {
                min_chi = chi;
                best_char = shift + 'A';
            }
        }
        key += best_char;
    }
    return key;
}

// Hàm giải mã Vigenère giữ nguyên định dạng (khoảng trắng, dấu câu, hoa/thường)
string decrypt_vigenere(const string& cipher, const string& key) {
    string plain = "";
    int key_len = key.length();
    int k_idx = 0;

    for (char c : cipher) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            int shift = toupper(key[k_idx % key_len]) - 'A';
            char dec = (c - base - shift + 26) % 26 + base;
            plain += dec;
            k_idx++;
        }
        else {
            plain += c; // Giữ nguyên dấu câu
        }
    }
    return plain;
}

int main() {
    cout << "=== CHUONG TRINH GIAI MA VIGENERE TU DONG ===" << endl;
    cout << "(De hoan tat viec nhap, hay go chu END o mot dong moi va nhan Enter): \n\n";

    string ciphertext = "";
    string line;

    // Vòng lặp đọc nhiều dòng liên tục
    while (getline(cin, line)) {
        if (line == "END") {
            break;
        }
        ciphertext += line + "\n";
    }

    if (ciphertext.empty() || ciphertext == "\n") {
        cout << "[!] Ban chua nhap Ciphertext nao ca!" << endl;
        return 1;
    }

    // Tiền xử lý: Lọc text để tính toán
    string clean_cipher = clean_text(ciphertext);


    // B1: Tìm độ dài khóa
    int key_length = find_key_length(clean_cipher);
    cout << "\n[+] Do dai khoa co kha nang cao nhat la: " << key_length << endl;

    // B2: Tìm khóa
    string key = find_key(clean_cipher, key_length);
    cout << "[+] Khoa (Key) tim duoc la: " << key << endl;

    // B3: Giải mã và in kết quả
    string plaintext = decrypt_vigenere(ciphertext, key);

    cout << "\n================ KET QUA GIAI MA ================\n";
    cout << plaintext << endl;
    cout << "=================================================\n";

    return 0;
}