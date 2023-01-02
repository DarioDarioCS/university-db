#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
using namespace std;

#include "Student.hpp"
#include "university-db.hpp"

#include <nlohmann/json.hpp>

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
    Student student("Mokebe", "Mensah", "ul. Wrocławska 3/4", "555666", "66052377411", Student::Gender::MALE);

    // At the beginning DB is empty
    EXPECT_TRUE(universityDb.numberOfRecords() == 0);
    EXPECT_FALSE(universityDb.hasStudent(student));

    // adding student should increment number of records
    universityDb.addRecord(student);
    EXPECT_TRUE(universityDb.numberOfRecords() == 1);
    EXPECT_TRUE(universityDb.hasStudent(student));

    // adding the same student shouldn't make any changes in DB
    universityDb.addRecord(student);
    EXPECT_TRUE(universityDb.numberOfRecords() == 1);
    EXPECT_TRUE(universityDb.hasStudent(student));

    // not added student shoudn't exists in DB
    Student not_added_student("Ukulele", "Mensah", "ul. Wrocławska 3/4", "555666", "66052377411", Student::Gender::MALE);
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
    Student student("Mokebe", "Mensah", "ul. Wrocławska 3/4", "555666", "66052377411", Student::Gender::MALE);
    universityDb.addRecord(student);

    const std::string expected =
        "UniversityDB:\n"
        "Number of records: 1\n"
        "Mokebe, Mensah, ul. Wrocławska 3/4, 555666, 66052377411, Mężczyzna\n"
        "\n";

    universityDb.print();
    EXPECT_TRUE(universityDb.toString() == expected);
}

TEST(UniversityDB, DisplayDB_whenDBHasTwoStudents) {
    UniversityDB universityDb;
    Student student("Mokebe", "Mensah", "ul. Wrocławska 3/4", "555666", "73022588919", Student::Gender::MALE);
    Student student2("Mbeppe", "Glappe", "ul. Wrocławska 3/4", "555677", "89012793171", Student::Gender::MALE);
    universityDb.addRecord(student);
    universityDb.addRecord(student2);

    const std::string expected =
        "UniversityDB:\n"
        "Number of records: 2\n"
        "Mokebe, Mensah, ul. Wrocławska 3/4, 555666, 73022588919, Mężczyzna\n"
        "Mbeppe, Glappe, ul. Wrocławska 3/4, 555677, 89012793171, Mężczyzna\n"
        "\n";

    universityDb.print();
    EXPECT_TRUE(universityDb.toString() == expected);
}

TEST(UniversityDB, FindStudentBySurname_whenDBIsEmpty_thenDontLetFindAnyStudent) {
    UniversityDB universityDb;
    Student student("Mokebe", "Mensah", "ul. Wrocławska 3/4", "555666", "66052377411", Student::Gender::MALE);

    Student student_to_find;
    auto result = universityDb.findStudentBySurname("Mensah", student_to_find);
    EXPECT_FALSE(result);
    EXPECT_FALSE(student == student_to_find);
}

TEST(UniversityDB, FindStudentBySurname_whenDBHasOneParticularStudent_thenAllowToFindThisStudent) {
    UniversityDB universityDb;
    Student student("Mokebe", "Mensah", "ul. Wrocławska 3/4", "555666", "66052377411", Student::Gender::MALE);
    universityDb.addRecord(student);

    Student student_to_find;
    auto result = universityDb.findStudentBySurname("Mensah", student_to_find);
    EXPECT_TRUE(result);
    EXPECT_TRUE(student == student_to_find);
}

TEST(UniversityDB, FindStudentBySurname_whenDBHasOneParticularStudent_thenDisallowToFindAnotherStudent) {
    UniversityDB universityDb;
    Student student("Mokebe", "Mensah", "ul. Wrocławska 3/4", "555666", "66052377411", Student::Gender::MALE);
    universityDb.addRecord(student);

    Student student_to_find;
    auto result = universityDb.findStudentBySurname("Mokebe", student_to_find);
    EXPECT_FALSE(result);
    EXPECT_FALSE(student == student_to_find);
}

TEST(UniversityDB, FindStudentByPesel_whenDBIsEmpty_thenDontLetFindAnyStudent) {
    UniversityDB universityDb;
    Student student("Mokebe", "Mensah", "ul. Wrocławska 3/4", "555666", "66052377411", Student::Gender::MALE);

    Student student_to_find;
    auto result = universityDb.findStudentByPesel("66052377411", student_to_find);
    EXPECT_FALSE(result);
    EXPECT_FALSE(student == student_to_find);
}

TEST(UniversityDB, FindStudentByPesel_whenDBHasOneParticularStudent_thenAllowToFindThisStudent) {
    UniversityDB universityDb;
    Student student("Mokebe", "Mensah", "ul. Wrocławska 3/4", "555666", "66052377411", Student::Gender::MALE);
    universityDb.addRecord(student);

    Student student_to_find;
    auto result = universityDb.findStudentByPesel("66052377411", student_to_find);
    EXPECT_TRUE(result);
    EXPECT_TRUE(student == student_to_find);
}

