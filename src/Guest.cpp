#include "../include/Guest.h"
#include "EBike.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cctype>
#include <vector>

using namespace std;

static string trim(const string& s) {
    size_t b = s.find_first_not_of(" \t\n\r");
    if (b == string::npos) return string();
    size_t e = s.find_last_not_of(" \t\n\r");
    return s.substr(b, e - b + 1);
}

Guest::Guest() : creditPoints(20), rating(3), licenseExpiry(0) {}

bool Guest::isUsernameAvailable(const string& username) {
    ifstream file("member.csv");
    if (!file.is_open()) return true; // if file missing, username is available
    string line;
    getline(file, line); // skip header if present
    while (getline(file, line)) {
        stringstream ss(line);
        string uname;
        if (!getline(ss, uname, ',')) continue;
        if (trim(uname) == username) return false;
    }
    return true;
}

bool Guest::isEmailAvailable(const string& email) {
    ifstream file("member.csv");
    if (!file.is_open()) return true;
    string line; getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string uname, pwd, mail;
        getline(ss, uname, ',');
        getline(ss, pwd, ',');
        getline(ss, mail, ',');
        if (trim(mail) == email) return false;
    }
    return true;
}

bool Guest::isPhoneNumberAvailable(const string& phone) {
    ifstream file("member.csv");
    if (!file.is_open()) return true;
    string line; getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        vector<string> cols;
        string token;
        while (getline(ss, token, ',')) cols.push_back(token);
        if (cols.size()>5 && trim(cols[5])==phone) return false;
    }
    return true;
}

bool Guest::isIDNumberAvailable(const string& id) {
    ifstream file("member.csv");
    if (!file.is_open()) return true;
    string line; getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        vector<string> cols; string token;
        while (getline(ss, token, ',')) cols.push_back(token);
        if (cols.size()>6 && trim(cols[6])==id) return false;
    }
    return true;
}

bool Guest::isPasswordValid(const string& password) {
    bool hasUpper = false, hasLower = false, hasDigit = false;
    if (password.size() < 8) return false;
    for (char c : password) {
        if (isupper(static_cast<unsigned char>(c))) hasUpper = true;
        if (islower(static_cast<unsigned char>(c))) hasLower = true;
        if (isdigit(static_cast<unsigned char>(c))) hasDigit = true;
    }
    return hasUpper && hasLower && hasDigit;
}

bool Guest::isLicenseNumberValid(const string& licenseNumber) {
    if (licenseNumber.empty()) return true; // optional
    // simple validation: alnum and length between 5 and 12
    if (licenseNumber.size() < 5 || licenseNumber.size() > 12) return false;
    for (char c : licenseNumber) if (!isalnum(static_cast<unsigned char>(c))) return false;
    return true;
}

void Guest::saveToFile() {
    // Ensure header exists
    ifstream fi("member.csv");
    bool hasHeader = false;
    if (fi.is_open()) {
        string first;
        if (getline(fi, first)) {
            if (first.find("username") != string::npos) hasHeader = true;
        }
        fi.close();
    }
    ofstream fo("member.csv", ios::app);
    if (!fo.is_open()) {
        cout << "Failed to open member.csv for writing.\n";
        return;
    }
    if (!hasHeader) {
        fo << "username,password,email,license,creditPoints,phone,idNumber,rating\n";
    }
    fo << username << "," << password << "," << email << "," << licenseNumber << "," << creditPoints << "," << phoneNumber << "," << idNumber << "," << rating << "\n";
    fo.close();
}

