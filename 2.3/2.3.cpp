#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

double unigram_scores[26] = { 0 };
double bigram_scores[26][26] = { 0 };
double trigram_scores[26][26][26] = { 0 };

void init_scores() {
    unigram_scores['E' - 'A'] = 12.02; unigram_scores['T' - 'A'] = 9.10; unigram_scores['A' - 'A'] = 8.12;
    unigram_scores['O' - 'A'] = 7.68;  unigram_scores['I' - 'A'] = 7.31; unigram_scores['N' - 'A'] = 6.95;
    unigram_scores['S' - 'A'] = 6.28;  unigram_scores['R' - 'A'] = 6.02; unigram_scores['H' - 'A'] = 5.92;
    unigram_scores['D' - 'A'] = 4.32;  unigram_scores['L' - 'A'] = 3.98; unigram_scores['U' - 'A'] = 2.88;
    unigram_scores['C' - 'A'] = 2.71;  unigram_scores['M' - 'A'] = 2.61; unigram_scores['F' - 'A'] = 2.30;
    unigram_scores['Y' - 'A'] = 2.11;  unigram_scores['W' - 'A'] = 2.09; unigram_scores['G' - 'A'] = 2.03;
    unigram_scores['P' - 'A'] = 1.82;  unigram_scores['B' - 'A'] = 1.49; unigram_scores['V' - 'A'] = 1.11;
    unigram_scores['K' - 'A'] = 0.69;  unigram_scores['X' - 'A'] = 0.17; unigram_scores['Q' - 'A'] = 0.11;
    unigram_scores['J' - 'A'] = 0.10;  unigram_scores['Z' - 'A'] = 0.07;

    string good_bigrams[] = { "TH", "HE", "IN", "ER", "AN", "RE", "ND", "AT", "ON", "NT", "HA", "ES", "ST", "EN", "ED", "TO", "IT", "OU", "EA", "HI", "IS", "OR", "TI", "AS", "TE", "ET", "NG", "OF", "AL", "DE", "SE", "LE", "SA", "SI", "AR", "VE", "RA", "RO", "FI", "LL", "NO", "NE", "CO", "IL", "OM", "MA", "LI", "CH", "ME", "WA" };
    for (string b : good_bigrams) bigram_scores[b[0] - 'A'][b[1] - 'A'] = 3.0;

    string good_trigrams[] = { "THE", "AND", "ING", "ENT", "ION", "HER", "FOR", "THA", "NTH", "INT", "ERE", "TIO", "TER", "EST", "ERS", "ATI", "HAT", "ATE", "ALL", "ETH", "HES", "VER", "OFT", "ITH", "FRO", "TCH", "IGH", "OUT", "WIT", "HOU", "OME", "ULD", "PRO", "CON", "ART", "EVE", "ARE", "WAS", "WER", "HIS", "NOT", "THI", "YOU", "BUT", "HAV", "WHI", "ONE", "MAN" };
    for (string t : good_trigrams) trigram_scores[t[0] - 'A'][t[1] - 'A'][t[2] - 'A'] = 5.0;

    string bad_bigrams[] = { "QZ", "QX", "QJ", "JZ", "JX", "ZX", "ZJ", "XZ", "XQ", "VK", "VQ", "VJ", "WW", "XX", "YY", "ZZ", "QQ", "JJ", "KX", "KZ", "FX", "FZ", "HX", "HZ", "VW", "VX", "VZ", "XR", "XC", "XD", "XF", "XG", "XM", "XN", "XS", "XT", "XV", "XW", "XY", "CB", "CF", "CG", "CJ", "CP", "CV", "CW", "CX", "DX", "FQ", "GV", "GX", "PB", "PQ", "PX", "QB", "QC", "QD", "QE", "QF", "QG", "QH", "QK", "QL", "QM", "QN", "QO", "QP", "QR", "QS", "QT", "QV", "QW", "QY", "VB", "VC", "VD", "VF", "VG", "VH", "VP", "VQ", "VT", "ZP", "ZQ", "ZR", "ZS", "ZT", "ZU", "ZV", "ZW", "ZY" };
    for (string b : bad_bigrams) bigram_scores[b[0] - 'A'][b[1] - 'A'] = -20.0;
}

