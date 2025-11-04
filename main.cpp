//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// USE ENCODER TO TEST DIFFERENT LENGTHS OF WORDS

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {
    // TODO:
    // 1. Create a MinHeap object.
    MinHeap heap = MinHeap();

    // 2. Push all leaf node indices into the heap.
    for (int i = 0; i < nextFree; ++i) {
        heap.push(i, weightArr);
    }



    // 3. While the heap size is greater than 1:
    //    - Pop two smallest nodes
    //    - Create a new parent node with combined weight
    //    - Set left/right pointers
    //    - Push new parent index back into the heap

    while (heap.size > 1) {

        // gets the current lowest key from heap.data
        int node1 = heap.pop(weightArr);

        // second heap.pop call
        int node2 = heap.pop(weightArr);

        // increment node pos
        leftArr[nextFree] = node1;
        rightArr[nextFree] = node2;

        // adds the weights together to make new parent
        int parent = weightArr[node1] + weightArr[node2];
        weightArr[nextFree] = parent;

        //pushes parent index back into heap
        heap.push(nextFree, weightArr);
        nextFree++;

    }

    // 4. Return the index of the last remaining node (root)
    return heap.data[0];
}


// Step 4: Use an STL stack to generate codes
/*
 *Generate code first pushes root into stack, from there it will push
 *its left and right child if it is an internal node (when leftArr[] and rightArr[] != =1)
 *if it is a leaf node, it records the resulting code in codes[], with the index matching
 *its repsective letter
 */
void generateCodes(int root, string codes[]) {

    stack<pair<int, string>> codesStack;
    // push the root into codeStack
    codesStack.push(pair<int, string>(root, ""));
    if (leftArr[root] == -1 && rightArr[root] == -1) {
        codes[charArr[root] - 'a'] = "0";
        return;
    }

    while (!codesStack.empty()) {
        pair<int, string> code = codesStack.top();
        codesStack.pop();

        // records node at index matching letter
        if (leftArr[code.first] == -1 && rightArr[code.first] == -1) {
           codes[charArr[code.first] - 'a']  = code.second;
        }

        // prevents the pushing of invalid nodes
        if (leftArr[code.first] != -1) {
            codesStack.push(pair<int, string>(leftArr[code.first], code.second + "0"));
        }

        if (rightArr[code.first] != -1) {
            codesStack.push(pair<int, string>(rightArr[code.first], code.second + "1"));
        }


    }



    // TODO:
    // Use stack<pair<int, string>> to simulate DFS traversal.
    // Left edge adds '0', right edge adds '1'.
    // Record code when a leaf node is reached.

}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}
