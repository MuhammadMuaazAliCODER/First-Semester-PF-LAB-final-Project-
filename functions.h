#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

/* ===== FUNCTION PROTOTYPES ===== */
int input_first_menu();
int input_passenger_first_menu();
string input_passenger_login_menu();
int input_passenger_choice(string username);
int input_passenger_flight_choice(string username);

/* ===== FUNCTION DEFINITIONS ===== */

int input_first_menu(){
    int choice;
    cout << "══════════════════════════════════════\n";
    cout << "      AIRLINE MANAGEMENT SYSTEM\n";
    cout << "══════════════════════════════════════\n\n";
    cout << "Enter your Identity?\n";
    cout << "  --> Press 1 for Admin\n";
    cout << "  --> Press 2 for Passenger\n";
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

int input_passenger_first_menu(){
    int choice;
    cout << "\nWelcome Passenger\n\n";
    cout << "  --> Press 1 for Login\n";
    cout << "  --> Press 2 for Signup\n";
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

string input_passenger_login_menu(){
    string unique_id, password;
    cout << "\nPassenger Login\n";
    cout << "Enter your unique ID: ";
    cin >> unique_id;
    cout << "Enter your password: ";
    cin >> password;
    return unique_id;
}

int input_passenger_choice(string username){
    int choice;
    cout << "\nWelcome " << username << " 👋\n\n";
    cout << " --> Press 1 to Book a Flight\n";
    cout << " --> Press 2 to Cancel Reservation\n";
    cout << " --> Press 3 to View Booking Report\n";
    cout << " --> Press 4 to Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

int input_passenger_flight_choice(string username){

    int choice;
    int seats[4][6] = {
        { 1,  2,  0,  0,  3,  4 },
        { 5,  6,  0,  0,  7,  8 },
        { 9, 10,  0,  0, 11, 12 },
        {13, 14,  0,  0, 15, 16 }
    };

    cout << "\n══════════════════════════════════════\n";
    cout << "✈️  PLANE SEAT MAP\n";
    cout << "══════════════════════════════════════\n";
    cout << "Numbers = Available | XX = Booked\n\n";

    for (int i = 0; i < 4; i++) {
        cout << "Row " << i + 1 << "  ";

        for (int j = 0; j < 6; j++) {

            if (j == 2) cout << "   ";

            if (seats[i][j] == 0)
                cout << setw(3) << "XX";
            else
                cout << setw(3) << seats[i][j];
        }
        cout << endl;
    }

    cout << "\nEnter seat number to book: ";
    cin >> choice;

    return choice;
}

#endif
