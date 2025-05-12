#ifndef student_h
#define student_h

#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string name;
    float mark;
    string student_id;
    string course;
    string id_course;

public:
    // Constructor
    Student(string name = "", float mark = 0.0, string student_id = "", string course = "", string id_course = "");

    // Getters
    string getName() const;
    float getMark() const;
    string getStudent_id() const;
    string getCourse() const;
    string getId_course() const;

    // Setters
    void setName(string name);
    void setMark(float mark);
    void setStudent_id(string student_id);
    void setCourse(string course);
    void setId_course(string id_course);

    // Virtual để cho phép lớp con override
    virtual void printInfo() const;
};

// Lớp DeletedStudent kế thừa Student
class DeletedStudent : public Student {
private:
    string deleteReason;

public:
    DeletedStudent(string name, float mark, string student_id, string course, string id_course, string reason);

    string getDeleteReason() const {
    return deleteReason;
    }
    void setDeleteReason(string reason);

    void printInfo() const override;
};

#endif // student_h
