//Файл ipublisher.h
#pragma once
#include "iobserver.h"

//Интерфейс для Издателя
class IPublisher {
public:
	virtual ~IPublisher() = default; //деструктор класса

	virtual void attach(IObserver* observer) = 0; //добавить наблюдателя на подписку
	virtual void detach(IObserver* observer) = 0; //исключить наблюдателя из подписки
	virtual void notifyAboutAll() = 0; //разослать информацию про общий чат
	virtual void notifyAboutSelf(const std::string& login) = 0; //проинформировать про личное сообщение
};
