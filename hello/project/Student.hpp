#pragma once
#include <string>

class Student
{
public:
    enum class Gender
    {
        MALE, FEMALE
    };

    Student() : name("Kłentin"), 
                surname("Lewandowski"),
                address("ul Wrocławska, Koziebrody"),
                id("652232"),
                pesel("99099088765"),
                gender(Gender::MALE)
    {

    }

    Student(const std::string name, 
            const std::string surname,
            const std::string address,
            const std::string id,
            const std::string pesel,
            enum Gender gender) 
            : name(name), 
                surname(surname),
                address(address),
                id(id),
                pesel(pesel),
                gender(gender)
    {

    }

    inline bool operator==(const Student& foo)
    {
        return (name == foo.name) and
                (surname == foo.surname) and
                (address == foo.address) and
                (id == foo.id) and
                (pesel == foo.pesel) and
                (gender == foo.gender);
    }

private:
    const std::string name;
    const std::string surname;
    const std::string address;
    const std::string id;
    const std::string pesel;
    enum Gender gender;

};