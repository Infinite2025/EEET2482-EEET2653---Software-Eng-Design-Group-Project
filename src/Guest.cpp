#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<limits>
#include<cctype>
#include "../include/Guest.h"
using namespace std;

// Default constructor for Guest class
Guest::Guest() {
    int creditPoints = 20; // Initialize credit points for guest
    int rating = 3; // Initialize rating for guest
}

// Pauses the program until the user presses Enter
void pause(){
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Check availablility during sign up
bool Guest::isUsernameAvailable(const string& username) {
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

bool Guest::isEmailAvailable(const string& email) {
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

bool Guest::isPhoneNumberAvailable(const string& phoneNumber) {
    // This function checks a list of existing phone numbers in Member.txt
    ifstream file("Member.csv");
    string line;
    getline(file, line); // Skip header line
    while(getline(file, line)) {
        stringstream ss(line);
        string existingPhoneNumber;
        for(int i = 0; i < 3; i++) { // Assuming phone number is the 4th field
            getline(ss, existingPhoneNumber, ',');
        }
        if(existingPhoneNumber == phoneNumber) {
            return false; // Phone number already exists
        }
    }
    return true; // Phone number is available
}

bool Guest::isIDNumberAvailable(const string& idNumber) {
    // This function checks a list of existing ID numbers in Member.txt
    ifstream file("Member.csv");
    string line;
    getline(file, line); // Skip header line
    while(getline(file, line)) {
        stringstream ss(line);
        string existingIDNumber;
        for(int i = 0; i < 6; i++) { // Assuming ID number is the 7th field
            getline(ss, existingIDNumber, ',');
        }
        if(existingIDNumber == idNumber) {
            return false; // ID number already exists
        }
    }
    return true; // ID number is available
}

// Validates if the password meets the minimum length requirement
bool Guest::isPasswordValid(const string& password) {
    if(password.length() < 8) {
        return false; // Password too short
    }
    if(password.find(' ') != string::npos) {
        return false; // Password contains spaces
    }
        int upper = 0;
        int lower = 0;
        int digit = 0;
    for(char c : password) {
        
        /*if (c < 0x21 || c >= 0x7F) {
            return false; // Password contains invalid characters
        }*/
        
        if(isupper(c)) {
            upper++;
        }
        if(isdigit(c)){
            digit++;
        }
        if(islower(c)){
           lower++;      
        }
    }
        if(upper == 0 || lower == 0 || digit == 0) {
            return false; // Password must contain at least one uppercase, one lowercase, and one digit
        
        // Password must contains at least one uppercase,lowercase and digit
        
    
    }
    return true; // Password is valid
}

bool Guest::isLicenseNumberValid(const string& licenseNumber) {
    if(licenseNumber.length() != 12) {
        return false; // License number must be exactly 12 characters
    }
    else if(licenseNumber.find(' ') != string::npos) {
        return false; // License number should not contain spaces
    }
    else{
        for(char c : licenseNumber) {
            if(!(isdigit(c))) {
                return false; // License number should be numeric
            }
        }
    }
    return true; // License number is valid
}

// Main Functions for Guest class


void Guest::signup() {
    cout << "Signing up for a new member account..." << endl;
    // Implementation for signing up a new member account
    // This involves collecting user details and storing them

    // Username and Password validation  
    
    do{
        cout << "Enter username: ";
        // cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
        getline(cin, username);
        if (!isUsernameAvailable(username)){
            cout << "Username already taken. Please choose another." << endl;
            username.clear();
        } else {
            username = username;
        }

    }while(username.empty());

    do{
        cout << "Enter password: ";
        getline(cin, password);
        if(!isPasswordValid(password)){
            cout << "Password must be at least 8 characters long, contain at least one uppercase letter, one lowercase letter, one digit, and no spaces." << endl;
            password.clear();
        }
        else{
            password = password;
        }
    }while(password.empty());

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
    do{
        cout << "Enter phone number: ";
        getline(cin, phoneNumber);
        if(phoneNumber.length() !=10) {
            cout << "Invalid phone number. Please enter a valid number." << endl;
            phoneNumber.clear();
        }
        else if(phoneNumber.length() ==10) {
            for(char c : phoneNumber) {
                if(!isdigit(c)) {
                    cout << "Phone number should contain only digits. Please try again." << endl;
                    phoneNumber.clear();
                    break;
                }
                if(phoneNumber[0] != '0') {
                    cout << "Phone number should start with 0. Please try again." << endl;
                    phoneNumber.clear();
                    break;
                }
                if(phoneNumber.find(' ') != string::npos) {
                    cout << "Phone number should not contain spaces. Please try again." << endl;
                    phoneNumber.clear();
                    break;
            }
            
        }
    }
        else if(!isPhoneNumberAvailable(phoneNumber)){
            cout << "Phone number already registered. Please use another or login to the Phone Number Account." << endl;
            phoneNumber.clear();
        }
        else{
            phoneNumber = phoneNumber;
        
        }
    }while(phoneNumber.empty());

    // ID Type and Number
    do{
        cout << "Enter ID type (e.g., Passport, National ID): ";
        getline(cin, idType);
        if(idType != "Passport"  && idType != "National ID") {
            cout << "Invalid ID type. Please enter 'Passport' or 'National ID'." << endl;
            idType.clear();
            continue;
        }
        else{
            idType = idType;
        }
    }while(idType.empty());
    
    do{
        cout << "Enter ID number: ";
        getline(cin, idNumber);
        if (!isIDNumberAvailable(idNumber)){
            cout << "ID number already registered. Please use another." << endl;
        } else {
            if(idType == "National ID`" && idNumber.length() != 12) {
                cout << "Invalid National ID number. It should be exactly 12 characters." << endl;
                idNumber.clear();
            }
            else if(idType == "Passport"){
                if (idNumber.length() != 8) {
                    cout << "Invalid Passport number. It should be between 6 to 9 characters." << endl;
                    idNumber.clear();
                }
                else if(idNumber.length() == 8 && (idNumber[0] < 'A' || idNumber[0] > 'Z')) {
                    cout << "Invalid Passport number. It should start with a capital letter." << endl;
                    idNumber.clear();
                }
                else{
                    idNumber = idNumber;
                }
            } 
            else{
                idNumber = idNumber;
            }
            idNumber = idNumber;
        }
    }while(idNumber.empty());

    // License Number and Expiry Date
    cout << "/n/nNote: A valid driving license is required to list a motorbike." << endl;
    cout << "Do you have a valid driving license? (yes/no): ";
    string hasLicense;
    getline(cin, hasLicense);
    if(hasLicense == "no") {
        cout << "You can only rent motorbikes with 50cc." << endl;

    }
    else if(hasLicense == "yes"){
        cout << "Proceeding with license details..." << endl;

        pause();
        do{
            cout << "Enter license number: ";
            getline(cin, licenseNumber);
            if(licenseNumber.length() != 12) {
                cout << "Invalid license number. Please enter a valid license number." << endl;
                licenseNumber.clear();
            }
            else if(!isLicenseNumberValid(licenseNumber)){
                cout << "License number not valid. Please enter a valid license number." << endl;
                licenseNumber.clear();
            }
            else{
                licenseNumber = licenseNumber;
            }
        }while(licenseNumber.empty());

        cout << "Enter license expiry date (DD/MM/YYYY): ";
        getline(cin, licenseExpiryDate);
    }

    saveToFile();
    cout << "Sign up successful! You can now log in with your new member account." << endl;
    pause();

}

void Guest::saveToFile(){
    std::ofstream file("Member.csv", std::ios::app);
    if(file.is_open()){
        cout << "Saving member details to file..." << endl;
        file << username << "," << password << "," << fullName << "," << phoneNumber << "," << email << "," << idType << "," << idNumber << "," << licenseNumber << "," << licenseExpiryDate << "," << creditPoints << "," << rating << endl;
        file.close();
    }
    else{
        cout << "Error opening file for writing." << endl;
    }
}

void Guest::viewListing() {
    cout << "Viewing available motorbikes for rent..." << endl;
    // Implementation for viewing available motorbikes
    
    ifstream file("EBike.csv");
    if(!file.is_open()) {
        cout << "Error opening motorbike listings file." << endl;
        return;
    }
    string line;
    getline(file, line); // Skip header line
    // Display header
    cout << left << setw(10) << "ID" 
         << setw(15) << "Owner" 
         << setw(20) << "Model" 
         << setw(20) << "Plate Number"
         << setw(10) << "CC" 
         << setw(10) << "Price/Day" 
         << setw(20) << "Status" 
         
         << endl;
    cout << string(75, '-') << endl;
    int renterRating = 3; // Default rating for guest

    while(getline(file, line)) {  // Read each motorbike listing
        stringstream ss(line);
        string id, owner, brand,model,color,engineSize_cc,year,plateNumber,startDate,endDate,priceDailyCP,status,renterRatingMin;
        getline(ss, id, ',');
        getline(ss, owner, ',');
        getline(ss, brand, ',');
        getline(ss, model, ',');
        getline(ss, color, ',');
        getline(ss, engineSize_cc, ',');
        getline(ss, year, ',');
        getline(ss, plateNumber, ',');
        getline(ss, startDate, ',');
        getline(ss, endDate, ',');
        getline(ss, priceDailyCP, ',');
        getline(ss, status, ',');
        getline(ss, renterRatingMin, ',');
        
        // Find owner's minimum renter rating from Member.csv
        ifstream memberFile("Member.csv");
        string memberLine;
        getline(memberFile, memberLine); // Skip header line
        renterRating = 3; // Default rating if not found
        while(getline(memberFile, memberLine)) {
            stringstream memberSS(memberLine);
            string memUsername, memPassword, memFullName, memPhoneNumber, memEmail, memIdType, memIdNumber, memLicenseNumber, memLicenseExpiryDate;
            int memCreditPoints, memRating;
            getline(memberSS, memUsername, ',');
            getline(memberSS, memPassword, ',');
            getline(memberSS, memFullName, ',');
            getline(memberSS, memPhoneNumber, ',');
            getline(memberSS, memEmail, ',');
            getline(memberSS, memIdType, ',');
            getline(memberSS, memIdNumber, ',');
            getline(memberSS, memLicenseNumber, ',');
            getline(memberSS, memLicenseExpiryDate, ',');
            string creditPointsStr;
            getline(memberSS, creditPointsStr, ',');
            memCreditPoints = stoi(creditPointsStr);
            string ratingStr;
            getline(memberSS, ratingStr);
            memRating = stoi(ratingStr);
            
            if(memUsername == owner) {
                renterRating = memRating;
                break;
            }
        }
        memberFile.close();
        
        // Only display motorbikes that are listed (status = "1")
        if(status == "1") {
            cout << left << setw(10) << id 
                 << setw(15) << owner 
                 << setw(20) << model 
                 << setw(20) << plateNumber
                 << setw(10) << engineSize_cc    
                 << setw(10) << priceDailyCP
                 << setw(20) << "Available" 
                 << endl;
            cout << "Minimum Renter Rating Required: " << renterRatingMin << endl;
            cout << "";
    



        }
    }
    file.close();
    pause();
}

// Testing Ground
int main(){
    Guest guest;
    cout << "Welcome, Guest!" << endl;
    cout << "1. Sign Up for a new member account" << endl;
    cout << "2. View available motorbikes for rent" << endl;
    cout << "3. Exit" << endl;
    cout << "Please select an option (1-3): ";
    int choice;
    cin >> choice;
    
    if(choice < 1 || choice > 3) {
        cout << "Invalid choice. Exiting." << endl;
        return 0;
    }
    else if(choice == 3) {
        cout << "Exiting. Goodbye!" << endl;
        return 0;
    }
    else if(choice == 1) {
            guest.signup(); // Clear
    }
    else if(choice == 2) {
        guest.viewListing();
    }


    
    return 0;
}



