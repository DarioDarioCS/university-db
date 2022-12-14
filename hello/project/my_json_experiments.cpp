#include <clocale>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

#include <fstream>
#include <vector>

using json = nlohmann::json;

void simple_example() {
    // Tworzenie obiektu JSON z danymi
    nlohmann::json data = {
        {"Number of records", 3},
        {"Records", {{{"Imię", "Alan"}, {"Nazwisko", "Moke"}, {"Adres", "ul. Sieśka 1/4"}, {"Numer ID", 666666}, {"Pesel", 85657510024}, {"Płeć", "Mężczyzna"}}, {{"Imię", "Lepe"}, {"Nazwisko", "Mene"}, {"Adres", "ul. Wiejska 4/4"}, {"Numer ID", 555666}, {"Pesel", 85657510025}, {"Płeć", "Mężczyzna"}}, {{"Imię", "Pepe"}, {"Nazwisko", "Vege"}, {"Adres", "ul. Burmańska 2/4"}, {"Numer ID", 555666}, {"Pesel", 85657510026}, {"Płeć", "Mężczyzna"}}}}

    };
    // Serializacja danych do formatu JSON
    std::string json_string = data.dump(4, ' ');

    std::cout << std::setw(4) << json_string << std::endl;
}

void example1_save_string_data_to_file() {
    std::vector<std::string> data{
        "Alan, Moke, ul. Sieśka 1/4, 666666, 85657510024, Mężczyzna",
        "Lepe, Mene, ul. Wiejska 4/4, 555666, 85657510025, Mężczyzna",
        "Pepe, Vege, ul. Burmańska 2/4, 555666, 85657510026, Mężczyzna"};

    // Utwórz obiekt JSON do przechowywania danych
    nlohmann::json json_data;

    // Dodaj informację o liczbie rekordów
    json_data["Number of records"] = data.size();

    // Dodaj rekordy do obiektu JSON
    for (const auto& record : data) {
        // Podziel rekord na poszczególne elementy
        std::vector<std::string> elements;
        std::stringstream ss(record);
        std::string element;
        while (std::getline(ss, element, ',')) {
            elements.push_back(element);
        }

        // Utwórz obiekt JSON dla pojedynczego rekordu
        nlohmann::json json_record;
        json_record["Imię"] = elements[0];
        json_record["Nazwisko"] = elements[1];
        json_record["Adres"] = elements[2];
        json_record["Numer ID"] = elements[3];
        json_record["Pesel"] = elements[4];
        json_record["Płeć"] = elements[5];

        // Dodaj obiekt JSON dla pojedynczego rekordu do obiektu JSON z całymi danymi
        json_data["Records"].push_back(json_record);
    }

    // Otwórz plik do zapisu
    std::ofstream out_file("data.json");
    if (out_file.is_open()) {
        // Zapisz dane w formacie JSON do pliku
        out_file << json_data.dump(4);  // 4 oznacza ilość wcięć w pliku wyjściowym

        // Zamknij plik
        out_file.close();
    } else {
        std::cerr << "Error opening file for writing!" << std::endl;
    }
}

struct Record {
    std::string name;
    std::string surname;
    std::string address;
    std::string id;
    std::string pesel;
    std::string gender;
};

void example2_load_json_data_from_file_to_container() {
    std::vector<Record> records;
    std::ifstream in_file("data.json");
    if (in_file.is_open()) {
        // Odczytaj dane z pliku do zmiennej typu std::string
        std::string data((std::istreambuf_iterator<char>(in_file)),
                         std::istreambuf_iterator<char>());
        // Zamknij plik
        in_file.close();

        // Użyj biblioteki nlohmann::json do przetworzenia danych z formacie JSON na obiekt JSON
        nlohmann::json json_data = nlohmann::json::parse(data);

        // Odczytaj liczbę rekordów z obiektu JSON
        int num_records = json_data["Number of records"];

        // Utwórz wektor do przechowywania rekordów

        records.reserve(num_records);

        // Iteruj przez rekordy w obiekcie JSON i dodaj je do wektora
        for (const auto& json_record : json_data["Records"]) {
            Record record;
            record.name = json_record["Imię"];
            record.surname = json_record["Nazwisko"];
            record.address = json_record["Adres"];
            record.id = json_record["Numer ID"];
            record.pesel = json_record["Pesel"];
            record.gender = json_record["Płeć"];
            records.push_back(record);
        }
    } else {
        std::cout << "Nie otworzono pliku. Koniec\n";
        return;
    }

    std::cout << "Wczytane dane:" << std::endl;
    std::cout << "BazaDanychDB" << std::endl;
    std::cout << "Number of records: " << records.size() << std::endl;
    for (const auto& record : records) {
        std::cout << record.name << ", " << record.surname << ", "
                  << record.address << ", " << record.id << ", "
                  << record.pesel << ", " << record.gender << std::endl;
    }
}

int main() {
    example1_save_string_data_to_file();
    example2_load_json_data_from_file_to_container();

    return 0;
}