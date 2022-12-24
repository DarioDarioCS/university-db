#include "university-db.hpp"

#include <algorithm>
#include <iostream>

void UniversityDB::print()
{
    std::cout << " nic " << std::endl;
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

