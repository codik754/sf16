//Файл baddata.h
#pragma once
#include <exception>
#include <string>

//Класс для исключений
class bad_data : public std::exception {
	std::string _message;//сообщение
public:
	//Конструктор по умолчанию
	bad_data() : _message("Exception bad_length") {}
	//Параметризированные конструкторы
	explicit bad_data(const std::string& message) : _message(message) {}

	//Переопределяем метод what
	virtual const char* what() const noexcept override;
};