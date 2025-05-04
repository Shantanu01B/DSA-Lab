#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
using namespace std;

const char* fileName = "Employee.txt";

class Employee {
private:
    int EmpID;
    char EmpName[50], Post[50], Department[10];
    float Salary;
public:
    void ReadData();
    int GetID();
    void DisplayRecord();
    char* GetDepartment();
};

void Employee::ReadData() {
    cout << "\nEmployee ID: ";
    cin >> EmpID;
    cout << "Employee Name: ";
    cin >> EmpName;
    cout << "Employee's Post: ";
    cin >> Post;
    cout << "Employee's Department: ";
    cin >> Department;
    cout << "Salary: ";
    cin >> Salary;
}

void Employee::DisplayRecord() {
    cout << endl << setw(5) << EmpID << setw(15) << EmpName
         << setw(15) << Post << setw(15) << Department << setw(8) << Salary;
}

int Employee::GetID() {
    return EmpID;
}

char* Employee::GetDepartment() {
    return Department;
}

int main() {
    Employee emp, e;
    char option, ch, Dept[50];
    int ID, isFound;

    fstream file;
    file.open(fileName, ios::ate | ios::in | ios::out | ios::binary);

    do {
        cout << "\n\n******* Menu ********";
        cout << "\n1 => Add new record";
        cout << "\n2 => Search by ID";
        cout << "\n3 => List by Department";
        cout << "\n4 => Display All";
        cout << "\n5 => Update Record";
        cout << "\n6 => Delete Record";
        cout << "\n7 => Exit";
        cout << "\nEnter your option: ";
        cin >> option;

        switch (option) {
        case '1': {
            emp.ReadData();
            file.seekg(0, ios::beg);
            isFound = 0;
            while (file.read((char*)&e, sizeof(e))) {
                if (e.GetID() == emp.GetID()) {
                    cout << "This ID already exists... Try another.";
                    isFound = 1;
                    break;
                }
            }
            if (isFound) break;
            file.clear();
            file.seekp(0, ios::end);
            file.write((char*)&emp, sizeof(emp));
            cout << "\nNew record added successfully.";
            break;
        }

        case '2': {
            isFound = 0;
            cout << "\nEnter ID to search: ";
            cin >> ID;
            file.clear();
            file.seekg(0, ios::beg);
            while (file.read((char*)&e, sizeof(e))) {
                if (e.GetID() == ID) {
                    cout << "\nRecord found:\n";
                    cout << setw(5) << "ID" << setw(15) << "Name" << setw(15)
                         << "Post" << setw(15) << "Department" << setw(8) << "Salary";
                    e.DisplayRecord();
                    isFound = 1;
                    break;
                }
            }
            if (!isFound)
                cout << "\nData not found for ID #" << ID;
            break;
        }

        case '3': {
            isFound = 0;
            cout << "Enter department: ";
            cin >> Dept;
            file.clear();
            file.seekg(0, ios::beg);
            while (file.read((char*)&e, sizeof(e))) {
                if (strcmp(e.GetDepartment(), Dept) == 0) {
                    cout << "\nRecord found:\n";
                    cout << setw(5) << "ID" << setw(15) << "Name" << setw(15)
                         << "Post" << setw(15) << "Department" << setw(8) << "Salary";
                    e.DisplayRecord();
                    isFound = 1;
                }
            }
            if (!isFound)
                cout << "\nNo employee found in department: " << Dept;
            break;
        }

        case '4': {
            int counter = 0;
            file.clear();
            file.seekg(0, ios::beg);
            cout << "\nAll Employee Records:\n";
            while (file.read((char*)&e, sizeof(e))) {
                if (counter == 0) {
                    cout << setw(5) << "ID" << setw(15) << "Name" << setw(15)
                         << "Post" << setw(15) << "Department" << setw(8) << "Salary";
                }
                e.DisplayRecord();
                counter++;
            }
            cout << "\nTotal records: " << counter;
            break;
        }

        case '5': {
            int recordNo = 0;
            isFound = 0;
            cout << "\nEnter employee ID to update: ";
            cin >> ID;
            file.clear();
            file.seekg(0, ios::beg);
            while (file.read((char*)&e, sizeof(e))) {
                recordNo++;
                if (e.GetID() == ID) {
                    cout << "Existing record:";
                    e.DisplayRecord();
                    isFound = 1;
                    break;
                }
            }
            if (!isFound) {
                cout << "\nRecord not found.";
                break;
            }
            int location = (recordNo - 1) * sizeof(e);
            file.clear();
            file.seekp(location, ios::beg);
            cout << "\nEnter new data:";
            e.ReadData();
            file.write((char*)&e, sizeof(e));
            cout << "\nRecord updated successfully.";
            break;
        }

        case '6': {
            int recordNo = 0;
            isFound = 0;
            cout << "\nEnter employee ID to delete: ";
            cin >> ID;
            file.clear();
            file.seekg(0, ios::beg);
            while (file.read((char*)&e, sizeof(e))) {
                if (e.GetID() == ID) {
                    cout << "Record to delete:";
                    e.DisplayRecord();
                    isFound = 1;
                    break;
                }
            }
            if (!isFound) {
                cout << "\nRecord not found.";
                break;
            }
            char tempFile[] = "temp.txt";
            fstream temp(tempFile, ios::out | ios::binary);
            file.clear();
            file.seekg(0, ios::beg);
            while (file.read((char*)&e, sizeof(e))) {
                if (e.GetID() != ID)
                    temp.write((char*)&e, sizeof(e));
            }
            file.close();
            temp.close();
            remove(fileName);
            rename(tempFile, fileName);
            file.open(fileName, ios::ate | ios::in | ios::out | ios::binary);
            cout << "\nRecord deleted successfully.";
            break;
        }

        case '7':
            cout << "Exiting program.";
            exit(0);

        default:
            cout << "Invalid option.";
        }

        cout << "\nDo you want to continue (y/n)? ";
        cin >> ch;

    } while (ch != 'n');

    return 0;
}
