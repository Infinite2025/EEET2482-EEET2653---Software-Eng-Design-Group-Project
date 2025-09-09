// Login Function
// Prompts the user to enter their username and password, and verifies the credentials against stored member data.
// If the credentials are valid, the user is granted access to member functionalities; otherwise, an error message is displayed.

// Member Credit Top-Up Function
// Allows members to top up their credit points by entering a valid amount.
// Access the csv file to update the member's credit points.
// Adds the specified amount to the member's existing credit points and updates the member data accordingly.

// View Rental History Function
// Displays the rental history of the logged-in member by reading from a rental history file.

// Rental Acceptance Function
// Allows members to accept or decline rental requests for their listed motorbikes.
// Members can view pending rental requests and choose to accept or decline them.
// Updates the rental status accordingly in the rental history file.

// Rated rides Function
// Allows members to rate their rental experiences after completing a ride.
// Members can provide a rating for each completed rental, which is then stored in the rental history file for future reference.
// For members sharing their motorbikes, they can also view the ratings given by renters.
// Only accepted rides can be rated.
/*
#include "../include/Member.h"
#include "../include/Rental.h"
#include "../include/EBike.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

Member::Member() {}

void Member::updatePersonalInfo(const string& newEmail, const string& newPhone) {
    email = newEmail;
    phoneNumber = newPhone;

    // Cập nhật trong file member.csv
    ifstream infile("member.csv");
    ofstream temp("temp.csv");
    string line;
    getline(infile, line);
    temp << line << "\n"; // header

    while (getline(infile, line)) {
        stringstream ss(line);
        vector<string> cols;
        string token;
        while (getline(ss, token, ',')) cols.push_back(token);

        if (!cols.empty() && cols[0] == username) {
            cols[2] = email;     // cột email
            cols[5] = phoneNumber; // cột phone
        }

        for (size_t i = 0; i < cols.size(); i++) {
            temp << cols[i];
            if (i < cols.size() - 1) temp << ",";
        }
        temp << "\n";
    }

    infile.close();
    temp.close();
    remove("member.csv");
    rename("temp.csv", "member.csv");
    cout << "✅ Personal info updated!\n";
}

void Member::requestRental(const string& bikePlate, const string& startDate, const string& endDate) {
    ofstream file("rental.csv", ios::app);
    file << username << "," << bikePlate << "," << startDate << "," << endDate << ",Pending\n";
    file.close();
    cout << "✅ Rental request submitted!\n";
}

void Member::viewAllRentals() {
    ifstream file("rental.csv");
    string line;
    getline(file, line); // header
    cout << "📄 Your rentals:\n";
    while (getline(file, line)) {
        stringstream ss(line);
        vector<string> cols;
        string token;
        while (getline(ss, token, ',')) cols.push_back(token);

        if (!cols.empty() && cols[0] == username) {
            cout << "Bike: " << cols[1]
                 << " | From: " << cols[2]
                 << " | To: " << cols[3]
                 << " | Status: " << cols[4] << "\n";
        }
    }
}

void Member::rateRental(const string& bikePlate, int rating) {
    ifstream infile("ebike.csv");
    ofstream temp("temp.csv");
    string line;
    getline(infile, line);
    temp << line << "\n"; // header

    while (getline(infile, line)) {
        stringstream ss(line);
        vector<string> cols;
        string token;
        while (getline(ss, token, ',')) cols.push_back(token);

        if (!cols.empty() && cols[5] == bikePlate) { // plateNumber ở cột 6
            int ratingSum = stoi(cols[11]);
            int ratingCount = stoi(cols[12]);
            ratingSum += rating;
            ratingCount++;
            cols[11] = to_string(ratingSum);
            cols[12] = to_string(ratingCount);
        }

        for (size_t i = 0; i < cols.size(); i++) {
            temp << cols[i];
            if (i < cols.size() - 1) temp << ",";
        }
        temp << "\n";
    }

    infile.close();
    temp.close();
    remove("ebike.csv");
    rename("temp.csv", "ebike.csv");
    cout << "✅ Rating submitted!\n";
}
*/

#include "../include/Member.h"
#include "EBike.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

static string trim(const string& s) {
    size_t b = s.find_first_not_of(" \t\n\r");
    if (b == string::npos) return string();
    size_t e = s.find_last_not_of(" \t\n\r");
    return s.substr(b, e - b + 1);
}

