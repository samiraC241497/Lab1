#include <bits/stdc++.h>
using namespace std;

int main(){

    string text;
    cout << "Enter text: ";
    cin >> text;

    map<char, int> freq;
    for(char c : text) freq[c]++;

    cout << "\nFrequencies : " << endl;
    for (auto it : freq) {
        cout << it.first << " : " << it.second << endl;
    }
    cout << endl;

    priority_queue<pair<int,string>,
        vector<pair<int,string>>,
        greater<pair<int,string>>> pq;

    for(auto it : freq){
        pq.push({it.second, string(1, it.first)});
    }

    map<char,string> code;

    while(pq.size() > 1) {
        auto left = pq.top(); pq.pop();
        auto right = pq.top(); pq.pop();

        for(char c : left.second)
            code[c] = "0" + code[c];

        for(char c : right.second)
            code[c] = "1" + code[c];

        pq.push({left.first + right.first,
                 left.second + right.second});
    }

    cout << "Huffman Codes : " << endl;
    for (auto it : freq) {
        cout << it.first << " : " << code[it.first] << endl;
    }
    cout << endl;

    int original = text.length() * 8;
    int compressed = 0;
    int table_bits = 0;

    for(auto it : freq) {
        compressed += it.second * code[it.first].length();
        table_bits += 8 + code[it.first].length();
    }

    cout << "Original Length : " << original << endl;
    cout << "Compressed msg length : " << compressed << endl;
    cout << "Table : " << table_bits << endl;
    cout << "New length : " << compressed + table_bits << endl;

    return 0;
}
