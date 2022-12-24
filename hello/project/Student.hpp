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

    inline bool operator==(const Student& other) const
    {
        return (name == other.name) and
                (surname == other.surname) and
                (address == other.address) and
                (id == other.id) and
                (pesel == other.pesel) and
                (gender == other.gender);
    }

private:
    friend class StudentPrinter;
    friend class StudentAccessor;
    friend class StudentFactory;
    // Student& operator=(const Student& other);
    std::string name;
    std::string surname;
    std::string address;
    std::string id;
    std::string pesel;
    enum Gender gender;

    const std::string getName() const
    {
        return name;
    }
    const std::string getSurname() const
    {
        return surname;
    }
    const std::string getAddress() const
    {
        return address;
    }
    const std::string getId() const
    {
        return id;
    }
    const std::string getPesel() const
    {
        return pesel;
    }
    enum Gender getGender() const
    {
        return gender;
    }
};

class StudentPrinter
{
public:
    static std::string printStudentToPlainText(const Student& student);
};

class StudentAccessor
{
public:
    static std::string getSurname(const Student& student);
    static std::string getPesel(const Student& student);
    struct SortByPesel{
        bool operator()(Student a, Student b) const { return a.pesel < b.pesel; }
    };
    struct SortBySurname{
        bool operator()(Student a, Student b) const { return a.surname < b.surname; }
    };
};

class StudentFactory
{
public:
    StudentFactory(){}
    Student cloneStudent(const Student& student);
};