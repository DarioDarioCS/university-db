#pragma once

#include <vector>
#include <string>
#include "Student.hpp"

class UniversityDB
{
    int number_of_records = 0;
    std::vector<Student> records;
    bool findStudentById(const std::string& id, Student& student);
    
public:
    int numberOfRecords() const;
    bool addRecord(const Student& student);
    bool hasStudent(const Student& student);
    std::string toString();
    void print();
    bool findStudentBySurname(const std::string& surname, Student& student);
    bool findStudentByPesel(const std::string& pesel, Student& student);
    void sortByPesel();
    void sortBySurname();
    bool deleteById(const std::string& id);
    inline bool operator==(const UniversityDB& other) const
    {
        return (records == other.records);
    }
};



