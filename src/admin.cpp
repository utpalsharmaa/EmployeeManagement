#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <iomanip>
#include<random>
#include<regex>
#include <exception>
#include "/Users/UT20449257/Desktop/EmpManagement/include/admin.h"

using namespace std;
int loginCount = 0;
void Employee::adminLogin()
{
    string userId = "utpal";
    string password = "12345";
    string id, pass;
    cout << "\n═══════════════════════════════════════════════════════" << endl;
    cout << "            Welcome to Employee Management System          " << endl;
    cout << "═══════════════════════════════════════════════════════\n" << endl;
    cout << "\n\nPlease Enter Your Username & Password For Authentiocation" << endl;

    try
    {
        cout << "\nEnter Your Username : ";
        cin >> id;

        cout << "\nEnter Your Password : ";
        cin >> pass;

        while (id != userId || pass != password)
        {
            cout << "\n!!!Login Error!!!" << endl;
            cout << "Please check your username or password again\n"
                 << endl;

            loginCount++;
            if (loginCount == 3)
            {
                cout << "ACCESS DENIED" << endl;
                cout << "You have reached your limit." << endl;
                exit(1);
            }

            cout << "\nEnter Your Username : ";
            cin >> id;
            cout << "\nEnter Your Password : ";
            cin >> pass;
        }
    }

    catch (exception &ex)
    {
        cerr << "Exception caught: " << ex.what() << endl;
    }

    cout << "\nCongratulations " << userId << endl;
    cout << "Your login as an administrator is successful.\n"
         << endl;
    adminDashboard();
}


void Employee::adminDashboard()
{
    try
    {
    cout << "\n═══════════════════════════════════════════════════════" << endl;
    cout << "            Employee Management System Dashboard          " << endl;
    cout << "═══════════════════════════════════════════════════════\n" << endl;
        cout << "\tEnter 1  To Add New Employee" << endl;
        cout << "\tEnter 2  To Display Employee details" << endl;
        cout << "\tEnter 3  To Search for Employee" << endl;
        cout << "\tEnter 4  To Update Employee Information" << endl;
        cout << "\tEnter 5  To Removing employee" << endl;
        cout << "\tEnter 6  To Quit From This Session" << endl;
        cout << "\n═══════════════════════════════════════════════════════" << endl;

        int choice;
        cout << "\n\nPlease enter your choice : ";
        cin >> choice;

        while (cin.fail() || choice < 1 || choice > 6)
        {
            cin.clear();
            cin.ignore(512, '\n');
            cout << "\nInvalid input. Please enter a number between 1 and 6: ";
            cin >> choice;
        }
        switch (choice)
        {
        case 1:
            AddEmployee();
            adminDashboard();
            break;
            
        case 2:
            DisplayEmployee();
            adminDashboard();
            break;
        case 3:
            SearchEmployee();
            adminDashboard();
            break;
        case 4:
            UpdateEmployee();
            adminDashboard();
            break;
        case 5:
            RemoveEmployee();
            adminDashboard();
            break;
        case 6:
            cout << "Thank you, will see you soon." << endl;
            break;

        default:
            cout << "Please choose valid Option" << endl;
            break;
        }
    }
    catch (exception &ex)
    {
        cerr << "Exception caught: " << ex.what() << endl;
    }
}

bool isValidPhoneNumber(const string &phoneNumber)
{
    regex phonePattern(R"(\d{10})");
    return regex_match(phoneNumber, phonePattern);
}

bool isValidEmail(const string &email)
{
    regex emailPattern(R"(\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Z|a-z]{2,}\b)");
    return regex_match(email, emailPattern);
}

bool isValidDate(const string &date)
{
    regex datePattern(R"(\d{2}-\d{2}-\d{2})"); // Assuming format is MM-DD-YY
    return regex_match(date, datePattern);
}

void Employee::AddEmployee() {
    try {
        random_device rd; // Initialize random device
        mt19937 gen(rd()); // Seed the random number generator
        uniform_int_distribution<int> dist(1000, 9999); // Define the range

        EmpID = dist(gen); // Gen
        cin.ignore(256, '\n');

        cout << "Enter employee first name: ";
        cin >> firstName;
        firstName[0] = toupper(firstName[0]);


        cout << "Enter employee last name: ";
        cin >> lastName;
        lastName[0] = toupper(lastName[0]);
        cin.ignore(256, '\n');
        cout << "Enter employee email: ";
        cin >> email;
        while (!isValidEmail(email)) {
            cout << "Invalid email format. Please enter a valid email: ";
            cin >> email;
        }
        cout << "Enter employee phone number: ";
        cin >> phoneNo;
        while (!isValidPhoneNumber(phoneNo)) {
            cout << "Invalid phone number format. Please enter a valid phone number: ";
            cin >> phoneNo;
        }
        cout << "Enter employee hire date (MM-DD-YY): ";
        cin >> hireDate;
        while (!isValidDate(hireDate)) {
            cout << "Invalid date format. Please enter a valid date (MM-DD-YY): ";
            cin >>hireDate;
        }

        cout << "Enter employee salary: ";
        while (!(cin >> salary) || cin.peek() != '\n') {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Invalid input. Please enter a valid Salary: ";
        }
        cin.ignore(256, '\n');

        ofstream f1("//Users/UT20449257/Desktop/EmpManagement/data/Employee_data.csv", ios::app);

        f1 << EmpID << ", " << firstName << ", " << lastName << ", " << email << ", " << phoneNo << ", " << hireDate << ", " << salary << endl;

        cout << "\nEmployee record has been added successfully.\n" << endl;

        string opt;
        cout << "\nDo you want to add another employee details (yes/no) : ";
        cin >> opt;

        while (true) {
            transform(opt.begin(), opt.end(), opt.begin(), ::tolower);

            if (opt == "yes") {
                AddEmployee();
                break;
            } else if (opt == "no") {
                // adminModules(); // Replace this with appropriate function call
                break;
            } else {
                cout << "Invalid input. Please enter 'yes' or 'no': ";
                cin >> opt;
            }
        }
    } catch (exception &ex) {
        cerr << "Exception caught: " << ex.what() << endl;
    }
}

