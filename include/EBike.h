#ifndef EBIKE_H
#define EBIKE_H

#include <string>
#include <vector>

using namespace std;

class EBike {
private:
    // Thông tin xe
    string brand;
    string model;
    string color;
    int    engineSize_cc;   // dung tích xi-lanh
    int    year;
    string plateNumber;

    // Thông tin niêm yết (listing)
    string startDate;       // dd/mm/yyyy
    string endDate;         // dd/mm/yyyy
    int    dailyCP;         // giá/ngày (Credit Points)
    int    minRenterRating; // điểm tối thiểu người thuê
    bool   listed;          // đang mở cho thuê?

    // Đánh giá
    int    ratingSum;       // tổng điểm đã nhận
    int    ratingCount;     // số lượt đánh giá

    //HÀM PHỤ TRỢ (cơ bản) 
    static void splitDate(const string& d, int& day, int& mon, int& year);
    static bool dateLE(const string& a, const string& b); // a <= b ?
    static int  daysInclusive(const string& a, const string& b); // số ngày (cả 2 đầu)

public:
    //Constructor 
    EBike(); // mặc định
    EBike(const string& brand,
          const string& model,
          const string& color,
          int engineSize_cc,
          int year,
          const string& plateNumber);

    // Getter cơ bản
    string getBrand()        const;
    string getModel()        const;
    string getColor()        const;
    int    getEngineSizeCC() const;
    int    getYear()         const;
    string getPlateNumber()  const;

    string getStartDate()       const;
    string getEndDate()         const;
    int    getDailyCP()         const;
    int    getMinRenterRating() const;
    bool   isListed()           const;
    double getAverageRating()   const; // trung bình đơn giản

    //Setter đơn giản
    void setColor(const string& c);
    void setEngineSizeCC(int cc);
    void setYear(int y);

    //Chức năng chính 
    // Tạo/ cập nhật thông tin niêm yết
    bool Listing(const string& start,
                 const string& end,
                 int dailyRate,
                 int minRate,
                 bool available);

    // Hủy niêm yết
    bool Unlist();

    // Kiểm tra còn thuê được trọn khoảng [s, e] không
    bool isAvailableFor(const string& s, const string& e) const;

    // Ước tính chi phí (CP) nếu thuê được
    int estimateCost(const string& s, const string& e) const;

    // Thêm một đánh giá (1..5)
    bool addRating(int score);

    //Lưu/đọc CSV (đơn giản) 
    string toCSV() const;                          // thành một dòng CSV
    static EBike fromCSV(const string& line);      // tạo đối tượng từ 1 dòng CSV
    static bool saveAll(const vector<EBike>& v, const string& path);
    static vector<EBike> loadAll(const string& path);

    // In gọn thông tin xe (cho debug/demo)
    void print() const;
};

#endif // EBIKE_H
