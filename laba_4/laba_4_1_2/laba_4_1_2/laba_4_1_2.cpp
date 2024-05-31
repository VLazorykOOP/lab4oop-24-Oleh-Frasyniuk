#include <iostream>
#include <cmath>

class VectorFloat {
private:
    float* ptr; //вказівник на масив дійсних чисел
    int size;   //кількість елементів у векторі
    int codeError; //код помилки

public:
    //конструктор без параметрів
    VectorFloat() : size(1), codeError(0) {
        ptr = new float[size];
        ptr[0] = 0.0f;
    }

    //конструктор з одним параметром
    VectorFloat(int s) : size(s), codeError(0) {
        ptr = new float[size];
        for (int i = 0; i < size; ++i) {
            ptr[i] = 0.0f;
        }
    }

    //конструктор із двома параметрами
    VectorFloat(int s, float value) : size(s), codeError(0) {
        ptr = new float[size];
        for (int i = 0; i < size; ++i) {
            ptr[i] = value;
        }
    }

    //деструктор
    ~VectorFloat() {
        delete[] ptr;
    }

    //перевантаження оператора ++i збільш на один та присвоєння (префіксний)
    VectorFloat& operator++() {
        for (int i = 0; i < size; ++i) {    
            if (ptr[i] < std::numeric_limits<float>::max()) {
                ++ptr[i];
            }
            else {
                codeError = -1; //перевищення максимального значення для float
            }
        }
        return *this;
    }

    //перевантаження оператора i++ присвоєння п а потім збільшення (постфіксний)
    VectorFloat operator++(int) {
        VectorFloat tmp(*this);
        operator++();
        return tmp;
    }

    //перевантаження оператора -- (префіксний)
    VectorFloat& operator--() {
        for (int i = 0; i < size; ++i) {
            --ptr[i];
        }
        return *this;
    }

    //перевантаження оператора -- (постфіксний)
    VectorFloat operator--(int) {
        VectorFloat tmp(*this);
        operator--();
        return tmp;
    }

    //перевантаження оператора ! (заперечення)
    bool operator!() const {
        return size != 0;
    }

    //перевантаження оператора мінус
    VectorFloat operator-() const {
        VectorFloat result(size);
        for (int i = 0; i < size; ++i) {
            result.ptr[i] = -ptr[i];
        }
        return result;
    }

    //перевантаження оператора =
    VectorFloat& operator=(const VectorFloat& other) {
        if (this != &other) {
            delete[] ptr;
            size = other.size;
            ptr = new float[size];
            for (int i = 0; i < size; ++i) {
                ptr[i] = other.ptr[i];
            }
        }
        return *this;
    }

    //перевантаження оператора +=
    VectorFloat& operator+=(const VectorFloat& other) {
        for (int i = 0; i < size; ++i) {
            if (ptr[i] < std::numeric_limits<float>::max() - other.ptr[i]) {
                ptr[i] += other.ptr[i];
            }
            else {
                codeError = -1; //перевищення максимального значення для float
            }
        }
        return *this;
    }

    //перевантаження оператора -=
    VectorFloat& operator-=(const VectorFloat& other) {
        for (int i = 0; i < size; ++i) {
            ptr[i] -= other.ptr[i];
        }
        return *this;
    }

    //перевантаження оператора *=
    VectorFloat& operator*=(float scalar) {
        for (int i = 0; i < size; ++i) {
            ptr[i] *= scalar;
        }
        return *this;
    }

    //перевантаження оператора /=
    VectorFloat& operator/=(float scalar) {
        if (scalar != 0) {
            for (int i = 0; i < size; ++i) {
                ptr[i] /= scalar;
            }
        }
        else {
            codeError = -1; //ділення на 0
        }
        return *this;
    }

    //перевантаження оператора %=
    VectorFloat& operator%=(float scalar) {
        if (scalar != 0) {
            for (int i = 0; i < size; ++i) {
                ptr[i] = std::fmod(ptr[i], static_cast<float>(scalar));
            }
        }
        else {
            codeError = -1; // Ділення на нуль
        }
        return *this;
    }

