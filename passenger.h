#ifndef PASSENGER_H
#define PASSENGER_H

#include "filehandling.h"
#include "validation.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Display seat map for a flight
void displaySeatMap(const Flight& flight) {
    cout << "\n=========================================================\n";
    cout << "✈️  PLANE SEAT MAP - " << flight.flightId << "\n";
    cout << "=========================================================\n";
    cout << "Available = Number | Booked = XX\n\n";

    for (int i = 0; i < 4; i++) {
        cout << "Row " << i + 1 << "  ";
        for (int j = 0; j < 4; j++) {
            int seatNum = i * 4 + j + 1;
            if (j == 2) cout << "   ";
            
            if (flight.seats[seatNum - 1])
                cout << setw(3) << "XX";
            else
                cout << setw(3) << seatNum;
        }
        cout << endl;
    }
    cout << "\n=========================================================\n";
}

// Passenger signup
bool passengerSignup() {
    Passenger p;
    
    cout << "\n===================================================═\n";
    cout << "     PASSENGER REGISTRATION\n";
    cout << "===================================================═\n";
    
    p.id = getValidatedString("Enter Unique ID (e.g., P001): ");
    
    if (passengerExists(p.id)) {
        cout << "\n❌ Error: ID already exists!\n";
        return false;
    }
    
    p.name = getValidatedString("Enter Full Name: ");
    p.password = getValidatedPassword();
    
    while (true) {
        p.email = getValidatedString("Enter Email: ");
        if (isValidEmail(p.email)) break;
        cout << "Invalid email format!\n";
    }
    
    while (true) {
        p.phone = getValidatedString("Enter Phone (10-15 digits): ");
        if (isValidPhone(p.phone)) break;
        cout << "Invalid phone number!\n";
    }
    
    p.bookedFlight = "NONE";
    p.seatNumber = 0;
    
    if (savePassenger(p)) {
        cout << "\n✅ Registration successful! You can now login.\n";
        return true;
    }
    
    cout << "\n❌ Registration failed!\n";
    return false;
}

// Passenger login
Passenger* passengerLogin() {
    string id, password;
    
    cout << "\n===================================================═\n";
    cout << "       PASSENGER LOGIN\n";
    cout << "===================================================═\n";
    
    id = getValidatedString("Enter your ID: ");
    password = getValidatedString("Enter your password: ");
    
    Passenger* p = findPassenger(id, password);
    
    if (p) {
        cout << "\n✅ Login successful!\n";
        return p;
    }
    
    cout << "\n❌ Invalid credentials!\n";
    return nullptr;
}

// Book a flight
void bookFlight(Passenger& passenger) {
    if (passenger.bookedFlight != "NONE") {
        cout << "\n❌ You already have a booking! Cancel it first.\n";
        return;
    }
    
    displayAllFlights();
    
    string flightId = getValidatedString("\nEnter Flight ID to book: ");
    
    Flight flight = getFlightById(flightId);
    
    if (flight.flightId.empty()) {
        cout << "\n❌ Flight not found!\n";
        return;
    }
    
    if (flight.availableSeats == 0) {
        cout << "\n❌ No seats available on this flight!\n";
        return;
    }
    
    displaySeatMap(flight);
    
    int seatNum = getValidatedSeat();
    
    if (flight.seats[seatNum - 1]) {
        cout << "\n❌ Seat already booked! Choose another.\n";
        return;
    }
    
    // Book the seat
    flight.seats[seatNum - 1] = true;
    flight.availableSeats--;
    
    if (updateFlightData(flight)) {
        passenger.bookedFlight = flightId;
        passenger.seatNumber = seatNum;
        
        if (updatePassengerData(passenger)) {
            cout << "\n✅ Booking successful!\n";
            cout << "Flight: " << flightId << " | Seat: " << seatNum << "\n";
        } else {
            cout << "\n❌ Booking failed to save!\n";
        }
    } else {
        cout << "\n❌ Booking failed!\n";
    }
}

// Cancel reservation
void cancelReservation(Passenger& passenger) {
    if (passenger.bookedFlight == "NONE") {
        cout << "\n❌ No booking found!\n";
        return;
    }
    
    Flight flight = getFlightById(passenger.bookedFlight);
    
    if (!flight.flightId.empty()) {
        flight.seats[passenger.seatNumber - 1] = false;
        flight.availableSeats++;
        updateFlightData(flight);
    }
    
    passenger.bookedFlight = "NONE";
    passenger.seatNumber = 0;
    
    if (updatePassengerData(passenger)) {
        cout << "\n✅ Reservation cancelled successfully!\n";
    } else {
        cout << "\n❌ Failed to cancel reservation!\n";
    }
}

// View booking report
void viewBookingReport(const Passenger& passenger) {
    cout << "\n===================================================═\n";
    cout << "       BOOKING REPORT\n";
    cout << "===================================================═\n";
    cout << "Name: " << passenger.name << "\n";
    cout << "ID: " << passenger.id << "\n";
    cout << "Email: " << passenger.email << "\n";
    cout << "Phone: " << passenger.phone << "\n";
    
    if (passenger.bookedFlight == "NONE") {
        cout << "Status: No active booking\n";
    } else {
        cout << "Booked Flight: " << passenger.bookedFlight << "\n";
        cout << "Seat Number: " << passenger.seatNumber << "\n";
        
        Flight flight = getFlightById(passenger.bookedFlight);
        
        if (!flight.flightId.empty()) {
            cout << "Destination: " << flight.destination << "\n";
            cout << "Departure: " << flight.departure << "\n";
            cout << "Date: " << flight.date << "\n";
            cout << "Time: " << flight.time << "\n";
            cout << "Price: Rs." << fixed << setprecision(0) << flight.price << "\n";
        }
    }
    cout << "===================================================═\n";
}

// Passenger menu
void passengerMenu(Passenger& passenger) {
    int choice;
    
    do {
        cout << "\n\n===================================================═\n";
        cout << "  Welcome " << passenger.name << " 👋\n";
        cout << "===================================================═\n";
        cout << "1. Book a Flight\n";
        cout << "2. Cancel Reservation\n";
        cout << "3. View Booking Report\n";
        cout << "4. Logout\n";
        cout << "___________________________________\n";
        cout << "Enter choice: ";
        
        choice = getValidatedInt(1, 4);
        
        switch (choice) {
            case 1:
                bookFlight(passenger);
                break;
            case 2:
                cancelReservation(passenger);
                break;
            case 3:
                viewBookingReport(passenger);
                break;
            case 4:
                cout << "\n✈️ Thank you for using our system!\n";
                break;
        }
        
        // Reload passenger data after operations
        if (choice != 4) {
            Passenger updated = getPassengerById(passenger.id);
            if (!updated.id.empty()) {
                passenger = updated;
            }
        }
        
    } while (choice != 4);
}

#endif