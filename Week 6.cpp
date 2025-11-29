// hello_inventory.cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Hello Inventory System!\n";
    cout << "\tWelcome to the inventory demo.\n\n";

    cout << "Demonstrating escape characters:\n";
    cout << "Line1\nLine2\n";
    cout << "Tabbed:\tColumn1\tColumn2\n";
    cout << "Quote: \"This is a quoted string\"\n";
    cout << "Backslash: C:\\path\\to\\file\n\n";

    cout << "Data Sizes (in bytes):\n";
    cout << "Size of int: " << sizeof(int) << " bytes\n";
    cout << "Size of float: " << sizeof(float) << " bytes\n";
    cout << "Size of char: " << sizeof(char) << " bytes\n";

    return 0;
}

// item_total_cost.cpp
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main() {
    string itemName;
    int quantity;
    double cost;

    cout << "Enter item name: ";
    cin >> itemName; // for multi-word names, use getline if desired
    cout << "Enter quantity: ";
    cin >> quantity;
    cout << "Enter cost (per item): ";
    cin >> cost;

    double total = quantity * cost;
    cout << fixed << setprecision(2);
    cout << "Total cost for " << itemName << ": $" << total << endl;

    return 0;
}

// menu_if_statements.cpp
#include <iostream>
using namespace std;

int main() {
    int choice;
    cout << "1. Add Item\n2. View Items\n3. Exit\n";
    cout << "Choose an option: ";
    cin >> choice;

    if (choice == 1) {
        cout << "Item added!\n";
    } else if (choice == 2) {
        cout << "Displaying items...\n";
    } else if (choice == 3) {
        cout << "Exiting...\n";
    } else {
        cout << "Invalid option.\n";
    }
    return 0;
}

// largest_of_three.cpp
#include <iostream>
using namespace std;

int main() {
    float n1, n2, n3;
    cout << "Enter three numbers: ";
    cin >> n1 >> n2 >> n3;

    // Nested if style: compare n1 vs others first, then n2 vs n3
    if (n1 >= n2) {
        if (n1 >= n3) {
            cout << "Largest number: " << n1 << endl;
        } else {
            cout << "Largest number: " << n3 << endl;
        }
    } else { // n2 > n1
        if (n2 >= n3) {
            cout << "Largest number: " << n2 << endl;
        } else {
            cout << "Largest number: " << n3 << endl;
        }
    }

    return 0;
}

// menu_with_functions.cpp
#include <iostream>
#include <string>
using namespace std;

void showMenu() {
    cout << "\n--- Main Menu ---\n";
    cout << "1. Add (simulated)\n";
    cout << "2. View (simulated)\n";
    cout << "3. Print Hello\n";
    cout << "4. Exit\n";
    cout << "Choose an option: ";
}

void doAdd() {
    cout << "Add: (this is a placeholder function).\n";
}

void doView() {
    cout << "View: (this is a placeholder function).\n";
}

void sayHello() {
    cout << "Hello from option 3!\n";
}

int main() {
    int option;
    do {
        showMenu();
        cin >> option;
        switch (option) {
            case 1: doAdd(); break;
            case 2: doView(); break;
            case 3: sayHello(); break;
            case 4: cout << "Exiting menu.\n"; break;
            default: cout << "Invalid option. Try again.\n";
        }
    } while (option != 4);

    return 0;
}

// Item_class_fileio.cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Item {
public:
    string name;
    int quantity;

    Item() : name(""), quantity(0) {}
    Item(const string& n, int q) : name(n), quantity(q) {}

    void saveToFile(const string& filename = "items.txt") {
        ofstream out(filename, ios::app); // append mode
        if (out.is_open()) {
            out << name << "," << quantity << "\n";
            out.close();
            cout << "Item saved to file: " << name << "," << quantity << endl;
        } else {
            cout << "Unable to open file for writing.\n";
        }
    }

    static void loadFromFile(const string& filename = "items.txt") {
        ifstream in(filename);
        if (in.is_open()) {
            string line;
            cout << "--- items.txt contents ---\n";
            while (getline(in, line)) {
                cout << line << "\n";
            }
            in.close();
        } else {
            cout << "Unable to open file for reading.\n";
        }
    }
};

int main() {
    Item tool;
    cout << "Enter item name: ";
    cin >> tool.name;
    cout << "Enter quantity: ";
    cin >> tool.quantity;

    tool.saveToFile();
    Item::loadFromFile();

    return 0;
}

// dynamic_items_binary_search.cpp
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct Item {
    string name;
    int id;
};

// comparator to sort by id
bool cmpById(const Item& a, const Item& b) {
    return a.id < b.id;
}

int binarySearchById(Item* arr, int size, int targetId) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid].id == targetId) return mid;
        if (arr[mid].id < targetId) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int main() {
    const int N = 100; // minimum 100 records
    Item* inventory = new Item[N];

    // Populate with sample, sorted by id. Names are example strings.
    for (int i = 0; i < N; ++i) {
        inventory[i].id = 1000 + i; // ids 1000..1099
        inventory[i].name = "Item_" + to_string(i + 1);
    }

    // Ensure sorted (they already are, but safer to call sort if data came unsorted)
    sort(inventory, inventory + N, cmpById);

    cout << "Populated inventory with " << N << " items (ids 1000..1099)\n";
    int searchId;
    cout << "Enter ID to search for: ";
    cin >> searchId;

    int idx = binarySearchById(inventory, N, searchId);
    if (idx >= 0) {
        cout << "Found item: ID=" << inventory[idx].id
             << ", Name=" << inventory[idx].name << endl;
    } else {
        cout << "Item with ID " << searchId << " not found.\n";
    }

    delete[] inventory;
    return 0;
}