    //перевантаження оператора +
    VectorFloat operator+(const VectorFloat& other) const {
        VectorFloat result(*this);
        result += other;
        return result;
    }

    //перевантаження оператора -
    VectorFloat operator-(const VectorFloat& other) const {
        VectorFloat result(*this);
        result -= other;
        return result;
    }

    //перевантаження оператора *
    VectorFloat operator*(float scalar) const {
        VectorFloat result(*this);
        result *= scalar;
        return result;
    }

    //перевантаження оператора /
    VectorFloat operator/(float scalar) const {
        VectorFloat result(*this);
        result /= scalar;
        return result;
    }

    //перевантаження оператора %
    VectorFloat operator%(float scalar) const {
        VectorFloat result(*this);
        result %= scalar;
        return result;
    }

    //перевантаження оператора ==
    bool operator==(const VectorFloat& other) const {
        if (size != other.size)
            return false;

        for (int i = 0; i < size; ++i) {
            if (ptr[i] != other.ptr[i])
                return false;
        }

        return true;
    }

    //перевантаження оператора !=
    bool operator!=(const VectorFloat& other) const {
        return !(*this == other);
    }

    //перевантаження оператора []
    float& operator[](int index) {
        if (index < 0 || index >= size) {
            codeError = -1; //помилковий індекс
            index = size - 1; //вказуємо на останній елемент
        }
        return ptr[index];
    }

    //перевантаження оператора ()
    float& operator()(int index) {
        return (*this)[index];
    }

    //перевантаження оператора <
    bool operator<(const VectorFloat& other) const {
        if (size != other.size)
            return false;

        for (int i = 0; i < size; ++i) {
            if (ptr[i] >= other.ptr[i])
                return false;
        }

        return true;
    }

    //перевантаження оператора <=
    bool operator<=(const VectorFloat& other) const {
        return (*this < other) || (*this == other);
    }

    //перевантаження оператора >
    bool operator>(const VectorFloat& other) const {
        return !(*this <= other);
    }

    //перевантаження оператора >=
    bool operator>=(const VectorFloat& other) const {
        return !(*this < other);
    }

    //перевантаження оператора виведення <<
    friend std::ostream& operator<<(std::ostream& os, const VectorFloat& vec) {
        for (int i = 0; i < vec.size; ++i) {
            os << vec.ptr[i] << " ";
        }
        return os;
    }

    //перевантаження оператора введення >>
    friend std::istream& operator>>(std::istream& is, VectorFloat& vec) {
        for (int i = 0; i < vec.size; ++i) {
            is >> vec.ptr[i];
        }
        return is;
    }

    //функція для отримання помилки
    int getErrorCode() const {
        return codeError;
    }
};

int main() {
    //приклад використання класу VectorFloat
    VectorFloat v1(5, 2.0); //ств вектору розміром 5 з усіма елементами 2.0
    std::cout << "Initial vector v1: " << v1 << std::endl;

    v1++; //збільшення всіх елементів вектора на 1
    std::cout << "Vector v1 after increment: " << v1 << std::endl;

    VectorFloat v2(5, 3.0);
    std::cout << "Initial vector v2: " << v2 << std::endl;

    VectorFloat v3 = v1 + v2; //додавання векторів v1 та v2
    std::cout << "Vector v1 + v2: " << v3 << std::endl;

    VectorFloat v4 = -v3; //від'ємне значення вектора v3
    std::cout << "Negative vector v3: " << v4 << std::endl;

    VectorFloat v5 = v4 * 2; //помноження вектора v4 на 2
    std::cout << "Vector v4 * 2: " << v5 << std::endl;

    VectorFloat v6 = v5 / 2; //поділ вектора v5 на 2
    std::cout << "Vector v5 / 2: " << v6 << std::endl;

    VectorFloat v7 = v6 % 3; //остача від ділення вектора v6 на 3
    std::cout << "Vector v6 % 3: " << v7 << std::endl;

    // Перевірка наявності помилок
    if (v7.getErrorCode() != 0) {
        std::cout << "Error occurred: Division by zero or invalid index." << std::endl;
    }

    return 0;
}
