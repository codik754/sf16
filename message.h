//Файл message.h
#pragma once
#include <string>
#include "datetime.h"

//Класс для сообщений
class Message {
	const std::string sendedFrom_;//от кого отправлено сообщение
	const std::string sendedTo_;  //кому отправлено сообщение
	const std::string text_;	//текст сообщения
	const Datetime dateandtime_; //дата отправки сообщения
public:
	//Конструктор по умолчанию
	Message();
	//Конструктор с параметрами
	Message(const std::string& from, const std::string& to, const std::string& text);
	//Конструктор копирования
	Message(const Message& other);
	//Деструктор
	~Message() = default;
	
	//Оператор присваивания
	const Message& operator = (const Message& other);

	//Узнать от кого отправлено сообщение
	const std::string& getSendedFrom() const;
	//Получить текст сообщения
	const std::string& getText() const;
	//Получить дату и время
	const std::string getDatetime() const;
	//Соответсвует ли поле кому отправлено сообщение переданной строке
	bool checkToSendedTo(const std::string &login) const;
};
