#include "../include/Admin.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

namespace {
    // Filenames (standardized)
    const string ADMINS_CSV = "admins.csv";        // in src/ directory
    const string MEMBERS_CSV = "member.csv";      // keep lower-case used by other code
    const string EBIKE_CSV = "ebike.csv";
    const string RENTAL_CSV = "rental.csv";

    static string trim(const string& s) {
        size_t b = s.find_first_not_of(" \t\n\r");
        if (b == string::npos) return string();
        size_t e = s.find_last_not_of(" \t\n\r");
        return s.substr(b, e - b + 1);
    }

    // Ensure a CSV exists with header; returns true if file exists or created successfully.
    bool ensureFileWithHeader(const string& path, const string& header) {
        ifstream fi(path);
        if (fi.is_open()) {
            // if file exists but empty, add header
            string first;
            if (!getline(fi, first) || trim(first).empty()) {
                fi.close();
                ofstream fo(path, ios::trunc);
                if (!fo.is_open()) return false;
                fo << header << "\n";
                fo.close();
            }
            return true;
        }
        // create file with header
        ofstream fo(path);
        if (!fo.is_open()) return false;
        fo << header << "\n";
        fo.close();
        return true;
    }
}

void Admin::loadAdmindata() {
    // Ensure admins.csv exists and has header
    const string header = "username,password,email";
    if (!ensureFileWithHeader(ADMINS_CSV, header)) {
        cerr << "Failed to create or open " << ADMINS_CSV << "\n";
        return;
    }
    // Nothing else to load for now; admin data is checked from file when login is called.
}

bool Admin::validateAdminCredentials(const string& u, const string& p) {
    ifstream fi(ADMINS_CSV);
    if (!fi.is_open()) return false;
    string line;
    // read header
    if (!getline(fi, line)) return false;
    while (getline(fi, line)) {
        if (trim(line).empty()) continue;
        stringstream ss(line);
        string uname, pwd, mail;
        getline(ss, uname, ',');
        getline(ss, pwd, ',');
        getline(ss, mail, ',');
        if (trim(uname) == u && trim(pwd) == p) return true;
    }
    return false;
}

bool Admin::login(const string& inputUsername, const string& inputPassword) {
    if (validateAdminCredentials(inputUsername, inputPassword)) {
        username = inputUsername;
        password = inputPassword;
        isAuthenticated = true;
        cout << "Admin logged in successfully.\n";
        return true;
    }
    isAuthenticated = false;
    cout << "Admin login failed.\n";
    return false;
}

void Admin::viewAllUsers() const {
    if (!isAuthenticated) {
        cout << "Unauthorized. Please login as admin.\n";
        return;
    }
    ifstream fi(MEMBERS_CSV);
    if (!fi.is_open()) {
        cout << "No members file found (" << MEMBERS_CSV << ").\n";
        return;
    }
    string line;
    // print header style
    cout << left << setw(15) << "Username" << setw(25) << "Email" << setw(15) << "Phone" << setw(12) << "License" << setw(14) << "CreditPts" << setw(8) << "Rating" << "\n";
    // skip header if present
    if (getline(fi, line)) {
        // check if header contains 'username'
        if (line.find("username") == string::npos) {
            // first line is data: process it
            stringstream ss(line);
            vector<string> cols;
            string token;
            while (getline(ss, token, ',')) cols.push_back(token);
            if (!cols.empty()) {
                cout << left << setw(15) << (cols.size()>0?cols[0]:"")
                     << setw(25) << (cols.size()>2?cols[2]:"")
                     << setw(15) << (cols.size()>5?cols[5]:"")
                     << setw(12) << (cols.size()>3?cols[3]:"")
                     << setw(14) << (cols.size()>4?cols[4]:"")
                     << setw(8)  << (cols.size()>7?cols[7]:"") << "\n";
            }
        }
    }
    while (getline(fi, line)) {
        if (trim(line).empty()) continue;
        stringstream ss(line);
        vector<string> cols;
        string token;
        while (getline(ss, token, ',')) cols.push_back(trim(token));
        cout << left << setw(15) << (cols.size()>0?cols[0]:"")
             << setw(25) << (cols.size()>2?cols[2]:"")
             << setw(15) << (cols.size()>5?cols[5]:"")
             << setw(12) << (cols.size()>3?cols[3]:"")
             << setw(14) << (cols.size()>4?cols[4]:"")
             << setw(8)  << (cols.size()>7?cols[7]:"") << "\n";
    }
    fi.close();
}

