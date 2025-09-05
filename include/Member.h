#pragma once
#include <string>
#include <vector>
#include "EBike.h"
#include "CreditAccount.h"
#include "Rental.h"

class Member {
private:
    std::string username;
    std::string password;
    std::string fullName;
    std::string email;
    std::string phone;
    std::string idType; // CCCD or Passport
    std::string idNumber;
    std::string licenseNumber;
    std::string licenseExpiry;
    int rating; // default 3
    EBike* registeredBike; // Each member can register one EBike
    CreditAccount account;
    std::vector<Rental> rentalHistory;
    bool isLoggedIn;

public:
    Member(const std::string& username,
           const std::string& password,
           const std::string& fullName,
           const std::string& email,
           const std::string& phone,
           const std::string& idType,
           const std::string& idNumber,
           const std::string& licenseNumber = "",
           const std::string& licenseExpiry = "");

    bool login(const std::string& inputPassword);
    void logout();
    void updateProfile(const std::string& newFullName,
                       const std::string& newEmail,
                       const std::string& newPhone,
                       const std::string& newIdType,
                       const std::string& newIdNumber,
                       const std::string& newLicenseNumber,
                       const std::string& newLicenseExpiry);
    void changePassword(const std::string& oldPassword, const std::string& newPassword);
    void viewProfile() const;
    void loadCredit(int usd, const std::string& inputPassword);
    bool registerBike(const EBike& bike);
    void viewRentalHistory() const;
    bool requestRental(EBike& bike, const std::string& startDate, const std::string& endDate);
    void rateBike(EBike& bike, int stars, const std::string& comment);
    void rateRenter(Member& renter, int stars, const std::string& comment);
    int getRating() const;
    CreditAccount& getAccount();
    EBike* getBike();
    bool hasActiveRental() const;
    bool hasValidLicense(int bikeCC) const;
    bool isBikeRegistered() const;
    // Add more functions
};