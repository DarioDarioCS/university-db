#include "university-db.hpp"

#include <algorithm>
#include <iostream>
#include <sstream>

std::string UniversityDB::toString()
{
    std::ostringstream out("");
    out << "UniversityDB:\n";
    out << "Number of records: " << records.size() << "\n";
    for(auto student : records)
    {
        out << StudentPrinter::printStudentToPlainText(student);
    }
    out <<  "\n";
    return out.str();
}

void UniversityDB::print()
{
    std::cout << toString();
}

int UniversityDB::numberOfRecords() const 
{
    return records.size();
}

bool UniversityDB::addRecord(const Student& student) 
{
    if(not hasStudent(student))
    {
        records.emplace_back(student);
        return true;
    }
    return false;
}

bool UniversityDB::hasStudent(const Student& student)
{
    auto result = std::find(begin(records), end(records), student);
    if((result != std::end(records)))
    {
        return true;
    }
    return false;
}

bool UniversityDB::findStudentBySurname(const std::string& surname, Student& student)
{
    bool result = false;
    for(auto studentInDB : records)
    {
        if(StudentAccessor::getSurname(studentInDB) == surname)
        {
            auto studentFactory = StudentFactory();
            student = studentFactory.cloneStudent(studentInDB);
            return true;
        }
    }
    return result;
}

bool UniversityDB::findStudentByPesel(const std::string& pesel, Student& student)
{
    bool result = false;
    for(auto studentInDB : records)
    {
        if(StudentAccessor::getPesel(studentInDB) == pesel)
        {
            auto studentFactory = StudentFactory();
            student = studentFactory.cloneStudent(studentInDB);
            return true;
        }
    }

    return result;
}