void Admin::viewAllBikes() const {
    if (!isAuthenticated) {
        cout << "Unauthorized. Please login as admin.\n";
        return;
    }
    ifstream fi(EBIKE_CSV);
    if (!fi.is_open()) {
        cout << "No ebike file found (" << EBIKE_CSV << ").\n";
        return;
    }
    string line;
    cout << left << setw(10) << "Brand" << setw(15) << "Model" << setw(10) << "Color" << setw(10) << "Engine" << setw(6) << "Year" << setw(15) << "Plate" << setw(12) << "Start" << setw(12) << "End" << setw(10) << "DailyCP" << setw(12) << "MinRate" << setw(8) << "Listed" << setw(8) << "AvgRate" << "\n";
    if (getline(fi, line)) {
        if (line.find("brand") == string::npos) {
            // first line is data
            stringstream ss(line);
            vector<string> cols; string token;
            while (getline(ss, token, ',')) cols.push_back(trim(token));
            if (!cols.empty()) {
                double avg = 0.0;
                if (cols.size()>12) {
                    int sum = stoi(cols[11]);
                    int cnt = stoi(cols[12]);
                    if (cnt>0) avg = double(sum)/cnt;
                }
                cout << left << setw(10) << (cols.size()>0?cols[0]:"")
                     << setw(15) << (cols.size()>1?cols[1]:"")
                     << setw(10) << (cols.size()>2?cols[2]:"")
                     << setw(10) << (cols.size()>3?cols[3]:"")
                     << setw(6)  << (cols.size()>4?cols[4]:"")
                     << setw(15) << (cols.size()>5?cols[5]:"")
                     << setw(12) << (cols.size()>6?cols[6]:"")
                     << setw(12) << (cols.size()>7?cols[7]:"")
                     << setw(10) << (cols.size()>8?cols[8]:"")
                     << setw(12) << (cols.size()>9?cols[9]:"")
                     << setw(8)  << (cols.size()>10?cols[10]:"")
                     << setw(8)  << (cols.size()>11?to_string((int)avg):"") << "\n";
            }
        }
    }
    while (getline(fi, line)) {
        if (trim(line).empty()) continue;
        stringstream ss(line);
        vector<string> cols; string token;
        while (getline(ss, token, ',')) cols.push_back(trim(token));
        double avg = 0.0;
        if (cols.size()>12) {
            int sum = 0;
            int cnt = 0;
            try { sum = stoi(cols[11]); cnt = stoi(cols[12]); } catch(...) { sum=0; cnt=0; }
            if (cnt>0) avg = double(sum)/cnt;
        }
        cout << left << setw(10) << (cols.size()>0?cols[0]:"")
             << setw(15) << (cols.size()>1?cols[1]:"")
             << setw(10) << (cols.size()>2?cols[2]:"")
             << setw(10) << (cols.size()>3?cols[3]:"")
             << setw(6)  << (cols.size()>4?cols[4]:"")
             << setw(15) << (cols.size()>5?cols[5]:"")
             << setw(12) << (cols.size()>6?cols[6]:"")
             << setw(12) << (cols.size()>7?cols[7]:"")
             << setw(10) << (cols.size()>8?cols[8]:"")
             << setw(12) << (cols.size()>9?cols[9]:"")
             << setw(8)  << (cols.size()>10?cols[10]:"")
             << setw(8)  << (cols.size()>11?to_string((int)avg):"") << "\n";
    }
    fi.close();
}

