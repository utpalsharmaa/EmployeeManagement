#include <iostream>
#include <string>
#include <fstream>

#ifndef ADMIN_H
#define ADMIN_H

using namespace std;

class Employee
{
    int EmpID;
    string firstName;
    string lastName;
    string email;
    string phoneNo;
    string hireDate;
    double salary;

public:
    void adminLogin();
    void adminDashboard();  // handles admin login credentials
    void AddEmployee();     // implements adding employee data functionality into a csv file
    void DisplayEmployee(); // implements updating employee data functionality into a csv file
    void SearchEmployee();   // displays the all contents of a employee data csv file
    void UpdateEmployee();  // Function to search and display employee data from a CSV file
    void RemoveEmployee();  // implements deleting employee data functionality from a csv file
};
#endif // ADMIN_H


