#include <iostream>
#include <string>
using namespace std;

const int BUFFER_SIZE = 5;
string buffer[BUFFER_SIZE];
int in = 0, out = 0;

int empty = BUFFER_SIZE;
int full = 0;
int myMutex = 1;

void wait(int &s) {
    s--;
}

void signal(int &s) {
    s++;
}

void displayBuffer() {
    cout << "Buffer: [ ";
    for (int i = 0; i < BUFFER_SIZE; i++) {
        cout << buffer[i] << " ";
    }
    cout << "]" << endl;
}

void produce(const string& item) {
    if (empty == 0) {
        cout << "Buffer is FULL! Cannot produce.\n";
        return;
    }
    wait(empty);
    wait(myMutex);

    buffer[in] = item;
    cout << "Produced: " << item << " at position " << in << endl;
    in = (in + 1) % BUFFER_SIZE;

    signal(myMutex);
    signal(full);
    displayBuffer();
}

void consume() {
    if (full == 0) {
        cout << "Buffer is EMPTY! Cannot consume.\n";
        return;
    }
    wait(full);
    wait(myMutex);

    string item = buffer[out];
    buffer[out] = "-";
    cout << "Consumed: " << item << " from position " << out << endl;
    out = (out + 1) % BUFFER_SIZE;

    signal(myMutex);
    signal(empty);
    displayBuffer();
}

int main() {
    for (int i = 0; i < BUFFER_SIZE; i++) buffer[i] = "-";

    int choice;
    string item;
    while (true) {
        cout << "\n1. Produce\n2. Consume\n3. Exit\n4. Display\nEnter choice: ";
        cin >> choice;
        cin.ignore(); // To clear newline after choice input

        switch (choice) {
            case 1:
                cout << "Enter item to produce: ";
                getline(cin, item);
                produce(item);
                break;
            case 2:
                consume();
                break;
            case 4:
                displayBuffer();
                break;
            case 3:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice!\n";
        }
    }
}