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

    // Function to get the data at the head node
    string get_front() {
        if (head) {
            return head->data;
        }
        return "";
    }

    // Function to get the data at the tail node
    string get_back() {
        if (tail) {
            return tail->data;
        }
        return "";
    }

    // Function to get the data at a certain position
    string get_at_pos(int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return "";
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size.\n";
            return "";
        }

        return temp->data;
    }

    // Function to get the number of nodes in the linked list
    int get_size() {
        int size = 0;

        Node* temp = head;
        while (temp) {
            ++size;
            temp = temp->next;
        }

        return size;
    }

    void insert_after(const string& value, int position) {
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
    }

    
    void delete_val(const string& value) {
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
    }

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
        if (tempPrev) {
            tempPrev->next = temp->next;
        }
        if (temp->next) {
            temp->next->prev = tempPrev;
        }
        delete temp;
    }

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
            cout << "\t\t" << current->data << "\n";
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
    cout << "\t" << newCustomer << " joined the line\n";
}

// TODO: possibly make it so that when a customer leaves, they get added back to the names vector (and can come back later?)
void customerGetsServed(DoublyLinkedList& customersLine) {
    cout << "\t" << customersLine.get_front() << " is served\n";
    customersLine.pop_front();
}

void customerAtEndLeaves(DoublyLinkedList& customersLine) {
    cout << "\t" << customersLine.get_back() << " (at the rear) left the line\n";
    customersLine.pop_back();
}

void randomCustomerLeaves(DoublyLinkedList& customersLine) {
    int randomPos = rand() % customersLine.get_size() + 1;
    cout << "\t" << customersLine.get_at_pos(randomPos) << " left the line\n";
    customersLine.delete_pos(randomPos);
}

void vipCustomerJoins(vector<string>& names, DoublyLinkedList& customersLine) {
    string newCustomer = getRandomCustomer(names);
    customersLine.push_back(newCustomer);
    cout << "\t" << newCustomer << " joined the line\n";
}

int main() {
    srand(time(0));                     // Seed for RNG
    DoublyLinkedList customersLine;     // Line of customers at the coffee shop

    // Read all the names from the file and store it in a vector.
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

    // Time step #1: Open the store and add five customers right away.
    cout << "Store opens:\n";
    for (int i = 0; i < 5; ++i) {
        customerJoinsLine(names, customersLine);
    }
    cout << "\tResulting line:\n";
    customersLine.print();

    // Time step #2 through #20:
    for (int i = 2; i <= 20; ++i) {
        cout << "Time step #" << i << ":\n";
        int probability;

        // 40% chance of a customer being helped at the beginning of hte line and ordering their coffee
        probability = rand() % 100 + 1;
        if (probability <= 40) {
            customerGetsServed(customersLine);
        }

        // 60% chance of a customer joining the end of the line
        probability = rand() % 100 + 1;
        if (probability <= 60) {
            customerJoinsLine(names, customersLine);
        }

        // 20% chance that a customer at the end of the line gets tired of waiting and leaves
        probability = rand() % 100 + 1;
        if (probability <= 20) {
            customerAtEndLeaves(customersLine);
        }

        // 10% chance that any particular customer in the line gets tired of waiting and leaves
        probability = rand() % 100 + 1;
        if (probability <= 10) {
            randomCustomerLeaves(customersLine);
        }
        
        // 10% chance that a VIP customer gets to skip the line and go straight to the counter and order
        probability = rand() % 100 + 1;
        if (probability <= 10) {
            vipCustomerJoins(names, customersLine);
        }

        // At the end of the time step, print the current line of customers.
        cout << "\tResulting line:\n";
        customersLine.print();
    }
    
    return 0;
}