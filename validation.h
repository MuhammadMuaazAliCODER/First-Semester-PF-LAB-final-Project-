#ifndef VALIDATION_H
#define VALIDATION_H

#include <iostream>
#include <string>
#include <cctype>
#include <limits>

using namespace std;

// Clear input buffer
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Validate integer input within range
int getValidatedInt(int min, int max) {
    int value;
    while (true) {
        cin >> value;
        if (cin.fail() || value < min || value > max) {
            cout << "Invalid input! Enter a number between " << min << " and " << max << ": ";
            clearInputBuffer();
        } else {
            clearInputBuffer();
            return value;
        }
    }
}

// Validate string is not empty
string getValidatedString(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        if (input.empty() || input.find_first_not_of(' ') == string::npos) {
            cout << "Input cannot be empty! Try again.\n";
        } else {
            return input;
        }
    }
}

// Validate password (min 6 characters)
string getValidatedPassword() {
    string password;
    while (true) {
        cout << "Enter password (min 6 characters): ";
        getline(cin, password);
        if (password.length() < 6) {
            cout << "Password too short! Must be at least 6 characters.\n";
        } else {
            return password;
        }
    }
}

// Validate email format
bool isValidEmail(const string& email) {
    size_t atPos = email.find('@');
    size_t dotPos = email.find_last_of('.');
    return (atPos != string::npos && dotPos != string::npos && 
            atPos < dotPos && dotPos < email.length() - 1);
}

// Validate phone number (digits only, 10-15 chars)
bool isValidPhone(const string& phone) {
    if (phone.length() < 10 || phone.length() > 15) return false;
    for (char c : phone) {
        if (!isdigit(c)) return false;
    }
    return true;
}

// Validate seat number (1-16)
int getValidatedSeat() {
    cout << "Enter seat number (1-16): ";
    return getValidatedInt(1, 16);
}

#endif