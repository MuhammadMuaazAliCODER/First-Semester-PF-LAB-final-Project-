#ifndef FILEHANDLING_H
#define FILEHANDLING_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Struct definitions
struct Passenger {
    string id;
    string name;
    string password;
    string email;
    string phone;
    string bookedFlight;
    int seatNumber;
};

struct Flight {
    string flightId;
    string destination;
    string departure;
    string date;
    string time;
    int totalSeats;
    int availableSeats;
    double price;
    bool seats[16]; // false = available, true = booked
};

struct Admin {
    string id;
    string name;
    string password;
};

// File paths
const string PASSENGER_FILE = "passengers.txt";
const string FLIGHT_FILE = "flights.txt";
const string ADMIN_FILE = "admins.txt";
const string TEMP_FILE = "temp.txt";

// ========== PASSENGER FILE OPERATIONS ==========

bool savePassenger(const Passenger& p) {
    ofstream file(PASSENGER_FILE, ios::app);
    if (!file) {
        cout << "Error: Unable to open passenger file!\n";
        return false;
    }
    file << p.id << "|" << p.name << "|" << p.password << "|" 
         << p.email << "|" << p.phone << "|" << p.bookedFlight << "|" 
         << p.seatNumber << "\n";
    file.close();
    return true;
}

Passenger* findPassenger(const string& id, const string& password) {
    static Passenger found;
    ifstream file(PASSENGER_FILE);
    if (!file) return nullptr;
    
    string line;
    while (getline(file, line)) {
        Passenger p;
        stringstream ss(line);
        getline(ss, p.id, '|');
        getline(ss, p.name, '|');
        getline(ss, p.password, '|');
        getline(ss, p.email, '|');
        getline(ss, p.phone, '|');
        getline(ss, p.bookedFlight, '|');
        ss >> p.seatNumber;
        
        if (p.id == id && p.password == password) {
            found = p;
            file.close();
            return &found;
        }
    }
    file.close();
    return nullptr;
}

bool passengerExists(const string& id) {
    ifstream file(PASSENGER_FILE);
    if (!file) return false;
    
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string passengerID;
        getline(ss, passengerID, '|');
        
        if (passengerID == id) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

bool updatePassengerData(const Passenger& updatedPassenger) {
    ifstream file(PASSENGER_FILE);
    ofstream tempFile(TEMP_FILE);
    
    if (!file || !tempFile) return false;
    
    string line;
    bool found = false;
    
    while (getline(file, line)) {
        Passenger p;
        stringstream ss(line);
        getline(ss, p.id, '|');
        getline(ss, p.name, '|');
        getline(ss, p.password, '|');
        getline(ss, p.email, '|');
        getline(ss, p.phone, '|');
        getline(ss, p.bookedFlight, '|');
        ss >> p.seatNumber;
        
        if (p.id == updatedPassenger.id) {
            tempFile << updatedPassenger.id << "|" << updatedPassenger.name << "|" 
                    << updatedPassenger.password << "|" << updatedPassenger.email << "|" 
                    << updatedPassenger.phone << "|" << updatedPassenger.bookedFlight << "|" 
                    << updatedPassenger.seatNumber << "\n";
            found = true;
        } else {
            tempFile << line << "\n";
        }
    }
    
    file.close();
    tempFile.close();
    
    remove(PASSENGER_FILE.c_str());
    rename(TEMP_FILE.c_str(), PASSENGER_FILE.c_str());
    
    return found;
}

bool deletePassenger(const string& id) {
    ifstream file(PASSENGER_FILE);
    ofstream tempFile(TEMP_FILE);
    
    if (!file || !tempFile) return false;
    
    string line;
    bool found = false;
    
    while (getline(file, line)) {
        stringstream ss(line);
        string passengerID;
        getline(ss, passengerID, '|');
        
        if (passengerID == id) {
            found = true;
            continue; // Skip this line (delete)
        }
        tempFile << line << "\n";
    }
    
    file.close();
    tempFile.close();
    
    remove(PASSENGER_FILE.c_str());
    rename(TEMP_FILE.c_str(), PASSENGER_FILE.c_str());
    
    return found;
}

void displayAllPassengers() {
    ifstream file(PASSENGER_FILE);
    if (!file) {
        cout << "\n❌ No passengers registered!\n";
        return;
    }
    
    cout << "\n========================================================================================================================\n";
    cout << "                              ALL PASSENGERS\n";
    cout << "========================================================================================================================\n";
    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(25) << "Email" 
         << setw(15) << "Phone" << setw(10) << "Flight" << "Seat\n";
    cout << "________________________________________________________________________________\n";
    
    string line;
    bool hasData = false;
    
    while (getline(file, line)) {
        hasData = true;
        Passenger p;
        stringstream ss(line);
        getline(ss, p.id, '|');
        getline(ss, p.name, '|');
        getline(ss, p.password, '|');
        getline(ss, p.email, '|');
        getline(ss, p.phone, '|');
        getline(ss, p.bookedFlight, '|');
        ss >> p.seatNumber;
        
        cout << left << setw(10) << p.id << setw(20) << p.name 
             << setw(25) << p.email << setw(15) << p.phone 
             << setw(10) << p.bookedFlight << p.seatNumber << "\n";
    }
    
    if (!hasData) {
        cout << "No passengers found!\n";
    }
    
    cout << "========================================================================================================================\n";
    file.close();
}

Passenger getPassengerById(const string& id) {
    Passenger p = {"", "", "", "", "", "NONE", 0};
    ifstream file(PASSENGER_FILE);
    if (!file) return p;
    
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, p.id, '|');
        getline(ss, p.name, '|');
        getline(ss, p.password, '|');
        getline(ss, p.email, '|');
        getline(ss, p.phone, '|');
        getline(ss, p.bookedFlight, '|');
        ss >> p.seatNumber;
        
        if (p.id == id) {
            file.close();
            return p;
        }
    }
    
    file.close();
    p.id = ""; // Not found
    return p;
}

