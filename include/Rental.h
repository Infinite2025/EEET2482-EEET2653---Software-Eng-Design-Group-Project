#pragma once
#include <string>
#include "EBike.h"

enum class RentalStatus {
    Pending,
    Accepted,
    Rejected,
    Completed
};

class Rental{
private:
    std::string renterUsername;
    std::string ownerUsername;
    EBike* bike;
    int days;
    RentalStatus status;
    std::string startDate;
    std::string endDate;
    int costCP;

public:
    Rental(const std::string& renterUsername,
           const std::string& ownerUsername,
           EBike* bike,
           int days,
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
};