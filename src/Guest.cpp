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
    ifstream file("Member.csv");
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

bool isEmailAvailable(const string& email) {
    // This function checks a list of existing emails in Member.txt
    ifstream file("Member.csv");
    string line;
    getline(file, line); // Skip header line
    while(getline(file, line)) {
        stringstream ss(line);
        string existingEmail;
        for(int i = 0; i < 4; i++) { // Assuming email is the 5th field
            getline(ss, existingEmail, ',');
        }
        if(existingEmail == email) {
            return false; // Email already exists
        }
    }
    return true; // Email is available
}

void Guest::signup() {
    cout << "Signing up for a new member account..." << endl;
    // Implementation for signing up a new member account
    // This involves collecting user details and storing them

    // Username and Password validation
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
        getline(cin, password);
    }while(!isPasswordValid(password));

    // Full Name
    do{
        cout << "Enter full name: ";
        getline(cin, fullName);
        
    }while(fullName.empty());

    // Email
    do{
        cout << "Enter email: ";
        getline(cin, email);
        if(email.find('@') == string::npos || email.find('.') == string::npos) {
            cout << "Invalid email format. Please try again." << endl;
            email.clear();
        }
        else if(!isEmailAvailable(email)){
            cout << "Email already registered. Please use another or login to the Email Account." << endl;
            email.clear();
        }
        else{
            email = email;
        }
    }while(email.empty());

    // Phone Number

}

void Guest::viewListing() {
    cout << "Viewing available motorbikes for rent..." << endl;
    // Implementation for viewing available motorbikes
    
    ifstream file("EBike.csv");
    if(!file.is_open()) {
        cout << "Error opening motorbike listings file." << endl;
        return;
    }


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
        if (c < 0x21 || c >= 0x7F) {
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