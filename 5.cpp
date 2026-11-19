#include <iostream>
#include <list>
using namespace std;

#define SIZE 10

// 1. Global Arrays (Sabse easy structure)
list<int> chainTable[SIZE]; // Chaining ke liye array of linked list
int probeTable[SIZE];       // Linear Probing ke liye normal array

// Hash Function (Common for both)
int hashFunction(int key) {
    return key % SIZE;
}

// ==========================================
// CHAINING LOGIC
// ==========================================
void insertChain(int key) {
    int index = hashFunction(key);
    chainTable[index].push_back(key); // In-built function to add at end
}

bool searchChain(int key) {
    int index = hashFunction(key);
    for (int x : chainTable[index]) { // Linked list traverse kar rahe hain
        if (x == key) 
        return true;
    }
    return false;
}

void displayChain() {
    cout << "\nChaining Hash Table:\n";
    for (int i = 0; i < SIZE; i++) {
        cout << i << " : ";
        for (int x : chainTable[i]) {
            cout << x << " -> ";
        }
        cout << "NULL\n";
    }
}

// ==========================================
// LINEAR PROBING LOGIC
// ==========================================
void insertProbe(int key) {
    int index = hashFunction(key);
    int i = 0;

    while (i < SIZE) {
        int newIndex = (index + i) % SIZE; // Magic Formula
        
        if (probeTable[newIndex] == -1) { // Agar jagah khali hai
            probeTable[newIndex] = key;
            return;
        }
        i++; // Nahi toh aage badho
    }
    cout << "Hash Table is Full!\n";
}

bool searchProbe(int key) {
    int index = hashFunction(key);
    int i = 0;

    while (i < SIZE) {
        int newIndex = (index + i) % SIZE;
        
        if (probeTable[newIndex] == -1) return false; // Khali matlab aage check mat karo
        if (probeTable[newIndex] == key) return true; // Mil gaya
        
        i++;
    }
    return false;
}

void displayProbe() {
    cout << "\nLinear Probing Hash Table:\n";
    for (int i = 0; i < SIZE; i++) {
        cout << i << " : ";
        if (probeTable[i] == -1) cout << "Empty";
        else cout << probeTable[i];
        cout << "\n";
    }
}

// ==========================================
// MAIN FUNCTION
// ==========================================
int main() {
    int n, key;

    // Step 1: Initialize probing table with -1
    for (int i = 0; i < SIZE; i++) {
        probeTable[i] = -1;
    }

    // Step 2: Take Input
    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> key;
        insertChain(key);
        insertProbe(key);
    }

    // Step 3: Display
    displayChain();
    displayProbe();

    // Step 4: Search
    cout << "\nEnter element to search: ";
    cin >> key;

    if (searchChain(key)) cout << "Found in Chaining\n";
    else cout << "Not Found in Chaining\n";

    if (searchProbe(key)) cout << "Found in Linear Probing\n";
    else cout << "Not Found in Linear Probing\n";

    return 0;
}