#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <algorithm>
#include <numeric>
#include <random>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
void findbyname(const list<Goat>& trip);
void doubleage(list<Goat>& trip);
void removegoats(list<Goat>& trip, int a);
void totalage(const list<Goat>& trip);
void incrementage(list<Goat>& trip);
void reversegoats(list<Goat>& trip);
void checkage(const list<Goat>& trip, int a);
void shuffle(list<Goat>& trip);
int main_menu();

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 7) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            case 4:
                cout << "Sorting by age:\n";
                trip.sort();
                display_trip(trip);
                break;
            case 5:
                cout << "Finding goat by name:\n";
                findbyname(trip);
                break;
            case 6: 
                cout << "Doubling age of each goat:\n";
                display_trip(trip);
                break;
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }
    

    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Sort goats by age:\n";
    cout << "[5] Find goat by name:\n";
    cout << "[6] Doubling goat age:\n";
    cout << "[7] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 7) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}
void findbyname(const list<Goat>& trip){
    string name;
    cout << "Enter goat name to find: ";
    cin >> name;

    auto it = find_if(trip.begin(), trip.end(), [&](const Goat g){ return g.get_name() == name; });
    if (it != trip.end()) {
        cout << it->get_name() << " found with age " << it->get_age() << " and color " << it->get_color() << endl;
    }
    else {
        cout << name << " could not be found.\n";
    }
}
void doubleage(list<Goat>& trip) {
    for_each(trip.begin(), trip.end(), [](Goat& g){ g.set_age(g.get_age() * 2); });
    cout << "Age doubled.\n";
}
void removegoats(list<Goat>& trip, int a){
    trip.erase(remove_if(trip.begin(), trip.end(), [a](Goat& g){ return g.get_age() < a;}), trip.end());
    cout << "Removed goats under age " << a << endl;
}
void totalage(const list<Goat>& trip){
    int total = accumulate(trip.begin(), trip.end(), 0, [](int sum, const Goat& g) { return sum + g.get_age(); });
    cout << "Total age: " << total << endl;
}
void incrementage(list<Goat>& trip){
    transform(trip.begin(), trip.end(), trip.begin(), [](Goat& g) { g.set_age(g.get_age() + 1); return g; });
}
void reversegoats(list<Goat>& trip){
    trip.reverse();
    cout << "Goat list has been reversed.\n";
}
void checkage(const list<Goat>& trip, int a){
    bool hasage = any_of(trip.begin(), trip.end(), [a](const Goat& g){ return g.get_age() == a; });
    cout << "Is there a goat with that age? " << (hasage ? "Yes" : "No") << endl << endl;
}
void shuffle(list<Goat>& trip){
    vector<Goat> goats(trip.begin(), trip.end());
    shuffle(goats.begin(), goats.end(), default_random_engine());
}