// ========== FLIGHT FILE OPERATIONS ==========

bool saveFlight(const Flight& f) {
    ofstream file(FLIGHT_FILE, ios::app);
    if (!file) return false;
    
    file << f.flightId << "|" << f.destination << "|" << f.departure << "|"
         << f.date << "|" << f.time << "|" << f.totalSeats << "|"
         << f.availableSeats << "|" << f.price << "|";
    
    for (int i = 0; i < 16; i++) {
        file << f.seats[i];
        if (i < 15) file << ",";
    }
    file << "\n";
    file.close();
    return true;
}

Flight getFlightById(const string& flightId) {
    Flight f = {"", "", "", "", "", 16, 16, 0.0};
    ifstream file(FLIGHT_FILE);
    if (!file) return f;
    
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, f.flightId, '|');
        getline(ss, f.destination, '|');
        getline(ss, f.departure, '|');
        getline(ss, f.date, '|');
        getline(ss, f.time, '|');
        ss >> f.totalSeats;
        ss.ignore();
        ss >> f.availableSeats;
        ss.ignore();
        ss >> f.price;
        ss.ignore();
        
        string seatData;
        getline(ss, seatData);
        stringstream seatStream(seatData);
        for (int i = 0; i < 16; i++) {
            char c;
            seatStream >> c;
            f.seats[i] = (c == '1');
            if (i < 15) seatStream.ignore();
        }
        
        if (f.flightId == flightId) {
            file.close();
            return f;
        }
    }
    
    file.close();
    f.flightId = ""; // Not found
    return f;
}

