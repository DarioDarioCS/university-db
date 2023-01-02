#include "university-db.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <nlohmann/json.hpp>

static std::string remove_leading_trailing_whitespaces(std::string str) {
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](int ch) {
                  return !std::isspace(ch);
              }));

    str.erase(std::find_if(str.rbegin(), str.rend(), [](int ch) {
                  return !std::isspace(ch);
              }).base(),
              str.end());

    return str;
};

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

void UniversityDBBackup::archiveDB() {
    nlohmann::json json_data;
    json_data["Number of records"] = db_to_backup.numberOfRecords();

    UniversityDBAccessor dbAccessor{db_to_backup};
    auto records = dbAccessor.getRecords();
    for (const auto& record : records) {
        std::vector<std::string> elements;
        std::stringstream ss{StudentPrinter::printStudentToPlainText(record)};
        std::string element;
        while (std::getline(ss, element, ',')) {
            elements.push_back(remove_leading_trailing_whitespaces(element));
        }

        nlohmann::json json_record;
        json_record["Name"] = elements[0];
        json_record["Surname"] = elements[1];
        json_record["Address"] = elements[2];
        json_record["ID"] = elements[3];
        json_record["Pesel"] = elements[4];
        json_record["Gender"] = elements[5];

        json_data["Records"].push_back(json_record);
    }

    std::ofstream out_file("data.json");
    if (out_file.is_open()) {
        out_file << json_data.dump(4);
        out_file.close();
    } else {
        std::cerr << "Error opening file for writing!" << std::endl;
    }
}

void UniversityDBBackup::cleanDB() {
    UniversityDBAccessor dbAccessor{db_to_backup};
    dbAccessor.deleteDB();
}

UniversityDB UniversityDBBackup::retrieveData() {
    UniversityDBAccessor dbAccessor{db_to_backup};

    std::ifstream in_file("data.json");
    if (in_file.is_open()) {
        std::string data((std::istreambuf_iterator<char>(in_file)),
                         std::istreambuf_iterator<char>());
        in_file.close();

        nlohmann::json json_data = nlohmann::json::parse(data);

        for (const auto& json_record : json_data["Records"]) {
            std::string name, surname, address, id, pesel, genderStr;
            std::istringstream input_stream;

            input_stream.str(
                json_record["Name"].get<std::string>() + ", " + json_record["Surname"].get<std::string>() + ", " + json_record["Address"].get<std::string>() + ", " + json_record["ID"].get<std::string>() + ", " + json_record["Pesel"].get<std::string>() + ", " + json_record["Gender"].get<std::string>());

            std::getline(input_stream, name, ',');
            std::getline(input_stream, surname, ',');
            std::getline(input_stream, address, ',');
            std::getline(input_stream, id, ',');
            std::getline(input_stream, pesel, ',');
            std::getline(input_stream, genderStr);

            name = remove_leading_trailing_whitespaces(name);
            surname = remove_leading_trailing_whitespaces(surname);
            address = remove_leading_trailing_whitespaces(address);
            id = remove_leading_trailing_whitespaces(id);
            pesel = remove_leading_trailing_whitespaces(pesel);
            genderStr = remove_leading_trailing_whitespaces(genderStr);

            auto gender = StudentAccessor::getGenderByStr(genderStr);
            Student record{name, surname, address, id, pesel, gender};
            db_to_backup.addRecord(record);
        }
    } else {
        throw UniversityDBBackupException("Couldn't open the file\n");
    }

    return db_to_backup;
}