// mod7 project2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//============================================================================

// mod7 project2.cpp

//author: karol guerra

//description: 

/*

This document outlines all of the courses that the advising team will need you to include in the program
you are developing. Once you start coding, the same information will be provided to you in a text file
that can be used as an input for your program. For now, you only need to understand all of the course
data inputs and will reference them while you create your pseudocode.
Note that the course data is composed of comma-separated values and contains the fields
courseNumber, name, prerequisite1, prerequisite2,...,prerequisiteN. While the courseNumber and
name will be shown on every line, a course may have 0, 1, or more prerequisites. A prerequisite will be
listed using only its courseNumber.*/

//============================================================================


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Course {
    string number;
    string title;
    vector<string> prereqs;
};

vector<Course> courseList;

void loadCourses() {
    ifstream file("ABCU_Advising_Program_Input.txt");
    if (!file) {
        cout << "Error: Could not open file.\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string piece;
        vector<string> data;
        while (getline(ss, piece, ',')) {
            data.push_back(piece);
        }

        Course c;
        c.number = data[0];
        c.title = data[1];
        if (data.size() > 2) {
            c.prereqs.assign(data.begin() + 2, data.end());
        }
        courseList.push_back(c);
    }
    cout << "Data loaded.\n";
}

void listCourses() {
    if (courseList.empty()) {
        cout << "Error: No data loaded.\n";
        return;
    }

    sort(courseList.begin(), courseList.end(),
        [](const Course& a, const Course& b) {
            return a.number < b.number;
        });

    cout << "Here is a sample schedule:\n";
    for (auto& c : courseList) {
        cout << c.number << ", " << c.title << "\n";
    }
}

void showCourse() {
    if (courseList.empty()) {
        cout << "Error: No data loaded.\n";
        return;
    }

    string input;
    cout << "What course do you want to know about? ";
    cin >> input;
    transform(input.begin(), input.end(), input.begin(), ::toupper);

    bool found = false;
    for (auto& c : courseList) {
        if (c.number == input) {
            found = true;
            cout << c.number << ", " << c.title << "\n";
            cout << "Prerequisites: ";
            if (c.prereqs.empty()) {
                cout << "None";
            }
            else {
                for (size_t i = 0; i < c.prereqs.size(); ++i) {
                    cout << c.prereqs[i];
                    if (i < c.prereqs.size() - 1) cout << ", ";
                }
            }
            cout << "\n";
            break;
        }
    }
    if (!found) {
        cout << "Invalid Course. Please try again.\n";
    }
}

int main() {
    bool running = true;
    cout << "Welcome to the course planner.\n";

    while (running) {
        string choice;
        cout << "1. Load Data Structure.\n";
        cout << "2. Print Course List.\n";
        cout << "3. Print Course.\n";
        cout << "9. Exit\n";
        cout << "What would you like to do? ";
        cin >> choice;

        while (choice != "1" && choice != "2" && choice != "3" && choice != "9") {
            cout << choice << " is not a valid option.\n";
            cout << "1. Load Data Structure.\n";
            cout << "2. Print Course List.\n";
            cout << "3. Print Course.\n";
            cout << "9. Exit\n";
            cout << "What would you like to do? ";
            cin >> choice;
        }

        if (choice == "1") loadCourses();
        else if (choice == "2") listCourses();
        else if (choice == "3") showCourse();
        else if (choice == "9") {
            cout << "Thank you for using the course planner!\n";
            running = false;
        }
    }
    return 0;
}
