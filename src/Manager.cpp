#include "Manager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits> // Cần cho numeric_limits
#include "Student.h" // Giả sử Student.h cũng định nghĩa DeletedStudent

using namespace std;

// Định nghĩa tên file (nên để ở Manager.h hoặc một file config riêng nếu lớn hơn)
const string FILENAME = "Students.txt";
const string FILENAME_DELETED = "DeletedStudents.txt";

Student_Manager::Student_Manager() {
    Read_from_file();
    Load_Deleted_Students_From_File();
}

Student_Manager::~Student_Manager() {
    cout << "Saving data.....";
    Save_to_file();
    // Cân nhắc có nên lưu danh sách deletedStudents vào file ở đây không,
    // nếu bạn muốn file FILENAME_DELETED luôn phản ánh trạng thái cuối cùng của vector.
    // Hiện tại, FILENAME_DELETED hoạt động như một log append-only.
}

void Student_Manager::Read_from_file() {
    student_list.clear();
    ifstream inFile(FILENAME); // Mở file trực tiếp
    if (!inFile.is_open()) {
        // Không nên báo lỗi nếu file chưa tồn tại lần đầu
        // cout << "File " << FILENAME << " khong ton tai hoac khong the mo. Co the day la lan chay dau tien." << endl;
        return;
    }

    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string name, id_str, course_str, id_course_str; // Đổi tên biến id thành id_str để tránh nhầm lẫn
        string mark_str_val; // Đọc điểm dưới dạng string
        float mark_val = 0.0f;

        // Đọc theo thứ tự: Name,Mark,ID,Course,CourseID
        if (getline(ss, name, ',') &&
            getline(ss, mark_str_val, ',') && // Đọc điểm
            getline(ss, id_str, ',') &&
            getline(ss, course_str, ',') &&
            getline(ss, id_course_str)) { // id_course_str là phần còn lại

            try {
                mark_val = stof(mark_str_val);
            } catch (const std::invalid_argument& ia) {
                cerr << "Loi dinh dang diem trong " << FILENAME << " (ID: " << id_str << "): " << mark_str_val << ". Su dung diem mac dinh 0.0." << endl;
                mark_val = 0.0f;
            } catch (const std::out_of_range& oor) {
                cerr << "Diem ngoai pham vi trong " << FILENAME << " (ID: " << id_str << "): " << mark_str_val << ". Su dung diem mac dinh 0.0." << endl;
                mark_val = 0.0f;
            }

            Student s(name, mark_val, id_str, course_str, id_course_str);
            student_list.push_back(s);
        } else {
            cerr << "Loi doc dong trong file " << FILENAME << ": " << line << endl;
        }
    }
    inFile.close();
}

void Student_Manager::Save_to_file() {
    ofstream outFile(FILENAME);
    if (!outFile.is_open()) {
        cout << "Cant open file " << FILENAME << " to write!";
        return;
    }

    for (const auto& s : student_list) {
        outFile << s.getName() << ","
                << s.getMark() << ","
                << s.getStudent_id() << ","
                << s.getCourse() << ","
                << s.getId_course() << endl;
    }
    outFile.close();
    cout << " Saved " << FILENAME << " successfully!" << endl;
}

