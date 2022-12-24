
#include "Student.hpp"
#include <sstream>


std::string StudentPrinter::printStudentToPlainText(const Student& student)
{
    std::ostringstream out("");
    out << student.getName() << ", "
        << student.getSurname() << ", "
        << student.getAddress() << ", "
        << student.getId() << ", "
        << student.getPesel() << ", ";
    auto gender = student.getGender();
    auto genderStr = (gender == Student::Gender::MALE) ? "Mężczyzna" : "Kobieta";
    out << genderStr;
    out << "\n";

    return out.str();
}