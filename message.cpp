//Файл message.cpp
#include "message.h"

//Конструктор по умолчанию
Message::Message() : sendedFrom_("UNKNOWN"), sendedTo_("UNKNOWN"), text_("UNKNOWN"), dateandtime_() {}

//Конструктор с параметрами
Message::Message(const std::string& from, const std::string& to, const std::string& text) : sendedFrom_(from), sendedTo_(to), text_(text), dateandtime_() {}

//Конструктор копирования
Message::Message(const Message& other) : sendedFrom_(other.sendedFrom_), sendedTo_(other.sendedTo_), text_(other.text_), dateandtime_(other.dateandtime_) {}

//Оператор присваивания
const Message& Message::operator = (const Message& other) {
	return *this;
}

//Узнать от кого отправлено сообщение
const std::string& Message::getSendedFrom() const {
	return sendedFrom_;
}

//Получить текст сообщения
const std::string& Message::getText() const {
	return text_;
}

//Получить дату и время
const std::string Message::getDatetime() const {
	return dateandtime_.getStrAll();
}

//Соответсвует ли поле кому отправлено сообщение переданной строке
bool Message::checkToSendedTo(const std::string& login) const {
	if (sendedTo_ == login) {
		return true;
	}
	else {
		return false;
	}
}
