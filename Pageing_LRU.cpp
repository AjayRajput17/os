/* Q6.Implement a virtual memory system with features like demand paging,
 page replacement algorithms (e.g., FIFO, LRU,Optimal), and handling page faults.

*/

#include <iostream>
#include <vector>

using namespace std;

void fifo(int n, int frames_size, vector<int>& arr) {
    vector<int> frames(frames_size, -1);
    int page_faults = 0;
    int index = 0;

    for (int i = 0; i < n; i++) {
        bool page_hit = false;

        // Check if the page is already in the frames
        for (int j = 0; j < frames_size; j++) {
            if (frames[j] == arr[i]) {
                page_hit = true;
                break;
            }
        }

        if (!page_hit) {
            frames[index] = arr[i];
            index = (index + 1) % frames_size;
            page_faults++;
        }

        cout << "Frames after accessing page " << arr[i] << ": ";
        for (int j = 0; j < frames_size; j++) {
            if (frames[j] != -1)
                cout << frames[j] << " ";
        }
        cout << "\n";
    }

    cout << "Page faults: " << page_faults << "\nPage Hits: " << n - page_faults << "\n";
}

void lru(int n, int frames_size, vector<int>& arr) {
    vector<int> frames(frames_size, -1);
    vector<int> timestamps(frames_size, 0);
    int page_faults = 0;

    for (int i = 0; i < n; i++) {
        bool page_hit = false;

        // Check if the page is already in the frames
        for (int j = 0; j < frames_size; j++) {
            if (frames[j] == arr[i]) {
                page_hit = true;
                timestamps[j] = i;
                break;
            }
        }
    

        if (!page_hit) {
            int lru_index = 0;
            for (int j = 1; j < frames_size; j++) {
                if (timestamps[j] < timestamps[lru_index]) {
                    lru_index = j;
                }
            }
            frames[lru_index] = arr[i];
            timestamps[lru_index] = i;
            page_faults++;
        }

        cout << "Frames after accessing page " << arr[i] << ": ";
        for (int j = 0; j < frames_size; j++) {
            if (frames[j] != -1)
                cout << frames[j] << " ";
        }
        cout << "\n";
    }

    cout << "Page faults: " << page_faults << "\nPage Hits: " << n - page_faults << "\n";
}

void optimal(int n, int frames_size, vector<int>& arr) {
    vector<int> frames(frames_size, -1);
    int page_faults = 0;

    for (int i = 0; i < n; i++) {
        bool page_hit = false;

        // Check if the page is already in the frames
        for (int j = 0; j < frames_size; j++) {
            if (frames[j] == arr[i]) {
                page_hit = true;
                break;
            }
        }

        if (!page_hit) {
            bool is_frame_empty = false;
            for (int j = 0; j < frames_size; j++) {
                if (frames[j] == -1) {
                    frames[j] = arr[i];
                    is_frame_empty = true;
                    break;
                }
            }

            if (!is_frame_empty) {
                int farthest = i, replace_index = -1;
                for (int j = 0; j < frames_size; j++) {
                    int next_use = -1;
                    for (int k = i + 1; k < n; k++) {
                        if (arr[k] == frames[j]) {
                            next_use = k;
                            break;
                        }
                    }
                    if (next_use == -1) {
                        replace_index = j;
                        break;
                    } else if (next_use > farthest) {
                        farthest = next_use;
                        replace_index = j;
                    }
                }
                frames[replace_index] = arr[i];
            }

            page_faults++;
        }

        cout << "Frames after accessing page " << arr[i] << ": ";
        for (int j = 0; j < frames_size; j++) {
            if (frames[j] != -1)
                cout << frames[j] << " ";
        }
        cout << "\n";
    }

    cout << "Page faults: " << page_faults << "\nPage Hits: " << n - page_faults << "\n";
}

int main() {
    int n, frames_size;
    cout << "Enter the total pages and frame size: ";
    cin >> n >> frames_size;
    vector<int> arr(n);
    cout << "Enter the pages: ";
    for (int i = 0; i < n; i++) cin >> arr[i];

    int choice;
    char cont;
    do {
        cout << "\nChoose Page Replacement Algorithm:\n";
        cout << "1. FIFO\n2. LRU\n3. Optimal\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nRunning FIFO Algorithm:\n";
                fifo(n, frames_size, arr);
                break;
            case 2:
                cout << "\nRunning LRU Algorithm:\n";
                lru(n, frames_size, arr);
                break;
            case 3:
                cout << "\nRunning Optimal Algorithm:\n";
                optimal(n, frames_size, arr);
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                continue;
        }

        cout << "----------------------------\n";
        cout << "Do you want to try another algorithm? (y/n): ";
        cin >> cont;
    } while (cont == 'y' || cont == 'Y');

    cout << "Exiting...\n";
    return 0;
}

