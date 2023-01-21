//Файл chat.h
#pragma once
#include "ipublisher.h"
#include <vector>
#include <list>
#include <memory>
#include "user.h"
#include "message.h"
#include <windows.h>
#include "sha256.h"


//Класс для чата
class Chat : public IPublisher {
	std::vector<User> users_;   //вектор пользователей зарегестрировавшихся в системе
	std::vector<Message> message_;//вектор сообщений
	std::list<IObserver*> subscribers_; //список подписчиков
	unsigned int amountAll_;//общее количество общих сообщений
	HANDLE hConsole_;//поле нужно для работы с цветом в консоле Windows
	std::unique_ptr<User*> currentUser;//указатель на текущего пользователя

public:
	//Конструктор по умолчанию
	Chat() : users_(), message_(), subscribers_(), amountAll_(0), hConsole_(GetStdHandle(STD_OUTPUT_HANDLE)), currentUser(nullptr) {
		//Создаем пользователя и добавляем в вектор
		users_.reserve(100);//резервируем место для вектора
		SHA256 sha256;//создаем объект для хеширования пароля
		users_.emplace_back("admin", sha256("a123"), "ADMIN", std::make_unique<IPublisher*>(this));
	}

	virtual ~Chat() override = default;//деструктор класса

	void attach(IObserver* observer) override; //добавить наблюдателя на подписку
	void detach(IObserver* observer) override; //исключить наблюдателя из подписки
	void notifyAboutAll() override; //разослать информацию про общий чат
	void notifyAboutSelf(const std::string& login) override; //проинформировать про личное сообщение

	unsigned int getAmountSelfMessage(const std::string &login) const;//получить общее количество личных сообщений для пользователя

	char showHelloMenu();//показать первое меню

	void showRegistrationMenu();//показать меню регистрации
	void showLogIn();//показать меню для входа
	void showChatMenu();//показать меню общего чата
	void showWriteMessageMenu();//показать меню для написания сообщений

	void setColorToConsole(WORD n);//установить цвет в консоле

	std::unique_ptr<User*> getUser(const std::string &login, const std::string &password);//получить пользователя с определенным логином и паролем

	bool checkLogin(const std::string& login);//проверка существует ли пользователь с таким логином

	void addMessage(const std::string& from, const std::string &to, const std::string& text);//добавить сообщение
};

