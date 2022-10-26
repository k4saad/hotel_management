/*
author      :   saad khan
project     :   Hotel Management
date        :   10/12/2022
*/

#include<iostream>
#include<stdio.h>
#include<sqlite3.h>
#include<fstream>
using namespace std;
string database = "HOTEL.db";



//function declaration
void main_menue();
void staff_menue();
void admin_login();
void staff_register();
void all_employee();
void staff_login();
void employee_menue();



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
        staff_menue();
        break;
    case 2:
        //void guest_menue();
        break;
    case 3:
        exit(1);
    default:
        cout << "Please enter valid input" << endl;
    }
    goto label_1;
}




//      staff Menue
void staff_menue() {
    int staff_choice;
    label_2:
    cout << "\t\t\t------------------------------------------------------------" << endl;
    cout << "\t\t\t                            STAFF                           " << endl;
    cout << "\t\t\t------------------------------------------------------------" << endl;
    cout << "\t\t\t  1)  Admin login                                           " << endl;
    cout << "\t\t\t  2)  Staff login                                           " << endl;
    cout << "\t\t\t  3)  Back                                                  " << endl;
    cin >> staff_choice;
    switch (staff_choice) {
    case 1:
        admin_login();
        break;
    case 2:
        staff_login();
        break;
    case 3:
        main_menue();
    default:
        cout << "Please enter valid input" << endl;
    }
    goto label_2;


}

void admin_login() {

    string username, password, admin_username, admin_pass;

    cout << "Enter Username : " << endl;
    cin >> username;
    cout << "Enter password : " << endl;
    cin >> password;

    //reading from file
    ifstream ad_file;
    ad_file.open("admin_file.txt");
    ad_file >> admin_username;
    ad_file >> admin_pass;

    if (admin_username == username && admin_pass == password) {
        int admin_choice;
        cout << "access granted" << endl;
    label_3:
        cout << "\t\t\t------------------------------------------------------------" << endl;
        cout << "\t\t\t                            STAFF                           " << endl;
        cout << "\t\t\t------------------------------------------------------------" << endl;
        cout << "\t\t\t  1)  Register                                              " << endl;
        cout << "\t\t\t  2)  All Employee                                          " << endl;
        cout << "\t\t\t  3)  Back                                                  " << endl;
        cin >> admin_choice;
        switch (admin_choice) {
        case 1:
            staff_register();
            break;
        case 2:
            all_employee();
            break;
        case 3:
            staff_menue();
        default:
            cout << "Please enter valid input" << endl;
        }
        goto label_3;

    }
    else {
        cout << "\n\t\t\tinvalid username or password\n" << endl;
        staff_menue();
    }
}

// staff registration 

