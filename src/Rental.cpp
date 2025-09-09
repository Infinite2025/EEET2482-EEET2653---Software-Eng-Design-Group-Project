#include "Rental.h"
#include "EBike.h"
#include <iostream>
#include <sstream>

Rental::Rental(const std::string& renterUsername,
               const std::string& ownerUsername,
               EBike* bike,
               const std::string& startDate,
               const std::string& endDate,
               int costCP)
    : renterUsername(renterUsername), ownerUsername(ownerUsername), bike(bike),
      status(RentalStatus::Pending), startDate(startDate), endDate(endDate), costCP(costCP) {}

RentalStatus Rental::getStatus() const {
    return status;
}

void Rental::setStatus(RentalStatus newStatus) {
    status = newStatus;
}

int Rental::getCost() const {
    return costCP;
}

std::string Rental::getRenterUsername() const {
    return renterUsername;
}

std::string Rental::getOwnerUsername() const {
    return ownerUsername;
}

EBike* Rental::getBike() const {
    return bike;
}

std::string Rental::getStartDate() const {
    return startDate;
}

std::string Rental::getEndDate() const {
    return endDate;
}

int Rental::getDays() const {
    // Simple implementation - in a real system you'd use proper date parsing
    return EBike::daysInclusive(startDate, endDate);
}