Member::Member()
: licenseExpiry(0), creditPoints(0), rating(3), isAuthenticated(false) {}

// CSV helpers
static vector<vector<string>> loadCSV(const string& path) {
    vector<vector<string>> out;
    ifstream fi(path);
    if (!fi.is_open()) return out;
    string line;
    // skip header if present
    if (!getline(fi, line)) return out;
    if (trim(line).empty()) return out;
    // if header lacks commas we still proceed
    while (getline(fi, line)) {
        if (trim(line).empty()) continue;
        stringstream ss(line);
        vector<string> cols; string token;
        while (getline(ss, token, ',')) cols.push_back(trim(token));
        out.push_back(cols);
    }
    fi.close();
    return out;
}

static bool saveCSVWithHeader(const string& path, const vector<vector<string>>& rows, const string& header) {
    ofstream fo(path, ios::trunc);
    if (!fo.is_open()) return false;
    fo << header << "\n";
    for (const auto& r : rows) {
        for (size_t i = 0; i < r.size(); ++i) {
            if (i) fo << ",";
            fo << r[i];
        }
        fo << "\n";
    }
    fo.close();
    return true;
}

// Load member data from member.csv into this object if username matches
void Member::loadMemberData() {
    auto rows = loadCSV("member.csv");
    for (const auto& r : rows) {
        if (r.size()>0 && r[0] == username) {
            password = (r.size()>1?r[1]:password);
            email = (r.size()>2?r[2]:email);
            ownedMotorbikePlate = (r.size()>3?r[3]:ownedMotorbikePlate);
            creditPoints = (r.size()>4?stoi(r[4]):creditPoints);
            phone = (r.size()>5?r[5]:phone);
            // idNumber at 6
            rating = (r.size()>7?stoi(r[7]):rating);
            break;
        }
    }
}

bool Member::login(const string& uname, const string& pwd) {
    auto rows = loadCSV("member.csv");
    for (const auto& r : rows) {
        if (r.size()>=2 && r[0]==uname && r[1]==pwd) {
            username = r[0]; password = r[1];
            email = (r.size()>2?r[2]:"");
            ownedMotorbikePlate = (r.size()>3?r[3]:"");
            creditPoints = (r.size()>4?stoi(r[4]):0);
            phone = (r.size()>5?r[5]:"");
            rating = (r.size()>7?stoi(r[7]):3);
            isAuthenticated = true;
            return true;
        }
    }
    return false;
}

void Member::logout() { isAuthenticated = false; }

void Member::showMemberMenu() const {
    cout << "\n=== MEMBER MENU ===\n";
    cout << "1. List a motorbike (carpool)\n";
    cout << "2. Search active carpools\n";
    cout << "3. Book a carpool\n";
    cout << "4. Manage bookings/requests\n";
    cout << "5. Purchase credits\n";
    cout << "6. View/ edit profile\n";
    cout << "7. Rate a ride\n";
    cout << "8. Transfer credits\n";
    cout << "9. Logout\n";
    cout << "Choose option: ";
}

void Member::memberMenuLoop() {
    if (!isAuthenticated) { cout << "Please login first.\n"; return; }
    string line; int choice = 0;
    do {
        showMemberMenu();
        getline(cin, line);
        if (!line.empty()) choice = stoi(line); else choice = 0;
        switch (choice) {
            case 1: listEBike(); break;
            case 2: searchActiveCarpool(); break;
            case 3: bookEBike(); break;
            case 4: manageBookings(); break;
            case 5: purchaseCredits(); break;
            case 6: viewProfile(); editProfile(); break;
            case 7: rating(); break;
            case 8: {
                cout << "Enter recipient username: "; string to; getline(cin, to);
                cout << "Enter amount: "; string amt; getline(cin, amt);
                transferCredits(username, to, stoi(amt));
                break;
            }
            case 9: logout(); cout << "Logged out.\n"; break;
            default: cout << "Invalid option.\n";
        }
    } while (choice != 9 && isAuthenticated);
}

void Member::registerMotorbike() { listEBike(); }

