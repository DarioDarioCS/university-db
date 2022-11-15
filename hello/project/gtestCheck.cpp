#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
using namespace std;

#include "university-db.hpp"

enum class Gender
{
    MALE, FEMALE
};


class Student
{
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

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(SimpleTest, CompareEqualValues) {
    ASSERT_EQ(1, 1);
}

TEST(UniversityDB, BasicCheck) {
    UniversityDB universityDb;
    universityDb.print();
}

