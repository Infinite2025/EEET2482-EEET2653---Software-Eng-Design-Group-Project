#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <vector>

class Admin {
public:
    Admin() : username(""), password(""), isAuthenticated(false) {} // Default constructor
    Admin(const std::string& username, const std::string& password)
        : username(username), password(password), isAuthenticated(false) {}

    std::string username;
    std::string password;
    std::string email;
    bool isAuthenticated;

    std::string getUsername() const { return username; }

    // login as admin: read from admins.csv and compare
    bool login(const std::string& inputUsername, const std::string& inputPassword);

    // Management functions (signatures preserved)
    void addBike(const std::string& brand, const std::string& model, const std::string& color, 
                 int engineSize, int year, const std::string& plateNumber, 
                 const std::string& startDate, const std::string& endDate,
                 int dailyCP, int minRenterRating, bool listed);  // Add a new bike
    void removeBike(const std::string& licensePlate); // Remove a bike by license plate
    void viewAllRentals() const; // View all rental transactions
    void viewAllUsers() const; // View all registered users
    void viewAllBikes() const; // View all bikes in the system

    // Load admin data (ensure CSV and header exist)
    void loadAdmindata(); // Load or initialize admin data from csv file

private:
    // Simulated validation (will read CSV)
    bool validateAdminCredentials(const std::string& username, const std::string& password);
};

#endif // ADMIN_H