string clean_text(const string& text) {
    string res = "";
    for (size_t i = 0; i < text.length(); ++i) {
        if (isalpha(text[i])) res += toupper(text[i]);
    }
    return res;
}

double calculate_fitness(const string& clean_t) {
    double score = 0.0;
    int len = clean_t.length();
    for (int i = 0; i < len; ++i) {
        int c1 = clean_t[i] - 'A';
        score += unigram_scores[c1];
        if (i < len - 1) {
            int c2 = clean_t[i + 1] - 'A';
            score += bigram_scores[c1][c2];
            if (i < len - 2) {
                int c3 = clean_t[i + 2] - 'A';
                score += trigram_scores[c1][c2][c3];
            }
        }
    }
    return score;
}

string fast_decrypt(const string& cipher, const string& key) {
    string plain = cipher;
    for (size_t i = 0; i < plain.length(); ++i) {
        plain[i] = key[plain[i] - 'A'];
    }
    return plain;
}

string full_decrypt(const string& cipher, const string& key) {
    string plain = cipher;
    for (size_t i = 0; i < plain.length(); ++i) {
        char c = plain[i];
        if (c >= 'A' && c <= 'Z') plain[i] = key[c - 'A'];
        else if (c >= 'a' && c <= 'z') plain[i] = tolower(key[toupper(c) - 'A']);
    }
    return plain;
}

string get_frequency_based_key(const string& clean_cipher) {
    int freq[26] = { 0 };
    for (size_t i = 0; i < clean_cipher.length(); ++i) {
        freq[clean_cipher[i] - 'A']++;
    }
    vector<pair<int, char>> sorted_freq;
    for (int i = 0; i < 26; ++i) sorted_freq.push_back(make_pair(freq[i], i + 'A'));
    sort(sorted_freq.rbegin(), sorted_freq.rend());

    string english_freq = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
    string key = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < 26; ++i) key[sorted_freq[i].second - 'A'] = english_freq[i];
    return key;
}

string generate_random_key() {
    string key = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 25; i > 0; i--) swap(key[i], key[rand() % (i + 1)]);
    return key;
}

int main() {
    srand(time(0));
    init_scores();

    cout << "=== GIAI MA MONO-ALPHABETIC ===" << endl;
    cout << "Hay dan (paste) Ciphertext vao day, go chu END o dong moi roi nhan Enter: \n\n";

    string ciphertext = "";
    string line;
    while (getline(cin, line)) {
        if (line == "END") break;
        ciphertext += line + "\n";
    }

    if (ciphertext.empty() || ciphertext == "\n") return 1;

    cout << "\nDang chay thuat toan Steepest Ascent (Tim duong di toi uu nhat)..." << endl;

    string clean_cipher = clean_text(ciphertext);
    string best_global_key = "";
    double best_global_score = -99999999.0;

    int num_restarts = 20;

    for (int restart = 0; restart < num_restarts; ++restart) {
        string current_key = (restart == 0) ? get_frequency_based_key(clean_cipher) : generate_random_key();
        double current_score = calculate_fitness(fast_decrypt(clean_cipher, current_key));

        bool improved = true;
        while (improved) {
            improved = false;
            double best_new_score = current_score;
            string best_new_key = current_key;

            for (int i = 0; i < 25; i++) {
                for (int j = i + 1; j < 26; j++) {
                    string new_key = current_key;
                    swap(new_key[i], new_key[j]);

                    double new_score = calculate_fitness(fast_decrypt(clean_cipher, new_key));

                    if (new_score > best_new_score) {
                        best_new_score = new_score;
                        best_new_key = new_key;
                        improved = true;
                    }
                }
            }
            if (improved) {
                current_score = best_new_score;
                current_key = best_new_key;
            }
        }

        if (current_score > best_global_score) {
            best_global_score = current_score;
            best_global_key = current_key;
        }
    }

    cout << "\n=== KET QUA GIAI MA HOAN CHINH ===" << endl;
    cout << "[+] Key tim duoc: " << best_global_key << endl;
    cout << "[+] Ban ro: \n\n" << full_decrypt(ciphertext, best_global_key) << endl;

    return 0;
}