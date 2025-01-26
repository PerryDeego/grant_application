/*
  Name: Grant Application system
  Copyright: UTech Computer Science Student
  Author: D. Perry
  Date: January 14, 2025
  Description: The primary objective of the program is to facilitate the process of applying for grants by students, checking their eligibility based on GPA and tuition shortfall, and summarizing the applications. It allows users to input application details, display summaries of applications, and identify grant awardees based on specific criteria.
Eligibility Criteria for Grant Application:
GPA Requirement:
A student must have a GPA of at least 2.7 to be considered for a grant.
Tuition Shortfall Requirement: The tuition shortfall must not exceed $300,000.
*/

#include <iostream>
#include <vector>
#include <string>
#include <limits> // For std::numeric_limits
#include <cctype> // For std::toupper

using namespace std;

#define VERSION "1.0.0"
const int MAX_STUDENTS = 5000;                // constant for maximum number of students
const int APPLICATION_NUMBER_OFFSET = 1000; // Offset for application number

// Constants for shortfall limits
const float SHORTFALL_LIMIT_1 = 10000;
const float SHORTFALL_LIMIT_2 = 20000;
const float SHORTFALL_LIMIT_3 = 30000;
const float SHORTFALL_LIMIT_4 = 50000;

// Constants for GPA thresholds
const float GPA_THRESHOLD_1 = 2.5;
const float GPA_THRESHOLD_2 = 3.0;
const float GPA_THRESHOLD_3 = 3.5;
const float GPA_THRESHOLD_4 = 3.75;

// Constraints for points toward grants
const int AWARD_POINTS_1 = 20;
const int AWARD_POINTS_2 = 60;
const int AWARD_POINTS_3 = 80;
const int AWARD_POINTS_4 = 100;

void displaySplashScreen() {
    cout << "\033[0;32m"; // Set text color to green
    cout << "\n";
    cout << "==================================================================================\n";
    cout << "   WELCOME TO THE STUDENTS' TUITION GRANTS APPLICATION SYSTEM   \n";
    cout << "==================================================================================\n";
    cout << "    VERSION: " << VERSION << "          \n";
    cout << "    DESCRIPTION: This program checks the criteria for students to receive grants.\n";
    cout << "    AUTHOR: D. Perry          \n";
    cout << "    LICENCE#: D. PERRY DIGITAL ENTERPRISE \n";
    cout << "==================================================================================\n\n\n";
    cout << "Press Enter to continue...\n";
    cout << "\033[0m";                                   // Reset text color
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Wait for user input
}

void displayMenu() {
    cout << "\033[0;32m"; // Set text color to green
    cout << "-----------------------------------------\n";
    cout << "TUITION GRANT APPLICATION SYSTEM\n";
    cout << "-----------------------------------------\n";
    cout << "MENU OPTIONS\n";
    cout << "-----------------------------------------\n";
    cout << "A.  INPUT APPLICATION DETAILS FOR STUDENT\n";
    cout << "B.  DISPLAY SUMMARY OF APPLICATIONS\n";
    cout << "C.  DISPLAY GRANT AWARDEES\n";
    cout << "X.  EXIT\n";
    cout << "-----------------------------------------\n";
    cout << "\033[0m"; // Reset text color
}

void clearScreen() {
    system("clear"); // or system("cls") for Windows
}

float getValidGPA() { // Prompts the user for a valid GPA input
    float gpa;
    while (true) {
        cout << "Enter Student GPA (0.0 - 4.0): ";
        cin >> gpa;
        if (cin.fail() || gpa < 0.0 || gpa > 4.0) {
            cin.clear();                                         // Clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cout << "Invalid GPA. Please enter a value between 0.0 and 4.0.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            return gpa;
        }
    }
}

float getValidShortfall() { // Prompts the user for a valid tuition shortfall input
    float shortfall;
    while (true) {
        cout << "Enter Student Tuition Shortfall ($): ";
        cin >> shortfall;
        if (cin.fail() || shortfall < 0) {
            cin.clear();                                         // Clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cout << "Invalid shortfall. Please enter a non-negative value.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            return shortfall;
        }
    }
}

