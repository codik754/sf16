//Файл chat.cpp
#include "chat.h"
#include <iostream>
#include <cstdlib>
#include "baddata.h"
#include <exception>
#include <algorithm> 

//Добавить наблюдателя на подписку
void Chat::attach(IObserver* observer) {
    subscribers_.push_back(observer);
}

//Исключить наблюдателя из подписки
void Chat::detach(IObserver* observer) {
    subscribers_.remove(observer);
}

//Разослать информацию про общий чат
void Chat::notifyAboutAll() {
    for (auto &subscriber : subscribers_) {
        subscriber->updateInformationAll();
    }
} 

//Проинформировать про личное сообщение
void Chat::notifyAboutSelf(const std::string& login) {
  for (auto subscriber : subscribers_) {
        //Если логин совпадает с ллогином пользователя в списке
        if (subscriber->isThisI(login)) {
            //Информируем пользователя
            subscriber->updateInformationSelf();
        }
   }
}

//Показать первое меню
char Chat::showHelloMenu() {
    char choice = '0';//переменная для выбора
    while (true) {
        setColorToConsole(6);
        std::cout << "Добрый день! Добро пожаловать в чат. Что будем делать?" << std::endl;
        std::cout << "1. Войти" << std::endl;
        std::cout << "2. Регистрация" << std::endl;
        std::cout << "q - Выход" << std::endl;
        setColorToConsole(3);
        std::cout << std::endl << "Введите символ: ";
        std::cin >> choice;
        //Если введены символы соответствующие требуемым
        if (choice == '1' || choice == '2' || choice == 'q') {
            break;
        }
        else {
            //Если введены символы не соответствующие выбранным
            system("cls");
            setColorToConsole(4);
            std::cout << "Команды " << choice << " не знаю!!!" << std::endl;
            setColorToConsole(15);
            system("pause");
            system("cls");
        }
    }
    setColorToConsole(15);
    system("cls");
    return choice;
}

//Показать меню регистрации
void Chat::showRegistrationMenu() {
    try {
        std::string tname;
        std::string tpassword;
        std::string tlogin;
        while (true) {
            setColorToConsole(6);
            std::cout << "Введите регистрационные данные" << std::endl;
            std::cout << "Имя: ";
            setColorToConsole(3);
            std::cin >> tname;
            setColorToConsole(6);
            std::cout << "Логин: ";
            setColorToConsole(3);
            std::cin >> tlogin;

            //Проверяем соответствует ли логин требованиям 
            if (tlogin.length() < 3) {
                throw bad_data("Логин очень короткий! Логин должен быть более 2 символов.");
            }

            if (tlogin.length() > 8) {
                throw bad_data("Логин очень длинный! Логин должен быть не более 8 символов.");
            }

            setColorToConsole(6);
            std::cout << "Пароль: ";
            setColorToConsole(3);
            std::cin >> tpassword;
            //Проверяем есть ли уже пользователь с таким логином
            if (checkLogin(tlogin)) {
                system("cls");
                setColorToConsole(4);
                std::cout << "Логин " << tlogin << " занят!" << std::endl;
                setColorToConsole(15);
                system("pause");
                system("cls");
                return;
            }
            else {
                break;
            }
        }
        setColorToConsole(15);

        //Создаем пользователя и добавляем в вектор
        //users_.emplace_back(User(tlogin, tpassword, tname, std::make_shared<IPublisher*>(this)));
        SHA256 sha256;//создаем объект для хеширования пароля
        users_.emplace_back(tlogin, sha256(tpassword), tname, std::make_shared<IPublisher*>(this));
        
        //Подписываем последнего добавленного пользователя на уведомления
        users_[users_.size() - 1].subscribe();

        //Отправляем пользователю личное сообщения от администратора
        addMessage("admin", tlogin, "Welcome to the chat! We are glad to see you here. Make yourself at home!");

        system("cls");
        setColorToConsole(10);
        std::cout << "Поздравляю! Вы зарегистрировались!" << std::endl;
        setColorToConsole(15);

        system("pause");
    }
    catch (bad_data& e) {
        system("cls");
        setColorToConsole(4);
        std::cout << e.what() << std::endl;
        setColorToConsole(15);
        system("pause");
    }
    catch (std::exception& e) {
        system("cls");
        setColorToConsole(4);
        std::cout << e.what() << std::endl;
        setColorToConsole(15);
        system("pause");
    }
    catch (...) {
        system("cls");
        setColorToConsole(4);
        std::cout << "Unknown exception" << std::endl;
        setColorToConsole(15);
        system("pause");
    }
    setColorToConsole(15);
    system("cls");
}

