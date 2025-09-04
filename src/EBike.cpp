#include "EBike.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

//Hàm phụ trợ

void EBike::splitDate(const string& d, int& day, int& mon, int& year) {
    // d: "dd/mm/yyyy" -> tách bằng substr
    // Giả định chuỗi luôn đúng định dạng (bạn có thể tự bổ sung kiểm tra nếu muốn)
    day  = stoi(d.substr(0, 2));
    mon  = stoi(d.substr(3, 2));
    year = stoi(d.substr(6, 4));
}

bool EBike::dateLE(const string& a, const string& b) {
    int da, ma, ya; splitDate(a, da, ma, ya);
    int db, mb, yb; splitDate(b, db, mb, yb);
    if (ya != yb) return ya < yb;
    if (ma != mb) return ma < mb;
    return da <= db;
}

int EBike::daysInclusive(const string& a, const string& b) {
    // Cách tính rất đơn giản: chỉ đúng khi các ngày trong cùng tháng/năm,
    // hoặc bạn dùng luật xấp xỉ (không xử lý số ngày/tháng chuẩn).
    // Với bài cơ bản, ta xử lý chuẩn trong trường hợp cùng tháng & năm,
    // còn khác tháng/năm sẽ tính xấp xỉ 30 ngày/tháng.
    int da, ma, ya; splitDate(a, da, ma, ya);
    int db, mb, yb; splitDate(b, db, mb, yb);

    int daysA = ya * 360 + ma * 30 + da; // 1 năm = 12*30 = 360 (xấp xỉ)
    int daysB = yb * 360 + mb * 30 + db;
    if (daysB < daysA) return -1;
    return (daysB - daysA) + 1;
}

//Cosntructor

EBike::EBike()
: brand(""), model(""), color(""), engineSize_cc(0), year(0), plateNumber(""),
  startDate(""), endDate(""), dailyCP(0), minRenterRating(0), listed(false),
  ratingSum(0), ratingCount(0) {}

EBike::EBike(const string& brand,
             const string& model,
             const string& color,
             int engineSize_cc,
             int year,
             const string& plateNumber)
: brand(brand), model(model), color(color),
  engineSize_cc(engineSize_cc), year(year), plateNumber(plateNumber),
  startDate(""), endDate(""), dailyCP(0), minRenterRating(0), listed(false),
  ratingSum(0), ratingCount(0) {}

//Getters

string EBike::getBrand()        const { return brand; }
string EBike::getModel()        const { return model; }
string EBike::getColor()        const { return color; }
int    EBike::getEngineSizeCC() const { return engineSize_cc; }
int    EBike::getYear()         const { return year; }
string EBike::getPlateNumber()  const { return plateNumber; }

string EBike::getStartDate()       const { return startDate; }
string EBike::getEndDate()         const { return endDate; }
int    EBike::getDailyCP()         const { return dailyCP; }
int    EBike::getMinRenterRating() const { return minRenterRating; }
bool   EBike::isListed()           const { return listed; }
double EBike::getAverageRating()   const {
    if (ratingCount == 0) return 0.0;
    return (double)ratingSum / (double)ratingCount;
}

//Setters

void EBike::setColor(const string& c) { color = c; }
void EBike::setEngineSizeCC(int cc)   { if (cc >= 0) engineSize_cc = cc; }
void EBike::setYear(int y)            { if (y >= 2000 && y <= 2100) year = y; }

//Chức năng chính

bool EBike::Listing(const string& start,
                    const string& end,
                    int dailyRate,
                    int minRate,
                    bool available) {
    // Kiểm tra đơn giản
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
    // Yêu cầu: khoảng [s,e] phải nằm trong khoảng đã niêm yết [startDate,endDate]
    if (!dateLE(startDate, s)) return false; // startDate <= s ?
    if (!dateLE(e, endDate))   return false; // e <= endDate ?
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

//CSV (đơn giản, không escape)

string EBike::toCSV() const {
    // Thứ tự cột:
    // brand,model,color,engineSize_cc,year,plateNumber,
    // startDate,endDate,dailyCP,minRenterRating,listed,ratingSum,ratingCount
    ostringstream oss;
    oss << brand << ","
        << model << ","
        << color << ","
        << engineSize_cc << ","
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
    // Kỳ vọng đủ 13 cột
    if (c.size() < 13) {
        // Trả về đối tượng mặc định nếu dòng hỏng (cách đơn giản cho beginner)
        return EBike();
    }

    EBike b;
    b.brand          = c[0];
    b.model          = c[1];
    b.color          = c[2];
    b.engineSize_cc  = stoi(c[3]);
    b.year           = stoi(c[4]);
    b.plateNumber    = c[5];
    b.startDate      = c[6];
    b.endDate        = c[7];
    b.dailyCP        = stoi(c[8]);
    b.minRenterRating= stoi(c[9]);
    b.listed         = (stoi(c[10]) != 0);
    b.ratingSum      = stoi(c[11]);
    b.ratingCount    = stoi(c[12]);
    return b;
}

bool EBike::saveAll(const vector<EBike>& v, const string& path) {
    ofstream fo(path);
    if (!fo.is_open()) return false;
    // Header (chỉ để người đọc file dễ hiểu)
    fo << "brand,model,color,engineSize_cc,year,plateNumber,startDate,endDate,"
          "dailyCP,minRenterRating,listed,ratingSum,ratingCount\n";
    for (size_t i = 0; i < v.size(); ++i) {
        fo << v[i].toCSV() << "\n";
    }
    fo.close();
    return true;
}

vector<EBike> EBike::loadAll(const string& path) {
    vector<EBike> out;
    ifstream fi(path);
    if (!fi.is_open()) return out;

    string line;
    // Bỏ header nếu có
    if (getline(fi, line)) {
        if (line.rfind("brand,model,", 0) != 0) {
            // Không phải header -> coi là dữ liệu
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

// In nhanh ra màn hình (demo)
void EBike::print() const {
    cout << "EBike: " << brand << " " << model
         << " | color=" << color
         << " | cc=" << engineSize_cc
         << " | year=" << year
         << " | plate=" << plateNumber << "\n"
         << "Listing: " << (listed ? "ON" : "OFF")
         << " | " << startDate << " -> " << endDate
         << " | " << dailyCP << " CP/day"
         << " | min renter rating: " << minRenterRating << "\n"
         << "Rating avg: " << getAverageRating()
         << " (" << ratingCount << " votes)\n";
}
