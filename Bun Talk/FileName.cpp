#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int max_attempts = 3;

struct Authentication {
    int attempts;
    bool locked;
    string current_user;
    string current_role;
};

bool CheckAdminCredentials(string username, string password) {
    return (username == "admin" && password == "admin@123");
}

bool CheckCashierCredentials(string username, string password) {
    return (username == "cashier" && password == "cashier@123");
}

void Login(Authentication& auth) {
    if (auth.locked) {
        cout << "System is locked. Please contact admin." << endl;
        return;
    }

    while (auth.attempts < max_attempts) {
        string username, password, role;
        cout << "------WELCOME TO BUN TALK------" << endl;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        cout << "Enter role (admin/cashier): ";
        cin >> role;

        if (role == "admin") {
            if (CheckAdminCredentials(username, password)) {
                auth.current_user = username;
                auth.current_role = "admin";
                cout << "Admin login successful" << endl;
                cout << "           " << endl;
                auth.attempts = 0;
                return;
            }
            else {
                cout << "Invalid admin username or password" << endl;
            }
        }
        else if (role == "cashier") {
            if (CheckCashierCredentials(username, password)) {
                auth.current_user = username;
                auth.current_role = "cashier";
                cout << "Cashier login successful." << endl;
                cout << "           " << endl;
                auth.attempts = 0;
                return;
            }
            else {
                cout << "Invalid cashier username or password" << endl;
            }
        }
        else {
            cout << "Invalid role" << endl;
        }

        auth.attempts++;
    }

    cout << "Exceeded maximum login attempts. System locked." << endl;
    auth.locked = true;
}

string getCurrentUser(Authentication& auth) {
    return auth.current_user;
}

string getCurrentRole(Authentication& auth) {
    return auth.current_role;
}

struct Menu {
    vector<pair<string, double>> items;
};

void InitializeMenu(Menu& menu) {
    menu.items = { {"Bread", 150}, {"Cup Cake", 180},{"Bun",75}, {"Muffin", 75},{"Pie",200}, {"Fish Roll",150}, {"Vegetable Roll",200},
    {"Doughnuts",200} };
}

void DisplayBreakfastItems(Menu& menu) {
    cout << "Welcome to Bun Talk! Here are our bakery items:" << endl;
    cout << "               " << endl;
    for (int i = 0; i < menu.items.size(); i++) {
        cout << i + 1 << ". " << menu.items[i].first << " - Rs." << menu.items[i].second << endl;
    }
}

bool IsValidMenuItem(Menu& menu, int choice) {
    return (choice >= 1 && choice <= menu.items.size());
}

pair<string, double> GetItem(Menu& menu, int choice) {
    return menu.items[choice - 1];
}

void AddItem(Menu& menu, string name, double price) {
    menu.items.push_back({ name, price });
    cout << "Item added successfully!" << endl;
}

void RemoveItem(Menu& menu, int index) {
    if (index >= 0 && index < menu.items.size()) {
        menu.items.erase(menu.items.begin() + index);
        cout << "Item removed successfully!" << endl;
    }
    else {
        cout << "Invalid index. Please try again." << endl;
    }
}

struct StaffManager {
    vector<pair<string, string>> staffList;
};

void InitializeStaffManager(StaffManager& staffManager) {
    staffManager.staffList = { {"Jhon", "Cashier"}, {"Stefan", "Chef"}, {"Duff", "Chef"} };
}

void DisplayStaffList(StaffManager& staffManager) {
    cout << "Here is the Bun Talk Staff List:" << endl;
    for (int i = 0; i < staffManager.staffList.size(); i++) {
        cout << i + 1 << ". " << staffManager.staffList[i].first << " (" << staffManager.staffList[i].second << ")" << endl;
    }
}

void AddStaff(StaffManager& staffManager, string name, string role) {
    staffManager.staffList.push_back({ name, role });
    cout << "Staff added successfully!" << endl;
}

void RemoveStaff(StaffManager& staffManager, int index) {
    if (index >= 0 && index < staffManager.staffList.size()) {
        staffManager.staffList.erase(staffManager.staffList.begin() + index);
        cout << "Staff removed successfully!" << endl;
    }
    else {
        cout << "Invalid index. Please try again." << endl;
    }
}

struct BillManager {
    void PrintBill(vector<pair<string, double>> selectedItems) {
        double total_cost = 0;

        if (selectedItems.size() > 0) {
            for (int i = 0; i < selectedItems.size(); i++) {
                cout << "Added " << selectedItems[i].first << " - Rs." << selectedItems[i].second << endl;
                total_cost += selectedItems[i].second;
            }

            cout << "       " << endl;
            cout << "Total: Rs." << total_cost << endl;
            cout << "       " << endl;
            cout << "Would you like to proceed with payment? (yes/no): ";
            string choice;
            cin >> choice;

            if (choice == "yes") {
                ProcessPayment(total_cost);
                cout << "           " << endl;
                cout << "Payment successful... Thank you.." << endl;
            }
            else {
                cout << "Payment canceled" << endl;
            }
        }
        else {
            cout << "No items selected" << endl;
        }
    }

