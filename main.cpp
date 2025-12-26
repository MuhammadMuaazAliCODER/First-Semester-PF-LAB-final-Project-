#include <iostream>
#include "validation.h"
#include "filehandling.h"
#include "passenger.h"
#include "admin.h"

using namespace std;

void displayMainMenu() {
    cout << "\n=========================================================\n";
    cout << "    AIRLINE MANAGEMENT SYSTEM\n";
    cout << "=========================================================\n";
    cout << "1. Admin Panel\n";
    cout << "2. Passenger Panel\n";
    cout << "3. Exit\n";
    cout << "______________________________________\n";
    cout << "Enter your choice: ";
}

void adminPanel() {
    int choice;
    
    cout << "\n===================================================═\n";
    cout << "        ADMIN PANEL\n";
    cout << "===================================================═\n";
    cout << "1. Login\n";
    cout << "2. Signup\n";
    cout << "3. Back to Main Menu\n";
    cout << "___________________________________\n";
    cout << "Enter choice: ";
    
    choice = getValidatedInt(1, 3);
    
    if (choice == 1) {
        Admin* admin = adminLogin();
        if (admin) {
            adminMenu(*admin);
        }
    } else if (choice == 2) {
        adminSignup();
    }
}

void passengerPanel() {
    int choice;
    
    cout << "\n===================================================═\n";
    cout << "      PASSENGER PANEL\n";
    cout << "===================================================═\n";
    cout << "1. Login\n";
    cout << "2. Signup\n";
    cout << "3. Back to Main Menu\n";
    cout << "___________________________________\n";
    cout << "Enter choice: ";
    
    choice = getValidatedInt(1, 3);
    
    if (choice == 1) {
        Passenger* passenger = passengerLogin();
        if (passenger) {
            passengerMenu(*passenger);
        }
    } else if (choice == 2) {
        passengerSignup();
    }
}

int main() {
    // Initialize sample data
    initializeData();
    
    int choice;
    
    do {
        displayMainMenu();
        choice = getValidatedInt(1, 3);
        
        switch (choice) {
            case 1:
                adminPanel();
                break;
            case 2:
                passengerPanel();
                break;
            case 3:
                cout << "\n✈️ Thank you for using Airline Management System!\n";
                cout << "=========================================================\n\n";
                break;
        }
    } while (choice != 3);
    
    return 0;
}