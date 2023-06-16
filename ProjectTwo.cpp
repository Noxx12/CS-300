//Kelly Perez Project Two

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Course {
    string code;
    string title;
    vector<string> prerequisites;
};

void loadDataStructure(const string& fileName, unordered_map<string, Course>& dataStructure) {
    // Open the file
    ifstream file(fileName);
    if (file.is_open()) {
        string line;
        // Read each line from the file
        while (getline(file, line)) {
            istringstream iss(line);

            string courseCode;
            getline(iss, courseCode, ',');

            string courseTitle;
            getline(iss, courseTitle, ',');

            Course course;
            course.code = courseCode;
            course.title = courseTitle;

            string prerequisiteCode;
            // Read each prerequisite code from the line
            while (getline(iss, prerequisiteCode, ',')) {
                if (!prerequisiteCode.empty()) {
                    course.prerequisites.push_back(prerequisiteCode);
                }
            }

            // Add the course to the data structure
            dataStructure[courseCode] = course;
        }
        // Close the file
        file.close();
        cout << "Data structure loaded successfully." << endl;
    }
    else {
        cout << "Failed to open file: " << fileName << endl;
    }
}

void printCourseList(const unordered_map<string, Course>& dataStructure) {
    // Iterate over the courses in the data structure and print their codes and titles
    for (const auto& coursePair : dataStructure) {
        const Course& course = coursePair.second;
        cout << course.code << ", " << course.title << endl;
    }
}

void printCourse(const unordered_map<string, Course>& dataStructure, const string& courseCode) {
    string lowerCourseCode = courseCode;
    // Convert the course code to lowercase for case-insensitive comparison
    transform(lowerCourseCode.begin(), lowerCourseCode.end(), lowerCourseCode.begin(), [](unsigned char c) {
        return tolower(c);
        });

    // Find the course with the matching code in the data structure
    auto it = find_if(dataStructure.begin(), dataStructure.end(), [&](const auto& coursePair) {
        string lowerCode = coursePair.first;
        // Convert the course code from the data structure to lowercase for comparison
        transform(lowerCode.begin(), lowerCode.end(), lowerCode.begin(), [](unsigned char c) {
            return tolower(c);
            });
        return lowerCode == lowerCourseCode;
        });

    if (it != dataStructure.end()) {
        const Course& course = it->second;
        cout << course.code << ", " << course.title << endl;
        cout << "Prerequisites:";
        if (course.prerequisites.empty()) {
            cout << " None";
        }
        else {
            for (const string& prerequisite : course.prerequisites) {
                cout << " " << prerequisite;
            }
        }
        cout << endl;
    }
    else {
        cout << "Course not found." << endl;
    }
}

int main() {
    unordered_map<string, Course> dataStructure;
    // Load the initial data structure from the file
    loadDataStructure("course.txt", dataStructure);

    cout << "Welcome to the course planner." << endl;
    int option = 0;
    while (option != 9) {
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";
        cin >> option;

        if (option == 1) {
            // Reload the data structure from the file
            loadDataStructure("course.txt", dataStructure);
        }
        else if (option == 2) {
            // Print the list of courses in the data structure
            printCourseList(dataStructure);
        }
        else if (option == 3) {
            cout << "Enter course code: ";
            string courseCode;
            cin >> courseCode;
            // Print the details of a specific course
            printCourse(dataStructure, courseCode);
        }
    }

    return 0;
}
