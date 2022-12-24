
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

std::string StudentAccessor::getSurname(const Student& student)
{
    return student.getSurname();
}


Student StudentFactory::cloneStudent(const Student& student)
{
    Student clonedStudent(student.getName(), 
        student.getSurname(),
        student.getAddress(),
        student.getId(),
        student.getPesel(),
        student.getGender());
    return clonedStudent;
}