    void ProcessPayment(double amount) {
        cout << "       " << endl;
        cout << "Processing payment of Rs " << amount << "..." << endl;
    }
};

void DisplayAdminMenu() {
    cout << "\n---Admin Menu---" << endl;
    cout << "               " << endl;
    cout << "1. View Bakery Items" << endl;
    cout << "2. Add Bakery Item" << endl;
    cout << "3. Remove Bakery Item" << endl;
    cout << "4. View Staff List" << endl;
    cout << "5. Add Staff" << endl;
    cout << "6. Remove Staff" << endl;
    cout << "7. Logout" << endl;
    cout << "8. Help" << endl;
    cout << "9. Exit" << endl;
    cout << "               " << endl;
    cout << "Enter your choice: ";
}

void DisplayCashierMenu() {
    cout << "\n---Cashier Menu---" << endl;
    cout << "               " << endl;
    cout << "1. View Bakery Items" << endl;
    cout << "2. Generate Bill" << endl;
    cout << "3. Help" << endl;
    cout << "4. Logout" << endl;
    cout << "5. Exit" << endl;
    cout << "               " << endl;
    cout << "Enter your choice: ";
}

void DisplayHelp() {
    cout << "\nHelp:" << endl;
    cout << "For Admin:" << endl;
    cout << "- To add a new item, choose option 2 and enter the item name and price." << endl;
    cout << "- To remove an item, choose option 3 and enter the index of the item." << endl;
    cout << "- To add a new staff member, choose option 5 and enter their name and role." << endl;
    cout << "- To remove a staff member, choose option 6 and enter the index of the staff member." << endl;
    cout << "               " << endl;
    cout << "For Cashier:" << endl;
    cout << "- To generate a bill, choose option 2 and select the items to add to the bill." << endl;
    cout << "Press any key to continue..." << endl;
    cin.ignore();
    cin.get();
}

int main() {
    Authentication auth = { 0, false, "", "" };

    while (true) {
        Login(auth);

        if (auth.locked) {
            break;  // Exit the loop if system is locked
        }

        if (getCurrentRole(auth) == "admin") {
            Menu menu;
            StaffManager staffManager;
            BillManager billManager;
            InitializeMenu(menu);
            InitializeStaffManager(staffManager);

            while (true) {
                DisplayAdminMenu();
                int choice;
                cin >> choice;

                switch (choice) {
                case 1:
                    DisplayBreakfastItems(menu);
                    break;
                case 2: {
                    string name;
                    double price;
                    cout << "Enter item name: ";
                    cin.ignore(); // Ignore newline character in buffer
                    getline(cin, name);
                    cout << "Enter item price: ";
                    cin >> price;
                    AddItem(menu, name, price);
                }
                      break;
                case 3: {
                    int index;
                    cout << "Enter index of item to remove: ";
                    cin >> index;
                    RemoveItem(menu, index - 1);
                }
                      break;
                case 4:
                    DisplayStaffList(staffManager);
                    break;
                case 5: {
                    string name, role;
                    cout << "Enter staff name: ";
                    cin.ignore(); // Ignore newline character in buffer
                    getline(cin, name);
                    cout << "Enter staff role: ";
                    getline(cin, role);
                    AddStaff(staffManager, name, role);
                }
                      break;
                case 6: {
                    int index;
                    cout << "Enter index of staff to remove: ";
                    cin >> index;
                    RemoveStaff(staffManager, index - 1);
                }
                      break;
                case 7:
                    break;
                case 8:
                    DisplayHelp();
                    break;
                case 9:
                    auth = { 0, false, "", "" }; // Reset authentication
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                }

                if (choice == 7 || choice == 9) {
                    break; // Return to login screen
                }
            }
        }
        else if (getCurrentRole(auth) == "cashier") {
            Menu menu;
            InitializeMenu(menu);
            DisplayBreakfastItems(menu);
            BillManager billManager;

            int choice;
            vector<pair<string, double>> selectedItems;

            while (true) {
                DisplayCashierMenu();
                cin >> choice;

                switch (choice) {
                case 1:
                    DisplayBreakfastItems(menu);
                    break;
                case 2: {
                    while (true) {
                        cout << "Enter the item number to add to the bill (or 0 to finish): ";
                        cin >> choice;

                        if (choice == 0) {
                            break;
                        }

                        if (IsValidMenuItem(menu, choice)) {
                            selectedItems.push_back(GetItem(menu, choice));
                        }
                        else {
                            cout << "Invalid choice. Please try again." << endl;
                        }
                    }

                    billManager.PrintBill(selectedItems);
                    selectedItems.clear(); // Clear selected items after printing bill
                }
                      break;
                case 3:
                    DisplayHelp();
                    break;
                case 4:
                    break;
                case 5:
                    auth = { 0, false, "", "" }; // Reset authentication
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                }

                if (choice == 4 || choice == 5) {
                    break; // Return to login screen
                }
            }
        }
    }

    return 0;
}
