#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cout << "Enter number of activities: ";
    cin >> n;

    int start[100], finish[100];

    cout << "Enter start times:\n";
    for(int i = 0; i < n; i++)
        cin >> start[i];

    cout << "Enter finish times:\n";
    for(int i = 0; i < n; i++)
        cin >> finish[i];

    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(finish[i] > finish[j]) {

                int temp = finish[i];
                finish[i] = finish[j];
                finish[j] = temp;

                temp = start[i];
                start[i] = start[j];
                start[j] = temp;
            }
        }
    }

    cout << "Selected activities:\n";

    int lastFinish = finish[0];
    cout << start[0] << " " << finish[0] << endl;

    for(int i = 1; i < n; i++) {
        if(start[i] >= lastFinish) {
            cout << start[i] << " " << finish[i] << endl;
            lastFinish = finish[i];
        }
    }

    return 0;
}