void Employee::DisplayEmployee() {
    try {
        ifstream file("/Users/UT20449257/Desktop/EmpManagement/data/Employee_data.csv");
        if (!file.is_open()) {
            throw runtime_error("Error opening file: Employee_data.csv");
        }

        cout << "Below are the list of employees" << endl;

        cout << setw(10) << "Emp ID" << setw(20) << "First Name" << setw(20) << "Last Name"
             << setw(30) << "Email" << setw(15) << "Phone No" << setw(15) << "Hire Date"
             << setw(15) << "Salary" << endl;

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string empId, firstName, lastName, email, phoneNo, hireDate, salary;

            getline(ss, empId, ',');
            getline(ss, firstName, ',');
            getline(ss, lastName, ',');
            getline(ss, email, ',');
            getline(ss, phoneNo, ',');
            getline(ss, hireDate, ',');
            getline(ss, salary, ',');

            // Output each column with appropriate formatting
            cout << setw(10) << empId << setw(20) << firstName << setw(20) << lastName
                 << setw(30) << email << setw(15) << phoneNo << setw(15) << hireDate
                 << setw(15) << salary << endl;
        }
        file.close();

        string choice;

        cout << "\nDo you want to continue with the session (yes/no): ";
        cin >> choice;

        // Input validation for choice
        while (true) {
            transform(choice.begin(), choice.end(), choice.begin(), ::tolower);

            if (choice == "yes") {
                // Call the appropriate function for further actions
                // adminModules();
                break;
            } else if (choice == "no") {
                cout << "See you again" << endl;
                break;
            } else {
                cout << "Invalid input. Please enter 'yes' or 'no': ";
                cin >> choice;
            }
        }
    } catch (const exception &ex) {
        cerr << "Exception caught: " << ex.what() << endl;
    }
}

 // Include the necessary header for setw

void Employee::SearchEmployee() {
    try {
        int searchEmpID;
        cout << "Enter the Employee ID to search: ";
        while (!(cin >> searchEmpID) || cin.peek() != '\n') {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Invalid input. Please enter a valid Employee ID: ";
        }
        cin.ignore(256, '\n');

        ifstream file("/Users/UT20449257/Desktop/EmpManagement/data/Employee_data.csv");
        if (!file.is_open()) {
            throw runtime_error("Error opening file: Employee_data.csv");
        }

        bool found = false;
        cout << "Below are the details of the employee with Emp ID " << searchEmpID << endl;

        cout << setw(10) << "Emp ID" << setw(20) << "First Name" << setw(20) << "Last Name"
             << setw(30) << "Email" << setw(15) << "Phone No" << setw(15) << "Hire Date"
             << setw(15) << "Salary" << endl;

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string empId, firstName, lastName, email, phoneNo, hireDate, salary;

            getline(ss, empId, ',');
            getline(ss, firstName, ',');
            getline(ss, lastName, ',');
            getline(ss, email, ',');
            getline(ss, phoneNo, ',');
            getline(ss, hireDate, ',');
            getline(ss, salary, ',');

            int empID = stoi(empId);
            if (empID == searchEmpID) {
                found = true;

                // Output each column with appropriate formatting
                cout << setw(10) << empId << setw(20) << firstName << setw(20) << lastName
                     << setw(30) << email << setw(15) << phoneNo << setw(15) << hireDate
                     << setw(15) << salary << endl;

                break; // Found the employee, exit the loop
            }
        }
        file.close();

        if (!found) {
            cout << "Employee with ID " << searchEmpID << " not found." << endl;
        }

        string choice;

        cout << "\nDo you want to continue with the session (yes/no): ";
        cin >> choice;

        // Input validation for choice
        while (true) {
            transform(choice.begin(), choice.end(), choice.begin(), ::tolower);

            if (choice == "yes") {
                // Call the appropriate function for further actions
                // adminModules();
                break;
            } else if (choice == "no") {
                cout << "See you again" << endl;
                break;
            } else {
                cout << "Invalid input. Please enter 'yes' or 'no': ";
                cin >> choice;
            }
        }
    } catch (const exception &ex) {
        cerr << "Exception caught: " << ex.what() << endl;
    }
}