bool flightExists(const string& flightId) {
    ifstream file(FLIGHT_FILE);
    if (!file) return false;
    
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id;
        getline(ss, id, '|');
        
        if (id == flightId) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

bool updateFlightData(const Flight& updatedFlight) {
    ifstream file(FLIGHT_FILE);
    ofstream tempFile(TEMP_FILE);
    
    if (!file || !tempFile) return false;
    
    string line;
    bool found = false;
    
    while (getline(file, line)) {
        Flight f;
        stringstream ss(line);
        getline(ss, f.flightId, '|');
        
        if (f.flightId == updatedFlight.flightId) {
            tempFile << updatedFlight.flightId << "|" << updatedFlight.destination << "|" 
                    << updatedFlight.departure << "|" << updatedFlight.date << "|" 
                    << updatedFlight.time << "|" << updatedFlight.totalSeats << "|"
                    << updatedFlight.availableSeats << "|" << updatedFlight.price << "|";
            
            for (int i = 0; i < 16; i++) {
                tempFile << updatedFlight.seats[i];
                if (i < 15) tempFile << ",";
            }
            tempFile << "\n";
            found = true;
        } else {
            tempFile << line << "\n";
        }
    }
    
    file.close();
    tempFile.close();
    
    remove(FLIGHT_FILE.c_str());
    rename(TEMP_FILE.c_str(), FLIGHT_FILE.c_str());
    
    return found;
}

bool deleteFlight(const string& flightId) {
    ifstream file(FLIGHT_FILE);
    ofstream tempFile(TEMP_FILE);
    
    if (!file || !tempFile) return false;
    
    string line;
    bool found = false;
    
    while (getline(file, line)) {
        stringstream ss(line);
        string id;
        getline(ss, id, '|');
        
        if (id == flightId) {
            found = true;
            continue; // Skip this line (delete)
        }
        tempFile << line << "\n";
    }
    
    file.close();
    tempFile.close();
    
    remove(FLIGHT_FILE.c_str());
    rename(TEMP_FILE.c_str(), FLIGHT_FILE.c_str());
    
    return found;
}

void displayAllFlights() {
    ifstream file(FLIGHT_FILE);
    if (!file) {
        cout << "\n❌ No flights available!\n";
        return;
    }

    cout << "\n========================================================================================================================\n";
    cout << "                               ALL FLIGHTS\n";
    cout << "========================================================================================================================\n";
    cout << left << setw(10) << "Flight ID" << setw(15) << "Destination" 
         << setw(15) << "Departure" << setw(12) << "Date" 
         << setw(8) << "Time" << setw(8) << "Avail" << setw(8) << "Total" << "Price\n";
    cout << "________________________________________________________________________________\n";

    string line;
    bool hasData = false;
    
    while (getline(file, line)) {
        hasData = true;
        Flight f;
        stringstream ss(line);
        getline(ss, f.flightId, '|');
        getline(ss, f.destination, '|');
        getline(ss, f.departure, '|');
        getline(ss, f.date, '|');
        getline(ss, f.time, '|');
        ss >> f.totalSeats;
        ss.ignore();
        ss >> f.availableSeats;
        ss.ignore();
        ss >> f.price;
        
        cout << left << setw(10) << f.flightId << setw(15) << f.destination 
             << setw(15) << f.departure << setw(12) << f.date 
             << setw(8) << f.time << setw(8) << f.availableSeats 
             << setw(8) << f.totalSeats << "Rs." << fixed << setprecision(0) << f.price << "\n";
    }
    
    if (!hasData) {
        cout << "No flights found!\n";
    }
    
    cout << "========================================================================================================================\n";
    file.close();
}

// ========== ADMIN FILE OPERATIONS ==========

bool saveAdmin(const Admin& a) {
    ofstream file(ADMIN_FILE, ios::app);
    if (!file) return false;
    file << a.id << "|" << a.name << "|" << a.password << "\n";
    file.close();
    return true;
}

Admin* findAdmin(const string& id, const string& password) {
    static Admin found;
    ifstream file(ADMIN_FILE);
    if (!file) return nullptr;
    
    string line;
    while (getline(file, line)) {
        Admin a;
        stringstream ss(line);
        getline(ss, a.id, '|');
        getline(ss, a.name, '|');
        getline(ss, a.password, '|');
        
        if (a.id == id && a.password == password) {
            found = a;
            file.close();
            return &found;
        }
    }
    file.close();
    return nullptr;
}

bool adminExists(const string& id) {
    ifstream file(ADMIN_FILE);
    if (!file) return false;
    
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string adminID;
        getline(ss, adminID, '|');
        
        if (adminID == id) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

// Initialize with sample data if files don't exist
void initializeData() {
    ifstream testFlight(FLIGHT_FILE);
    if (!testFlight) {
        Flight f1 = {"FL001", "Dubai", "Karachi", "2025-01-15", "10:00", 16, 16, 15000.0};
        Flight f2 = {"FL002", "London", "Lahore", "2025-01-16", "14:30", 16, 16, 50000.0};
        Flight f3 = {"FL003", "New York", "Islamabad", "2025-01-17", "08:00", 16, 16, 80000.0};
        
        for (int i = 0; i < 16; i++) {
            f1.seats[i] = false;
            f2.seats[i] = false;
            f3.seats[i] = false;
        }
        
        saveFlight(f1);
        saveFlight(f2);
        saveFlight(f3);
    }
    testFlight.close();
    
    ifstream testAdmin(ADMIN_FILE);
    if (!testAdmin) {
        Admin a1 = {"admin01", "Admin User", "admin123"};
        saveAdmin(a1);
    }
    testAdmin.close();
}

#endif