void Admin::viewAllRentals() const {
    if (!isAuthenticated) {
        cout << "Unauthorized. Please login as admin.\n";
        return;
    }
    ifstream fi(RENTAL_CSV);
    if (!fi.is_open()) {
        cout << "No rental file found (" << RENTAL_CSV << ").\n";
        return;
    }
    string line;
    cout << left << setw(18) << "Renter Username" << setw(15) << "Bike Plate" << setw(12) << "Start Date" << setw(12) << "End Date" << setw(10) << "Status" << "\n";
    if (getline(fi, line)) {
        if (line.find("username") == string::npos) {
            // first line is data
            stringstream ss(line);
            vector<string> cols; string token;
            while (getline(ss, token, ',')) cols.push_back(trim(token));
            if (!cols.empty()) {
                cout << left << setw(18) << (cols.size()>0?cols[0]:"") << setw(15) << (cols.size()>1?cols[1]:"") << setw(12) << (cols.size()>2?cols[2]:"") << setw(12) << (cols.size()>3?cols[3]:"") << setw(10) << (cols.size()>4?cols[4]:"") << "\n";
            }
        }
    }
    while (getline(fi, line)) {
        if (trim(line).empty()) continue;
        stringstream ss(line);
        vector<string> cols; string token;
        while (getline(ss, token, ',')) cols.push_back(trim(token));
        cout << left << setw(18) << (cols.size()>0?cols[0]:"") << setw(15) << (cols.size()>1?cols[1]:"") << setw(12) << (cols.size()>2?cols[2]:"") << setw(12) << (cols.size()>3?cols[3]:"") << setw(10) << (cols.size()>4?cols[4]:"") << "\n";
    }
    fi.close();
}

void Admin::addBike(const string& brand, const string& model, const string& color, int engineSize, int year, const string& licensePlate, const string& startDate, const string& endDate, int dailyCP, int minRenterRating, bool listed) {
    if (!isAuthenticated) {
        cout << "Unauthorized. Please login as admin.\n";
        return;
    }
    // Read existing lines (including header if exists)
    vector<string> lines;
    ifstream fi(EBIKE_CSV);
    bool hasHeader = false;
    if (fi.is_open()) {
        string first;
        if (getline(fi, first)) {
            if (first.find("brand") != string::npos) {
                hasHeader = true;
                lines.push_back(first);
            } else {
                lines.push_back(first);
            }
            string l;
            while (getline(fi, l)) lines.push_back(l);
        }
        fi.close();
    }
    if (!hasHeader) {
        // add a standard header expected by other code
        lines.insert(lines.begin(), string("brand,model,color,engineSize_cc,year,plateNumber,startDate,endDate,dailyCP,minRenterRating,listed,ratingSum,ratingCount"));
    }
    // Build new bike row
    ostringstream row;
    row << brand << "," << model << "," << color << "," << engineSize << "," << year << "," << licensePlate << "," << startDate << "," << endDate << "," << dailyCP << "," << minRenterRating << "," << (listed?1:0) << ",0,0";
    lines.push_back(row.str());
    ofstream fo(EBIKE_CSV, ios::trunc);
    if (!fo.is_open()) {
        cout << "Failed to write to " << EBIKE_CSV << "\n";
        return;
    }
    for (const auto& l : lines) fo << l << "\n";
    fo.close();
    cout << "Bike added: " << licensePlate << "\n";
}

void Admin::removeBike(const string& licensePlate) {
    if (!isAuthenticated) {
        cout << "Unauthorized. Please login as admin.\n";
        return;
    }
    ifstream fi(EBIKE_CSV);
    if (!fi.is_open()) {
        cout << "No ebike file to modify.\n";
        return;
    }
    string line;
    vector<string> kept;
    bool headerKept = false;
    if (getline(fi, line)) {
        // always keep header if present
        if (line.find("brand") != string::npos) { kept.push_back(line); headerKept = true; }
        else kept.push_back(line);
    }
    while (getline(fi, line)) {
        if (trim(line).empty()) continue;
        stringstream ss(line);
        vector<string> cols; string token;
        while (getline(ss, token, ',')) cols.push_back(trim(token));
        if (cols.size() > 5 && cols[5] == licensePlate) {
            // skip this bike (remove)
            continue;
        }
        kept.push_back(line);
    }
    fi.close();
    ofstream fo(EBIKE_CSV, ios::trunc);
    if (!fo.is_open()) {
        cout << "Failed to write ebike file.\n";
        return;
    }
    for (const auto& l : kept) fo << l << "\n";
    fo.close();
    cout << "Bike removed (if existed): " << licensePlate << "\n";
}
