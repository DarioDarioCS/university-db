#pragma once

#include <vector>
#include <string>
#include "Student.hpp"

class UniversityDB
{
    int number_of_records = 0;
    std::vector<Student> records;
public:
    int numberOfRecords() const;
    bool addRecord(const Student& student);
    bool hasStudent(const Student& student);
    std::string toString();
    void print();
    bool findStudentBySurname(const std::string& surname, Student& student);
};



