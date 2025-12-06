#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of characters: ";
    cin >> n;

    char ch[100];
    int freq[100];
    string code[100];
    cout << "Enter characters:\n";
    for(int i=0;i<n;i++) cin >> ch[i];

    cout << "Enter frequencies:\n";
    for(int i=0;i<n;i++) {
        cin >> freq[i];
        code[i] = "";
    }

    while(true) {
        int min1 = -1, min2 = -1;
        int active = 0;
        for(int i=0;i<n;i++)
            if(freq[i] != -1) active++;

        if(active == 1) break;

        for(int i=0;i<n;i++) {
            if(freq[i] != -1) {
                if(min1 == -1 || freq[i] < freq[min1]) {
                    min2 = min1;
                    min1 = i;
                }
                else if(min2 == -1 || freq[i] < freq[min2]) {
                    min2 = i;
                }
            }
        }
        code[min1] = "0" + code[min1];
        code[min2] = "1" + code[min2];

        freq[min1] = freq[min1] + freq[min2];
        freq[min2] = -1;
    }

    cout << "\nHuffman Codes:\n";
    for(int i=0;i<n;i++) {
        cout << ch[i] << " : " << code[i] << endl;
    }

    return 0;
}