// BankAccount.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

class BankAccount {
private:
    double balance;

    void saveTransaction(const string& type, double amount) {
        ofstream file("transactions.txt", ios::app);
        if (file.is_open()) {
            file << type << ": $" << fixed << setprecision(2) << amount << "\n";
            file.close();
        }
    }

public:
    BankAccount() : balance(0.0) {}

    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Deposit amount must be positive.\n";
            return;
        }
        balance += amount;
        cout << "Deposited $" << fixed << setprecision(2) << amount << ". New balance: $" << balance << endl;
        saveTransaction("Deposit", amount);
    }

    void makePurchase(const string& item, double cost) {
        if (cost <= 0) {
            cout << "Invalid cost.\n";
            return;
        }
        if (cost > balance) {
            cout << "Insufficient funds for " << item << ".\n";
            saveTransaction("Failed Purchase - " + item, cost);
        } else {
            balance -= cost;
            cout << "Purchased " << item << " for $" << fixed << setprecision(2) << cost << ".\n";
            saveTransaction("Purchase - " + item, cost);
        }
    }

    void displayBalance() const {
        cout << "Current Balance: $" << fixed << setprecision(2) << balance << endl;
    }
};

int main() {
    BankAccount myAccount;
    myAccount.deposit(100.00);
    myAccount.makePurchase("Coffee", 4.50);
    myAccount.makePurchase("Book", 25.00);
    myAccount.displayBalance();

    cout << "Transactions have been written to transactions.txt\n";
    return 0;
}

// inventory_array.cpp
#include <iostream>
#include <string>
using namespace std;

class Item {
public:
    string name;
    int quantity;
};

void displayItems(Item items[], int size) {
    cout << "\nCurrent Inventory:\n";
    for (int i = 0; i < size; ++i) {
        cout << i+1 << ". " << items[i].name << " - Qty: " << items[i].quantity << "\n";
    }
}

int findItemByName(Item items[], int size, const string& searchName) {
    for (int i = 0; i < size; ++i) {
        if (items[i].name == searchName) return i;
    }
    return -1;
}

int main() {
    const int SIZE = 5;
    Item inventory[SIZE];

    for (int i = 0; i < SIZE; ++i) {
        cout << "Enter name for item " << i+1 << ": ";
        cin >> inventory[i].name;
        cout << "Enter quantity: ";
        cin >> inventory[i].quantity;
    }

    displayItems(inventory, SIZE);

    string query;
    cout << "\nEnter a name to search: ";
    cin >> query;
    int idx = findItemByName(inventory, SIZE, query);
    if (idx != -1) {
        cout << "Found " << inventory[idx].name << " with quantity " << inventory[idx].quantity << endl;
    } else {
        cout << "Item not found.\n";
    }

    return 0;
}

// inheritance_access_levels.cpp
#include <iostream>
using namespace std;

class User {
public:
    virtual void accessLevel() {
        cout << "General Access\n";
    }
    virtual ~User() = default;
};

class Employee : public User {
public:
    void accessLevel() override {
        cout << "Employee Access\n";
    }
};

class InventoryManager : public Employee {
public:
    void accessLevel() override {
        cout << "Full Inventory Management Access\n";
    }
};

int main() {
    InventoryManager mgr;
    mgr.accessLevel(); // should call InventoryManager::accessLevel
    return 0;
}

// Product_ctor_dtor.cpp
#include <iostream>
#include <string>
using namespace std;

class Product {
private:
    int id;
    string name;
    float price;

public:
    Product(int i, const string& n, float p) : id(i), name(n), price(p) {
        cout << "Constructor called for product: " << name << endl;
    }

    ~Product() {
        cout << "Destructor called for product: " << name << endl;
    }

    void printDetails() const {
        cout << "ID: " << id << ", Name: " << name << ", Price: $" << price << endl;
    }
};

int main() {
    Product p(101, "Notebook", 4.99f);
    p.printDetails();
    // destructor will run at end of scope
    return 0;
}

// csv_loader.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

int main() {
    string filename;
    cout << "Enter CSV filename (e.g., dataset.csv): ";
    cin >> filename;

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << filename << "\n";
        return 1;
    }

    string header;
    if (!getline(file, header)) {
        cerr << "Empty file or read error.\n";
        return 1;
    }

    cout << "Header: " << header << "\n";

    string line;
    int count = 0;
    const int maxEntries = 10;
    while (getline(file, line) && count < maxEntries) {
        vector<string> fields;
        string token;
        stringstream ss(line);

        // Simple CSV split on commas (does not handle embedded commas with quotes).
        while (getline(ss, token, ',')) {
            fields.push_back(token);
        }

        // Ensure at least 5 fields; if not, pad with empty strings
        fields.resize(max(5, (int)fields.size()));

        cout << "\nEntry " << (count + 1) << ":\n";
        cout << "Field 1: " << fields[0] << "\n";
        cout << "Field 2: " << fields[1] << "\n";
        cout << "Field 3: " << fields[2] << "\n";
        cout << "Field 4: " << fields[3] << "\n";
        cout << "Field 5: " << fields[4] << "\n";

        // If you want, parse more fields here.
        ++count;
    }

    cout << "\nLoaded " << count << " entries (up to " << maxEntries << ").\n";
    file.close();
    return 0;
}
