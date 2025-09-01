#ifndef GUEST_H
#define GUEST_H

#include<string>

class Guest {
public:
    Guest();  //Default Constuctor
    void signup();  // Sign up for a new member account
    void viewListing();  // View available motorbikes for rent
private:
    // Private variables for sign up
    std::string username;
    std::string password;
    std::string fullName;
    std::string phoneNumber;
    std::string email;
    std::string idType;
    std::string idNumber;
    //std::string License;
    std::string licenseNumber;
    std::string licenseExpiryDate;
    int creditPoints;
    int rating;



    // Validating variables during sign up
    bool isUsernameAvailable(const std::string& username);
    bool isPasswordValid(const std::string& password);
    bool isEmailAvailable(const std::string& email);
    bool isPhoneNumberAvailable(const std::string& phoneNumber);
    bool isIDNumberAvailable(const std::string& idNumber);
    bool hasValidLicense(const std::string& licenseNumber);
};


#endif // GUEST_H