//Получить общее количество личных сообщений для пользователя
unsigned int Chat::getAmountSelfMessage(const std::string &login) const {
    unsigned int amount = 0;

    //Подсчитываем количество совпадений
    _int64 n = std::count_if(message_.begin(), message_.end(), [login](const Message& m) {
        return m.checkToSendedTo(login);
        });

    amount = static_cast<unsigned int>(n);

    return amount;
}

//Показать меню для входа
void Chat::showLogIn() {
    std::string tlogin;
    std::string tpassword;
    setColorToConsole(6);
    std::cout << "Введите данные для входа " << std::endl;
    std::cout << "Логин: ";
    setColorToConsole(3);
    std::cin >> tlogin;
    setColorToConsole(6);
    std::cout << "Пароль: ";
    setColorToConsole(3);
    std::cin >> tpassword;
    SHA256 sha256;//создаем объект для хеширования пароля
    currentUser = getUser(tlogin, sha256(tpassword));
    system("cls");
    //Если пользователь не найден
    if (!currentUser) {
        setColorToConsole(4);
        std::cout << "Логин или пароль введены неверно!" << std::endl;
        setColorToConsole(15);
        system("pause");
        system("cls");
        return;
    }
    setColorToConsole(15);
    showChatMenu();
}

//Показать меню общего чата
void Chat::showChatMenu() {
     
    short type = 1;//тип чата(общий или личнные сообщения)
    char choice = '0';//выбор в чате
    Datetime date;//объект для определения даты и времени

    while (true) {
        //Если type = 1 выводим общий чат
        if (type == 1){
            setColorToConsole(6);
            std::cout << "Общий чат" << std::endl;
            date.setNow();//устанавливаем текущую дату и время
            //Выводим на экран
            std::cout << date.getStrDate() << std::endl;
            std::cout << date.getStrTime() << std::endl;
           
            std::cout << "________________________________________________________________________________________________" << std::endl;
            //Определяем есть ли сообщения в общем чате
            if (amountAll_ == 0) {
                setColorToConsole(9);
                std::cout << std::endl << "Сообщений нет" << std::endl;
            }
            else {
                //Определяем количество новых сообщений в общем чате
                unsigned int tnewAllMessage = amountAll_ - (*currentUser)->getNewAllMessages();
                unsigned int i = 1;//переменная. Нужная для определения, где нужно вывести строку с надписью Новое
                for (const auto& message : message_) {
                    //Если поле кому содержит all
                    if (message.checkToSendedTo("all")) {
                        setColorToConsole(224);//224
                        //Выводим того кто отправл сообщение
                        std::cout << "[" << message.getSendedFrom() << "]" << std::endl;
                        setColorToConsole(3);
                        //Выводим текст
                        std::cout << message.getText() << std::endl;
                        SetConsoleMode(hConsole_, ENABLE_PROCESSED_OUTPUT);//это надо, чтобы не появлялась лишняя цветная полоса при переносе
                        setColorToConsole(11);
                        //Выводим дату и время отправки сообщения
                        std::cout << message.getDatetime() << std::endl;
                        std::cout << std::endl;
                        //Выводим линию с надписью новое сообщение, если выполняются условия
                        if (i == tnewAllMessage && tnewAllMessage != amountAll_ && (*currentUser)->getIsSubscribes()) {
                            setColorToConsole(6);
                            std::cout << "==================Новое===================" << std::endl;
                        }
                        ++i;//увеличиваем счетчик
                    }
                }
            }
            setColorToConsole(6);
            std::cout << "________________________________________________________________________________________________" << std::endl;
            //Подсчитываем количество новых дичных сообщений
            unsigned int tself = (*currentUser)->getNewSelfMessages();
            std::string tstrtemp;//строка, которая нужна для выввода уведомления о сообщение вида (2)
            //Если количество больше 0
            if (tself > 0) {
                tstrtemp = "(" + std::to_string(tself) + ")";
            }
            std::cout << "1 - Обновить чат   2 - Личные сообщения" << ((*currentUser)->getIsSubscribes() ? tstrtemp : "" ) << "  3 - Написать сообщение  4 - " <<
                ((*currentUser)->getIsSubscribes() ? "Отписаться от уведомлений" : "Подписаться на уведомления") << std::endl;
            std::cout << "q - Выход" << std::endl;
            std::cout << "Введите символ: ";
            setColorToConsole(3);
            std::cin >> choice;//считываем ввод от пользователя
            (*currentUser)->resetNewAllMessages();//сбрасываем количество новых солбщений в общем чате
            setColorToConsole(15);
        }
        
        //Если type = 2 выводим чат с личными сообщениями
        if (type == 2) {
            //Определяем количество личных сообщений
            (*currentUser)->setAmountSelfMessages(getAmountSelfMessage((*currentUser)->getLogin()));
            setColorToConsole(6);
            std::cout << "Личные сообщения" << std::endl;
            date.setNow();//устанавливаем текущую дату и время
            //Выводим на экран
            std::cout << date.getStrDate() << std::endl;
            std::cout << date.getStrTime() << std::endl;
            std::cout << "________________________________________________________________________________________________" << std::endl;
            //Если количество личных сообщений равно 0
            if ((*currentUser)->getAmountSelfMessages() == 0) {
                setColorToConsole(9);
                std::cout << std::endl << "Сообщений нет" << std::endl;
            }
            else {
                unsigned int tAmountSelfMessage = (*currentUser)->getAmountSelfMessages();
                //Определяем количество новых личных сообщений
                unsigned int tnewSelfMessage = tAmountSelfMessage - (*currentUser)->getNewSelfMessages();
                unsigned int i = 1;//переменная. Нужна для подсчета номера сообщения, после которого нужно вывести надпись "Новое"
                
                std::string tlogin = (*currentUser)->getLogin();
                for (const auto& message : message_) {
                    //Если поле в сообщение кому соответствует логину текущего пользователя
                    if (message.checkToSendedTo(tlogin)) {
                        setColorToConsole(224);
                        //Выводим логин отправителя
                        std::cout << "[" << message.getSendedFrom() << "]" << std::endl;
                        setColorToConsole(3);
                        //Выводим сообщение
                        std::cout << message.getText() << std::endl;
                        SetConsoleMode(hConsole_, ENABLE_PROCESSED_OUTPUT);//это надо, чтобы не появлялась лишняя цветная полоса при переносе
                        setColorToConsole(11);
                        //Выводим дату и время отправки сообщения
                        std::cout << message.getDatetime() << std::endl;
                        std::cout << std::endl;
                        //Если услвоие выполняется, то выводим Новое
                        if (i == tnewSelfMessage && tnewSelfMessage != tAmountSelfMessage && (*currentUser)->getIsSubscribes()) {
                            setColorToConsole(6);
                            std::cout << "==================Новое===================" << std::endl;
                        }
                        ++i;//увеличиваем на 1
                    }
                }
            }
            setColorToConsole(6);
            std::cout << "________________________________________________________________________________________________" << std::endl;
            //Подсчитываем количество новых сообщений в общем чате
            unsigned int tall = (*currentUser)->getNewAllMessages();
            std::string tstrtemp;//строка. Нужна для вывода информации о новых сообщениях в общем чате в виде (2)
            //Если количесво новых сообщений в общем чате больше 0
            if (tall > 0) {
                tstrtemp = "(" + std::to_string(tall) + ")";
            }
            std::cout << "1 - Общий чат" << ((*currentUser)->getIsSubscribes() ? tstrtemp : "") << "  2 - Обновить чат" << "  3 - Написать сообщение  4 - " <<
                ((*currentUser)->getIsSubscribes() ? "Отписаться от уведомлений" : "Подписаться на уведомления") << std::endl;
            std::cout << "q - Выход" << std::endl;
            std::cout << "Введите символ: ";
            setColorToConsole(3);
            std::cin >> choice;//считываем ввод от пользователя
            (*currentUser)->resetNewSelfMessages();//сбрасываем количество новых личных сообщений 
            setColorToConsole(15);
        }

        if (choice == 'q') {
            break;
        }
        else if (choice == '1') {
            if (type == 2) {
                type = 1;
            }
            system("cls");
            continue;
        }
        else if (choice == '2') {
            if (type == 1) {
                type = 2;
            }
            system("cls");
            continue;
        }
        else if (choice == '3') {
            system("cls");
            showWriteMessageMenu();
        }
        else if(choice == '4') {
            if ((*currentUser)->getIsSubscribes()) {
                (*currentUser)->unscribe();
            }
            else {
                (*currentUser)->subscribe();
            }
        }
        system("cls");
       
    }
    
    system("cls");
}

