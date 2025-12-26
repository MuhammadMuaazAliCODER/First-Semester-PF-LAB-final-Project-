#ifndef ADMIN_H
#define ADMIN_H

#include "filehandling.h"
#include "validation.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Admin signup
bool adminSignup() {
    Admin a;
    
    cout << "\n===================================================═\n";
    cout << "      ADMIN REGISTRATION\n";
    cout << "===================================================═\n";
    
    a.id = getValidatedString("Enter Unique Admin ID: ");
    
    if (adminExists(a.id)) {
        cout << "\n❌ Admin ID already exists!\n";
        return false;
    }
    
    a.name = getValidatedString("Enter Admin Name: ");
    a.password = getValidatedPassword();
    
    if (saveAdmin(a)) {
        cout << "\n✅ Admin registration successful!\n";
        return true;
    }
    
    cout << "\n❌ Registration failed!\n";
    return false;
}

// Admin login
Admin* adminLogin() {
    string id, password;
    
    cout << "\n===================================================═\n";
    cout << "         ADMIN LOGIN\n";
    cout << "===================================================═\n";
    
    id = getValidatedString("Enter Admin ID: ");
    password = getValidatedString("Enter Password: ");
    
    Admin* a = findAdmin(id, password);
    
    if (a) {
        cout << "\n✅ Admin login successful!\n";
        return a;
    }
    
    cout << "\n❌ Invalid admin credentials!\n";
    return nullptr;
}

// Add flight
void addFlight() {
    Flight f;
    
    cout << "\n===================================================═\n";
    cout << "         ADD NEW FLIGHT\n";
    cout << "===================================================═\n";
    
    f.flightId = getValidatedString("Enter Flight ID: ");
    
    if (flightExists(f.flightId)) {
        cout << "\n❌ Flight ID already exists!\n";
        return;
    }
    
    f.destination = getValidatedString("Enter Destination: ");
    f.departure = getValidatedString("Enter Departure City: ");
    f.date = getValidatedString("Enter Date (YYYY-MM-DD): ");
    f.time = getValidatedString("Enter Time (HH:MM): ");
    
    cout << "Enter Price: ";
    f.price = getValidatedInt(1000, 1000000);
    
    f.totalSeats = 16;
    f.availableSeats = 16;
    
    for (int i = 0; i < 16; i++) {
        f.seats[i] = false;
    }
    
    if (saveFlight(f)) {
        cout << "\n✅ Flight added successfully!\n";
    } else {
        cout << "\n❌ Failed to add flight!\n";
    }
}

// Update flight
void updateFlight() {
    displayAllFlights();
    
    string flightId = getValidatedString("\nEnter Flight ID to update: ");
    
    Flight flight = getFlightById(flightId);
    
    if (flight.flightId.empty()) {
        cout << "\n❌ Flight not found!\n";
        return;
    }
    
    cout << "\nUpdating Flight: " << flightId << "\n";
    cout << "Leave blank to keep current value\n\n";
    
    string input;
    
    cout << "Current Destination: " << flight.destination << "\n";
    cout << "New Destination (or press Enter): ";
    getline(cin, input);
    if (!input.empty()) flight.destination = input;
    
    cout << "Current Departure: " << flight.departure << "\n";
    cout << "New Departure (or press Enter): ";
    getline(cin, input);
    if (!input.empty()) flight.departure = input;
    
    cout << "Current Date: " << flight.date << "\n";
    cout << "New Date (or press Enter): ";
    getline(cin, input);
    if (!input.empty()) flight.date = input;
    
    cout << "Current Time: " << flight.time << "\n";
    cout << "New Time (or press Enter): ";
    getline(cin, input);
    if (!input.empty()) flight.time = input;
    
    cout << "Current Price: " << flight.price << "\n";
    cout << "New Price (or 0 to skip): ";
    double price;
    cin >> price;
    clearInputBuffer();
    if (price > 0) flight.price = price;
    
    if (updateFlightData(flight)) {
        cout << "\n✅ Flight updated successfully!\n";
    } else {
        cout << "\n❌ Update failed!\n";
    }
}

// Remove flight
void removeFlight() {
    displayAllFlights();
    
    string flightId = getValidatedString("\nEnter Flight ID to remove: ");
    
    if (!flightExists(flightId)) {
        cout << "\n❌ Flight not found!\n";
        return;
    }
    
    if (deleteFlight(flightId)) {
        cout << "\n✅ Flight removed successfully!\n";
    } else {
        cout << "\n❌ Removal failed!\n";
    }
}

