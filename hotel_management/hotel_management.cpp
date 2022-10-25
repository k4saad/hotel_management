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
const char* database = "HOTEL.db";


//function declaration
void main_menue();
void staff_menue();
void staff_register();
void staff_login();


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
    cout << "\t\t\t  1)  Register                                              " << endl;
    cout << "\t\t\t  2)  Login                                                 " << endl;
    cout << "\t\t\t  3)  Back                                                  " << endl;
    cin >> staff_choice;
    switch (staff_choice) {
    case 1:
        staff_register();
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



// staff registration 

void staff_register() {
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


        cout << "access granted" << endl;

        //opening of database for registering employee

        string database = "HOTEL.db";
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
            }
            else {
                cout << "Error preparing insert statement" << endl;
            }

            sqlite3_finalize(myStatement);
        }
        else {
            cout << "Error opening in database" << endl;
        }

    }
    else {
        cout << "\n\t\t\tinvalid username or password\n" << endl;
        staff_menue();
    }
}

//done till here

/*
        // using sqlite3 database
        try {

            //create database if not exist

            sqlite3* db;
            sqlite3_stmt* stmt;
            char* messageError;
            sqlite3_open(database, &db);
            string sql_employee_register = "CREATE TABLE IF NOT EXISTS EMPLOYEE ("
		    "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
		    "NAME TEXT NOT NULL, "
		    "USER_NAME TEXT NOT NULL, "
		    "PASSWORD TEXT NOT NULL );";  


            int exit = 0;
            exit = sqlite3_open(database, &db);

            // An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here 
            exit = sqlite3_exec(db, sql_employee_register.c_str(), 0, &stmt, &messageError);
            if (exit != SQLITE_OK) {
                cerr << "cannot open database" << endl;
                sqlite3_free(messageError);
            }
            else {

                //inserting employee into the database

                string employee_name, employee_username, employee_password;
                cout << "Enter Employee Name : " << endl;
                cin >> employee_name;
                cout << "Enter Employee username : " << endl;
                cin >> employee_username;
                cout << "Enter Employee password :  " << endl;
                cin >> employee_password;


                sqlite3* db;
                char* messageError;

                string sql_insert_employee = "INSERT INTO Employee (NAME,USER_NAME, PASSWORD) VALUES('" + employee_name + "','" + employee_username + "','" + employee_password +"');";
                int exit = sqlite3_open(database, &db);
                 An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here 
                exit = sqlite3_exec(db, sql_insert_employee.c_str(), NULL, 0, &messageError);
                if (exit != SQLITE_OK) {
                    cerr << "Error in insertData function." << endl;
                    sqlite3_free(messageError);
                }
                else {
                    cout << "Records inserted Successfully!" << endl;



                }
                sqlite3_close(db);
            }


        }
        catch (const exception& e)
        {
            cerr << e.what();
        }

*/



void staff_login() {
    /*
    string username, password;

    cout << "Enter Username : " << endl;
    cin >> username;
    cout << "Enter password : " << endl;
    cin >> password;

    
        try {
            sqlite3* db;
            sqlite3_stmt* stmt;
            char* messageError;
            sqlite3_open(database, &db);
            string sql_employee_login = "SELECT USER_NAME, PASSWORD FROM EMPLOYEE WHERE USER_NAME='" + username + "'AND password ='" + password + "';";

            //below code is for reference 
            //compare value of username and password from user with USER_NAME and PASSWORD from database

            int exit = 0;
            exit = sqlite3_open(database, &db);

            // An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here
            exit = sqlite3_exec(db, sql_employee_login.c_str(), 0, &stmt, &messageError);
            if (exit != SQLITE_OK) {
                cerr << "\n\t\t\tinvalid username or password\n" << endl;
                sqlite3_free(messageError);
            }
            else {
                cout << "Welcome " << username;
                sqlite3_close(db);
            }


        }
        catch (const exception& e)
        {
            cerr << e.what();
        }



        */
}
    
    



int main() {
    main_menue();



    //sqlite3_close(db);
}