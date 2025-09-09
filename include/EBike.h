#ifndef EBIKE_H
#define EBIKE_H

#include <string>
#include <vector>

class EBike {
public:
    // Thông tin xe
    std::string brand;
    std::string model;
    std::string color;
    int engineSize; // dung tích xi-lanh (changed from engineSize_cc to match Main.cpp)
    int year;
    std::string plateNumber;

    // Thông tin niêm yết (listing) (định dạng ISO: YYYY-MM-DD)
    std::string startDate; // YYYY-MM-DD
    std::string endDate;   // YYYY-MM-DD
    int dailyCP; // giá/ngày (Credit Points)
    int minRenterRating; // điểm tối thiểu người thuê
    bool listed; // đang mở cho thuê?

    // Đánh giá
    int ratingSum; // tổng điểm đã nhận
    int ratingCount; // số lượt đánh giá

    // Constructor
    EBike();
    EBike(const std::string& brand, const std::string& model, const std::string& color,
          int engineSize, int year, const std::string& plateNumber);

    // HÀM PHỤ TRỢ (cơ bản)
    static void splitDate(const std::string& d, int& year, int& mon, int& day);
    static bool dateLE(const std::string& a, const std::string& b); // a <= b ?
    static int daysInclusive(const std::string& a, const std::string& b); // số ngày (cả 2 đầu)

    // Chức năng chính
    bool Listing(const std::string& start, const std::string& end,
                 int dailyRate, int minRate, bool available);
    bool Unlist();
    bool isAvailableFor(const std::string& s, const std::string& e) const;
    int estimateCost(const std::string& s, const std::string& e) const;
    bool addRating(int score);
    double getAverageRating() const;
    
    // CSV operations
    std::string toCSV() const;
    static EBike fromCSV(const std::string& line);
    static bool saveAll(const std::vector<EBike>& v, const std::string& path);
    static std::vector<EBike> loadAll(const std::string& path);
    
    void print() const;
};

#endif // EBIKE_H