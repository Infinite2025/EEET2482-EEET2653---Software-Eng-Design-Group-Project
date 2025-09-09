#include<iostream>
#include<string>
#include<iomanip>

#include "Guest.h"
#include "Member.h"
#include "Admin.h"

using namespace std;
 
// Clears the console screen by printing multiple new lines
void clearScreen(){
    for(int i=0; i<70; i++){
        cout << endl;
    }
}

// Shows the welcome menu to the user
void displayWelcomeMenu(){
    clearScreen();
    cout << "=================================" << endl;
    cout << " Welcome to the E-motorbike Rental App " << endl;
    cout << "=================================" << endl;
    cout << "Please select your user type:" << endl;
    cout << "1. Guest" << endl;
    cout << "2. Member" << endl;
    cout << "3. Admin" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice (1-4): ";
}

// Gets a valid integer choice from the user within the specified range
int getChoice(int min, int max){
    int n;
    while(true){
        cin >> n;
        if(cin.fail() || n < min || n > max){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between " << min << " and " << max << ": ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return n;
        }
    }
}

// Pauses the program until the user presses Enter
void pause(){
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Activate Guest mode
void guestMode(){
    Guest guest;
    bool exitGuestMenu = false;
    while(!exitGuestMenu){
        clearScreen();
        cout << "==============================================="   << endl;
        cout << " Guest Menu " << endl; 
        cout << "==============================================="   << endl;
        cout << "1. Sign Up for a New Member Account" << endl;
        cout << "2. View Available Motorbikes for Rent" << endl;
        cout << "3. Return to Main Menu" << endl;
        cout << "Enter your choice (1-3): ";
        int guestChoice = getChoice(1, 3);
        switch(guestChoice){
            case 1:
                cout << "=== Guest Sign Up ===" << endl;
                guest.signup();
                break;
            case 2:
                cout << "=== View Motorbike Listings ===" << endl;
                guest.viewListing();
                break;
            case 3:
                exitGuestMenu = true;
                break;
        }
        pause();
        if(!exitGuestMenu){
            pause();
            cin.get(); // Wait for user to press Enter

        }

    }
}
void memberMode(){
    // Placeholder for member mode functionality
    // Member member;
    // Implement member functionalities here
}
void adminMode(){
    void adminMode() {
    Admin admin;
    bool continueSession = true;
    bool isLoggedIn = false;

    while (!isLoggedIn) {
        clearScreen();
        cout << "========== Admin Login ==========" << endl;
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        
        if (admin.login(username, password)) {
            showLoadingAnimation("Logging in", 3);
            clearScreen();
            cout << "Welcome, Admin!" << endl;
            cout << "\nPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            isLoggedIn = true;
        } else {
            cout << "Login failed. Press Enter to try again...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }

    while (continueSession && isLoggedIn) {
        clearScreen();
        cout << "========== Admin Menu ==========" << endl;
        cout << "1. View All Users" << endl;
        cout << "2. View All E-Bikes" << endl;
        cout << "3. View All Rentals" << endl;
        cout << "4. Logout" << endl;
        cout << "Enter your choice (1-4): ";

        int adminChoice = getChoice(1, 4);

        switch(adminChoice) {
            case 1:
                clearScreen();
                cout << "===== All User Information =====" << endl;
                admin.viewAllUsers();
                pause();
                break;
                
            case 2:
                clearScreen();
                cout << "===== All E-Bike Information =====" << endl;
                admin.viewAllBikes();
                
                // Sub-menu for bike operations
                cout << "\n===== E-Bike Operations =====" << endl;
                cout << "1. Add New E-Bike" << endl;
                cout << "2. Remove E-Bike" << endl;
                cout << "3. Return to Admin Menu" << endl;
                cout << "Enter your choice (1-3): ";
                
                int bikeChoice = getChoice(1, 3);
                switch(bikeChoice) {
                    case 1: {
                        string brand, model, color, plate, startDate, endDate;
                        int engineSize, year, dailyCP, minRenterRating;
                        bool listed;
                        
                        cout << "Brand: "; cin >> brand;
                        cout << "Model: "; cin >> model;
                        cout << "Color: "; cin >> color;
                        cout << "Engine Size (cc): "; cin >> engineSize;
                        cout << "Year: "; cin >> year;
                        cout << "Plate Number: "; cin >> plate;
                        cout << "Start Date (YYYY-MM-DD): "; cin >> startDate;
                        cout << "End Date (YYYY-MM-DD): "; cin >> endDate;
                        cout << "Daily Cost (CP): "; cin >> dailyCP;
                        cout << "Minimum Renter Rating: "; cin >> minRenterRating;
                        cout << "Listed (1 for yes, 0 for no): "; cin >> listed;
                        
                        admin.addBike(brand, model, color, engineSize, year, plate, 
                                     startDate, endDate, dailyCP, minRenterRating, listed);
                        pause();
                        break;
                    }
                    case 2: {
                        string plate;
                        cout << "Enter plate number to remove: "; cin >> plate;
                        admin.removeBike(plate);
                        pause();
                        break;
                    }
                    case 3:
                        // Just return to admin menu
                        break;
                }
                break;
                
            case 3:
                clearScreen();
                cout << "===== All Rental Information =====" << endl;
                admin.viewAllRentals();
                pause();
                break;
                
            case 4:
                continueSession = false;
                cout << "Logging out..." << endl;
                this_thread::sleep_for(chrono::seconds(2));
                break;
        }
    }
}
}

int main(){
    displayWelcomeMenu();
    int choice = getChoice(1, 4);
    switch(choice){
        case 1:
            guestMode();
            break;
        case 2:
            // memberMode(); // Implement memberMode function
            cout << "Member mode is under construction." << endl;
            pause();
            break;
        case 3:
            // adminMode(); // Implement adminMode function
            cout << "Admin mode is under construction." << endl;
            pause();
            break;
        case 4:
            cout << "Exiting the application. Goodbye!" << endl;
            break;
    }
}