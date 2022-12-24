#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
using namespace std;

#include "university-db.hpp"
#include "Student.hpp"


int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(SimpleTest, CompareEqualValues) {
    ASSERT_EQ(1, 1);
}

TEST(UniversityDB, BasicCheck) {
    UniversityDB universityDb;
}

TEST(UniversityDB, AddNewStudent) {
    UniversityDB universityDb;
    Student student("Mokebe", "Mensah", "ul. Wrocławska 3/4", "555666", "90032108093", Student::Gender::MALE);

    //At the beginning DB is empty
    EXPECT_TRUE(universityDb.numberOfRecords() == 0);
    EXPECT_FALSE(universityDb.hasStudent(student));
    
    //adding student should increment number of records
    universityDb.addRecord(student);
    EXPECT_TRUE(universityDb.numberOfRecords() == 1);
    EXPECT_TRUE(universityDb.hasStudent(student));
    
    //adding the same student shouldn't make any changes in DB
    universityDb.addRecord(student);
    EXPECT_TRUE(universityDb.numberOfRecords() == 1);
    EXPECT_TRUE(universityDb.hasStudent(student));

    //not added student shoudn't exists in DB
    Student not_added_student("Ukulele", "Mensah", "ul. Wrocławska 3/4", "555666", "90032108093", Student::Gender::MALE);
    EXPECT_TRUE(universityDb.numberOfRecords() == 1);
    EXPECT_FALSE(universityDb.hasStudent(not_added_student));
}

TEST(UniversityDB, DisplayDB_whenDBIsEmpty) {
    UniversityDB universityDb;

    const std::string expected =
    "UniversityDB:\n"
    "Number of records: 0\n"
    "\n";

    universityDb.print();
    EXPECT_TRUE(universityDb.toString() == expected);
}

TEST(UniversityDB, DisplayDB_whenDBHasOneStudent) {
    UniversityDB universityDb;
    Student student("Mokebe", "Mensah", "ul. Wrocławska 3/4", "555666", "90032108093", Student::Gender::MALE);
    universityDb.addRecord(student);

    const std::string expected =
    "UniversityDB:\n"
    "Number of records: 1\n"
    "Mokebe, Mensah, ul. Wrocławska 3/4, 555666, 90032108093, Mężczyzna\n"
    "\n";

    universityDb.print();
    EXPECT_TRUE(universityDb.toString() == expected);
}

TEST(UniversityDB, DisplayDB_whenDBHasTwoStudents) {
    UniversityDB universityDb;
    Student student("Mokebe", "Mensah", "ul. Wrocławska 3/4", "555666", "90032108093", Student::Gender::MALE);
    Student student2("Mbeppe", "Glappe", "ul. Wrocławska 3/4","555677", "90032108393", Student::Gender::MALE);
    universityDb.addRecord(student);
    universityDb.addRecord(student2);

    const std::string expected =
    "UniversityDB:\n"
    "Number of records: 2\n"
    "Mokebe, Mensah, ul. Wrocławska 3/4, 555666, 90032108093, Mężczyzna\n"
    "Mbeppe, Glappe, ul. Wrocławska 3/4, 555677, 90032108393, Mężczyzna\n"
    "\n";

    universityDb.print();
    EXPECT_TRUE(universityDb.toString() == expected);
}

TEST(UniversityDB, FindStudentBySurname_whenDBIsEmpty_thenDontLetFindAnyStudent)
{
    UniversityDB universityDb;
    Student student("Mokebe", "Mensah", "ul. Wrocławska 3/4", "555666", "90032108093", Student::Gender::MALE);

    Student student_to_find;
    auto result = universityDb.findStudentBySurname("Mensah", student_to_find);
    EXPECT_FALSE(result);
    EXPECT_FALSE(student == student_to_find);
}

TEST(UniversityDB, FindStudentBySurname_whenDBHasOneParticularStudent_thenAllowToFindThisStudent)
{
    UniversityDB universityDb;
    Student student("Mokebe", "Mensah", "ul. Wrocławska 3/4", "555666", "90032108093", Student::Gender::MALE);
    universityDb.addRecord(student);

    Student student_to_find;
    auto result = universityDb.findStudentBySurname("Mensah", student_to_find);
    EXPECT_TRUE(result);
    EXPECT_TRUE(student == student_to_find);
}

TEST(UniversityDB, FindStudentBySurname_whenDBHasOneParticularStudent_thenDisallowToFindAnotherStudent)
{
    UniversityDB universityDb;
    Student student("Mokebe", "Mensah", "ul. Wrocławska 3/4", "555666", "90032108093", Student::Gender::MALE);
    universityDb.addRecord(student);

    Student student_to_find;
    auto result = universityDb.findStudentBySurname("Mokebe", student_to_find);
    EXPECT_FALSE(result);
    EXPECT_FALSE(student == student_to_find);
}

TEST(UniversityDB, FindStudentByPesel_whenDBIsEmpty_thenDontLetFindAnyStudent)
{
    UniversityDB universityDb;
    Student student("Mokebe", "Mensah", "ul. Wrocławska 3/4", "555666", "90032108093", Student::Gender::MALE);

    Student student_to_find;
    auto result = universityDb.findStudentByPesel("90032108093", student_to_find);
    EXPECT_FALSE(result);
    EXPECT_FALSE(student == student_to_find);
}

TEST(UniversityDB, FindStudentByPesel_whenDBHasOneParticularStudent_thenAllowToFindThisStudent)
{
    UniversityDB universityDb;
    Student student("Mokebe", "Mensah", "ul. Wrocławska 3/4", "555666", "90032108093", Student::Gender::MALE);
    universityDb.addRecord(student);

    Student student_to_find;
    auto result = universityDb.findStudentByPesel("90032108093", student_to_find);
    EXPECT_TRUE(result);
    EXPECT_TRUE(student == student_to_find);
}

