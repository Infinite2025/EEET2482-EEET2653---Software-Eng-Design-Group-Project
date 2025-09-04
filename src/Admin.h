#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <vector>

class Admin {
public:
    Admin(const std::string& username, const std::string& password)
        : username(username), password(password) {}

    std::string getUsername() const { return username; }
    bool login(const std::string& username, const std::string& password); //login as admin

    void addBike(const std::string& brand, const std::string& model, int year, int cc, const std::string& licensePlate); // Add a new bike
    void removeBike(const std::string& licensePlate); // Remove a bike by license plate
    void viewAllRentals() const; // View all rental transactions
    void viewAllUsers() const; // View all registered users 
    void viewAllBikes() const; // View all bikes in the system
    void loadAdmindata(); // Load admin data from csv file
private:
    std::string username; // Stored admin's username
    std::string password; // Stored admin's password
    bool isAuthenticated; // Track authentication status
    bool validateAdminCredentials(const std::string& username, const std::string& password) const; // Simulated validation
};

#endif