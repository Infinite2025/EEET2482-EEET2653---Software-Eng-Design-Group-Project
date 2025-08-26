#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>
#include<sstream>
#include "Guest.h"
using namespace std;

// Default constructor for Guest class
Guest::Guest() {
    int creditPoints = 10; // Initialize credit points for guest
    int rating = -1; // Initialize rating for guest
}

// Check available usernames
bool isUsernameAvailable(const string& username) {
    // This function checks a list of existing usernames Member.txt
    ifstream file("Member.txt");
    string line;
    getline(file, line); // Skip header line
    while(getline(file, line)) {
        stringstream ss(line);
        string existingUsername;
        getline(ss, existingUsername, ','); // Assuming username is the first field
            if(existingUsername == username) {
                return false; // Username already exists
            }
    }
    return true;// Username is available
}

void Guest::signup() {
    cout << "Signing up for a new member account..." << endl;
    // Implementation for signing up a new member account
    // This involves collecting user details and storing them
    string input;
    do{
        cout << "Enter username: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, input);
        if(input.empty()){
            cout << "Username cannot be empty. Please try again." << endl;
        } else if (!isUsernameAvailable(input)){
            cout << "Username already taken. Please choose another." << endl;
        } else {
            username = input;
        }

    }while(username.empty());
    do{
        cout << "Enter password: ";
        getline(cin, input);
        if(input.empty()){
            cout << "Password cannot be empty. Please try again." << endl;
        } else if (!isPasswordValid(input)){
            cout << "Password must be at least 8 characters long. Please try again." << endl;
        } else {
            password = input;
        }
    }while(password.empty());

}

// Validates if the password meets the minimum length requirement
bool Guest::isPasswordValid(const string& password) {
    if (password.length() < 8) {
        return false; // Password too short
    }
    if(password.find(' ') != string::npos) {
        return false; // Password contains spaces
    }
    for(char c : password) {
        if (!isalnum(c) && c != '_' && c != '@' && c != '#' && c != '$' && c != '%') {
            return false; // Password contains invalid characters
        }
        if(isupper(c)) {
            if(isdigit(c) && islower(c)){
                return true; // Password contains at least one uppercase,lowercase and digit
            }
        }
        
    return true; // Password is valid
    }
}