TEST(UniversityDB, FindStudentByPesel_whenDBHasOneParticularStudent_thenDisallowToFindAnotherStudent) {
    UniversityDB universityDb;
    Student student("Mokebe", "Mensah", "ul. Wrocławska 3/4", "555666", "66052377411", Student::Gender::MALE);
    universityDb.addRecord(student);

    Student student_to_find;
    auto result = universityDb.findStudentByPesel("00000000000", student_to_find);
    EXPECT_FALSE(result);
    EXPECT_FALSE(student == student_to_find);
}

TEST(UniversityDB, SortDBByPesel_whenDBIsEmpty_thenOnlyLetInvokeSortMethod) {
    UniversityDB universityDb;

    universityDb.sortByPesel();
}

TEST(UniversityDB, SortDBByPesel_whenDBHasOneStudent_thenDBShouldBeTheSameAsBefore) {
    UniversityDB universityDb;
    UniversityDB expectedDb;
    Student student("Mokebe", "Mensah", "ul. Wrocławska 3/4", "555666", "66052377411", Student::Gender::MALE);
    universityDb.addRecord(student);
    expectedDb.addRecord(student);

    universityDb.sortByPesel();

    universityDb.print();
    EXPECT_TRUE(universityDb == expectedDb);
}

TEST(UniversityDB, SortDBByPesel_whenDBHasTwoStudents_thenDBBeSorted) {
    UniversityDB universityDb;
    UniversityDB expectedDb;
    Student student("Mokebe", "Mensah", "ul. Wrocławska 3/4", "555666", "89012793171", Student::Gender::MALE);
    Student student2("Nbeppe", "Glappe", "ul. Wrocławska 3/4", "555666", "77073081476", Student::Gender::MALE);

    universityDb.addRecord(student);
    universityDb.addRecord(student2);
    expectedDb.addRecord(student2);
    expectedDb.addRecord(student);

    universityDb.sortByPesel();

    universityDb.print();
    EXPECT_TRUE(universityDb == expectedDb);
}

TEST(UniversityDB, SortDBByPesel_whenDBHasThreeStudents_thenDBBeSorted) {
    UniversityDB universityDb;
    UniversityDB expectedDb;
    Student student("Mokebe", "Mensah", "ul. Wrocławska 3/4", "555666", "89012793171", Student::Gender::MALE);
    Student student2("Nbeppe", "Glappe", "ul. Wrocławska 3/4", "555666", "77073081476", Student::Gender::MALE);
    Student student3("Leppe", "Meppe", "ul. Wrocławska 3/4", "555666", "96082899193", Student::Gender::MALE);

    universityDb.addRecord(student);
    universityDb.addRecord(student2);
    universityDb.addRecord(student3);

    expectedDb.addRecord(student2);
    expectedDb.addRecord(student);
    expectedDb.addRecord(student3);

    universityDb.sortByPesel();

    universityDb.print();
    EXPECT_TRUE(universityDb == expectedDb);
}

TEST(UniversityDB, SortDBBySurname_whenDBIsEmpty_thenOnlyLetInvokeSortMethod) {
    UniversityDB universityDb;

    universityDb.sortBySurname();
}

TEST(UniversityDB, SortDBBySurname_whenDBHasOneStudent_thenDBShouldBeTheSameAsBefore) {
    UniversityDB universityDb;
    UniversityDB expectedDb;
    Student student("Mokebe", "Mensah", "ul. Wrocławska 3/4", "555666", "66052377411", Student::Gender::MALE);
    universityDb.addRecord(student);
    expectedDb.addRecord(student);

    universityDb.sortBySurname();

    universityDb.print();
    EXPECT_TRUE(universityDb == expectedDb);
}

TEST(UniversityDB, SortDBBySurname_whenDBHasTwoStudents_thenDBBeSorted) {
    UniversityDB universityDb;
    UniversityDB expectedDb;
    Student student("Mokebe", "Mensah", "ul. Wrocławska 3/4", "555666", "89012793171", Student::Gender::MALE);
    Student student2("Nbeppe", "Glappe", "ul. Wrocławska 3/4", "555666", "77073081476", Student::Gender::MALE);

    universityDb.addRecord(student);
    universityDb.addRecord(student2);

    expectedDb.addRecord(student2);
    expectedDb.addRecord(student);

    universityDb.sortBySurname();

    universityDb.print();
    EXPECT_TRUE(universityDb == expectedDb);
}

