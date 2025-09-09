#ifndef RENTAL_H
#define RENTAL_H
#pragma once

#include <string>

class EBike; // forward declaration

enum class RentalStatus {
    Pending,
    Accepted,
    Rejected,
    Completed
};

class Rental {
private:
    std::string renterUsername;
    std::string ownerUsername;
    EBike* bike;
    RentalStatus status;
    std::string startDate;
    std::string endDate;
    int costCP;

public:
    Rental(const std::string& renterUsername,
           const std::string& ownerUsername,
           EBike* bike,
           const std::string& startDate,
           const std::string& endDate,
           int costCP);

    RentalStatus getStatus() const;
    void setStatus(RentalStatus newStatus);
    int getCost() const;
    std::string getRenterUsername() const;
    std::string getOwnerUsername() const;
    EBike* getBike() const;
    std::string getStartDate() const;
    std::string getEndDate() const;

    // Tính số ngày thuê dựa trên startDate/endDate
    int getDays() const;
};

#endif // RENTAL_H