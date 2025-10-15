// COMSC-210 | Midterm 2 | Mika Aquino
// IDE used: Visual Studio 2022

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        string data;    // Node data has been modified to a string to hold the customer names.
        Node* prev;
        Node* next;
        Node(const string& val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    string get_front() {
        if (head) {
            return head->data;
        }
    }

    /*
    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }*/

    /*
    void delete_val(int value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }*/

    // Any particular customer in the line (random position) decides they don't want to wait and leaves
    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    // New customer joins the end of the line
    void push_back(string v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    // VIP skips the line
    void push_front(string v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    // Customer at the beginning of the line is helped (and leaves)
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    // Customer at the end of the line gets tired of waiting and leaves
    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    // Destructor
    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << "\t" << current->data << "\n";
            current = current->next;
        }
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

string getRandomCustomer(vector<string>& names) {
    if (names.empty()) {
        return "";
    }
    string customer;
    int randomNum = rand() % names.size();      // Generate a random index

    customer = names.at(randomNum);             // Get a random customer at that index
    names.erase(names.begin() + randomNum);     // Remove the customer from the list

    return customer;
}

void customerJoinsLine(vector<string>& names, DoublyLinkedList& customersLine) {
    string newCustomer = getRandomCustomer(names);
    customersLine.push_back(newCustomer);
    cout << "\t" << newCustomer << " joins the line\n";
}

void customerGetsServed(DoublyLinkedList& customersLine) {
    cout << 
    customersLine.pop_front();
}

int main() {
    srand(time(0)); // Seed

    DoublyLinkedList customersLine;

    // Read all the names from the file, store it in a vector
    vector<string> names;
    ifstream namesFile("names.txt");
    if (!namesFile) {
        cout << "Unable to open file.\n";
        return 1;
    }
    string name;
    while (namesFile >> name) {
        names.push_back(name);
    }

    // Open the store and add five customers (time step 1)
    cout << "Store opens:\n";
    for (int i = 0; i < 5; ++i) {
        customerJoinsLine(names, customersLine);
    }
    cout << "\tResulting line:\n";
    customersLine.print();

    // Time period runs 20 times.
    for (int i = 2; i <= 20; ++i) {
        cout << "Time step #" << i << ":\n";
        
        int probability = rand() % 100 + 1;    // returns a random number 1-100
        // 40% chance of a customer being helped at the beginning of hte line and ordering their coffee
        if (probability <= 40) {
            customerGetsServed(customerLine);

            cout < " "
        }


        // 60% chance of a customer joining the end of the line
        if (probability <= 60) {
            customerJoinsLine(names, customersLine);
        }

    }

    
    return 0;
}