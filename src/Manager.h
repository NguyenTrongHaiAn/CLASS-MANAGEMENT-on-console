#ifndef MANAGER_H
#define MANAGER_H

#include<iostream>
#include <vector>
#include <string>
#include "Student.h"

// Sử dụng vector để duyệt danh sách sinh viên tối ưu hơn bằng RAM
class Student_Manager {
private:
    // Danh sách học sinh hiện tại
    vector<Student> student_list;

    // Danh sách học sinh đã bị xóa
   

    const string FILENAME = "Students.txt"; // File lưu học sinh
    const string FILENAME_DELETED = "DeletedStudents.txt"; // File lưu học sinh đã xóa

public:
    vector<DeletedStudent> deletedStudents; 
    // Constructor và Destructor
    Student_Manager();
    ~Student_Manager();

    // Các phương thức quản lý học sinh
    void Read_from_file();  // Đọc dữ liệu học sinh từ file
    void Save_to_file();    // Lưu danh sách học sinh vào file
    void Save_Deleted_Students_To_File();  // Lưu học sinh đã bị xóa vào file
    void Load_Deleted_Students_From_File();  // Đọc học sinh đã xóa từ file
    void Display_Deleted_Students();// in ra hoc sinh bi xoa
    void search_deleted_id();
    // Các phương thức chức năng chính
    void Add_Student();
    void Delete_Student();
    void Display_all_information_Student();
    void Search_Student_byID() const;
    void Sort_Student_byName();
    void Sort_Student_byMark();
    void Show_Topper();
    void Show_Average_Mark();
    void Edit_Name();
    void Edit_ID();
    void Edit_Mark();
    void Edit_Course();
    void Edit_CourseID();
};

#endif
