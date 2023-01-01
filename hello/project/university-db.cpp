#include "university-db.hpp"

#include <algorithm>
#include <iostream>
#include <sstream>

#include <nlohmann/json.hpp>

std::string UniversityDB::toString() {
    std::ostringstream out("");
    out << "UniversityDB:\n";
    out << "Number of records: " << records.size() << "\n";
    for (auto student : records) {
        out << StudentPrinter::printStudentToPlainText(student);
    }
    out << "\n";
    return out.str();
}

void UniversityDB::print() {
    std::cout << toString();
}

bool UniversityDB::empty() const {
    return numberOfRecords() == 0;
}

int UniversityDB::numberOfRecords() const {
    return records.size();
}

bool UniversityDB::addRecord(const Student& student) {
    if (not hasStudent(student)) {
        records.emplace_back(student);
        return true;
    }
    return false;
}

bool UniversityDB::hasStudent(const Student& student) {
    auto result = std::find(begin(records), end(records), student);
    if ((result != std::end(records))) {
        return true;
    }
    return false;
}

template <typename T>
bool UniversityDB::findStudentBy(const T& value,
                                 std::function<std::string(const Student&)> getter,
                                 Student& student) {
    auto foundStudent = std::find_if(records.begin(), records.end(), [&value, &getter](auto studentInDB) {
        return getter(studentInDB) == value;
    });
    if (foundStudent != std::end(records)) {
        auto studentFactory = StudentFactory();
        student = studentFactory.cloneStudent(*foundStudent);
        return true;
    }

    return false;
}

bool UniversityDB::findStudentBySurname(const std::string& surname, Student& student) {
    return findStudentBy(surname, StudentAccessor::getSurname, student);
}

bool UniversityDB::findStudentByPesel(const std::string& pesel, Student& student) {
    return findStudentBy(pesel, StudentAccessor::getPesel, student);
}

bool UniversityDB::findStudentById(const std::string& id, Student& student) {
    return findStudentBy(id, StudentAccessor::getId, student);
}

void UniversityDB::sortByPesel() {
    std::sort(records.begin(), records.end(), StudentAccessor::SortByPesel());
}

void UniversityDB::sortBySurname() {
    std::sort(records.begin(), records.end(), StudentAccessor::SortBySurname());
}

bool UniversityDB::deleteById(const std::string& id) {
    bool result = false;
    Student student;
    if (findStudentById(id, student)) {
        records.erase(std::remove_if(records.begin(),
                                     records.end(),
                                     [student](Student x) { return x == student; }),
                      records.end());
        result = true;
    }
    return result;
}

void UniversityDBBackup::archiveDB() 
{
    nlohmann::json json_data;
    json_data["Number of records"] = db_to_backup.numberOfRecords();

    UniversityDBAccessor dbAccessor{db_to_backup};
    auto records = dbAccessor.getRecords();
    for (const auto& record : records)
    {
        // Podziel rekord na poszczególne elementy
        std::vector<std::string> elements;
        std::stringstream ss{StudentPrinter::printStudentToPlainText(record)};
        std::string element;
        while (std::getline(ss, element, ','))
        {
            elements.push_back(element);
        }

        // Utwórz obiekt JSON dla pojedynczego rekordu
        nlohmann::json json_record;
        json_record["Imię"] = elements[0];
        json_record["Nazwisko"] = elements[1];
        json_record["Adres"] = elements[2];
        json_record["Numer ID"] = elements[3];
        json_record["Pesel"] = elements[4];
        json_record["Płeć"] = elements[5];

        // Dodaj obiekt JSON dla pojedynczego rekordu do obiektu JSON z całymi danymi
        json_data["Records"].push_back(json_record);
    }
}

void UniversityDBBackup::cleanDB() 
{
    UniversityDBAccessor dbAccessor{db_to_backup};
    dbAccessor.deleteDB();
}

UniversityDB UniversityDBBackup::retrieveData() 
{
    UniversityDB db;
    Student student;
    db.addRecord(student);
    return db;
}