#include "EBike.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Helper functions

void EBike::splitDate(const string& d, int& year, int& mon, int& day) {
    // Expect YYYY-MM-DD
    if (d.size() < 10) { year = mon = day = 0; return; }
    try {
        year = stoi(d.substr(0, 4));
        mon  = stoi(d.substr(5, 2));
        day  = stoi(d.substr(8, 2));
    } catch(...) { year = mon = day = 0; }
}

bool EBike::dateLE(const string& a, const string& b) {
    int ya, ma, da; splitDate(a, ya, ma, da);
    int yb, mb, db; splitDate(b, yb, mb, db);
    if (ya != yb) return ya < yb;
    if (ma != mb) return ma < mb;
    return da <= db;
}

int EBike::daysInclusive(const string& a, const string& b) {
    int ya, ma, da; splitDate(a, ya, ma, da);
    int yb, mb, db; splitDate(b, yb, mb, db);

    if (ya==0 || yb==0) return -1;
    int daysA = ya * 360 + ma * 30 + da; // approximate conversion
    int daysB = yb * 360 + mb * 30 + db;
    if (daysB < daysA) return -1;
    return (daysB - daysA) + 1;
}

//Constructor

EBike::EBike()
: brand(""), model(""), color(""), engineSize(0), year(0), plateNumber(""),
  startDate(""), endDate(""), dailyCP(0), minRenterRating(0), listed(false),
  ratingSum(0), ratingCount(0) {}

EBike::EBike(const string& brand,
             const string& model,
             const string& color,
             int engineSize,
             int year,
             const string& plateNumber)
: brand(brand), model(model), color(color),
  engineSize(engineSize), year(year), plateNumber(plateNumber),
  startDate(""), endDate(""), dailyCP(0), minRenterRating(0), listed(false),
  ratingSum(0), ratingCount(0) {}

// Core features

bool EBike::Listing(const string& start,
                    const string& end,
                    int dailyRate,
                    int minRate,
                    bool available) {
    if (!dateLE(start, end)) return false;
    if (dailyRate <= 0) return false;
    if (minRate < 0) return false;

    startDate = start;
    endDate = end;
    dailyCP = dailyRate;
    minRenterRating = minRate;
    listed = available;
    return true;
}

bool EBike::Unlist() {
    if (!listed) return false;
    listed = false;
    return true;
}

bool EBike::isAvailableFor(const string& s, const string& e) const {
    if (!listed) return false;
    if (!dateLE(s, e)) return false;
    if (!dateLE(startDate, s)) return false;
    if (!dateLE(e, endDate))   return false;
    return true;
}

int EBike::estimateCost(const string& s, const string& e) const {
    if (!isAvailableFor(s, e)) return -1;
    int days = daysInclusive(s, e);
    if (days <= 0) return -1;
    return days * dailyCP;
}

bool EBike::addRating(int score) {
    if (score < 1 || score > 5) return false;
    ratingSum += score;
    ratingCount += 1;
    return true;
}

double EBike::getAverageRating() const {
    if (ratingCount <= 0) return 0.0;
    return static_cast<double>(ratingSum) / ratingCount;
}

//CSV (simple, no escaping)

string EBike::toCSV() const {
    // brand,model,color,engineSize_cc,year,plateNumber,startDate,endDate,dailyCP,minRenterRating,listed,ratingSum,ratingCount
    ostringstream oss;
    oss << brand << ","
        << model << ","
        << color << ","
        << engineSize << ","
        << year << ","
        << plateNumber << ","
        << startDate << ","
        << endDate << ","
        << dailyCP << ","
        << minRenterRating << ","
        << (listed ? 1 : 0) << ","
        << ratingSum << ","
        << ratingCount;
    return oss.str();
}

static vector<string> splitByComma(const string& line) {
    vector<string> out;
    string cur;
    for (size_t i = 0; i < line.size(); ++i) {
        char ch = line[i];
        if (ch == ',') {
            out.push_back(cur);
            cur.clear();
        } else {
            cur.push_back(ch);
        }
    }
    out.push_back(cur);
    return out;
}

EBike EBike::fromCSV(const string& line) {
    vector<string> c = splitByComma(line);
    if (c.size() < 13) {
        return EBike();
    }

    EBike b;
    b.brand          = c[0];
    b.model          = c[1];
    b.color          = c[2];
    try { b.engineSize     = stoi(c[3]); } catch(...) { b.engineSize = 0; }
    try { b.year           = stoi(c[4]); } catch(...) { b.year = 0; }
    b.plateNumber    = c[5];
    b.startDate      = c[6];
    b.endDate        = c[7];
    try { b.dailyCP        = stoi(c[8]); } catch(...) { b.dailyCP = 0; }
    try { b.minRenterRating= stoi(c[9]); } catch(...) { b.minRenterRating = 0; }
    try { b.listed         = (stoi(c[10]) != 0); } catch(...) { b.listed = false; }
    try { b.ratingSum      = stoi(c[11]); } catch(...) { b.ratingSum = 0; }
    try { b.ratingCount    = stoi(c[12]); } catch(...) { b.ratingCount = 0; }
    return b;
}

bool EBike::saveAll(const vector<EBike>& v, const string& path) {
    ofstream fo(path);
    if (!fo.is_open()) return false;
    // Header (standardized for Admin::viewAllBikes)
    fo << "brand,model,color,engineSize_cc,year,plateNumber,startDate,endDate,dailyCP,minRenterRating,listed,ratingSum,ratingCount" << endl;
    for (size_t i = 0; i < v.size(); ++i) {
        fo << v[i].toCSV() << endl;
    }
    fo.close();
    return true;
}

vector<EBike> EBike::loadAll(const string& path) {
    vector<EBike> out;
    ifstream fi(path);
    if (!fi.is_open()) return out;

    string line;
    if (getline(fi, line)) {
        if (line.rfind("brand,model,", 0) != 0) {
            // first line is data
            out.push_back(EBike::fromCSV(line));
        }
    }
    while (getline(fi, line)) {
        if (line.empty()) continue;
        out.push_back(EBike::fromCSV(line));
    }
    fi.close();
    return out;
}

void EBike::print() const {
    cout << "EBike: " << brand << " " << model
         << " | color=" << color
         << " | cc=" << engineSize
         << " | year=" << year
         << " | plate=" << plateNumber << endl
         << "Listing: " << (listed ? "ON" : "OFF")
         << " | " << startDate << " -> " << endDate
         << " | " << dailyCP << " CP/day"
         << " | min renter rating: " << minRenterRating << endl
         << "Rating avg: " << getAverageRating()
         << " (" << ratingCount << " votes)" << endl;
}