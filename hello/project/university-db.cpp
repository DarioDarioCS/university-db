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
    auto foundStudent = std::find_if(records.begin(), 
                               records.end(),
                               [&surname](auto studentInDB){
                                return StudentAccessor::getSurname(studentInDB) == surname;
                               });
    if(foundStudent != std::end(records))
    {
        auto studentFactory = StudentFactory();
        student = studentFactory.cloneStudent(*foundStudent);
        return true;
    }

    return false;
}

bool UniversityDB::findStudentByPesel(const std::string& pesel, Student& student)
{
    auto foundStudent = std::find_if(records.begin(), 
                               records.end(),
                               [&pesel](auto studentInDB){
                                return StudentAccessor::getPesel(studentInDB) == pesel;
                               });
    if(foundStudent != std::end(records))
    {
        auto studentFactory = StudentFactory();
        student = studentFactory.cloneStudent(*foundStudent);
        return true;
    }

    return false;
}

bool UniversityDB::findStudentById(const std::string& id, Student& student)
{
    auto foundStudent = std::find_if(records.begin(), 
                               records.end(),
                               [&id](auto studentInDB){
                                return StudentAccessor::getId(studentInDB) == id;
                               });
    if(foundStudent != std::end(records))
    {
        auto studentFactory = StudentFactory();
        student = studentFactory.cloneStudent(*foundStudent);
        return true;
    }

    return false;
}

void UniversityDB::sortByPesel()
{
    std::sort(records.begin(), records.end(), StudentAccessor::SortByPesel());
}

void UniversityDB::sortBySurname()
{
    std::sort(records.begin(), records.end(), StudentAccessor::SortBySurname());
}

bool UniversityDB::deleteById(const std::string& id)
{
    bool result = false;
    Student student;
    if(findStudentById(id, student))
    {
        records.erase(std::remove_if(records.begin(), 
                                    records.end(), 
                                    [student](Student x){return x == student;}),
                                    records.end());
        result = true;
    }
    return result;
}