void Student_Manager::Add_Student() {
    string name, id_str, course_str, id_course_str; // Đổi tên biến
    float mark_val;

    cout << "Enter name: ";
    getline(cin >> ws, name); // ws để loại bỏ khoảng trắng đầu dòng nếu có từ lần nhập trước

    cout << "Enter mark: ";
    while (!(cin >> mark_val) || mark_val < 0 || mark_val > 10) { // Kiểm tra cả cin fail
        cout << "Invalid mark. Must be a number between 0 and 10.\n";
        cout << "Enter mark: ";
        cin.clear(); // Xóa cờ lỗi
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Bỏ qua input lỗi
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xử lý newline sau khi đọc số

    cout << "Enter student's id: ";
    getline(cin, id_str); // Dùng getline để có thể nhập ID có khoảng trắng

    cout << "Enter course: ";
    getline(cin, course_str);

    cout << "Enter course's id: ";
    getline(cin, id_course_str);

    Student s(name, mark_val, id_str, course_str, id_course_str);
    student_list.push_back(s);
    Save_to_file(); // Lưu ngay sau khi thêm
    cout << "Student added!\n";
}


void Student_Manager::Display_all_information_Student() {
    if (student_list.empty()) {
        cout << "No student data available.\n";
        return;
    }

    cout << "\n---------- All students' information: ----------\n";
    for (const auto& s : student_list) {
        // Có thể gọi s.printInfo() nếu bạn muốn định dạng giống hệt khi tìm kiếm
        cout << "Name: " << s.getName() << ", "
             << "Mark: " << s.getMark() << ", "
             << "ID: " << s.getStudent_id() << ", "
             << "Course: " << s.getCourse() << ", "
             << "Course ID: " << s.getId_course() << endl;
    }
}

void Student_Manager::Search_Student_byID() const  {
    string id_to_search;
    cout << "Enter ID to search: ";
    getline(cin >> ws, id_to_search); // ws để xử lý nếu có newline từ lựa chọn menu

    bool found = false;
    for (const auto& s : student_list) {
        if (s.getStudent_id() == id_to_search) {
            cout << "\n--- Student Information Found ---" << endl;
            s.printInfo();
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "No student with ID: " << id_to_search << endl;
    }
}

void Student_Manager::Sort_Student_byName() {
    if (student_list.empty()) {
        cout << "No students to sort.\n";
        return;
    }
    sort(student_list.begin(), student_list.end(), [](const Student& a, const Student& b) {
        return a.getName() < b.getName();
    });
    cout << "Sorted by name (A-Z).\n";
    Display_all_information_Student(); // Hiển thị sau khi sắp xếp
    Save_to_file(); // Lưu lại trạng thái đã sắp xếp
}

void Student_Manager::Sort_Student_byMark() {
    if (student_list.empty()) {
        cout << "No students to sort.\n";
        return;
    }
    sort(student_list.begin(), student_list.end(), [](const Student& a, const Student& b) {
        return a.getMark() > b.getMark(); // Sắp xếp giảm dần theo điểm
    });
    cout << "Sorted by mark (high to low).\n";
    Display_all_information_Student(); // Hiển thị sau khi sắp xếp
    Save_to_file(); // Lưu lại trạng thái đã sắp xếp
}

void Student_Manager::Show_Topper() {
    if (student_list.empty()) {
        cout << "No student data available.\n";
        return;
    }

    auto top_iterator = max_element(student_list.begin(), student_list.end(), [](const Student& a, const Student& b) {
        return a.getMark() < b.getMark();
    });

    // max_element trả về iterator, nên cần kiểm tra xem nó có phải là end() không (dù student_list.empty() đã kiểm tra)
    if (top_iterator != student_list.end()) {
        cout << "\n--- Topper Student ---" << endl;
        top_iterator->printInfo();
    }
}

void Student_Manager::Show_Average_Mark() {
    if (student_list.empty()) {
        cout << "No student data available to calculate average.\n";
        return;
    }

    float sum = 0;
    for (const auto& s : student_list) {
        sum += s.getMark();
    }
    // Đảm bảo không chia cho 0, dù student_list.empty() đã kiểm tra
    if (!student_list.empty()) {
        cout << "Average mark of all students: " << sum / student_list.size() << endl;
    }
}

// Các hàm Edit_...
// Nên thêm cin.ignore sau mỗi lần đọc ID bằng cin >> id
// và dùng getline cho các trường chuỗi để cho phép có khoảng trắng.

void Student_Manager::Edit_Name() {
    string id_to_edit;
    cout << "Enter student ID to edit name: ";
    getline(cin >> ws, id_to_edit);

    for (auto& s : student_list) {
        if (s.getStudent_id() == id_to_edit) {
            string newName;
            cout << "Current name: " << s.getName() << endl;
            cout << "Enter new name: ";
            getline(cin, newName); // Không cần ws ở đây vì getline trước đã xử lý
            s.setName(newName);
            cout << "Name updated.\n";
            Save_to_file();
            return;
        }
    }
    cout << "Student with ID " << id_to_edit << " not found.\n";
}

void Student_Manager::Edit_ID() {
    string current_id;
    cout << "Enter current student ID to edit: ";
    getline(cin >> ws, current_id);

    for (auto& s : student_list) {
        if (s.getStudent_id() == current_id) {
            string newID;
            cout << "Current ID: " << s.getStudent_id() << endl;
            cout << "Enter new ID: ";
            getline(cin, newID);
            // Cần kiểm tra xem newID có trùng với ID của sinh viên khác không (nếu ID là duy nhất)
            // Logic kiểm tra trùng ID có thể phức tạp hơn
            s.setStudent_id(newID);
            cout << "ID updated.\n";
            Save_to_file();
            return;
        }
    }
    cout << "Student with ID " << current_id << " not found.\n";
}

void Student_Manager::Edit_Mark() {
    string id_to_edit;
    cout << "Enter student ID to edit mark: ";
    getline(cin >> ws, id_to_edit);

    for (auto& s : student_list) {
        if (s.getStudent_id() == id_to_edit) {
            float newMark;
            cout << "Current mark: " << s.getMark() << endl;
            cout << "Enter new mark (0 - 10): ";
            while (!(cin >> newMark) || newMark < 0 || newMark > 10) {
                cout << "Invalid mark. Must be a number between 0 and 10.\n";
                cout << "Enter new mark: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xử lý newline

            s.setMark(newMark);
            cout << "Mark updated.\n";
            Save_to_file();
            return;
        }
    }
    cout << "Student with ID " << id_to_edit << " not found.\n";
}

void Student_Manager::Edit_Course() {
    string id_to_edit;
    cout << "Enter student ID to edit course: ";
    getline(cin >> ws, id_to_edit);

    for (auto& s : student_list) {
        if (s.getStudent_id() == id_to_edit) {
            string newCourse;
            cout << "Current course: " << s.getCourse() << endl;
            cout << "Enter new course name: ";
            getline(cin, newCourse);
            s.setCourse(newCourse);
            cout << "Course updated.\n";
            Save_to_file();
            return;
        }
    }
    cout << "Student with ID " << id_to_edit << " not found.\n";
}

void Student_Manager::Edit_CourseID() {
    string id_to_edit;
    cout << "Enter student ID to edit course ID: ";
    getline(cin >> ws, id_to_edit);

    for (auto& s : student_list) {
        if (s.getStudent_id() == id_to_edit) {
            string newCourseID;
            cout << "Current course ID: " << s.getId_course() << endl;
            cout << "Enter new course ID: ";
            getline(cin, newCourseID);
            s.setId_course(newCourseID);
            cout << "Course ID updated.\n";
            Save_to_file();
            return;
        }
    }
    cout << "Student with ID " << id_to_edit << " not found.\n";
}

// DELETED STUDENT FUNCTIONS

void Student_Manager::Delete_Student() {
    string id_to_delete;
    cout << "Nhap ID sinh vien muon xoa: ";
    getline(cin >> ws, id_to_delete); // Dùng getline để nhất quán

    auto it = find_if(student_list.begin(), student_list.end(), [&](const Student& s) {
        return s.getStudent_id() == id_to_delete;
    });

    if (it != student_list.end()) {
        string reason;
        cout << "Nhap ly do xoa sinh vien: ";
        getline(cin, reason); // Không cần ws vì getline trước đã xử lý

        DeletedStudent delStudent(
            it->getName(),
            it->getMark(),
            it->getStudent_id(),
            it->getCourse(),
            it->getId_course(),
            reason
        );

        deletedStudents.push_back(delStudent);

        ofstream outFile(FILENAME_DELETED, ios::app);
        if (outFile.is_open()) {
            outFile << delStudent.getStudent_id() << ","
                    << delStudent.getName() << ","
                    << delStudent.getMark() << ","
                    << delStudent.getCourse() << ","
                    << delStudent.getId_course() << ","
                    << delStudent.getDeleteReason() << endl;
            outFile.close();
        } else {
            cerr << "Khong the mo file " << FILENAME_DELETED << " de ghi!" << endl;
        }

        student_list.erase(it);
        Save_to_file();
        cout << "Da xoa sinh vien va luu vao danh sach bi xoa.\n";
    } else {
        cout << "Khong tim thay sinh vien voi ID " << id_to_delete << ".\n";
    }
}

void Student_Manager::Load_Deleted_Students_From_File() {
    deletedStudents.clear();
    ifstream inFile(FILENAME_DELETED);
    if (!inFile.is_open()) {
        return;
    }

    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string id_str, name_str, mark_str_val, course_str, course_id_str, reason_str;
        float mark_val = 0.0f;

        if (getline(ss, id_str, ',') &&
            getline(ss, name_str, ',') &&
            getline(ss, mark_str_val, ',') &&
            getline(ss, course_str, ',') &&
            getline(ss, course_id_str, ',') &&
            getline(ss, reason_str)) {

            try {
                mark_val = stof(mark_str_val);
            } catch (const std::invalid_argument& ia) {
                cerr << "Loi dinh dang diem trong " << FILENAME_DELETED << " (ID: " << id_str << "): " << mark_str_val << ". Su dung diem mac dinh 0.0." << endl;
                mark_val = 0.0f;
            } catch (const std::out_of_range& oor) {
                cerr << "Diem ngoai pham vi trong " << FILENAME_DELETED << " (ID: " << id_str << "): " << mark_str_val << ". Su dung diem mac dinh 0.0." << endl;
                mark_val = 0.0f;
            }

            if (name_str.empty()) name_str = "N/A";
            if (course_str.empty()) course_str = "N/A";
            if (course_id_str.empty()) course_id_str = "N/A";
            if (reason_str.empty()) reason_str = "Khong ro";

            DeletedStudent s(name_str, mark_val, id_str, course_str, course_id_str, reason_str);
            deletedStudents.push_back(s);
        } else {
            cerr << "Loi doc dong trong file " << FILENAME_DELETED << ": " << line << endl;
        }
    }
    inFile.close();
}

void Student_Manager::Display_Deleted_Students() {
    if (deletedStudents.empty()) {
        cout << "No deleted students to display." << endl; // Sửa thông báo
    } else {
        cout << "\n---------- Danh sach sinh vien da xoa ----------" << endl; // Sửa tiêu đề
        for (const auto& student : deletedStudents) {
            // In đầy đủ thông tin hơn
             cout << "ID: " << student.getStudent_id()
                 << ", Ten: " << student.getName()
                 << ", Diem: " << student.getMark()
                 << ", Khoa hoc: " << student.getCourse()
                 << ", Ma KH: " << student.getId_course()
                 << ", Ly do xoa: " << student.getDeleteReason() << endl;
            // Hoặc đơn giản là gọi student.printInfo() nếu nó đã được định dạng theo ý muốn
            // student.printInfo();
        }
    }
}

void Student_Manager::search_deleted_id() {
    string studentID_to_search;
    cout << "Enter student ID to search in deleted students: ";
    getline(cin >> ws, studentID_to_search); // ws để xử lý newline từ lựa chọn menu

    if (studentID_to_search.empty()) {
        cout << "Invalid input. Student ID cannot be empty!" << endl;
        return;
    }

    bool found = false;
    for (const auto& student : deletedStudents) {
        if (student.getStudent_id() == studentID_to_search) {
            cout << "\n--- Thong tin sinh vien da xoa tim thay ---" << endl;
            student.printInfo();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "No deleted student found with ID: " << studentID_to_search << endl;
    }
}