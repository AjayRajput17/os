#include <iostream>
using namespace std;

void solve(int n, int m, int available[], int allocation[][10], int need[][10]) {
    bool finish[10] = {false};
    int ans[10], idx = 0;

    while (idx < n) {
        bool found = false; //found flag is used to check if a process is found in each iteration that can be safely allocated resources.
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > available[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < m; j++) {
                        available[j] += allocation[i][j];
                    }
                    ans[idx++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            cout << "The system is not in a safe state." << endl;
            return;
        }
    }

    cout << "The system is in a safe state.\nSafe sequence is: ";
    for (int i = 0; i < n; i++) {
        cout << "P" << ans[i] << " ";
    }
    cout << endl;
}

int main() {
    int n, m;
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the number of resources: ";
    cin >> m;

    int available[10];
    int max[10][10], allocation[10][10], need[10][10];

    cout << "Enter the available resources: ";
    for (int i = 0; i < m; i++) {
        cin >> available[i];
    }

    cout << "Enter the Max matrix for each process (P0 to P" << n - 1 << "):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> max[i][j];
        }
    }

    cout << "Enter the Allocation matrix for each process (P0 to P" << n - 1 << "):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> allocation[i][j];
            need[i][j] = max[i][j] - allocation[i][j]; // Calculate Need matrix
        }
    }

    solve(n, m, available, allocation, need);
    return 0;
}


/*Enter the number of processes: 5
Enter the number of resources: 3
Enter the available resources: 3 3 2
Enter the Max matrix for each process (P0 to P4):
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
Enter the Allocation matrix for each process (P0 to P4):
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
The system is in a safe state.
Safe sequence is: P1 P3 P4 P0 P2
*/
