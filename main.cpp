#include <iostream>
#include "functions.h"

using namespace std;

int main(){

    int choice;
    string username;

    choice = input_first_menu();

    if(choice == 1){
        cout << "\nAdmin panel will be added later...\n";
    }
    else if(choice == 2){

        choice = input_passenger_first_menu();

        if(choice == 1){
            username = input_passenger_login_menu();

            int passenger_choice = input_passenger_choice(username);

            if(passenger_choice == 1){
                input_passenger_flight_choice(username);
            }
            else{
                cout << "\nThank you for using our Airline System ✈️\n";
            }
        }
    }

    return 0;
}
