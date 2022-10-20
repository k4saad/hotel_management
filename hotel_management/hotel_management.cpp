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
                /* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
                exit = sqlite3_exec(db, sql_insert_employee.c_str(), NULL, 0, &messageError);
                if (exit != SQLITE_OK) {
                    cerr << "Error in insertData function." << endl;
                    sqlite3_free(messageError);
                }
                else {
                    cout << "Records inserted Successfully!" << endl;

                }
            }


        }
        catch (const exception& e)
        {
            cerr << e.what();
        }


    }
    else {
        cout << "\n\t\t\tinvalid username or password\n" << endl;
        staff_menue();
    }

}

void staff_login() {


    /*
        try {
            sqlite3* db;
            sqlite3_stmt* stmt;
            char* messageError;
            sqlite3_open(database, &db);
            string sql_employee_login = "SELECT username, password FROM employee WHERE username = '" + username + "'AND password = '" + password + "';";


            int exit = 0;
            exit = sqlite3_open(database, &db);

            // An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here
            exit = sqlite3_exec(db, sql_employee_login.c_str(), 0, &stmt, &messageError);
            if (exit != SQLITE_OK) {
                cerr << "\n\t\t\tinvalid username or password\n" << endl;
                sqlite3_free(messageError);
            }
            else

                sqlite3_close(db);
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