#include <iostream>
#include <map>
#include <string>

class CountryCapitalMap {
private:
    std::map<std::string, std::string> countryToCapital; //масив для збереження країн та їх столиць
    int codeError; //змінна для зберігання коду помилки

public:
    //конструктор за замовчуванням
    CountryCapitalMap() : codeError(0) {}

    //функція для додавання країни та столиці
    void add(const std::string& country, const std::string& capital) {
        countryToCapital[country] = capital;
    }

    //перевантаження оператора індексації []
    std::string& operator[](const std::string& country) {
        if (countryToCapital.find(country) != countryToCapital.end()) {
            codeError = 0; //код помилки - немає помилки
            return countryToCapital[country];
        }
        else {
            codeError = -1; //код помилки - відсутня країна
            return countryToCapital.begin()->second; //повертаємо столицю першої країни у мапі
        }
    }

    //перевантаження оператора виклику функції ()
    std::string getByCountry(const std::string& country) {
        return (*this)[country];
    }

    //функція для отримання коду помилки
    int getErrorCode() const {
        return codeError;
    }

    //перевантаження оператора виведення <<
    friend std::ostream& operator<<(std::ostream& os, const CountryCapitalMap& obj) {
        for (const auto& pair : obj.countryToCapital) {
            os << pair.first << ": " << pair.second << std::endl;
        }
        return os;
    }

    //перевантаження оператора введення >>
    friend std::istream& operator>>(std::istream& is, CountryCapitalMap& obj) {
        std::string country, capital;
        std::cout << "Enter country: ";
        is >> country;
        std::cout << "Enter capital: ";
        is >> capital;
        obj.add(country, capital);
        return is;
    }
};

int main() {
    CountryCapitalMap map;

    //додавання країн та столиць
    map.add("Ukraine", "Kyiv");
    map.add("Germany", "Berlin");
    map.add("France", "Paris");

    //виведення масиву
    std::cout << "Countries and their capitals:" << std::endl;
    std::cout << map;

    //отримання столиці за назвою країни
    std::string country;
    std::cout << "Enter a country to get its capital: ";
    std::cin >> country;
    std::string capital = map.getByCountry(country);
    if (map.getErrorCode() == 0)
        std::cout << "Capital of " << country << " is " << capital << std::endl;
    else
        std::cout << "Country not found." << std::endl;

    //додавання нової країни та столиці через перевантажений оператор введення >>
    std::cin >> map;

    //виведення масиву після додавання 
    std::cout << "Updated countries and their capitals:" << std::endl;
    std::cout << map;

    return 0;
}
