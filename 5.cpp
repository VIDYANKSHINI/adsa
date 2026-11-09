
#include <iostream>
#include <list>
using namespace std;

#define SIZE 10

// Hash Table using Chaining
list<int> chainTable[SIZE];

// Hash Table using Linear Probing
int probeTable[SIZE];

// Hash Function
int hashFunction(int key)
{
    return key % SIZE;
}

// Insert element using Chaining
void insertChain(int key)
{
    int index = hashFunction(key);

    // Insert element at the end of linked list
    chainTable[index].push_back(key);
}

// Search element using Chaining
bool searchChain(int key)
{
    int index = hashFunction(key);

    // Traverse the linked list
    for (int x : chainTable[index])
    {
        if (x == key)
            return true;
    }

    return false;
}

// Insert element using Linear Probing
void insertProbe(int key)
{
    int index = hashFunction(key);
    int i = 0;

    // Find an empty position
    while (i < SIZE)
    {
        int newIndex = (index + i) % SIZE;

        // Check whether position is empty
        if (probeTable[newIndex] == -1)
        {
            probeTable[newIndex] = key;
            return;
        }

        // Check next position
        i++;
    }

    cout << "Hash Table is Full!" << endl;
}

// Search element using Linear Probing
bool searchProbe(int key)
{
    int index = hashFunction(key);
    int i = 0;

    // Search in consecutive positions
    while (i < SIZE)
    {
        int newIndex = (index + i) % SIZE;

        // If empty position is found
        if (probeTable[newIndex] == -1)
            return false;

        // If key matches
        if (probeTable[newIndex] == key)
            return true;

        i++;
    }

    return false;
}

// Display Chaining Hash Table
void displayChain()
{
    cout << "\nChaining Hash Table:\n";

    for (int i = 0; i < SIZE; i++)
    {
        cout << i << " : ";

        // Display linked list elements
        for (int x : chainTable[i])
        {
            cout << x << " -> ";
        }

        cout << "NULL" << endl;
    }
}

// Display Linear Probing Hash Table
void displayProbe()
{
    cout << "\nLinear Probing Hash Table:\n";

    for (int i = 0; i < SIZE; i++)
    {
        cout << i << " : ";

        if (probeTable[i] == -1)
            cout << "Empty";
        else
            cout << probeTable[i];

        cout << endl;
    }
}

// Main Function
int main()
{
    int n, key;

    // Initialize all positions as empty
    for (int i = 0; i < SIZE; i++)
    {
        probeTable[i] = -1;
    }

    // Input number of elements
    cout << "Enter number of elements: ";
    cin >> n;

    // Input and insert elements
    cout << "Enter elements:\n";

    for (int i = 0; i < n; i++)
    {
        cin >> key;

        insertChain(key);
        insertProbe(key);
    }

    // Display both hash tables
    displayChain();
    displayProbe();

    // Search an element
    cout << "\nEnter element to search: ";
    cin >> key;

    // Search using Chaining
    if (searchChain(key))
        cout << "Found in Chaining" << endl;
    else
        cout << "Not Found in Chaining" << endl;

    // Search using Linear Probing
    if (searchProbe(key))
        cout << "Found in Linear Probing" << endl;
    else
        cout << "Not Found in Linear Probing" << endl;

    return 0;
}
