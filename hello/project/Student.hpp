#include <string>


class Student
{
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

private:
    const std::string name;
    const std::string surname;
    const std::string address;
    const std::string id;
    const std::string pesel;
    enum Gender gender;

};