#include "Rental.h"

Rental::Rental(const std::string& renterUsername,
               const std::string& ownerUsername,
               EBike* bike,
               int days,
               const std::string& startDate,
               const std::string& endDate,
               int costCP)
    : renterUsername(renterUsername),
      ownerUsername(ownerUsername),
      bike(bike),
      days(days),
      status(RentalStatus::Pending),
      startDate(startDate),
      endDate(endDate),
      costCP(costCP) {}

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