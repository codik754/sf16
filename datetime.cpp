//Файл datetime.cpp

#include "datetime.h"
#include "chat.h"
#include <ctime>
#include <sstream>

//Конструктор по умолчанию
Datetime::Datetime() {
    std::time_t t = std::time(nullptr);
    std::tm now;
    localtime_s(&now, &t);

    sec_ = now.tm_sec;
    min_ = now.tm_min;
    hour_ = now.tm_hour;
    day_ = now.tm_mday;
    month_ = now.tm_mon + 1;
    year_ = now.tm_year + 1900;
}

//Конструктор копирования
Datetime::Datetime(const Datetime& other) {
    sec_ = other.sec_;
    min_ = other.min_;
    hour_ = other.hour_;
    day_ = other.day_;
    month_ = other.month_;
    year_ = other.year_;
}

//Оператор присваивания
Datetime& Datetime::operator = (const Datetime &other) {
    //Проверка на самоприсваивание
    if (&other == this) {
        return *this;
    }
    sec_ = other.sec_;
    min_ = other.min_;
    hour_ = other.hour_;
    day_ = other.day_;
    month_ = other.month_;
    year_ = other.year_;
    return *this;
}

//Установить текущие время
void Datetime::setNow() {
    std::time_t t = std::time(nullptr);
    std::tm now;
    localtime_s(&now, &t);

    sec_ = now.tm_sec;
    min_ = now.tm_min;
    hour_ = now.tm_hour;
    day_ = now.tm_mday;
    month_ = now.tm_mon + 1;
    year_ = now.tm_year + 1900;
}

//Получить дату и время в виде строки
const std::string Datetime::getStrAll() const {
    std::ostringstream os;
    os << day_ << "." << month_ << "." << year_ << "  " << hour_ << ":" << min_ << ":" << sec_;
    return os.str();
}

//Получить дату в виде строки
const std::string Datetime::getStrDate() const {
    std::ostringstream os;
    os << day_ << "." << month_ << "." << year_;
    return os.str();
}

//Получить время в виде строки
const std::string Datetime::getStrTime() const {
    std::ostringstream os;
    os << hour_ << ":" << min_ << ":" << sec_;
    return os.str();
}
