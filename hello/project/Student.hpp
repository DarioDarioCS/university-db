#pragma once
#include <string>

#include <exception>
#include <iostream>
#include <sstream>
#include <vector>

class PeselValidationException : public std::exception {
private:
    std::string message;

public:
    PeselValidationException(const std::string& msg)
        : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class PeselValidator {
    class PeselTable {
        const std::string W_k = "13791379131";
        std::string C_k;
        std::string I_k;

    public:
        PeselTable(const std::string pesel)
            : C_k{pesel} {
            C_k.reserve(11);
            I_k.reserve(11);
        }
        char getControlDigit() const {
            return C_k.at(10);
        }
        void setControlDigit(char controlDigit) {
            C_k[10] = controlDigit;
        }
        const std::string getFirstTenCKDigits() const {
            return C_k.substr(0, 10);
        }

        const std::string getFirstTenWKDigits() const {
            return W_k.substr(0, 10);
        }

        std::vector<std::string> getIkDigits() {
            auto ck_digits = getFirstTenCKDigits();
            auto wk_digits = getFirstTenWKDigits();

            std::vector<std::string> ik_digits;
            for (std::size_t i = 0; i < ck_digits.size(); ++i) {
                int ck_digitInt = ck_digits[i] - '0';
                int wk_digitInt = wk_digits[i] - '0';

                auto result = ck_digitInt * wk_digitInt;

                std::string result_string;
                std::stringstream ss;
                ss << result;
                ss >> result_string;
                ik_digits.emplace_back(result_string);
            }

            return ik_digits;
        }

        int getSumOfIKs() {
            int S = 0;
            for (auto ik_digit : getIkDigits()) {
                int ik_digitInt = std::stoi(ik_digit);
                S += ik_digitInt;
            }
            return S;
        }

        int getM() {
            int result;
            result = getSumOfIKs() % 10;
            return result;
        }

        int tenMinusM() {
            int result;
            result = 10 - getM();
            return result;
        }

        int getControlDigitInt() {
            return getControlDigit() - '0';
        }

        bool checkM() {
            // https://pl.wikipedia.org/wiki/PESEL#Cyfra_kontrolna_i_sprawdzanie_poprawno%C5%9Bci_numeru
            if (getM() == 0) {
                if (getControlDigitInt() == 0) {
                    return true;
                }
            } else {
                if (tenMinusM() == getControlDigitInt()) {
                    return true;
                }
            }
            return false;
        }
    };

public:
    PeselValidator(){};
    bool validate(const std::string& pesel) {
        if (pesel.size() == 11) {
            PeselTable table{pesel};
            return table.checkM();
        }
        return false;
    }
};

class Student {
    PeselValidator peselValidator;

public:
    enum class Gender {
        MALE,
        FEMALE
    };

    Student()
        : name("Kłentin"),
          surname("Lewandowski"),
          address("ul Wrocławska, Koziebrody"),
          id("652232"),
          pesel("66052377411"),
          gender(Gender::MALE) {
        PeselValidator peselValidator;
        peselValidator = peselValidator;
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
          gender(gender) {
        if (false == peselValidator.validate(pesel)) {
            throw PeselValidationException("Pesel is invalid\n");
        }
    }

    inline bool operator==(const Student& other) const {
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

    const std::string getName() const {
        return name;
    }
    const std::string getSurname() const {
        return surname;
    }
    const std::string getAddress() const {
        return address;
    }
    const std::string getId() const {
        return id;
    }
    const std::string getPesel() const {
        return pesel;
    }
    enum Gender getGender() const {
        return gender;
    }
};

class StudentPrinter {
public:
    static std::string printStudentToPlainText(const Student& student);
};

class StudentAccessor {
public:
    static std::string getSurname(const Student& student);
    static std::string getPesel(const Student& student);
    static std::string getId(const Student& student);
    static Student::Gender getGenderByStr(const std::string& genderStr) {
        if (genderStr == "Kobieta") {
            return Student::Gender::FEMALE;
        } else {
            return Student::Gender::MALE;
        }
    }
    struct SortByPesel {
        bool operator()(Student a, Student b) const { return a.pesel < b.pesel; }
    };
    struct SortBySurname {
        bool operator()(Student a, Student b) const { return a.surname < b.surname; }
    };
};

class StudentFactory {
public:
    StudentFactory() {}
    Student cloneStudent(const Student& student);
};