void Employee::UpdateEmployee() {
    try {
        int searchEmpID;
        cout << "Enter the Employee ID of the employee to update data: ";
        while (!(cin >> searchEmpID) || cin.peek() != '\n') {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Invalid input. Please enter a valid Employee ID: ";
        }
        cin.ignore(256, '\n');

        ifstream inputFile("/Users/UT20449257/Desktop/EmpManagement/data/Employee_data.csv");
        ofstream tempFile("/Users/UT20449257/Desktop/EmpManagement/data/temp.csv");

        bool found = false;
        string line;

        while (getline(inputFile, line)) {
            stringstream ss(line);
            string column;
            int empID;

            getline(ss, column, ',');
            empID = stoi(column);

            if (empID == searchEmpID) {
                found = true;

                cout << "Employee found with ID " << searchEmpID << ". Please enter updated data:" << endl;
cout << "Enter employee first name: ";
        cin >> firstName;
        firstName[0] = toupper(firstName[0]);


        cout << "Enter employee last name: ";
        cin >> lastName;
        lastName[0] = toupper(lastName[0]);
        cin.ignore(256, '\n');
        cout << "Enter employee email: ";
        cin >> email;
        while (!isValidEmail(email)) {
            cout << "Invalid email format. Please enter a valid email: ";
            cin >> email;
        }
        cout << "Enter employee phone number: ";
        cin >> phoneNo;
        while (!isValidPhoneNumber(phoneNo)) {
            cout << "Invalid phone number format. Please enter a valid phone number: ";
            cin >> phoneNo;
        }
        cout << "Enter employee hire date (MM-DD-YY): ";
        cin >> hireDate;
        while (!isValidDate(hireDate)) {
            cout << "Invalid date format. Please enter a valid date (MM-DD-YY): ";
            cin >>hireDate;
        }

        cout << "Enter employee salary: ";
        while (!(cin >> salary) || cin.peek() != '\n') {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Invalid input. Please enter a valid Salary: ";
        }
                cin.ignore(256, '\n');

                // Write the updated data to temp file
                tempFile << empID << ", " << firstName << ", " << lastName << ", " << email << ", " << phoneNo << ", " << hireDate << ", " << salary << endl;
            } else {
                // Write the original data to temp file
                tempFile << line << endl;
            }
        }

        inputFile.close();
        tempFile.close();

        if (!found) {
            cout << "Employee with ID " << searchEmpID << " not found." << endl;
        } else {
            // Rename the temp file to replace the original file
            remove("/Users/UT20449257/Desktop/EmpManagement/data/Employee_data.csv");
            rename("/Users/UT20449257/Desktop/EmpManagement/data/temp.csv", "/Users/UT20449257/Desktop/EmpManagement/data/Employee_data.csv");
            cout << "Employee data updated successfully." << endl;
        }

        string opt;
        cout << "\nDo you want to update another employee details (yes/no) : ";
        cin >> opt;

        // Input validation for opt
        while (true) {
            transform(opt.begin(), opt.end(), opt.begin(), ::tolower);

            if (opt == "yes") {
                UpdateEmployee();
                break;
            } else if (opt == "no") {
                // adminModules(); // Replace with appropriate function call
                break;
            } else {
                cout << "Invalid input. Please enter 'yes' or 'no': ";
                cin >> opt;
            }
        }
    } catch (exception &ex) {
        cerr << "Exception caught: " << ex.what() << endl;
    }
}


void Employee::RemoveEmployee() {
    try {
        int searchEmpID;
        cout << "Enter the Employee ID of the employee to delete data: ";
        while (!(cin >> searchEmpID) || cin.peek() != '\n') {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Invalid input. Please enter a valid Employee ID: ";
        }
        cin.ignore(256, '\n');

        ifstream inputFile("/Users/UT20449257/Desktop/EmpManagement/data/Employee_data.csv");
        ofstream tempFile("/Users/UT20449257/Desktop/EmpManagement/data/temp.csv");

        bool found = false;
        string line;

        while (getline(inputFile, line)) {
            stringstream ss(line);
            string column;
            int empID;

            getline(ss, column, ',');
            empID = stoi(column);

            if (empID == searchEmpID) {
                found = true;
                cout << "Employee found with ID " << searchEmpID << ". Data deleted." << endl;
            } else {
                // Write the original data to temp file
                tempFile << line << endl;
            }
        }

        inputFile.close();
        tempFile.close();

        if (!found) {
            cout << "Employee with ID " << searchEmpID << " not found." << endl;
        } else {
            // Rename the temp file to replace the original file
            remove("/Users/UT20449257/Desktop/EmpManagement/data/Employee_data.csv");
            rename("/Users/UT20449257/Desktop/EmpManagement/data/temp.csv", "/Users/UT20449257/Desktop/EmpManagement/data/Employee_data.csv");
            cout << "Employee data deleted successfully." << endl;
        }
    } catch (exception &ex) {
        cerr << "Exception caught: " << ex.what() << endl;
    }
}