void staff_register() {

    //opening of database for registering employee

    sqlite3* db;
    int statusOfOpen = sqlite3_open(database.c_str(), &db);
    if (statusOfOpen == SQLITE_OK) {
        sqlite3_stmt* myStatement;
        int statusOfPrep = sqlite3_prepare_v2(db, "CREATE TABLE IF NOT EXISTS employee(id INTEGER PRIMARY KEY CHECK(id != 0),name TEXT NOT NULL, username TEXT NOT NULL, password TEXT);", -1, &myStatement, NULL);
        if (statusOfPrep == SQLITE_OK) {
            int statusOfStep = sqlite3_step(myStatement);
            if (statusOfStep == SQLITE_DONE) {
                cout << "Successfully accessed employee table" << endl;
            }
            else {
                cout << "Error creating of accessing the employee table" << endl;
            }

            sqlite3_finalize(myStatement);

        }
        else {
            cout << "Error preparing the statement" << endl;
        }
        int employee_id;
        string employee_name, employee_username, employee_password;
        cout << "enter Employee Id : " << endl;
        cin >> employee_id;
        cout << "Enter Employee Name : " << endl;
        cin >> employee_name;
        cout << "Enter Employee username : " << endl;
        cin >> employee_username;
        cout << "Enter Employee password :  " << endl;
        cin >> employee_password;

        //inserting value in the database

        statusOfPrep = sqlite3_prepare_v2(db, "INSERT INTO employee VALUES(?,?,?,?);", -1, &myStatement, NULL);
        sqlite3_bind_int(myStatement, 1, employee_id);
        sqlite3_bind_text(myStatement, 2, employee_name.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(myStatement, 3, employee_username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(myStatement, 4, employee_password.c_str(), -1, SQLITE_STATIC);
        if (statusOfPrep == SQLITE_OK) {
            int statusOfStep = sqlite3_step(myStatement);
            if (statusOfStep == SQLITE_DONE) {
                cout << "Successfully added new employee" << endl;
            }
            else {
                cout << "Error adding employee" << endl;
            }
            sqlite3_finalize(myStatement);
        }
        else {
            cout << "Error preparing insert statement" << endl;
        }
        sqlite3_close(db);

    }
    else {
        cout << "Error in opening database" << endl;
    }

}


void all_employee() {
    cout << "all employee" << endl;
    sqlite3* db;
    int statusOfOpen = sqlite3_open(database.c_str(), &db);
    if (statusOfOpen == SQLITE_OK) {
        sqlite3_stmt* myStatement;
        int statusOfPrep = sqlite3_prepare_v2(db, "SELECT employee.id, employee.name, employee.username, employee.password FROM employee", -1, &myStatement, NULL);
        if (statusOfPrep == SQLITE_OK) {
            int empId;
            string empName, empUsername, empPassword;
            int statusOfStep = sqlite3_step(myStatement);
            while (statusOfStep == SQLITE_ROW) {
                empId = sqlite3_column_int(myStatement, 0);
                empName = (char*)sqlite3_column_text(myStatement, 1);
                empUsername = (char*)sqlite3_column_text(myStatement, 2);
                empPassword = (char*)sqlite3_column_text(myStatement, 3);
                
                cout << "---------------------------" << endl;
                cout << "Id : " << empId << endl;
                cout << "Name : " << empName << endl;
                cout << "Username : " << empUsername << endl;
                cout << "Password : " << empPassword << endl;

                statusOfStep = sqlite3_step(myStatement);
            }
            sqlite3_finalize(myStatement);
        }
        else {
            cout << "Error preparing a select statement" << endl;
        }
        sqlite3_close(db);
    }
    else {
        cout << "Error in opening database" << endl;
    }
}

void staff_login() {
    
    string username, password, eName;

    cout << "Enter Username : " << endl;
    cin >> username;
    cout << "Enter password : " << endl;
    cin >> password;
    
    sqlite3* db;
    int statusOfOpen = sqlite3_open(database.c_str(), &db);
    if (statusOfOpen == SQLITE_OK) {
        sqlite3_stmt* myStatement;
        int statusOfPrep = sqlite3_prepare_v2(db, "SELECT employee.name FROM employee WHERE username=(?) AND password=(?);", -1, &myStatement, NULL);
        sqlite3_bind_text(myStatement, 1, username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(myStatement, 2, password.c_str(), -1, SQLITE_STATIC);
        if (statusOfPrep == SQLITE_OK) {
            int statusOfStep = sqlite3_step(myStatement);
            if (statusOfStep == SQLITE_ROW) {
                eName = (char*) sqlite3_column_text(myStatement, 0);
                cout << "Welcome " << eName << endl;
                employee_menue();
            }
            else {
                cout << "No user found" << endl;
            }
            sqlite3_finalize(myStatement);
        }
        else {
            cout << "Error preparing select statement" << endl;
        }
        sqlite3_close(db);
    }
    else {
        cout << "Error opening database" << endl;
    }
       
}

void employee_menue() {
    cout << "hello saad khan" << endl;
    //nothings
}
    
    



int main() {
    main_menue();



    //sqlite3_close(db);
}