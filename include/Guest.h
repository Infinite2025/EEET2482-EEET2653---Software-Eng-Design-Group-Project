#ifndef GUEST_H
#define GUEST_H

#include <string>

class Guest {
public:
    Guest(); // Default Constructor
    void signup(); // Sign up for a new member account
    void viewListing(); // View available motorbikes for rent
    void viewLimitedBikes(); // View first 3 bikes from ebike.csv
    std::string getUsername() const;
private:
    // Private variables for sign up
    std::string username;
    std::string password;
    std::string fullName;
    std::string phoneNumber;
    std::string email;
    std::string idType;
    std::string idNumber;
    std::string licenseNumber;
    long licenseExpiry; // YYYYMMDD as integer for simple comparison
    int creditPoints;
    int rating;

    // Validating variables during sign up
    bool isUsernameAvailable(const std::string& username);
    bool isPasswordValid(const std::string& password);
    bool isEmailAvailable(const std::string& email);
    bool isPhoneNumberAvailable(const std::string& phoneNumber);
    bool isIDNumberAvailable(const std::string& idNumber);
    bool isLicenseNumberValid(const std::string& licenseNumber);
    void saveToFile(); // Save new member details to member.csv
};

#endif // GUEST_H