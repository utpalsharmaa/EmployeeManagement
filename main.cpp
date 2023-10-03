#include <iostream>
#include "/Users/UT20449257/Desktop/EmpManagement/include/admin.h"

using namespace std;

int main()
{
    Employee employee;
    int choice;
    cout << "\n═══════════════════════════════════════════════════════" << endl;
    cout << "            Employee Management System                   " << endl;
    cout << "═══════════════════════════════════════════════════════\n" << endl;
    cout << "\n\t\t Welcome To Home Page" << endl;
    cout << "\n\t\tEnter 1  Login" << endl;
    cout << "\t\tEnter 2  Exit" << endl;
    cout << "\nPlease Enter Your Choice : ";

    try
    {
        // Input validation for choice
        while (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(512, '\n');
            cout << "\nPlease enter a number!!" << endl;
            cout << "\nPlease Enter Your Choice : ";
        }

        switch (choice)
        {
        case 1:
            employee.adminLogin();
            break;
        case 2:
            cout << "See you again." << endl;
            break;
        default:
            cout << "\nPlease select from the options given above" << endl;
            main();
        }
    }
    catch (const std::exception &ex)
    {
        cerr << "Exception caught: " << ex.what() << endl;
    }
    return 0;
}
