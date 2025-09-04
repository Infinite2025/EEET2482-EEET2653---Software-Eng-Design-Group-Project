#include <Admin.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>  
using namespace std;

Admin::Admin() : isAuthenticated(false) {}

void loadAdmindata() {
    ifstream file("admins.csv");
    if (!file.is_open()) {
        cerr << "Error! admins.csv" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string username, password;

        getline(ss, username, ',');
        getline(ss, password, ',');
        if (username != "username") {
            this->username = username;
            this->password = password;
        }
        // For simplicity, we just print the loaded admin credentials
        cout << "Loaded admin: " << username << endl;
    }

    file.close();
}

bool Admin::login(const string& username, const string& password) {
    if (validateAdminCredentials(username, password)) {
        isAuthenticated = true;
        cout << "Admin logged in successfully." << endl;
        return true;
    } else {
        cout << "Invalid admin credentials." << endl;
        return false;
    }
}

void Admin::viewAllUsers() {
    if (!isAuthenticated) {
        cout << "Access denied. Please log in as admin." << endl;
        return;
    }
    ifstream file("member.csv")
}