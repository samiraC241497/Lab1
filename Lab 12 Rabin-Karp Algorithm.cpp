#include <bits/stdc++.h>
using namespace std;

int main() {
    string text, pattern;
    cout << "Enter text: ";
    cin >> text;
    cout << "Enter pattern: ";
    cin >> pattern;

    int n = text.length();
    int m = pattern.length();

    int base = 256;
    int mod = 101;

    int patHash = 0, txtHash = 0, power = 1;

    for(int i = 0; i < m - 1; i++)
        power = (power * base) % mod;


    for(int i = 0; i < m; i++) {
        patHash = (base * patHash + pattern[i]) % mod;
        txtHash = (base * txtHash + text[i]) % mod;
    }

    for(int i = 0; i <= n - m; i++) {

        if(patHash == txtHash) {
            bool found = true;
            for(int j = 0; j < m; j++) {
                if(text[i + j] != pattern[j]) {
                    found = false;
                    break;
                }
            }

            if(found)
                cout << "Pattern found at index: " << i << endl;
        }
        if(i < n - m) {
            txtHash = (base * (txtHash - text[i] * power) + text[i + m]) % mod;
            if(txtHash < 0) txtHash += mod;
        }
    }

    return 0;
}

