#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
using namespace std;

class UniversityDB
{
    public:
    void print()
    {
        std::cout << " nic " << std::endl;
    }
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