void Guest::signup() {
    cout << "\n--- Guest: Sign up for a new member account ---\n";
    while (true) {
        cout << "Enter username: ";
        getline(cin, username);
        username = trim(username);
        if (username.empty()) { cout << "Username cannot be empty.\n"; continue; }
        if (!isUsernameAvailable(username)) { cout << "Username already exists.\n"; continue; }
        break;
    }
    while (true) {
        cout << "Enter email: "; getline(cin, email); email = trim(email);
        if (email.empty()) { cout << "Email cannot be empty.\n"; continue; }
        if (!isEmailAvailable(email)) { cout << "Email already used.\n"; continue; }
        break;
    }
    while (true) {
        cout << "Enter password: "; getline(cin, password); password = trim(password);
        if (!isPasswordValid(password)) { cout << "Password must be >=8 chars and include upper, lower and digit.\n"; continue; }
        break;
    }
    cout << "Enter full name: "; getline(cin, fullName); fullName = trim(fullName);
    while (true) {
        cout << "Enter phone number: "; getline(cin, phoneNumber); phoneNumber = trim(phoneNumber);
        bool ok = true; if (phoneNumber.size()<9 || phoneNumber.size()>11) ok=false; for (char c: phoneNumber) if (!isdigit(static_cast<unsigned char>(c))) ok=false;
        if (!ok) { cout << "Invalid phone. Use digits only, length 9-11.\n"; continue; }
        if (!isPhoneNumberAvailable(phoneNumber)) { cout << "Phone already used.\n"; continue; }
        break;
    }
    while (true) {
        cout << "ID type [1] CCCD [2] Passport: "; string t; getline(cin, t); t = trim(t);
        if (t=="1") { idType = "CCCD"; break; } else if (t=="2") { idType = "Passport"; break; } else cout << "Invalid choice.\n";
    }
    while (true) {
        cout << "Enter ID number: "; getline(cin, idNumber); idNumber = trim(idNumber);
        if (idNumber.empty()) { cout << "ID cannot be empty.\n"; continue; }
        if (!isIDNumberAvailable(idNumber)) { cout << "ID already used.\n"; continue; }
        // basic checks
        bool ok = true;
        if (idType=="CCCD") { if (idNumber.size()!=12) ok=false; for (char c: idNumber) if (!isdigit(static_cast<unsigned char>(c))) ok=false; }
        else { if (idNumber.size()!=8) ok=false; }
        if (!ok) { cout << "Invalid ID format for " << idType << ".\n"; continue; }
        break;
    }
    cout << "Enter license number (optional): "; getline(cin, licenseNumber); licenseNumber = trim(licenseNumber);
    if (!isLicenseNumberValid(licenseNumber)) { cout << "Invalid license number format. Keeping empty.\n"; licenseNumber.clear(); }
    // license expiry: optional; skip on empty
    while (true) {
        cout << "Enter license expiry (YYYYMMDD) or leave empty: "; string s; getline(cin, s); s = trim(s);
        if (s.empty()) { licenseExpiry = 0; break; }
        bool digits = !s.empty() && all_of(s.begin(), s.end(), [](char c){ return isdigit(static_cast<unsigned char>(c)); });
        if (!digits || s.size()!=8) { cout << "Invalid format. Use YYYYMMDD.\n"; continue; }
        licenseExpiry = 0; for (char c: s) licenseExpiry = licenseExpiry*10 + (c - '0');
        break;
    }
    // deposit leads to creditPoints
    while (true) {
        cout << "Enter initial deposit in USD (minimum 20): "; string s; getline(cin, s); s = trim(s);
        if (s.empty()) { cout << "Please enter a number.\n"; continue; }
        bool digits = all_of(s.begin(), s.end(), [](char c){ return isdigit(static_cast<unsigned char>(c)); });
        if (!digits) { cout << "Invalid input. Use digits only.\n"; continue; }
        int v = stoi(s);
        if (v < 20) { cout << "Minimum deposit is $20.\n"; continue; }
        creditPoints = v;
        break;
    }
    // finalize
    rating = 3;
    saveToFile();
    cout << "Signup successful. You have " << creditPoints << " CP.\n";
}

void Guest::viewListing() {
    vector<EBike> bikes = EBike::loadAll("ebike.csv");
    cout << "Available bikes:\n";
    for (const auto& b : bikes) {
        if (!b.listed) continue;
        cout << "- " << b.brand << " " << b.model << " | " << b.engineSize << "cc | Plate: " << b.plateNumber << " | " << b.dailyCP << " CP/day | Rating: " << b.getAverageRating() << "\n";
    }
}

void Guest::viewLimitedBikes() {
    vector<EBike> bikes = EBike::loadAll("ebike.csv");
    cout << "First up to 3 bikes:\n";
    int shown = 0;
    for (const auto& b : bikes) {
        if (!b.listed) continue;
        cout << "- " << b.brand << " " << b.model << " | " << b.engineSize << "cc | Plate: " << b.plateNumber << " | " << b.dailyCP << " CP/day | Rating: " << b.getAverageRating() << "\n";
        shown++;
        if (shown >= 3) break;
    }
    if (shown == 0) cout << "No listed bikes available.\n";
}

string Guest::getUsername() const { return username; }