void Member::listEBike() {
    if (!isAuthenticated) { cout << "Login first.\n"; return; }
    vector<EBike> bikes = EBike::loadAll("ebike.csv");
    EBike m;
    cout << "Enter brand: "; getline(cin, m.brand);
    cout << "Enter model: "; getline(cin, m.model);
    cout << "Enter color: "; getline(cin, m.color);
    cout << "Enter engine size (cc): "; string s; getline(cin, s); m.engineSize = stoi(s);
    cout << "Enter year: "; getline(cin, s); m.year = stoi(s);
    cout << "Enter plate number: "; getline(cin, m.plateNumber);
    cout << "Enter available start date (YYYY-MM-DD): "; getline(cin, m.startDate);
    cout << "Enter available end date (YYYY-MM-DD): "; getline(cin, m.endDate);
    cout << "Enter daily CP price: "; getline(cin, s); m.dailyCP = stoi(s);
    cout << "Enter minimum renter rating (1-5): "; getline(cin, s); m.minRenterRating = stoi(s);
    m.listed = true;
    bikes.push_back(m);
    if (!EBike::saveAll(bikes, "ebike.csv")) cout << "Failed to save ebike.csv\n";
    else {
        ownedMotorbikePlate = m.plateNumber;
        // update member.csv
        auto rows = loadCSV("member.csv");
        for (auto& r : rows) if (r.size()>0 && r[0]==username) { if (r.size()>3) r[3]=ownedMotorbikePlate; else while (r.size()<=3) r.push_back(ownedMotorbikePlate); }
        saveCSVWithHeader("member.csv", rows, "username,password,email,license,creditPoints,phone,idNumber,rating");
        cout << "Listed motorbike: " << ownedMotorbikePlate << "\n";
    }
}

void Member::unlistEBike() {
    if (!isAuthenticated) { cout << "Login first.\n"; return; }
    if (ownedMotorbikePlate.empty()) { cout << "You have no listed motorbike.\n"; return; }
    auto bikes = EBike::loadAll("ebike.csv");
    bool found = false;
    for (auto& b : bikes) {
        if (b.plateNumber == ownedMotorbikePlate) { b.Unlist(); found = true; }
    }
    if (found) { EBike::saveAll(bikes, "ebike.csv"); cout << "Unlisted your motorbike.\n"; }
    else cout << "Motorbike not found.\n";
}

void Member::bookEBike() { bookEBike: // label for clarity
    if (!isAuthenticated) { cout << "Login first.\n"; return; }
    // reuse search/request rental
    searchAndRequestRental();
}

void Member::searchAndRequestRental() { // kept for compatibility
    if (!isAuthenticated) { cout << "Login first.\n"; return; }
    vector<EBike> bikes = EBike::loadAll("ebike.csv");
    cout << "Enter desired start date (YYYY-MM-DD): "; string s; getline(cin, s);
    cout << "Enter desired end date (YYYY-MM-DD): "; string e; getline(cin, e);
    cout << "Available matches:\n";
    vector<EBike> matches; int idx=0;
    for (const auto& b : bikes) {
        if (!b.listed) continue;
        if (b.isAvailableFor(s,e)) {
            cout << "["<<idx<<"] "<<b.brand<<" "<<b.model<<" | Plate:"<<b.plateNumber<<" | "<<b.dailyCP<<" CP/day\n";
            matches.push_back(b); idx++;
        }
    }
    if (matches.empty()) { cout << "No matches.\n"; return; }
    cout << "Enter index to request: "; string choice; getline(cin, choice);
    if (choice.empty()) return; int ci = stoi(choice);
    if (ci<0||ci>=(int)matches.size()) { cout << "Invalid index.\n"; return; }
    EBike chosen = matches[ci];
    int cost = chosen.estimateCost(s,e);
    if (cost<0) { cout<<"Cannot compute cost.\n"; return; }
    if (creditPoints < cost) { cout<<"Insufficient CP. You have "<<creditPoints<<"\n"; return; }
    if (rating < chosen.minRenterRating) { cout<<"Your rating too low.\n"; return; }
    if (chosen.engineSize>50 && licenseNumber.empty()) { cout<<"License required to rent this bike.\n"; return; }
    // append to rental.csv
    // ensure header exists
    ifstream fi("rental.csv"); bool hasHeader=false; if (fi.is_open()) { string first; if (getline(fi, first)) { if (first.find("username")!=string::npos) hasHeader=true; } fi.close(); }
    ofstream fo("rental.csv", ios::app);
    if (!fo.is_open()) { cout<<"Failed to open rental.csv\n"; return; }
    if (!hasHeader) fo << "username,bikePlate,startDate,endDate,status\n";
    fo << username << "," << chosen.plateNumber << "," << s << "," << e << ",Pending\n";
    fo.close();
    cout<<"Booking request submitted.\n";
}

