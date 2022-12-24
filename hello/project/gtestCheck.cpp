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