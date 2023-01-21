//Файл user.cpp
#include "user.h"

//Получить логин
const std::string& User::getLogin() const {
	return login_;
}

//Обновить информацию полученную от Издателя про общий чат
void User::updateInformationAll() {
	++newAllMessages_;
}

//Обновить информацию полученную от Издателя про личные сообщения
void User::updateInformationSelf() {
	++newSelfMessages_;
}

//метод для сравнения поля логин с переданным значением
bool User::isThisI(const std::string& str) {
	if (login_ == str) {
		return true;
	}
	else {
		return false;
	}
}

//Подписаться на уведомления
void User::subscribe() {
	(*publisher_)->attach(this);
	isSubribes_ = true;
}

//Отписаться от уведомления
void User::unscribe() {
	(*publisher_)->detach(this);
	isSubribes_ = false;
}

//Проверка логина
bool User::checkLogin(const std::string& login) const {
	if (login_ == login) {
		return true;
	}
	else {
		return false;
	}
}

//Проверка пароля
bool User::checkPassword(const std::string& password) const {
	if (password_ == password) {
		return true;
	}
	else {
		return false;
	}
}

//Получить статус подписки
bool User::getIsSubscribes() const {
	return isSubribes_;
}

//Получить количество личных сообщений
unsigned int User::getAmountSelfMessages() {
	return amountSelfMessages_;
}

//Получить количество новых непрочитыннах личных сообщений
unsigned int User::getNewSelfMessages() {
	return newSelfMessages_;
} 

//Получить количество новых непрочитанных сообщений в общем чате
unsigned int User::getNewAllMessages() {
	return newAllMessages_;
}

//Сбросить количество непрочитанных сообщений в общем чате в 0
void User::resetNewAllMessages() {
	newAllMessages_ = 0;
}

//Сбросить количество непрочитанных сообщений в личных сообщениях в 0
void User::resetNewSelfMessages() {
	newSelfMessages_ = 0;
}

//Установить значение для amountSelfMessages_
void User::setAmountSelfMessages(unsigned int n) {
	amountSelfMessages_ = n;
}