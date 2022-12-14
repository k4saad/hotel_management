
/*
author      :   saad khan
project     :   Hotel Management
date        :   10/12/2022
*/

#include<iostream>
#include<stdio.h>
#include<sqlite3.h>
#include<fstream>
#include<string>
using namespace std;
string database = "HOTEL.db";



//function declaration
void main_menue();
void staff_menue();
void admin_login();
void staff_register();
void delete_employee();
void all_employee();
void staff_login();
void employee_menue();
void room_opr();
void add_room();
void delete_room();
void all_room();
void food_opr();
void add_food();
void delete_food();
void all_food();
void ledger();
void room_income();
void food_income();
void total_income();
//guest part
void guest_menue();
void book_room();
void order_food();





// main menue 
void main_menue() {
    int main_choice;
label_1:
    cout << "\t\t\t------------------------------------------------------------" << endl;
    cout << "\t\t\t                          Main Menue                        " << endl;
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
        guest_menue();
        break;
    case 3:
        exit(1);
    default:
        cout<< "Please enter valid input" << endl;
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
        cout << "\t\t\t                           ADMIN MENUE                      " << endl;
        cout << "\t\t\t------------------------------------------------------------" << endl;
        cout << "\t\t\t  1)  Register                                              " << endl;
        cout << "\t\t\t  2)  Delete Employee                                       " << endl;
        cout << "\t\t\t  3)  All Employee                                          " << endl;
        cout << "\t\t\t  4)  Back                                                  " << endl;
        cin >> admin_choice;
        switch (admin_choice) {
        case 1:
            staff_register();
            break;
        case 2:
            delete_employee();
        case 3:
            all_employee();
            break;
        case 4:
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
        int statusOfPrep = sqlite3_prepare_v2(db, "CREATE TABLE IF NOT EXISTS employee(id INTEGER PRIMARY KEY CHECK(id != 0 AND id > 0),name TEXT NOT NULL, username TEXT NOT NULL, password TEXT);", -1, &myStatement, NULL);
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

//delete employee
void delete_employee() {
    sqlite3* db;
    int statusOfOpen = sqlite3_open(database.c_str(), &db);
    if (statusOfOpen == SQLITE_OK) {
        sqlite3_stmt* myStatement;
        int statusOfPrep = sqlite3_prepare_v2(db, "SELECT employee.id, employee.name, employee.username, employee.password FROM employee ORDER BY employee.id", -1, &myStatement, NULL);
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
        int empId;
        cout << "\nEnter id of employee to be deleted : " << endl;
        cin >> empId;
        statusOfPrep = sqlite3_prepare_v2(db, "DELETE FROM employee WHERE id = (?);", -1, &myStatement, NULL);
        sqlite3_bind_int(myStatement, 1, empId);
        if (statusOfPrep == SQLITE_OK) {
            int statusOfStep = sqlite3_step(myStatement);
            if (statusOfStep == SQLITE_DONE) {
                cout << "Employee with id : " << empId << " deleted" << endl;
            }
            else {
                cout << "No Empolyee found or deleted" << endl;
            }
            sqlite3_finalize(myStatement);
        }
        else {
            cout << "Error preparing delete statement" << endl;
        }
        sqlite3_close(db);
    }
    else {
        cout << "Error in opening database" << endl;
    }
}



void all_employee() {
    cout << "\nAll employee" << endl;
    sqlite3* db;
    int statusOfOpen = sqlite3_open(database.c_str(), &db);
    if (statusOfOpen == SQLITE_OK) {
        sqlite3_stmt* myStatement;
        int statusOfPrep = sqlite3_prepare_v2(db, "SELECT employee.id, employee.name, employee.username, employee.password FROM employee ORDER BY employee.id", -1, &myStatement, NULL);
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
                eName = (char*)sqlite3_column_text(myStatement, 0);
                sqlite3_finalize(myStatement);
                sqlite3_close(db);
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

    int employee_choice;
label_4:
    cout << "\t\t\t------------------------------------------------------------" << endl;
    cout << "\t\t\t                            STAFF                           " << endl;
    cout << "\t\t\t------------------------------------------------------------" << endl;
    cout << "\t\t\t  1)  Room                                                  " << endl;
    cout << "\t\t\t  2)  Food                                                  " << endl;
    cout << "\t\t\t  3)  Ledger                                                " << endl;
    cout << "\t\t\t  4)  Back                                                  " << endl;
    cin >> employee_choice;
    switch (employee_choice) {
    case 1:
        room_opr();
        break;
    case 2:
        food_opr();
        break;
    case 3:
        ledger();
    case 4:
        staff_menue();
    default:
        cout << "Please enter valid input" << endl;
    }
    goto label_4;

}

void room_opr() {

    int employee_choice;
label_5:
    cout << "\t\t\t------------------------------------------------------------" << endl;
    cout << "\t\t\t                            ROOM                            " << endl;
    cout << "\t\t\t------------------------------------------------------------" << endl;
    cout << "\t\t\t  1)  Add Room                                              " << endl;
    cout << "\t\t\t  2)  Delete Room                                           " << endl;
    cout << "\t\t\t  3)  All Room                                              " << endl;
    cout << "\t\t\t  4)  Back                                                  " << endl;
    cin >> employee_choice;
    switch (employee_choice) {
    case 1:
        add_room();
        break;
    case 2:
        delete_room();
        break;
    case 3:
        all_room();
    case 4:
        employee_menue();
    default:
        cout << "Please enter valid input" << endl;
    }
    goto label_5;
}

void add_room() {

    //creating room table in database
    sqlite3* db;
    int statusOfOpen = sqlite3_open(database.c_str(), &db);
    if (statusOfOpen == SQLITE_OK) {
        sqlite3_stmt* myStatement;
        int statusOfPrep = sqlite3_prepare_v2(db, "CREATE TABLE IF NOT EXISTS room(id INTEGER PRIMARY KEY CHECK(id != 0 AND id > 0), name TEXT , capacity INTEGER, price INTEGER, roomsize INTEGER, bedsize TEXT, discription TEXT);", -1, &myStatement, NULL);
        if (statusOfPrep == SQLITE_OK) {
            int statusOfStep = sqlite3_step(myStatement);
            if (statusOfStep == SQLITE_DONE) {
                cout << "Successfully accessed room table" << endl;
            }
            else {
                cout << "Error creating room table" << endl;
            }
            sqlite3_finalize(myStatement);
        }
        else {
            cout << "Error preparing create table statement" << endl;
        }
        //taking value for room
        int rId, rSize, rCapacity, rPrice;
        string rName, rDiscription, rBedSize;
        cout << "\t\t\t---Enter room details---" << endl;
        cout << "Room id : " << endl;
        cin >> rId;
        cout << "Room name : " << endl;
        cin.ignore();
        getline(cin, rName);
        cout << "Room capacity : " << endl;
        cin >> rCapacity;
        cout << "Room rate/night : " << endl;
        cin >> rPrice;
        cout << "Room Size : " << endl;
        cin >> rSize;
        cout << "Room Bed Size : " << endl;
        cin >> rBedSize;
        cout << "Room Discription : " << endl;
        cin.ignore();
        getline(cin,rDiscription);

        //inserting value in room table
        statusOfPrep = sqlite3_prepare_v2(db, "INSERT INTO room VALUES(?,?,?,?,?,?,?)", -1, &myStatement, NULL);
        sqlite3_bind_int(myStatement, 1, rId);
        sqlite3_bind_text(myStatement, 2, rName.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(myStatement, 3, rCapacity);
        sqlite3_bind_int(myStatement, 4, rPrice);
        sqlite3_bind_int(myStatement, 5, rSize);
        sqlite3_bind_text(myStatement, 6, rBedSize.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(myStatement, 7, rDiscription.c_str(), -1, SQLITE_STATIC);

        if (statusOfPrep == SQLITE_OK) {
            int statusOfStep = sqlite3_step(myStatement);
            if (statusOfStep == SQLITE_DONE) {
                cout << "Room inserted successfully" << endl;
            }
            else {
                cout << "Error inserting valule" << endl;
            }
            sqlite3_finalize(myStatement);
        }
        else {
            cout << "Error preparing the insert statement" << endl;
        }
        sqlite3_close(db);
    }
    else {
        cout << "Error in opening of database" << endl;
    }


}


//delete room
void delete_room() {


    sqlite3* db;
    int statusOfOpen = sqlite3_open(database.c_str(), &db);
    if (statusOfOpen == SQLITE_OK) {
        sqlite3_stmt* myStatement;
        int statusOfPrep = sqlite3_prepare_v2(db, "SELECT room.id, room.name, room.capacity, room.price, room.roomsize, room.bedsize, room.discription FROM room ORDER BY room.id", -1, &myStatement, NULL);
        if (statusOfPrep == SQLITE_OK) {
            cout << "\nRoom list" << endl;
            int rId, rSize, rCapacity, rPrice;
            string rName, rDiscription, rBedSize;
            int statusOfStep = sqlite3_step(myStatement);
            while (statusOfStep == SQLITE_ROW) {
                rId = sqlite3_column_int(myStatement, 0);
                rName = (char*)sqlite3_column_text(myStatement, 1);
                rCapacity = sqlite3_column_int(myStatement, 2);
                rPrice = sqlite3_column_int(myStatement, 3);
                rSize = sqlite3_column_int(myStatement, 4);
                rBedSize = (char*)sqlite3_column_text(myStatement, 5);
                rDiscription = (char*)sqlite3_column_text(myStatement, 6);

                cout << "---------------------------" << endl;
                cout << "Room id : " << rId <<endl;
                cout << "Room name : " << rName << endl;
                cout << "Room capacity : " << rCapacity << " guests" << endl;
                cout << "Room price : " << rPrice << " Rupees / night" << endl;
                cout << "Room size : " << rSize << " sq mt" << endl;
                cout << "Bed size : " << rBedSize << " size" << endl;
                cout << "Room Discription : "<< rDiscription << endl;
                statusOfStep = sqlite3_step(myStatement);

            }
            sqlite3_finalize(myStatement);
        }
        else {
            cout << "Error preparing select statement" << endl;
        }

        int rId;
        cout << "\nEnter id of room to be deleted : " << endl;
        cin >> rId;
        statusOfPrep = sqlite3_prepare_v2(db, "DELETE FROM room WHERE id = (?);", -1, &myStatement, NULL);
        sqlite3_bind_int(myStatement, 1, rId);
        if (statusOfPrep == SQLITE_OK) {
            int statusOfStep = sqlite3_step(myStatement);
            if (statusOfStep == SQLITE_DONE) {
                cout << "Room with id " << rId << " deleted" << endl;
            }
            else {
                cout << "No room found or deleted" << endl;
            }
            sqlite3_finalize(myStatement);
        }
        else {
            cout << "Error preparing delete statement" << endl;
        }
        sqlite3_close(db);
    }
    else {
        cout << "Error in opening of database" << endl;
    }

}
//to see all available rooms
void all_room() {
    cout << "All Room" << endl;
    int rId, rSize, rCapacity, rPrice;
    string rName, rDiscription, rBedSize;
    sqlite3* db;
    int statusOfOpen = sqlite3_open(database.c_str(), &db);
    if (statusOfOpen == SQLITE_OK) {
        sqlite3_stmt* myStatement;
        int statusOfPrep = sqlite3_prepare_v2(db, "SELECT room.id, room.name, room.capacity, room.price, room.roomsize, room.bedsize, room.discription FROM room ORDER BY room.id", -1, &myStatement, NULL);
        if (statusOfPrep == SQLITE_OK) {
            int statusOfStep = sqlite3_step(myStatement);
            while (statusOfStep == SQLITE_ROW) {

                rId = sqlite3_column_int(myStatement, 0);
                rName = (char*)sqlite3_column_text(myStatement, 1);
                rCapacity = sqlite3_column_int(myStatement, 2);
                rPrice = sqlite3_column_int(myStatement, 3);
                rSize = sqlite3_column_int(myStatement, 4);
                rBedSize = (char*)sqlite3_column_text(myStatement, 5);
                rDiscription = (char*)sqlite3_column_text(myStatement, 6);

                cout << "---------------------------" << endl;
                cout << "Room id : " << rId << endl;
                cout << "Room name : " << rName << endl;
                cout << "Room capacity : " << rCapacity << " guests" << endl;
                cout << "Room price : " << rPrice << " rupees / night" << endl;
                cout << "Room size : " << rSize << " sq mt" << endl;
                cout << "Bed size : " << rBedSize << " size" << endl;
                cout << "Room Discription : " << rDiscription << endl;
                statusOfStep = sqlite3_step(myStatement);

            }
            sqlite3_finalize(myStatement);
        }
        else {
            cout << "Error preparing select statement" << endl;
        }
        sqlite3_close(db);
    }
    else {
        cout << "Error in opening of database" << endl;
    }
}

//food menue
void food_opr() {

    int employee_choice;
label_6:
    cout << "\t\t\t------------------------------------------------------------" << endl;
    cout << "\t\t\t                            FOOD                            " << endl;
    cout << "\t\t\t------------------------------------------------------------" << endl;
    cout << "\t\t\t  1)  Add Food                                              " << endl;
    cout << "\t\t\t  2)  Delete Food                                           " << endl;
    cout << "\t\t\t  3)  All Food                                              " << endl;
    cout << "\t\t\t  4)  Back                                                  " << endl;
    cin >> employee_choice;
    switch (employee_choice) {
    case 1:
        add_food();
        break;
    case 2:
        delete_food();
        break;
    case 3:
        all_food();
    case 4:
        employee_menue();
    default:
        cout << "Please enter valid input" << endl;
    }
    goto label_6;
}

//to add food
void add_food() {
    sqlite3* db;
    int statusOfOpen = sqlite3_open(database.c_str(), &db);
    if (statusOfOpen == SQLITE_OK) {
        sqlite3_stmt* myStatement;
        int statusOfPrep = sqlite3_prepare_v2(db, "CREATE TABLE IF NOT EXISTS food(name TEXT PRIMARY KEY, type TEXT, price INTEGER)", -1, &myStatement, NULL);
        if (statusOfPrep == SQLITE_OK) {
            int statusOfStep = sqlite3_step(myStatement);
            if (statusOfStep == SQLITE_DONE) {
                cout << "food table acccessed" << endl;
            }
            else {
                cout << "Error accessing food table" << endl;
            }
            sqlite3_finalize(myStatement);
        }
        else {
            cout << "Error in preparing create statement" << endl;
        }
        string fName, fType;
        int fPrice;
        cout << "\t\t\t---Enter food details---" << endl;
        cout << "Food Name : " << endl;
        cin.ignore();
        getline(cin, fName);
        cout << "Food Type ( soup, starter, entree )  : " << endl;
        cin >> fType;
        cout << "Food Price : " << endl;
        cin >> fPrice;

        statusOfPrep = sqlite3_prepare_v2(db, "INSERT INTO food VALUES(?,?,?)", -1, &myStatement, NULL);
        sqlite3_bind_text(myStatement, 1, fName.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(myStatement, 2, fType.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(myStatement, 3, fPrice);


        if (statusOfPrep == SQLITE_OK) {
            int statusOfStep = sqlite3_step(myStatement);
            if (statusOfStep == SQLITE_DONE) {
                cout << "Successfully added food " << endl;
            }
            else {
                cout << "Error in adding food " << endl;
            }
            sqlite3_finalize(myStatement);
        }
        else {
            cout << "Error in preparing create statement" << endl;
        }
        sqlite3_close(db);
    }
    else {
        cout << "Error in opening of database" << endl;
    }
}

//delete food
void delete_food() {
    sqlite3* db;
    int statusOfOpen = sqlite3_open(database.c_str(), &db);
    if (statusOfOpen == SQLITE_OK) {
        sqlite3_stmt* myStatement;
        
        int statusOfPrep = sqlite3_prepare_v2(db, "SELECT food.name, food.type, food.price FROM food ORDER BY food.type", -1, &myStatement, NULL);
        if (statusOfPrep == SQLITE_OK) {
            string fName, fType;
            int fPrice;
            int statusOfStep = sqlite3_step(myStatement);
            while (statusOfStep == SQLITE_ROW) {
                fName = (char*)sqlite3_column_text(myStatement, 0);
                fType = (char*)sqlite3_column_text(myStatement, 1);
                fPrice = sqlite3_column_int(myStatement, 2);
                cout << "---------------------------" << endl;
                
                cout << "Food name : " << fName << endl;
                cout << "Food type : " << fType << endl;
                cout << "Food price : " << fPrice << " per plate" << endl;
                statusOfStep = sqlite3_step(myStatement);

            }

            sqlite3_finalize(myStatement);
        }
        else {
            cout << "Error Preparing select statement" << endl;
        }
        
        string fName;
        cout << "\nEnter food name to be deleted" << endl;
        cin.ignore();
        getline(cin, fName);
        
        statusOfPrep = sqlite3_prepare_v2(db, "DELETE FROM food WHERE name = (?)", -1, &myStatement, NULL);
        sqlite3_bind_text(myStatement, 1, fName.c_str(), -1, SQLITE_STATIC);
        if (statusOfPrep == SQLITE_OK) {
            int statusOfStep = sqlite3_step(myStatement);
            if (statusOfStep == SQLITE_DONE) {
                cout << fName << " successfully deleted" << endl;
            }
        }
        else {
            cout << "Error preparing delete statement" << endl;
        }

        sqlite3_close(db);
    }
    else {
        cout << "Error in opening of database" << endl;
    }
}

//to see all food available
void all_food() {
    cout << "All Food" << endl;
    sqlite3* db;
    int statusOfOpen = sqlite3_open(database.c_str(), &db);
    if (statusOfOpen == SQLITE_OK) {
        sqlite3_stmt* myStatement;

        int statusOfPrep = sqlite3_prepare_v2(db, "SELECT food.name, food.type, food.price FROM food ORDER BY food.type", -1, &myStatement, NULL);
        if (statusOfPrep == SQLITE_OK) {
            string fName, fType;
            int fPrice;
            int statusOfStep = sqlite3_step(myStatement);
            while (statusOfStep == SQLITE_ROW) {
                fName = (char*)sqlite3_column_text(myStatement, 0);
                fType = (char*)sqlite3_column_text(myStatement, 1);
                fPrice = sqlite3_column_int(myStatement, 2);
                cout << "---------------------------" << endl;

                cout << "Food name : " << fName << endl;
                cout << "Food type : " << fType << endl;
                cout << "Food price : " << fPrice << " Rupees" << endl;
                statusOfStep = sqlite3_step(myStatement);

            }

            sqlite3_finalize(myStatement);
        }
        else {
            cout << "Error Preparing select statement" << endl;
        }
        sqlite3_close(db);
    }
    else {
        cout << "Error in opening of database" << endl;
    }
}

//all income report
void ledger() {

    int employee_choice;
label_6:
    cout << "\t\t\t------------------------------------------------------------" << endl;
    cout << "\t\t\t                            LEDGER                          " << endl;
    cout << "\t\t\t------------------------------------------------------------" << endl;
    cout << "\t\t\t  1)  Room Income                                           " << endl;
    cout << "\t\t\t  2)  Food Income                                           " << endl;
    cout << "\t\t\t  3)  Total Income                                          " << endl;
    cout << "\t\t\t  4)  Back                                                  " << endl;
    cin >> employee_choice;
    switch (employee_choice) {
    case 1:
        room_income();
        break;
    case 2:
        food_income();
        break;
    case 3:
        total_income();
    case 4:
        employee_menue();
    default:
        cout << "Please enter valid input" << endl;
    }
    goto label_6;
}



void room_income() {
    sqlite3* db;
    int statusOfOpen = sqlite3_open(database.c_str(), &db);
    if (statusOfOpen == SQLITE_OK) {
        sqlite3_stmt* myStatement;
        string proName;
        int proQuantity, proIncome, proPrice, totalIncome = 0;
        int statusOfPrep = sqlite3_prepare_v2(db, "SELECT name, quantity, amount from income WHERE dept = 'room'", -1, &myStatement, NULL);
        if (statusOfPrep == SQLITE_OK) {
            int statusOfStep = sqlite3_step(myStatement);
            while (statusOfStep == SQLITE_ROW) {
                proName = (char*)sqlite3_column_text(myStatement, 0);
                proQuantity = sqlite3_column_int(myStatement, 1);
                proPrice = sqlite3_column_int(myStatement, 2);
                proIncome = proPrice * proQuantity;
                totalIncome = totalIncome + proIncome;
                cout << "---------------------------" << endl;
                cout << "Room Name : " << proName << endl;
                cout << "Nights : " << proQuantity << " nights" << endl;
                cout << "Price : " << proPrice <<" Rs / night" << endl;
                cout << "Income : " << proIncome << " Rs" << endl;
                statusOfStep = sqlite3_step(myStatement);
            }

            cout << "\n------------------------------------------" << endl;
            cout << "Total Income : " << totalIncome << " Rs" << endl;
            cout << "------------------------------------------\n\n" << endl;

            sqlite3_finalize(myStatement);
        }
        else {
            cout << "Error preparing select statement" << endl;
        }
        sqlite3_close(db);
    }
    else {
        cout << "Error in opening of database" << endl;
    }
}


void food_income() {
    sqlite3* db;
    int statusOfOpen = sqlite3_open(database.c_str(), &db);
    if (statusOfOpen == SQLITE_OK) {
        sqlite3_stmt* myStatement;
        string proName;
        int proQuantity, proIncome,proPrice, totalIncome = 0;
        int statusOfPrep = sqlite3_prepare_v2(db, "SELECT name, quantity, amount from income WHERE dept = 'food' ", -1, &myStatement, NULL);
        if (statusOfPrep == SQLITE_OK) {
            int statusOfStep = sqlite3_step(myStatement);
            while (statusOfStep == SQLITE_ROW) {
                proName = (char*)sqlite3_column_text(myStatement, 0);
                proQuantity = sqlite3_column_int(myStatement, 1);
                proPrice = sqlite3_column_int(myStatement, 2);
                proIncome = proPrice * proQuantity;
                totalIncome = totalIncome + proIncome;
                cout << "---------------------------" << endl;
                cout << "Food Name : " << proName << endl;
                cout << "Quantity : " << proQuantity << endl;
                cout << "price : " << proPrice << " Rs" << endl;
                cout << "Income : " << proIncome << " Rs" << endl;

                statusOfStep = sqlite3_step(myStatement);
            }

            cout << "\n------------------------------------------" << endl;
            cout << "Total Income : " << totalIncome <<" Rs" << endl;
            cout << "------------------------------------------\n\n" << endl;
            

            sqlite3_finalize(myStatement);
        }
        else {
            cout << "Error preparing select statement" << endl;
        }
        sqlite3_close(db);
    }
    else {
        cout << "Error in opening of database" << endl;
    }
}

void total_income() {
    sqlite3* db;
    int statusOfOpen = sqlite3_open(database.c_str(), &db);
    if (statusOfOpen == SQLITE_OK) {
        sqlite3_stmt* myStatement;
        int statusOfPrep = sqlite3_prepare_v2(db, "CREATE TABLE IF NOT EXISTS income(name TEXT, quantity INTEGER, amount INTEGER, dept TEXT)", -1, &myStatement, NULL);
        if (statusOfPrep == SQLITE_OK) {
            int statusOfStep = sqlite3_step(myStatement);
            if (statusOfStep == SQLITE_DONE) {
                cout << "Successfully accessed income table" << endl;
            }
            else {
                cout << "Error creating income table" << endl;
            }

            sqlite3_finalize(myStatement);
        }
        else {
            cout << "Error preparing create statement" << endl;
        }
        int proQuantity, proIncome, totalIncome = 0;
        statusOfPrep = sqlite3_prepare_v2(db, "SELECT quantity, amount from income", -1, &myStatement, NULL);
        if (statusOfPrep == SQLITE_OK) {
            int statusOfStep = sqlite3_step(myStatement);
           
            while (statusOfStep == SQLITE_ROW) {
               
                proQuantity = sqlite3_column_int(myStatement, 0);
                proIncome = sqlite3_column_int(myStatement, 1);
                totalIncome = totalIncome + proIncome * proQuantity;
                                
                statusOfStep = sqlite3_step(myStatement);
            }
            cout << "\n------------------------------------------" << endl;
            cout << "Total Income : " << totalIncome <<" Rs" << endl;
            cout << "------------------------------------------" << endl;


            sqlite3_finalize(myStatement);
        }
        else {
            cout << "Error preparing select statement" << endl;
        }
        sqlite3_close(db);
    }
    else {
        cout << "Error in opening of database" << endl;
    }
}

//guest menue
void guest_menue() {
    int guest_choice;
label_7:
    cout << "\t\t\t------------------------------------------------------------" << endl;
    cout << "\t\t\t                    Welcome To Saad's Hotel                 " << endl;
    cout << "\t\t\t------------------------------------------------------------" << endl;
    cout << "\t\t\t  1)  Book Room                                             " << endl;
    cout << "\t\t\t  2)  Order Food                                            " << endl;
    cout << "\t\t\t  3)  Back                                                  " << endl;
    cin >> guest_choice;
    switch (guest_choice) {
    case 1:
        book_room();
        break;
    case 2:
        order_food();
        break;
    case 3:
        main_menue();
    default:
        cout << "Please enter valid input" << endl;
    }
    goto label_7;

}

void book_room() {

    sqlite3* db;
    int statusOfOpen = sqlite3_open(database.c_str(), &db);
    if (statusOfOpen == SQLITE_OK) {

        //taking no. of guest and fetching all room with or greater guest capacity  

        int roomId, roomSize, roomCapacity, roomPrice, noOfGuest;
        string roomName, roomDiscription, roomBedSize;
    label_10:
        cout << "Number of Guest : " << endl;
        cin >> noOfGuest;

        if (noOfGuest > 0) {
            sqlite3_stmt* myStatement;
            int statusOfPrep = sqlite3_prepare_v2(db, "SELECT room.id, room.name, room.capacity, room.price, room.roomsize, room.bedsize, room.discription FROM room WHERE room.capacity >= (?) ORDER BY room.capacity", -1, &myStatement, NULL);
            sqlite3_bind_int(myStatement, 1, noOfGuest);
            if (statusOfPrep == SQLITE_OK) {
                int statusOfStep = sqlite3_step(myStatement);
                cout << "\n\n+---------------------------AVAILABLE ROOMS---------------------------+" << endl;
                if (statusOfStep != SQLITE_ROW) {
                    cout << "No room available" << endl;
                    return;
                }
                else {
                    while (statusOfStep == SQLITE_ROW) {
                        roomId = sqlite3_column_int(myStatement, 0);
                        roomName = (char*)sqlite3_column_text(myStatement, 1);
                        roomCapacity = sqlite3_column_int(myStatement, 2);
                        roomPrice = sqlite3_column_int(myStatement, 3);
                        roomSize = sqlite3_column_int(myStatement, 4);
                        roomBedSize = (char*)sqlite3_column_text(myStatement, 5);
                        roomDiscription = (char*)sqlite3_column_text(myStatement, 6);

                        cout << "Room id : " << roomId << "\tName : " << roomName << endl;
                        cout << "\t\tcapacity : " << roomCapacity << " guests" << endl;
                        cout << "\t\tprice : " << roomPrice << " rupees / night" << endl;
                        cout << "\t\tsize : " << roomSize << " sq mt" << endl;
                        cout << "\t\tBed size : " << roomBedSize << " size" << endl;
                        cout << "\t\tDiscription: " << roomDiscription << endl;
                        cout << "---------------------------+" << endl;

                        statusOfStep = sqlite3_step(myStatement);
                    }
                }
                cout << "+-----------------------------------------------------------------------+\n\n" << endl;
                sqlite3_finalize(myStatement);
            }
            else {
                cout << "Error preparing select statement" << endl;
            }

            //To accept customer choice room id and accept number of night 
            int crId = 0, numberOfNight, customerChoice;

        label_11:
            cout << "\nEnter 0 to retrun back or 1 to continue :  " << endl;
            cin >> customerChoice;
            if (customerChoice == 0) {
                return;
            }
            cout << "Enter room id : " << endl;
            cin >> crId;
            cout << "Number of night : " << endl;
            cin >> numberOfNight;

            int crPrice;
            string crName;

            //fetching information about selected room 
            
            statusOfPrep = sqlite3_prepare_v2(db, "SELECT room.name, room.price FROM room WHERE room.id = (?)", -1, &myStatement, NULL);
            sqlite3_bind_int(myStatement, 1, crId);
            if (statusOfPrep == SQLITE_OK) {
                int statusOfStep = sqlite3_step(myStatement);
                if (statusOfStep == SQLITE_ROW) {
                    crName = (char*)sqlite3_column_text(myStatement, 0);
                    crPrice = sqlite3_column_int(myStatement, 1);
                    cout << "\n\n\t+----------------------RECIPT----------------------+\n" << endl;
                    cout << "\tRoom : " << crName << " booked" << endl;
                    cout << "\tPrice : " << crPrice << " rupees / night" << endl;
                    cout << "\tNumber of night : " << numberOfNight << endl;
                    cout << "\tTotal payable amount : " << crPrice * numberOfNight << endl;
                    cout << "\n\t+--------------------------------------------------+\n" << endl;
                }

                else {
                    cout << "No room with room id " << crId << " found" << endl;
                    goto label_11;
                }
                sqlite3_finalize(myStatement);
            }
            else {
                cout << "Error preparing select statement" << endl;
            }

            // Entry to the income table
            string dept = "room";
            
            statusOfPrep = sqlite3_prepare_v2(db, "INSERT INTO income VALUES(?,?,?,?)", -1, &myStatement, NULL);
            sqlite3_bind_text(myStatement, 1, crName.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_int(myStatement, 2, numberOfNight);
            sqlite3_bind_int(myStatement, 3, crPrice);
            sqlite3_bind_text(myStatement, 4, dept.c_str(), -1, SQLITE_STATIC);
            if (statusOfPrep == SQLITE_OK) {
                int statusOfStep = sqlite3_step(myStatement);
                if (statusOfStep == SQLITE_DONE) {
                    //done
                }
                else {
                    cout << "Error inserting values in income table" << endl;
                }
                sqlite3_finalize(myStatement);
            }
            else {
                cout << "Error preparing insert statement" << endl;
            }
        }
        else {
            cout << "Please enter valid number of guests" << endl;
            goto label_10;
        }
        
    }

    else {
        cout << "Error in opening database" << endl;
    }
}



void order_food() {
    sqlite3* db;
    int statusOfOpen = sqlite3_open(database.c_str(), &db);
    if (statusOfOpen == SQLITE_OK) {
        sqlite3_stmt* myStatement;

        //getting food from database for food menue

        string fName;
        int fPrice;
        int statusOfPrep = sqlite3_prepare_v2(db, "SELECT food.name, food.price FROM food ORDER BY food.type", -1, &myStatement, NULL);
        if (statusOfPrep == SQLITE_OK) {
            int statusOfStep = sqlite3_step(myStatement);
            cout << "\n\n+---------------------------MENUE---------------------------+" << endl;
            cout << "\tNAME\t\t\t\t" << "PRICE\n" << endl;
            while (statusOfStep == SQLITE_ROW) {
                fName = (char*)sqlite3_column_text(myStatement, 0);
                fPrice = sqlite3_column_int(myStatement, 1);
                cout << "\t" << fName << "\t\t\t\t" << fPrice << endl;
                statusOfStep = sqlite3_step(myStatement);
            }
            cout << "+-----------------------------------------------------------+\n\n" << endl;
            sqlite3_finalize(myStatement);
        }
        else {
            cout << "Error preparing select statement " << endl;
        }
        
        //taking user input 

        int n = 0, user_choice;
        string cfName, cfName_arr[10];
        int cfQuantity, cfQuantity_arr[10]={ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },cfPrice_arr[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        cout << "\nEnter 0 to retrun back or 1 to continue :  " << endl;
        cin >> user_choice;
        if (user_choice == 0) {
            return;
        }
        while (user_choice) {
            if (n == 10) {
                cout << "You can only order 10 item at a time" << endl;
                break;
            }
            cout << "Enter Food name : " << endl;
            cin >> cfName;
            cout << "Enter Quantity : " << endl;
            cin >> cfQuantity;
            statusOfPrep = sqlite3_prepare_v2(db, "SELECT food.price FROM food WHERE food.name=(?)", -1, &myStatement, NULL);
            sqlite3_bind_text(myStatement, 1, cfName.c_str(), -1, SQLITE_STATIC);
            if (statusOfPrep == SQLITE_OK) {
                int statusOfStep = sqlite3_step(myStatement);
                if (statusOfStep == SQLITE_ROW) {
                    cfPrice_arr[n] = sqlite3_column_int(myStatement, 0);
                    cfQuantity_arr[n] = cfQuantity;
                    cfName_arr[n] = cfName;
                    cout <<cfQuantity<<" " << cfName << " ordered." << endl;
                }
                else {
                    cout << cfName << " is not available." << endl;
                    n--;//to neutralize on failure
                }
                sqlite3_finalize(myStatement);
            }
            else {
                cout << "Error preparing user input select statement" << endl;
            }
            cout << "For recipt press 0 or to continue press 1" << endl;
            cin >> user_choice;
            n++;
        }
        //entry to the income table
        n = 0;
        
        string dept = "food";   //dept used in food income function

        while (cfPrice_arr[n]) {
            if (n == 10) {
                break;
            }
            statusOfPrep = sqlite3_prepare_v2(db, "INSERT INTO income VALUES(?,?,?,?)", -1, &myStatement, NULL);
            sqlite3_bind_text(myStatement, 1, cfName_arr[n].c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_int(myStatement, 2, cfQuantity_arr[n]);
            sqlite3_bind_int(myStatement, 3, cfPrice_arr[n]);
            sqlite3_bind_text(myStatement, 4, dept.c_str(), -1, SQLITE_STATIC);
            if (statusOfPrep == SQLITE_OK) {
                int statusOfStep = sqlite3_step(myStatement);
                if (statusOfStep == SQLITE_DONE) {
                    //for debugging
                    //cout << cfName_arr[n] << " inserted" << endl;

                }
                else {
                    cout << "Error inserting in income table" << endl;
                }
                sqlite3_finalize(myStatement);
            }
            else {
                cout << "Error preparing insert statement" << endl;
            }
            n++;
        }

        //print recipt for order above
        n = 0;
        int cfTotal=0;
        if (cfPrice_arr[n]) {
            cfTotal = cfTotal + cfPrice_arr[n] * cfQuantity_arr[n];
            cout << "\n\n\t+----------------------RECIPT----------------------+" << endl;
            cout << "\t  NAME\t\t" << "PRICE\t\t" << "QUANTITY\n" << endl;
            while (cfPrice_arr[n]) {
                cout << "\t " << cfName_arr[n] << "\t\t" << cfPrice_arr[n] << " Rs" << "\t\t" << cfQuantity_arr[n] << endl;
                n++;
            }
            n = 0;

            cout << "\t+--------------------------------------------------+" << endl;
            cout << "\n\nGrand Total : " << cfTotal << " Rs" << "\n\n" << endl;

        }
        else{
            cout << "No food selected" << endl;
        }


        sqlite3_close(db);
    }
    else {
        cout << "Error in opening database" << endl;
    }
}


int main() {
    main_menue();



    //sqlite3_close(db);
}