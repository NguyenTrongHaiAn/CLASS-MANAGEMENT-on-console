#include "Student.h"
#include <iostream>

using namespace std;

// Constructor implementation
Student::Student(string name, float mark, string student_id, string course, string id_course)
{
    this->name = name;
    this->mark = mark;
    this->student_id = student_id;
    this->course = course;
    this->id_course = id_course;
}

// Getter implementations
string Student::getName() const {
    return name;
}

float Student::getMark() const {
    return mark;
}

string Student::getStudent_id() const {
    return student_id;
}

string Student::getCourse() const {
    return course;
}

string Student::getId_course() const {
    return id_course;
}

// Setter implementations
void Student::setName(string name) {
    this->name = name;
}

void Student::setMark(float mark) {
    this->mark = mark;
}

void Student::setStudent_id(string student_id) {
    this->student_id = student_id;
}

void Student::setCourse(string course) {
    this->course = course;
}

void Student::setId_course(string id_course) {
    this->id_course = id_course;
}

// Method to print student information
void Student::printInfo() const {
    cout << "Student's information: " << endl;
    cout << "Name: " << name << endl;
    cout << "Mark: " << mark << endl;
    cout << "Student ID: " << student_id << endl;
    cout << "Course: " << course << endl;
    cout << "ID Course: " << id_course << endl;
}


// ------------------ DeletedStudent ------------------

DeletedStudent::DeletedStudent(string name, float mark, string student_id, string course, string id_course, string reason)
    : Student(name, mark, student_id, course, id_course), deleteReason(reason) {}



void DeletedStudent::setDeleteReason(string reason) {
    deleteReason = reason;
}

void DeletedStudent::printInfo() const {
    Student::printInfo();
    cout << "Reason for deletion: " << deleteReason << endl;
}