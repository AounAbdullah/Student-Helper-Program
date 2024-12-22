#include <iostream>
#include "Plagiarism_detector.h"
#include "budget_manager_2023049.h"
#include "Time_Manager_Main.h>

using namespace std;

void displayMainMenu() {
    cout << "Student Helper Program\n";
    cout << "1. Budget Manager\n";
    cout << "2. Plagiarism Detector\n";
    cout << "3. Time Manager\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    int choice;
    do {
        displayMainMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                budgetMenu();  // Function from budget_manager_2023049.cpp
                break;
            case 2:
                plagiarismMenu();  // Function from Plagiarism_detector.cpp
                break;
            case 3:
                timeManagerMenu();  // Function from Time_Manager_Main.cpp
                break;
            case 4:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
