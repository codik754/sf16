//Файл baddata.cpp
#include "baddata.h"

// Переопределяем метод what
const char* bad_data::what() const noexcept {
	return _message.c_str();
}