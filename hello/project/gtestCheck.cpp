#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
using namespace std;

#include "university-db.hpp"



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