// Add passenger (by admin)
void addPassenger() {
    Passenger p;
    
    cout << "\n===================================================═\n";
    cout << "        ADD NEW PASSENGER\n";
    cout << "===================================================═\n";
    
    p.id = getValidatedString("Enter Passenger ID: ");
    
    if (passengerExists(p.id)) {
        cout << "\n❌ Passenger ID already exists!\n";
        return;
    }
    
    p.name = getValidatedString("Enter Name: ");
    p.password = getValidatedPassword();
    
    while (true) {
        p.email = getValidatedString("Enter Email: ");
        if (isValidEmail(p.email)) break;
        cout << "Invalid email!\n";
    }
    
    while (true) {
        p.phone = getValidatedString("Enter Phone: ");
        if (isValidPhone(p.phone)) break;
        cout << "Invalid phone!\n";
    }
    
    p.bookedFlight = "NONE";
    p.seatNumber = 0;
    
    if (savePassenger(p)) {
        cout << "\n✅ Passenger added successfully!\n";
    } else {
        cout << "\n❌ Failed to add passenger!\n";
    }
}

// Update passenger
void updatePassenger() {
    displayAllPassengers();
    
    string passengerId = getValidatedString("\nEnter Passenger ID to update: ");
    
    Passenger passenger = getPassengerById(passengerId);
    
    if (passenger.id.empty()) {
        cout << "\n❌ Passenger not found!\n";
        return;
    }
    
    cout << "\nUpdating Passenger: " << passengerId << "\n";
    cout << "Leave blank to keep current value\n\n";
    
    string input;
    
    cout << "Current Name: " << passenger.name << "\n";
    cout << "New Name (or press Enter): ";
    getline(cin, input);
    if (!input.empty()) passenger.name = input;
    
    cout << "Current Email: " << passenger.email << "\n";
    cout << "New Email (or press Enter): ";
    getline(cin, input);
    if (!input.empty() && isValidEmail(input)) passenger.email = input;
    
    cout << "Current Phone: " << passenger.phone << "\n";
    cout << "New Phone (or press Enter): ";
    getline(cin, input);
    if (!input.empty() && isValidPhone(input)) passenger.phone = input;
    
    if (updatePassengerData(passenger)) {
        cout << "\n✅ Passenger updated successfully!\n";
    } else {
        cout << "\n❌ Update failed!\n";
    }
}

// Remove passenger
void removePassenger() {
    displayAllPassengers();
    
    string passengerId = getValidatedString("\nEnter Passenger ID to remove: ");
    
    if (!passengerExists(passengerId)) {
        cout << "\n❌ Passenger not found!\n";
        return;
    }
    
    if (deletePassenger(passengerId)) {
        cout << "\n✅ Passenger removed successfully!\n";
    } else {
        cout << "\n❌ Removal failed!\n";
    }
}

// Admin menu
void adminMenu(Admin& admin) {
    int choice;
    
    do {
        cout << "\n\n===================================================═\n";
        cout << "  Welcome Admin " << admin.name << " 👋\n";
        cout << "===================================================═\n";
        cout << "1. View All Flights\n";
        cout << "2. Add Flight\n";
        cout << "3. Update Flight\n";
        cout << "4. Remove Flight\n";
        cout << "5. View All Passengers\n";
        cout << "6. Add Passenger\n";
        cout << "7. Update Passenger\n";
        cout << "8. Remove Passenger\n";
        cout << "9. Logout\n";
        cout << "___________________________________\n";
        cout << "Enter choice: ";
        
        choice = getValidatedInt(1, 9);
        
        switch (choice) {
            case 1:
                displayAllFlights();
                break;
            case 2:
                addFlight();
                break;
            case 3:
                updateFlight();
                break;
            case 4:
                removeFlight();
                break;
            case 5:
                displayAllPassengers();
                break;
            case 6:
                addPassenger();
                break;
            case 7:
                updatePassenger();
                break;
            case 8:
                removePassenger();
                break;
            case 9:
                cout << "\n✈️ Admin logged out successfully!\n";
                break;
        }
    } while (choice != 9);
}

#endif