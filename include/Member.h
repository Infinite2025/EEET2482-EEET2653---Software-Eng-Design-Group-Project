/*#ifndef MEMBER_H
#define MEMBER_H
#pragma once

#include <string>
#include <vector>
#include "EBike.h"
#include "CreditAccount.h"
#include "Rental.h"

class Member {
public:
    std::string username;
    std::string password;
    std::string email;
    std::string license;
    int creditPoints;
    std::string phoneNumber;
    std::string idNumber;
    int rating;

    Member() : creditPoints(20), rating(3) {} // Default constructor
    
    // Simplified constructor for existing code
    Member(const std::string& username, const std::string& password, const std::string& email,
           const std::string& license, int creditPoints, const std::string& phoneNumber,
           const std::string& idNumber, int rating)
        : username(username), password(password), email(email), license(license),
          creditPoints(creditPoints), phoneNumber(phoneNumber), idNumber(idNumber), rating(rating) {}

    void updatePersonalInfo(const std::string& newEmail, const std::string& newPhone);
    void requestRental(const std::string& bikePlate, const std::string& startDate, const std::string& endDate);
    void viewAllRentals();
    void rateRental(const std::string& bikePlate, int rating);
};

#endif // MEMBER_H */

#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <map>
#include <vector>

// Declaration of the Member class
class Member {
private:
    bool isMemberAuthenticated; // Flag to check if the member is currently authenticated
    std::string username; // Stores the username of the member
    std::string password; // Stores the password of the member
    std::string fullname; // Stores the full name of the member
    
    // A map to store member credentials, with the username as the key and a pair (password, fullname) as the value
    std::map<std::string, std::pair<std::string, std::string>> memberCredentials;

    // Private method to validate the username and password during login
    bool validateCredentials(const std::string& username, const std::string& password) const;
     

public:
    Member(); // Default constructor

    // Authentication
    bool login(const std::string& uname, const std::string& pwd);
    void logout();

    // Data
    void loadMemberData(); // Loads member data from a data source

    // Menus
    void showMemberMenu() const;
    void memberMenuLoop();

    // Member operations
    void registerMotorbike();
    void searchAndRequestRental();
    void topUpCredit();
    void viewAllRentals() const;
    void approveRentalRequests();
    void returnRentedMotorbike();
    void rateRental();

    // New requested features (carpool terminology preserved)
    void searchActiveCarpool(); // Allows members to search for active carpool listings
    void viewProfile() const; // Displays the member's profile information
    void editProfile(); // Allows the member to edit their profile information
    void bookEBike(); // Enables a member to book an EBike (was bookCarpool)
    void listEBike(); // Allows a member to list a new EBike (was listCarpool)
    void unlistEBike(); // Provides functionality for a member to unlist an existing EBike (was unlistCarpool)
    void manageRequests(); // Manages incoming requests for carpools listed by the member
    void confirmEBikeRides(); // Confirms the rides for a booked EBike (was confirmCarpoolRides)
    void rating(); // Manages the rating system for carpools
    void purchaseCredits(); // Enables a member to purchase credits for booking carpools
    void manageBookings(); // Manages all bookings made by the member
    void transferCredits(const std::string& fromUser, const std::string& toUser, int amount); // Transfers credits from one user to another

    std::string getUserName() const; // Returns username
    int getCredits() const; // Returns the current credit balance of the member

    // Basic info
    std::string username;
    std::string password;
    std::string fullName;
    std::string phone;
    std::string email;
    std::string licenseNumber;
    long licenseExpiry; // YYYYMMDD
    int creditPoints;
    int rating;
    std::string ownedMotorbikePlate; // plate if member has registered a bike
    std::string rentingMotorbikePlate; // plate if currently renting
    bool isAuthenticated;
};

#endif // MEMBER_H