void Member::manageRequests() { approveRentalRequests(); }

void Member::approveRentalRequests() {
    if (!isAuthenticated) { cout<<"Login first.\n"; return; }
    if (ownedMotorbikePlate.empty()) { cout<<"You do not own a listed motorbike.\n"; return; }
    auto rows = loadCSV("rental.csv");
    bool any=false;
    for (size_t i=0;i<rows.size();++i) {
        auto& r = rows[i];
        if (r.size()>=5 && r[1]==ownedMotorbikePlate && r[4]=="Pending") {
            any=true; cout<<"Request "<<i<<": renter="<<r[0]<<" period="<<r[2]<<"->"<<r[3]<<"\n";
            cout<<"Accept? (y/n): "; string a; getline(cin,a);
            if (!a.empty() && (a[0]=='y'||a[0]=='Y')) {
                r[4] = "Accepted";
                // deduct cp from renter
                auto users = loadCSV("member.csv");
                for (auto& u : users) if (u.size()>0 && u[0]==r[0]) {
                    int cp = (u.size()>4?stoi(u[4]):0);
                    int cost = 0; auto bikes = EBike::loadAll("ebike.csv"); for (const auto& b: bikes) if (b.plateNumber==ownedMotorbikePlate) cost = b.estimateCost(r[2], r[3]);
                    if (cost>cp) cp = 0; else cp -= cost;
                    if (u.size()>4) u[4]=to_string(cp); else while (u.size()<=4) u.push_back(to_string(cp));
                }
                saveCSVWithHeader("member.csv", loadCSV("member.csv"), "username,password,email,license,creditPoints,phone,idNumber,rating");
                cout<<"Accepted.\n";
            } else { r[4] = "Rejected"; cout<<"Rejected.\n"; }
        }
    }
    if (!any) cout<<"No pending requests.\n";
    saveCSVWithHeader("rental.csv", rows, "username,bikePlate,startDate,endDate,status");
}

void Member::confirmEBikeRides() { // mark accepted as Completed for this user
    if (!isAuthenticated) { cout<<"Login first.\n"; return; }
    auto rows = loadCSV("rental.csv"); bool found=false;
    for (auto& r : rows) if (r.size()>=5 && r[0]==username && r[4]=="Accepted") { r[4] = "Completed"; found=true; }
    if (found) { saveCSVWithHeader("rental.csv", rows, "username,bikePlate,startDate,endDate,status"); cout<<"Confirmed rides.\n"; } else cout<<"No accepted bookings to confirm.\n";
}

void Member::returnRentedMotorbike() { confirmEBikeRides(); }

void Member::manageBookings() { viewAllRentals(); }

void Member::viewAllRentals() const {
    if (!isAuthenticated) { cout<<"Login first.\n"; return; }
    ifstream fi("rental.csv"); if (!fi.is_open()) { cout<<"No rental records.\n"; return; }
    string line; getline(fi, line);
    cout<<left<<setw(15)<<"Renter"<<setw(12)<<"Plate"<<setw(12)<<"Start"<<setw(12)<<"End"<<setw(10)<<"Status"<<"\n";
    while (getline(fi, line)) {
        if (trim(line).empty()) continue;
        stringstream ss(line); vector<string> c; string t; while (getline(ss,t,',')) c.push_back(trim(t));
        if (c.size()>=5 && (c[0]==username || c[1]==ownedMotorbikePlate)) cout<<left<<setw(15)<<(c.size()>0?c[0]:"")<<setw(12)<<(c.size()>1?c[1]:"")<<setw(12)<<(c.size()>2?c[2]:"")<<setw(12)<<(c.size()>3?c[3]:"")<<setw(10)<<(c.size()>4?c[4]:"")<<"\n";
    }
    fi.close();
}

void Member::viewProfile() const {
    if (!isAuthenticated) { cout<<"Login first.\n"; return; }
    cout<<"Profile:\n";
    cout<<"Username: "<<username<<"\n";
    cout<<"Full name: "<<fullName<<"\n";
    cout<<"Email: "<<email<<"\n";
    cout<<"Phone: "<<phone<<"\n";
    cout<<"CreditPoints: "<<creditPoints<<"\n";
    cout<<"Rating: "<<rating<<"\n";
}

