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
        int choice;
        cin >> choice;
    }
}
int main(){
    
}