int main() {
    // Call the splash screen function
    displaySplashScreen();

    vector<int> points_1(MAX_STUDENTS), points_2(MAX_STUDENTS), total_points(MAX_STUDENTS);
    vector<string> studentName(MAX_STUDENTS);
    vector<string> status(MAX_STUDENTS);
    vector<float> GPA(MAX_STUDENTS);
    vector<float> shortfall(MAX_STUDENTS);

    int index = 0, curr_num_records = 0; // Loop variables
    char selection;                      // Switch input

    // Main program logic continues...
    do {
        clearScreen(); // Clear screen
        displayMenu(); // Display the menu

        do {
            cout << "\nEnter your option: ";
            cin >> selection;               // Read user input
            selection = toupper(selection); // Convert to uppercase

            // Check for invalid input
            if (selection != 'A' && selection != 'B' && selection != 'C' && selection != 'X') {
                cout << "Invalid option. Please enter A, B, C, or X.\n";
            }
        } while (selection != 'A' && selection != 'B' && selection != 'C' && selection != 'X');

        switch (selection) {
        case 'A':
            while (index < MAX_STUDENTS) {
                clearScreen();

                cout << "\nNUMBER OF APPLICATIONS PROCESSED: " << curr_num_records << "\n";
                cout << "_______________________________________\n";
                cout << "INPUT APPLICATION DETAILS FOR STUDENT\n";
                cout << "_______________________________________\n\n";

                cout << "Enter Student's Name: ";
                cin.ignore();                      // Clear the newline character from the input buffer
                getline(cin, studentName[index]); // Read the student's name

                // Check if the name is empty
                if (studentName[index].empty()) {
                    cout << "Student name cannot be empty. Please enter a valid name.\n";
                    continue; // Skip to the next iteration to re-enter the name
                }

                GPA[index] = getValidGPA();             // Get a valid GPA
                shortfall[index] = getValidShortfall(); // Get a valid shortfall

                // Assign application number
                curr_num_records++;
                index++;

                char choice;
                cout << "\nDo you want to add another application? [ Y/N ]: ";
                cin >> choice;
                choice = toupper(choice); // Convert to uppercase

                if (choice == 'N') {
                    break;
                }
            }

            if (index >= MAX_STUDENTS) {
                cout << "Maximum number of students reached. Cannot add more applications.\n";
            }

            cout << "\n\nPress Enter to continue...\n";
            cin.ignore();
            cin.get();
            break;

        case 'B': {
            clearScreen();
            // Reset summary variables for this case
            float shortfall_TOTAL = 0;                          // Reset total for summary
            float shortfall_MIN = numeric_limits<float>::max(); // Reset min for summary
            float shortfall_MAX = 0;                            // Reset max for summary

            cout << "__________________________________________\n";
            cout << "\nDISPLAY SUMMARY OF APPLICATIONS\n";
            cout << "__________________________________________\n";
            cout << "CURRENT NUMBER OF STUDENT APPLICATIONS: " << curr_num_records << "\n\n\n";

            if (curr_num_records > 0) {
                for (int index_b = 0; index_b < curr_num_records; index_b++) {
                    shortfall_TOTAL += shortfall[index_b];
                    if (shortfall[index_b] < shortfall_MIN) {
                        shortfall_MIN = shortfall[index_b]; // Update minimum
                    }
                    if (shortfall[index_b] > shortfall_MAX) {
                        shortfall_MAX = shortfall[index_b]; // Update maximum
                    }

                    cout << "\nAPPLICATION NUMBER: UL" << (APPLICATION_NUMBER_OFFSET + index_b) << "\n";
                    cout << "STUDENT NAME: " << studentName[index_b] << "\n";
                    cout << "TUITION SHORTFALL ($): " << shortfall[index_b] << "\n";

                    if (GPA[index_b] < GPA_THRESHOLD_1 || shortfall[index_b] < SHORTFALL_LIMIT_1) {
                        status[index_b] = "REJECTED";
                    } else {
                        status[index_b] = "SHORTLISTED";
                    }
                    cout << "STATUS: " << status[index_b] << "\n";
                }

                float shortfall_AVE = shortfall_TOTAL / curr_num_records; // Calculate average
                
                cout << "\nTOTAL TUITION SHORTFALL ($): " << shortfall_TOTAL << "\n";
                cout << "AVERAGE TUITION SHORTFALL ($): " << shortfall_AVE << "\n";
                cout << "MAXIMUM TUITION SHORTFALL ($): " << shortfall_MAX << "\n";
                cout << "MINIMUM TUITION SHORTFALL ($): " << shortfall_MIN << "\n\n";
            } else {
                cout << "==================================\n";
                cout << "NO APPLICATIONS TO SUMMARIZE\n";
                cout << "==================================\n\n";
                cout << "TOTAL TUITION SHORTFALL ($): 0\n";
                cout << "AVERAGE TUITION SHORTFALL ($): 0\n";
                cout << "MAXIMUM TUITION SHORTFALL ($): 0\n";
                cout << "MINIMUM TUITION SHORTFALL ($): 0\n\n";
            }

            cout << "\n\nPress Enter to continue...\n";
            cin.ignore();
            cin.get();
            clearScreen();
            break;
        }

        case 'C': {
            clearScreen();
            cout << "____________________________\n";
            cout << "\nGRANT AWARDEES RECORDS\n";
            cout << "____________________________\n\n";

            bool hasGrants = false; // Flag to check if there are any grants approved

            for (int index_b = 0; index_b < curr_num_records; index_b++) {
                if (status[index_b] != "REJECTED") {
                    hasGrants = true; // At least one grant is approved

                    if (GPA[index_b] >= GPA_THRESHOLD_1 && GPA[index_b] < GPA_THRESHOLD_2) {
                        points_1[index_b] = AWARD_POINTS_1;
                    } else if (GPA[index_b] >= GPA_THRESHOLD_2 && GPA[index_b] < GPA_THRESHOLD_3) {
                        points_1[index_b] = AWARD_POINTS_2;
                    } else if (GPA[index_b] >= GPA_THRESHOLD_3 && GPA[index_b] < GPA_THRESHOLD_4) {
                        points_1[index_b] = AWARD_POINTS_3;
                    } else if (GPA[index_b] >= GPA_THRESHOLD_4) {
                        points_1[index_b] = AWARD_POINTS_4;
                    }

                    // Check shortfall
                    if (shortfall[index_b] <= SHORTFALL_LIMIT_1) {
                        points_2[index_b] = AWARD_POINTS_4;
                    } else if (shortfall[index_b] > SHORTFALL_LIMIT_1 && shortfall[index_b] <= SHORTFALL_LIMIT_2) {
                        points_2[index_b] = AWARD_POINTS_3;
                    } else if (shortfall[index_b] > SHORTFALL_LIMIT_2 && shortfall[index_b] <= SHORTFALL_LIMIT_3) {
                        points_2[index_b] = AWARD_POINTS_2;
                    } else if (shortfall[index_b] > SHORTFALL_LIMIT_3 && shortfall[index_b] <= SHORTFALL_LIMIT_4) {
                        points_2[index_b] = AWARD_POINTS_1;
                    } else {
                        points_2[index_b] = 0; // No points for shortfall beyond limits
                    }

                    total_points[index_b] = points_1[index_b] + points_2[index_b];

                    cout << "APPLICATION NUMBER: UL" << (APPLICATION_NUMBER_OFFSET + index_b) << "\n";
                    cout << "STUDENT NAME: " << studentName[index_b] << "\n";
                    cout << "POINTS FROM GPA: " << points_1[index_b] << "\n";
                    cout << "POINTS FROM SHORTFALL: " << points_2[index_b] << "\n";
                    cout << "TOTAL ACCUMULATED POINTS: " << total_points[index_b] << "\n\n";

                    if (total_points[index_b] > 160) {
                        cout << "FULL GRANT AWARDED\n\n";
                    } else if (total_points[index_b] > (AWARD_POINTS_3 + AWARD_POINTS_2)) {
                        cout << "GRANT IS ONLY FOR [ 75% ] OF SHORTFALL AWARDED \n\n";
                    } else {
                        cout << "GRANT IS ONLY FOR [ 50% ] OF SHORTFALL AWARDED \n\n";
                    }
                }
            }

            if (!hasGrants) {
                cout << "ZERO GRANTS APPROVED\n\n";
            }

            cout << "\n\nPress Enter to continue...\n";
            cin.ignore();
            cin.get();
            clearScreen();
            break;
        }

        case 'X':
            cout << "\n\n<Exiting Application>\n";
            break;
        }

    } while (selection != 'X'); // Exit loop when sentinel (X) is entered.

    return 0;
}