//Установить цвет в консоле
void Chat::setColorToConsole(WORD n) {
    SetConsoleTextAttribute(hConsole_, n);
}

//проверка существует ли пользователь с таким логином
bool Chat::checkLogin(const std::string& login) {
   
    if (std::any_of(users_.begin(), users_.end(), [login](const User& user) {
        return user.checkLogin(login);
        })) {
        return true;
    }

    return false;
}

//Проверка существует ли пользователь с таким логином. Если да, то правильно ли введен пароль
std::unique_ptr<User*> Chat::getUser(const std::string& login, const std::string& password) {
    for (auto& user : users_) {
        if (user.checkLogin(login)) {
            if (user.checkPassword(password)) {
                return std::make_unique<User*>(&user);
            }
        }
    }
    return nullptr;
}

//Добавить сообщение
void Chat::addMessage(const std::string& from, const std::string& to, const std::string& text) {
   // message_.emplace_back(Messagefrom, to, text));
    message_.emplace_back(from, to, text);
    if (to == "all") {
        notifyAboutAll();//информируем подписчиков о новом сообщении
        ++amountAll_;
    }
    else {
        notifyAboutSelf(to);//информируем пользователя с определенным логином о новом сообщении
    }
}

//Показать меню для написания сообщений
void Chat::showWriteMessageMenu() {
    std::string to;
    std::string text;
    while (true) {
        setColorToConsole(6);
        std::cout << "Кому писать сообщение(all в общий чат): ";
        setColorToConsole(3);
        std::cin >> to;
        setColorToConsole(6);
        std::cout << "Текст сообщения: ";
        setColorToConsole(3);
        std::cin.ignore();
        std::getline(std::cin, text);
        //Если поле пустое
        if (text.empty()) {
            system("cls");
            setColorToConsole(4);
            std::cout << "Поле сообщение пустое!!!" << std::endl;
            setColorToConsole(15);
            system("pause");
            system("cls");
            break;
        }
        //Если пользователя с таким логином нет
        else if (!checkLogin(to) && to != "all") {
            system("cls");
            setColorToConsole(4);
            std::cout << "Пользователь с логином " << to << " не зарегистрирован в чате!" << std::endl;
            setColorToConsole(15);
            system("pause");
            system("cls");
            break;
        }
        else {
            break;
        }
    }
    //Добавляем сообщение
    addMessage((*currentUser)->getLogin(), to, text);
    setColorToConsole(15);
    system("cls");
}