void Member::editProfile() {
    if (!isAuthenticated) { cout<<"Login first.\n"; return; }
    cout<<"Edit profile (leave empty to keep current):\n";
    cout<<"Full name ["<<fullName<<"]: "; string s; getline(cin,s); if (!s.empty()) fullName = s;
    cout<<"Email ["<<email<<"]: "; getline(cin,s); if (!s.empty()) email = s;
    cout<<"Phone ["<<phone<<"]: "; getline(cin,s); if (!s.empty()) phone = s;
    // persist to member.csv
    auto rows = loadCSV("member.csv");
    for (auto& r : rows) if (r.size()>0 && r[0]==username) {
        if (r.size()>2) r[2]=email; else while (r.size()<=2) r.push_back(email);
        if (r.size()>5) r[5]=phone; else while (r.size()<=5) r.push_back(phone);
    }
    saveCSVWithHeader("member.csv", rows, "username,password,email,license,creditPoints,phone,idNumber,rating");
    cout<<"Profile updated.\n";
}

void Member::rating() { rateRental(); }

void Member::rateRental() {
    if (!isAuthenticated) { cout<<"Login first.\n"; return; }
    cout<<"Enter bike plate to rate: "; string plate; getline(cin, plate);
    cout<<"Enter rating (1-5): "; string s; getline(cin,s); int rscore = stoi(s);
    auto bikes = EBike::loadAll("ebike.csv"); bool updated=false;
    for (auto& b : bikes) if (b.plateNumber==plate) { if (b.addRating(rscore)) updated=true; }
    if (updated) EBike::saveAll(bikes, "ebike.csv");
    cout<<(updated?"Rating saved.\n":"Failed to rate.\n");
}

void Member::purchaseCredits() { topUpCredit(); }

void Member::topUpCredit() {
    if (!isAuthenticated) { cout<<"Login first.\n"; return; }
    cout<<"Enter USD to add: "; string s; getline(cin,s); if (s.empty()) return; int v = stoi(s); if (v<=0) { cout<<"Invalid amount.\n"; return; }
    creditPoints += v;
    auto rows = loadCSV("member.csv");
    for (auto& r : rows) if (r.size()>0 && r[0]==username) { if (r.size()>4) r[4]=to_string(creditPoints); else while (r.size()<=4) r.push_back(to_string(creditPoints)); }
    saveCSVWithHeader("member.csv", rows, "username,password,email,license,creditPoints,phone,idNumber,rating");
    cout<<"Added "<<v<<" CP. New balance: "<<creditPoints<<"\n";
}

void Member::manageBookings() { viewAllRentals(); }

void Member::bookCarpool() { searchAndRequestRental(); }

void Member::unlistCarpool() { unlistEBike(); }

void Member::confirmCarpoolRides() { confirmEBikeRides(); }

void Member::transferCredits(const string& fromUser, const string& toUser, int amount) {
    if (!isAuthenticated) { cout<<"Login first.\n"; return; }
    if (amount<=0) { cout<<"Invalid amount.\n"; return; }
    auto rows = loadCSV("member.csv");
    bool fromFound=false, toFound=false;
    for (auto& r : rows) {
        if (r.size()>0 && r[0]==fromUser) { int cp=(r.size()>4?stoi(r[4]):0); if (cp<amount) { cout<<"Insufficient funds.\n"; return; } cp-=amount; if (r.size()>4) r[4]=to_string(cp); else while (r.size()<=4) r.push_back(to_string(cp)); fromFound=true; }
        if (r.size()>0 && r[0]==toUser) { int cp=(r.size()>4?stoi(r[4]):0); cp+=amount; if (r.size()>4) r[4]=to_string(cp); else while (r.size()<=4) r.push_back(to_string(cp)); toFound=true; }
    }
    if (!fromFound || !toFound) { cout<<"User(s) not found.\n"; return; }
    saveCSVWithHeader("member.csv", rows, "username,password,email,license,creditPoints,phone,idNumber,rating");
    cout<<"Transferred "<<amount<<" CP from "<<fromUser<<" to "<<toUser<<"\n";
}

string Member::getUserName() const { return username; }
int Member::getCredits() const { return creditPoints; }