TEST(UniversityDB, SortDBBySurname_whenDBHasThreeStudents_thenDBBeSorted) {
    UniversityDB universityDb;
    UniversityDB expectedDb;
    Student student("Mokebe", "Mensah", "ul. Wrocławska 3/4", "555666", "89012793171", Student::Gender::MALE);
    Student student2("Nbeppe", "Glappe", "ul. Wrocławska 3/4", "555666", "77073081476", Student::Gender::MALE);
    Student student3("Leppe", "Meppe", "ul. Wrocławska 3/4", "555666", "96082899193", Student::Gender::MALE);

    universityDb.addRecord(student);
    universityDb.addRecord(student2);
    universityDb.addRecord(student3);

    expectedDb.addRecord(student2);
    expectedDb.addRecord(student);
    expectedDb.addRecord(student3);

    universityDb.sortBySurname();

    universityDb.print();
    EXPECT_TRUE(universityDb == expectedDb);
}

TEST(UniversityDB, DeleteStudent_whenDBIsEmpty_thenDeletionShouldntChangeAnything) {
    UniversityDB universityDb;
    EXPECT_TRUE(universityDb.numberOfRecords() == 0);

    auto deleted = universityDb.deleteById("555666");

    EXPECT_FALSE(deleted);
    EXPECT_TRUE(universityDb.numberOfRecords() == 0);
}

TEST(UniversityDB, DeleteStudent_whenDBHasOneStudent_thenDeletionShouldMakeDBEmpty) {
    UniversityDB universityDb;
    EXPECT_TRUE(universityDb.numberOfRecords() == 0);
    Student student("Mokebe", "Mensah", "ul. Wrocławska 3/4", "555666", "66052377411", Student::Gender::MALE);
    universityDb.addRecord(student);

    auto deleted = universityDb.deleteById("555666");

    EXPECT_TRUE(deleted);
    EXPECT_TRUE(universityDb.numberOfRecords() == 0);
}

TEST(UniversityDB, DeleteStudent_whenDBHasTwoStudents_thenSingleDeletionShouldRemainOneRecord) {
    UniversityDB universityDb;
    EXPECT_TRUE(universityDb.numberOfRecords() == 0);
    Student student("Mokebe", "Mensah", "ul. Wrocławska 3/4", "555666", "66052377411", Student::Gender::MALE);
    Student student2("Mokebe", "Mensah", "ul. Wrocławska 3/4", "111111", "89012793171", Student::Gender::MALE);
    universityDb.addRecord(student);
    universityDb.addRecord(student2);

    auto deleted = universityDb.deleteById("555666");

    EXPECT_TRUE(deleted);
    EXPECT_TRUE(universityDb.numberOfRecords() == 1);
}

TEST(UniversityDBBackup, IntegrationTest_whenBackupDataToFileAndCleanDB_thenRetrieveDataFromFileAndCheckIfDBIsTheSameAsAtBeggining) {
    UniversityDB universityDb;
    UniversityDB expectedDb;
    Student student("Mokebe", "Mensah", "ul. Wrocławska 3/4", "555666", "66052377411", Student::Gender::MALE);
    Student student2("Nbeppe", "Glappe", "ul. Wrocławska 3/4", "555666", "89012793171", Student::Gender::MALE);
    Student student3("Leppe", "Meppe", "ul. Wrocławska 3/4", "555666", "01251788145", Student::Gender::MALE);

    // Make two the same DBs
    universityDb.addRecord(student);
    universityDb.addRecord(student2);
    universityDb.addRecord(student3);
    expectedDb.addRecord(student);
    expectedDb.addRecord(student2);
    expectedDb.addRecord(student3);

    EXPECT_TRUE(universityDb == expectedDb);

    UniversityDBBackup backup{universityDb};

    // here any mock for JSON dependencies?
    backup.archiveDB();
    backup.cleanDB();
    EXPECT_TRUE(universityDb.numberOfRecords() == 0);
    EXPECT_FALSE(universityDb == expectedDb);

    backup.retrieveData();

    EXPECT_TRUE(universityDb.numberOfRecords() == 3);

    universityDb.print();
    expectedDb.print();

    EXPECT_TRUE(universityDb == expectedDb);
}

TEST(PeselValidation, hasIncorrectAmountOfDigitsCorrectEqualsToElevenDigits) {
    std::string incorrect_pesel_str = "0001112221";

    PeselValidator validator;
    EXPECT_FALSE(validator.validate(incorrect_pesel_str));
}

TEST(PeselValidation, checkAFewCasesFromWikipedia) {
    PeselValidator validator;
    std::string pesel_str = "55030101193";
    EXPECT_TRUE(validator.validate(pesel_str));

    std::string pesel_str2 = "55030101230";
    EXPECT_TRUE(validator.validate(pesel_str2));

    std::string pesel_str3 = "00011100011";
    EXPECT_FALSE(validator.validate(pesel_str3));
}

TEST(PeselValidation, checkAFewFromOnlineGenerator) {
    PeselValidator validator;
    std::vector<std::string> pesels =
        {
            "77073081476",
            "56052891561",
            "96082899193",
            "73022588919",
            "70011969669",
            "66052377411",
            "73062495473",
            "70111054227",
            "89012793171",
            "01251788145"};

    for (auto pesel : pesels) {
        EXPECT_TRUE(validator.validate(pesel));
    }
}
