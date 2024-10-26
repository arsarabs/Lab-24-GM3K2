// COMSC-210 | Lab 23 | Anthony R. Sarabia
// IDE used: Visual Studio

#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <set>
#include <cstdlib>
#include <limits>
#include <ctime>
#include "Goat.h"

using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

void delete_goat(set<Goat>& trip);
void add_goat(set<Goat>& trip, string[], string[]);
void display_trip(const set<Goat>& trip);
int main_menu();

int main() {

    //Variables all in one place
    srand(time(0));
    bool again = true; // initliaze to something
    string names[SZ_NAMES];
    string colors[SZ_COLORS];
    int i = 0;
    ifstream fin("names.txt");
    ifstream fin1("colors.txt");
    set<Goat> trip; // List to store Goats for the trip

    // read & populate arrays for both names and colors arrays
    if (!fin) {
        cout << "ERROR! Couldn't open file." << endl;
        return 1;
    }
    while (i < SZ_NAMES && fin >> names[i++]); // populating name array
    fin.close();

    i = 0;

    if (!fin1) {
        cout << "ERROR! Couldn't open file." << endl;
        return 1;
    }
    while (i < SZ_COLORS && fin1 >> colors[i++]); // populating color array
    fin1.close();

    //MAIN MENU
    while (again) {
        int userChoice = main_menu();
        switch (userChoice) {
        case 1:
            //add a goat to trip
            add_goat(trip, names, colors); // Add a goat to the trip
            break;
        case 2:
            //delete a goat from the trip
            delete_goat(trip); // Delete a goat from the trip
            break;
        case 3:
            //display all goats
            display_trip(trip); // Display all goats in the trip
            break;
        case 4:
            again = false; // Exit the loop
            //Exit program
            break;
        default:
            //Invalid choice
            cout << "INVALID CHOICE" << endl;
        }
    }
    return 0;
}


void delete_goat(set<Goat>& trip) {
    string name_to_delete;
    if (trip.empty()) { // Check if the trip has any Goats to delete
        cout << "The trip has no goats to delete." << endl;
        return;
    }

    cout << "Enter name that you'd like to delete" << endl;
    cin >> name_to_delete;
    
    //Now, we need to make a temp Goat object with only the name to search 
    Goat temp(name_to_delete);
    auto it = trip.find(temp);

    if (it != trip.end()){
        cout << "Deleting goat: " << *it << endl;
        trip.erase(it);
    }
    else {
        cout << "Goat with name \"" << name_to_delete << "\" not found." << endl;
    }

}
void add_goat(set<Goat>& trip, string names[], string colors[]) {
    //the strucutre of this function shouldn't be too bad (SEE BELOW)

    //1. Randomly select name from names array & color from the colors array
    string selected_name = names[rand() % SZ_NAMES];
    string selected_color = colors[rand() % SZ_COLORS];

    //2. generate an age of 0-MAX_AGE
    int selected_age = rand() % (MAX_AGE + 1); // using random formula

    //3.  Create a new Goat object with the selected attributes
    Goat new_goat(selected_name, selected_age, selected_color);

    //4. Add the new Goat to the set 
    auto result = trip.insert(new_goat);

    //5. check if insertion worked
    if (result.second) {
        cout << "Goat Added: " << new_goat << endl;
    }
    else {
        cout << "Goat with name \"" << selected_name << "\" already exists. " << endl;
    }

}
//This function displays all the details 
void display_trip(const list<Goat> trip) {
    int index = 1; // Counter for numbering Goats
    set<string> unique_colors; // Set to store unique colors

    if (trip.empty()) { // Check if the trip has any Goats
        cout << "The trip has no goats." << endl;
        return;
    }
    cout << "     *** Current Trip Goats ***     " << endl;
    cout << endl;


    cout << left << setw(5) << "GOAT# " << setw(15) << "Name" << setw(10) << "Age" << "Color" << endl;
    cout << string(40, '-') << endl;

    // Iterate through the trip list and display each Goat's details
    for (const auto& goat : trip) {
        cout << left << setw(5) << index++
            << setw(15) << goat.get_name()
            << setw(10) << goat.get_age()
            << goat.get_color() << endl;

        unique_colors.insert(goat.get_color()); // Insert color into the set
    }
    cout << endl;
    cout << endl;
}
int main_menu() {
    int userChoice;
    bool valid = false;

    while (!valid) {
        // menu options
        cout << "*** GOAT MANAGER 3001 ***" << endl;
        cout << "[1] Add a goat" << endl;
        cout << "[2] Delete a goat" << endl;
        cout << "[3] List goats" << endl;
        cout << "[4] Quit" << endl;
        cout << "Choice --> ";

        cin >> userChoice;

        // Check for input failure or invalid range
        if (cin.fail() || userChoice < 1 || userChoice > 4) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }
        else {
            valid = true; // Valid input received
        }
    }
    return userChoice; // Return the validated choice

}