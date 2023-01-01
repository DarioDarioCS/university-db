#pragma once

#include <functional>
#include <string>
#include <vector>

#include "Student.hpp"

class UniversityDBAccessor;

class UniversityDB {
    int number_of_records = 0;
    std::vector<Student> records;
    bool findStudentById(const std::string& id, Student& student);

    template <typename T>
    inline bool findStudentBy(const T& value,
                              std::function<std::string(const Student&)> getter,
                              Student& student);

    std::vector<Student> getRecords() const 
    {
        return records;
    }
    friend UniversityDBAccessor;
public:
    int numberOfRecords() const;
    bool empty() const;
    bool addRecord(const Student& student);
    bool hasStudent(const Student& student);
    std::string toString();
    void print();
    bool findStudentBySurname(const std::string& surname, Student& student);
    bool findStudentByPesel(const std::string& pesel, Student& student);
    void sortByPesel();
    void sortBySurname();
    bool deleteById(const std::string& id);
    inline bool operator==(const UniversityDB& other) const {
        return (records == other.records);
    }
};

class UniversityDBAccessor
{
    UniversityDB& db;
public:
    UniversityDBAccessor(UniversityDB& db) :db{db} {}
    std::vector<Student> getRecords()
    {
        return db.records;
    }

    void deleteDB()
    {
        db.records.clear();
    }
};

class UniversityDBBackup
{
    UniversityDB& db_to_backup;
public:
    explicit UniversityDBBackup(UniversityDB& db_to_backup) : db_to_backup{db_to_backup}{

    }
    void archiveDB();
    void cleanDB();
    UniversityDB retrieveData();
};