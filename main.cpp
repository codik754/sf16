//Файл main.cpp
#include <iostream>
#include "chat.h"

//В этой функции реализуется основной код
void clientCode() {
	Chat chat;//создаем объект для чата
	char choice = '0';//переменная для выбора

	while (choice != 'q') {
		if (choice == '0'){
			//Показываем основное первое меню
			choice = chat.showHelloMenu();
		}
		else if (choice == '1') {
			//Показываем меню для входа
			chat.showLogIn();
			choice = '0';
		}
		else if (choice == '2') {
			//Показываем меню для регистрации
			chat.showRegistrationMenu();
			choice = '0';
		}

		if (choice == 'q') {
			//Выводим сообщение, показываемое перед выходом
			chat.setColorToConsole(12);
			std::cout << "До встречи!!!" << std::endl;
			chat.setColorToConsole(15);
		}

	}
}

int main() {
	setlocale(LC_ALL, "");
	//Запускаем основной код
	clientCode();
	return 0;
}