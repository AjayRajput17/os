/* Q7.Design and implement a simple file system with basic 
operations like file creation, deletion, reading, and writing 
using data structures like inodes and file allocation tables.
*/

#include <iostream>
#include <string>

using namespace std;

#define MAX_FILES 50
#define BLOCK_SIZE 10
#define MAX_BLOCKS 50

// Structure to represent each file in the system
struct File {
    string fileName;
    int startBlock;
    int size;
    bool isAllocated;
};

class SimpleFileSystem {
private:
    File fileSystem[MAX_FILES];  // Array to store files
    bool blockAllocation[MAX_BLOCKS];  // Block allocation status (true = allocated, false = free)
    int fileCount;  // Current number of files

public:
    SimpleFileSystem() {
        fileCount = 0;
        for (int i = 0; i < MAX_BLOCKS; i++) {
            blockAllocation[i] = false;  // Initialize all blocks as free
        }
        for (int i = 0; i < MAX_FILES; i++) {
            fileSystem[i].isAllocated = false;  // Initialize all files as not allocated
        }
    }

    // Function to allocate contiguous blocks for a file
    int allocateBlocks(int size) {
        int startBlock = -1;
        int blockCount = 0;

        // Try to find contiguous free blocks
        for (int i = 0; i < MAX_BLOCKS; i++) {
            if (!blockAllocation[i]) {
                if (startBlock == -1) {
                    startBlock = i;  // First unallocated block found
                }
                blockCount++;
                if (blockCount == size) {
                    for (int j = startBlock; j < startBlock + size; j++) {
                        blockAllocation[j] = true;  // Mark blocks as allocated
                    }
                    return startBlock;
                }
            } else {
                startBlock = -1;
                blockCount = 0;
            }
        }
        return -1;  // Not enough space
    }

    // Function to create a file
    void createFile(string fileName, int size) {
        if (fileCount >= MAX_FILES) {
            cout << "Error: Maximum number of files reached." << endl;
            return;
        }

        int startBlock = allocateBlocks(size);

        if (startBlock == -1) {
            cout << "Error: Not enough contiguous blocks to create file." << endl;
            return;
        }

        // Initialize the file structure
        fileSystem[fileCount].fileName = fileName;
        fileSystem[fileCount].startBlock = startBlock;
        fileSystem[fileCount].size = size;
        fileSystem[fileCount].isAllocated = true;
        fileCount++;

        cout << "File created successfully!" << endl;
    }

    // Function to delete a file
    void deleteFile(string fileName) {
        for (int i = 0; i < fileCount; i++) {
            if (fileSystem[i].fileName == fileName && fileSystem[i].isAllocated) {
                int startBlock = fileSystem[i].startBlock;
                int size = fileSystem[i].size;

                // Free the allocated blocks
                for (int j = startBlock; j < startBlock + size; j++) {
                    blockAllocation[j] = false;
                }

                // Mark the file as not allocated
                fileSystem[i].isAllocated = false;

                cout << "File deleted successfully!" << endl;
                return;
            }
        }
        cout << "Error: File not found." << endl;
    }

    // Function to write content to a file
    void writeFile(string fileName, string content) {
        for (int i = 0; i < fileCount; i++) {
            if (fileSystem[i].fileName == fileName && fileSystem[i].isAllocated) {
                cout << "Writing to file " << fileName << ": " << content << endl;
                return;
            }
        }
        cout << "Error: File not found or not allocated." << endl;
    }

    // Function to read the content of a file
    void readFile(string fileName) {
        for (int i = 0; i < fileCount; i++) {
            if (fileSystem[i].fileName == fileName && fileSystem[i].isAllocated) {
                cout << "Reading file " << fileName << ": " << endl;
                cout << "File content here (Content simulation)" << endl; // Simulating file content
                return;
            }
        }
        cout << "Error: File not found or not allocated." << endl;
    }

    // Function to list all files
    void listFiles() {
        cout << "Files in the system:" << endl;
        bool filesExist = false;
        for (int i = 0; i < fileCount; i++) {
            if (fileSystem[i].isAllocated) {
                cout << fileSystem[i].fileName << endl;
                filesExist = true;
            }
        }
        if (!filesExist) {
            cout << "No files found in the system." << endl;
        }
    }
};

int main() {
    SimpleFileSystem sfs;
    int choice;
    string fileName, content;
    int size;

    do {
        // Display menu options
        cout << "\nMenu:\n";
        cout << "1. Create File\n";
        cout << "2. Write to File\n";
        cout << "3. Read File\n";
        cout << "4. Delete File\n";
        cout << "5. List Files\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter file name: ";
                cin >> fileName;
                cout << "Enter file size (in blocks): ";
                cin >> size;
                sfs.createFile(fileName, size);
                break;

            case 2:
                cout << "Enter file name: ";
                cin >> fileName;
                cout << "Enter content: ";
                cin.ignore();
                getline(cin, content);
                sfs.writeFile(fileName, content);
                break;

            case 3:
                cout << "Enter file name: ";
                cin >> fileName;
                sfs.readFile(fileName);
                break;

            case 4:
                cout << "Enter file name: ";
                cin >> fileName;
                sfs.deleteFile(fileName);
                break;

            case 5:
                sfs.listFiles();
                break;

            case 6:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice, please try again.\n";
                break;
        }

    } while (choice != 6);

    return 0;
}