TEST(UniversityDB, FindStudentByPesel_whenDBHasOneParticularStudent_thenDisallowToFindAnotherStudent)
{
    UniversityDB universityDb;
    Student student("Mokebe", "Mensah", "ul. Wrocławska 3/4", "555666", "90032108093", Student::Gender::MALE);
    universityDb.addRecord(student);

    Student student_to_find;
    auto result = universityDb.findStudentByPesel("00000000000", student_to_find);
    EXPECT_FALSE(result);
    EXPECT_FALSE(student == student_to_find);
}

TEST(UniversityDB, SortDBByPesel_whenDBIsEmpty_thenOnlyLetInvokeSortMethod)
{
    UniversityDB universityDb;

    universityDb.sortByPesel();
}

TEST(UniversityDB, SortDBByPesel_whenDBHasOneStudent_thenDBShouldBeTheSameAsBefore)
{
    UniversityDB universityDb;
    UniversityDB notSortedDb;
    Student student("Mokebe", "Mensah", "ul. Wrocławska 3/4", "555666", "90032108093", Student::Gender::MALE);
    universityDb.addRecord(student);
    notSortedDb.addRecord(student);

    universityDb.sortByPesel();

    universityDb.print();
    EXPECT_TRUE(universityDb == notSortedDb);
}

TEST(UniversityDB, SortDBByPesel_whenDBHasTwoStudents_thenDBBeSorted)
{
    UniversityDB universityDb;
    UniversityDB notSortedDb;
    Student student("Mokebe", "Mensah", "ul. Wrocławska 3/4", "555666", "90032108093", Student::Gender::MALE);
    Student student2("Nbeppe", "Glappe", "ul. Wrocławska 3/4", "555666", "80032108093", Student::Gender::MALE);

    universityDb.addRecord(student);
    universityDb.addRecord(student2);
    notSortedDb.addRecord(student);
    notSortedDb.addRecord(student2);

    universityDb.sortByPesel();

    universityDb.print();
    EXPECT_FALSE(universityDb == notSortedDb);
}

TEST(UniversityDB, SortDBByPesel_whenDBHasThreeStudents_thenDBBeSorted)
{
    UniversityDB universityDb;
    UniversityDB notSortedDb;
    Student student("Mokebe", "Mensah", "ul. Wrocławska 3/4", "555666", "90032108093", Student::Gender::MALE);
    Student student2("Nbeppe", "Glappe", "ul. Wrocławska 3/4", "555666", "50032108093", Student::Gender::MALE);
    Student student3("Leppe", "Meppe", "ul. Wrocławska 3/4", "555666", "80032108093", Student::Gender::MALE);

    universityDb.addRecord(student);
    universityDb.addRecord(student2);
    universityDb.addRecord(student3);
    notSortedDb.addRecord(student);
    notSortedDb.addRecord(student2);
    notSortedDb.addRecord(student3);

    universityDb.sortByPesel();

    universityDb.print();
    EXPECT_FALSE(universityDb == notSortedDb);
}

TEST(UniversityDB, SortDBBySurname_whenDBIsEmpty_thenOnlyLetInvokeSortMethod)
{
    UniversityDB universityDb;

    universityDb.sortBySurname();
}

TEST(UniversityDB, SortDBBySurname_whenDBHasOneStudent_thenDBShouldBeTheSameAsBefore)
{
    UniversityDB universityDb;
    UniversityDB notSortedDb;
    Student student("Mokebe", "Mensah", "ul. Wrocławska 3/4", "555666", "90032108093", Student::Gender::MALE);
    universityDb.addRecord(student);
    notSortedDb.addRecord(student);

    universityDb.sortBySurname();

    universityDb.print();
    EXPECT_TRUE(universityDb == notSortedDb);
}

TEST(UniversityDB, SortDBBySurname_whenDBHasTwoStudents_thenDBBeSorted)
{
    UniversityDB universityDb;
    UniversityDB notSortedDb;
    Student student("Mokebe", "Mensah", "ul. Wrocławska 3/4", "555666", "90032108093", Student::Gender::MALE);
    Student student2("Nbeppe", "Glappe", "ul. Wrocławska 3/4", "555666", "80032108093", Student::Gender::MALE);

    universityDb.addRecord(student);
    universityDb.addRecord(student2);
    notSortedDb.addRecord(student);
    notSortedDb.addRecord(student2);

    universityDb.sortBySurname();

    universityDb.print();
    EXPECT_FALSE(universityDb == notSortedDb);
}

TEST(UniversityDB, SortDBBySurname_whenDBHasThreeStudents_thenDBBeSorted)
{
    UniversityDB universityDb;
    UniversityDB notSortedDb;
    Student student("Mokebe", "Mensah", "ul. Wrocławska 3/4", "555666", "90032108093", Student::Gender::MALE);
    Student student2("Nbeppe", "Glappe", "ul. Wrocławska 3/4", "555666", "50032108093", Student::Gender::MALE);
    Student student3("Leppe", "Meppe", "ul. Wrocławska 3/4", "555666", "80032108093", Student::Gender::MALE);

    universityDb.addRecord(student);
    universityDb.addRecord(student2);
    universityDb.addRecord(student3);
    notSortedDb.addRecord(student);
    notSortedDb.addRecord(student2);
    notSortedDb.addRecord(student3);

    universityDb.sortBySurname();

    universityDb.print();
    EXPECT_FALSE(universityDb == notSortedDb);
}

