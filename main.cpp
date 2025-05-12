#include <iostream>
#include <limits>
#include <cstdlib> // Cho exit(0)
#include "src/Manager.h"

using namespace std;

void display_MENU() {
    cout << "---------- Please select from the following options ----------" << endl;
    cout << "1. Add a student" << endl;
    cout << "2. Delete a student" << endl;
    cout << "3. Display all students" << endl;
    cout << "4. Search student by ID" << endl;  
    cout << "5. Sort students " << endl;
    cout << "6. Edit student" << endl;
    cout << "7. Show toppers with highest mark " << endl;
    cout << "8. Show average of all students " << endl;
    cout << "9. Display all student deleted " << endl;
    cout << "10. Search student deleted by ID" << endl; // Sửa ENDL thành endl
    cout << "11. Exit the program" << endl;
    cout << "Your choice: ";
}

bool display_SORT(Student_Manager& manager) {
    int choice;
    while (true) {
        cout << "\n---------- SORT STUDENTS AND PRINT ----------" << endl;
        cout << "1. Sort by higher score " << endl;
        cout << "2. Sort by name (A-Z) " << endl;
        cout << "3. Back to main menu" << endl;
        cout << "4. Exit the program" << endl;
        cout << "Your choice: ";
        
        cin >> choice;
        if (cin.fail()) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                manager.Sort_Student_byMark();
                break;
            case 2:
                manager.Sort_Student_byName();
                break;
            case 3:
                return false;
            case 4:
                return true;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

bool display_Edit(Student_Manager& manager) {
    int choice;
    while (true) {
        cout << "\n---------- EDIT STUDENT ----------" << endl;
        cout << "1. Edit mark" << endl;
        cout << "2. Edit student name" << endl;
        cout << "3. Edit course ID" << endl;
        cout << "4. Edit course name" << endl;
        cout << "5. Edit student ID" << endl;
        cout << "6. Back to main menu" << endl;
        cout << "7. Exit the program" << endl;
        cout << "Your choice: ";

        cin >> choice;
        if (cin.fail()) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                manager.Edit_Mark();
                break;
            case 2:
                manager.Edit_Name();
                break;
            case 3:
                manager.Edit_CourseID();
                break;
            case 4:
                manager.Edit_Course();
                break;
            case 5:
                manager.Edit_ID();
                break;
            case 6:
                return false;
            case 7:
                return true;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

int main() {
    
    Student_Manager manager;
    manager.Read_from_file();
    

    int choice;

    while (true) {
        display_MENU();

        // Kiểm tra và yêu cầu nhập lại nếu lựa chọn sai
        while (true) {
            cin >> choice;

            if (cin.fail()) {
                cout << "Invalid input. Please enter a number." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (choice >= 1 && choice <= 11) { // Thêm điều kiện cho case 11
                break;
            } else {
                cout << "Invalid choice. Please enter a valid option " << endl;
            }
        }

        bool should_exit = false;

        switch (choice) {
            case 1:
                manager.Add_Student();
                break;
            case 2:
                manager.Delete_Student();
                break;
            case 3:
                manager.Display_all_information_Student();
                break;
            case 4:
                manager.Search_Student_byID();
                break;
            case 5:
                should_exit = display_SORT(manager);
                break;
            case 6:
                should_exit = display_Edit(manager);
                break;
            case 7:
                manager.Show_Topper();
                break;
            case 8:
                manager.Show_Average_Mark();
                break;
            case 9:
                manager.Display_Deleted_Students(); // Gọi hàm in học sinh bị xóa
                break;
            case 10:
                manager.search_deleted_id(); // Gọi hàm tìm kiếm học sinh bị xóa theo ID
                break;
            case 11:
                should_exit = true;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        if (should_exit) {
            cout << "Exiting the program." << endl;
            break;
        }
    }

    manager.Save_to_file();
    return 0;
}
