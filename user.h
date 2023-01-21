//Файл user.h
#pragma once
#include <string>
#include <memory>
#include "iobserver.h"
#include "ipublisher.h"

//Класс для пользователя
class User : public IObserver {
	const std::string login_;//поле для логина
	std::string password_;//поле для пароля
	std::string name_;//поле для имени
	unsigned int amountSelfMessages_; //количество личных сообщений
	unsigned int newSelfMessages_;  //количество новых непрочитыннах личных сообщений
	unsigned int newAllMessages_; //количество новых непрочитанных сообщений в общем чате
	bool isSubribes_; //пользователь подписан на оповещения
	std::shared_ptr<IPublisher*> publisher_; //указатель на издателя
public:
	//Конструктор по умолчанию
	User() : login_("UNKNOWN"), password_("UNKNOWN"), name_("UNKNOWN"), amountSelfMessages_(0), newSelfMessages_(0), newAllMessages_(0), isSubribes_(false), publisher_(nullptr) {}
	//Параметризированный конструктор
	User(const std::string& login, const std::string& password, const std::string& name, std::shared_ptr<IPublisher*> publisher)
		: login_(login), password_(password), name_(name), amountSelfMessages_(0), newSelfMessages_(0), newAllMessages_(0), isSubribes_(false), publisher_(publisher) {}

	const std::string& getLogin() const;//получить логин

	//Получить статус подписки
	bool getIsSubscribes() const;

	unsigned int getAmountSelfMessages(); //получить количество личных сообщений
	unsigned int getNewSelfMessages();  //получить количество новых непрочитыннах личных сообщений
	unsigned int getNewAllMessages(); //получить количество новых непрочитанных сообщений в общем чате

	virtual ~User() override = default;//деструктор класса

	void updateInformationAll() override;//обновить информацию полученную от Издателя про общий чат
	void updateInformationSelf() override;//обновить информацию полученную от Издателя про личные сообщения
	bool isThisI(const std::string& str) override;//метод для сравнения поля логин с переданным значением
	void subscribe(); //подписаться на рассылку
	void unscribe();//отписаться от рассылки

	//Проверка логина
	bool checkLogin(const std::string &login) const;

	//Проверка пароля
	bool checkPassword(const std::string& password) const;

	//Сбросить количество непрочитанных сообщений в общем чате в 0
	void resetNewAllMessages();

	//Сбросить количество непрочитанных сообщений в личных сообщениях в 0
	void resetNewSelfMessages();

	//Установить значение для amountSelfMessages_
	void setAmountSelfMessages(unsigned int n);
};