/*
author      :   saad khan
project     :   Hotel Management
date        :   10/12/2022
*/

#include<iostream>
#include<string>
#include<fstream>
using namespace std;

//class for room in a hotel

class Room {
    string name, discription, bed_size;
    float size;
    int no_of_guest, price;
    bool wifi_avalability;
public:
    Room(string na, string di, string be, float si, int no, int pr, bool wifi) { name = na; discription = di; bed_size = be;  size = si; no_of_guest = no; price = pr; wifi_avalability = wifi; }
};

//class for food
class Food {
    string name, type;
    int price;
public:
    Food(string na, int pr) { name = na; price = pr; }
};



// main menue 
void main_menue() {
    int main_choice;
label_1:
    cout << "\t\t\t------------------------------------------------------------" << endl;
    cout << "\t\t\t                     Welcome To Saad's Hotel                " << endl;
    cout << "\t\t\t------------------------------------------------------------" << endl;
    cout << "\t\t\t  1)  Staff                                                 " << endl;
    cout << "\t\t\t  2)  Guest                                                 " << endl;
    cout << "\t\t\t  3)  Exit                                                  " << endl;
    cin >> main_choice;
    switch (main_choice) {
    case 1:
        //void staff_menue();
        break;
    case 2:
        //void guest_menue();
        break;
    case 3:
        exit(1);
    default:
        cout << "\n\t\t\tPlease enter valid input\n" << endl;
    }
    goto label_1;
}




//      staff Menue
void staff_menue() {
    string username, password;
    //------------------>        continue from here     <---------



}
int main() {
    main_menue();



}