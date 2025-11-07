#include<iostream>
#include<vector>
#include <iomanip> 
#include<fstream>
#include<limits>
#include <sstream>

//#include<variant>to use diff datatypes in single variable

using namespace std;

//class
class student_data{
    public:
  string name;
  int roll_no;
  float marks;
};
//Functions
//Input fuction
void inputData(vector<student_data>& students, int totalStudents){
    student_data s;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer from menu
    for(int i=0; i<totalStudents; i++){
        cout << "Enter Student name " << i+1 << " : ";
        getline(cin, s.name);  // full name with spaces
        
        // Safe input for roll number
        while (true) {
            cout << "Enter Student Roll No " << s.name << " : ";
            if (cin >> s.roll_no) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // IMPORTANT: clear after reading
                break;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Roll No must be a number.\n";
        }
        // Safe input for marks
        while (true) {
            cout << "Enter Student Marks " << s.name << " : ";
            if (cin >> s.marks) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // IMPORTANT: clear after reading
                break;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Marks must be a number.\n";
        }
        students.push_back(s);
    }
}

//Display outPut Functions
void displayData(const vector<student_data>& students){
     cout << left << setw(12) << "Name"
         << setw(12) << "Roll No"
         << setw(12) << "Marks" << endl;
    cout << "--------------------------------------" << endl;

    for (const auto& s : students) {
        cout << left << setw(12) << s.name
             << setw(12) << s.roll_no
             << setw(12) << s.marks << endl;
    }
}
// Function to calculate average marks
float calculateAverage(const vector<student_data>& students) {
    float total = 0;
    for (const auto& s : students) {
        total += s.marks;
    }
    return students.empty() ? 0 : total / students.size();
}

// Function to find highest marks
void highestMarks(const vector<student_data>& students) {
    if (students.empty()) {
        cout << "\nNo data available.\n";
        return;
    }

    float maxMarks = students[0].marks;
    string topStudent = students[0].name;

    for (const auto& s : students) {
        if (s.marks > maxMarks) {
            maxMarks = s.marks;
            topStudent = s.name;
        }
    }

    cout << "\nTop Student: " << topStudent << " with " << maxMarks << " marks.\n";
}
//edit data
void editStudent(vector<student_data>& students) {
    int roll;
    cout << "Enter Roll No of student to edit: ";
    cin >> roll;

    bool found = false;
    for (auto& s : students) {
        if (s.roll_no == roll) {
            found = true;
            cout << "\nEditing record for " << s.name << endl;
            cout << "Enter new name: ";
            cin >> s.name;
            cout << "Enter new roll no: ";
            cin >> s.roll_no;
            cout << "Enter new marks: ";
            cin >> s.marks;
            cout << "Record updated successfully!\n";
            break;
        }
    }

    if (!found)
        cout << "No student found with Roll No " << roll << endl;
}
//delete data
void deleteStudent(vector<student_data>& students) {
    int roll;
    cout << "Enter Roll No of student to delete: ";
    cin >> roll;

    bool found = false;
    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->roll_no == roll) {
            found = true;
            cout << "Deleting record of " << it->name << endl;
            students.erase(it);
            cout << "Record deleted successfully!\n";
            break;
        }
    }

    if (!found)
        cout << "No student found with Roll No " << roll << endl;
}


//Saving to file 
void saveToFile(const vector<student_data>& students) {
    ofstream file("students.txt");

    if (!file) {
        cerr << "Error opening file for writing!\n";
        return;
    }

    for (const auto& s : students) {
        file << s.name << " " << s.roll_no << " " << s.marks << endl;
    }

    file.close();
    cout << "\nData successfully saved to 'students.txt'\n";
}
//load file 
void loadFromFile(vector<student_data>& students) {
    ifstream file("students.txt");
    if (!file) {
        cout << "No previous data found. Starting fresh...\n";
        return;
    }
    
    student_data s;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string temp;
        getline(ss, s.name, '|');  // Use delimiter
        ss >> s.roll_no >> s.marks;
        students.push_back(s);
    }
    file.close();
}
int main()
{
    vector<student_data> students;

    loadFromFile(students);

    int choice;
    do {
        cout << "\n===== Student Management Menu =====\n";
        cout << "1. Add New Students\n";
        cout << "2. Display All Students\n";
        cout << "3. Show Average Marks\n";
        cout << "4. Show Top Student\n";
        cout << "5. Delete Student Record\n";
        cout << "6. Edit Student Record\n";
        cout << "7. Save & Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

       switch (choice) {
    case 1: {
        int total;
        cout << "Enter number of new students: ";
        cin >> total;
        inputData(students, total);
        break;
    }
    case 2:
        displayData(students);
        break;
    case 3:
        cout << "\nAverage Marks: " << calculateAverage(students) << endl;
        break;
    case 4:
        highestMarks(students);
        break;
    case 5:
        deleteStudent(students);  
        saveToFile(students);
        break;
    case 6:
        editStudent(students);   
        saveToFile(students);
        break;
    case 7:
        saveToFile(students);
        cout << "Exiting program...\n";
        break;
    default:
        cout << "Invalid choice!\n";
}

    } while (choice != 7);

    return 0;
}

