// lab06_14.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include <iostream>
#include <string>
#include <fstream> 

using namespace std;

class HomeLibrary{   // класс домашней библиотеки   

private:     // функции и поля доступные только внутри класса
	struct book{     // описываем структуру одного экземпляра книги
		string name; // название 
		string author; // автор
		int date;    // дата публикации
	};
	book books[100];   // массив структур книг
    int count;       // индекс книги с которой работаем
public:    // функции и поля доступные снаружи

void readinput(){    // считываем данные с файла в массив структур книг класса
		string S;
		ifstream file("input.txt");
		while (file){
			getline(file, books[count].name);
			getline(file, books[count].author);
			getline(file, S);
            books[count].date = atoi(S.c_str());
			count++;
		}
		count--;
	}
void set_count_books(int p){ count = p; }   // задаём индекс книги с которой работаем

int get_count_books(){ return count; }      // возвращает этот индекс при обращении снаружи

void add_book(){          // процедура добавления книги в класс библиотеки
	//char name_tmp[100], author_tmp[100];
	//int date_tmp;
	cout << "Название: ";
	cin >> books[count].name;
	cout << "Автор: ";
	cin >> books[count].author;
	cout << "Дата публикации: ";
	cin >> books[count].date;
	count++;
	cout << "Книга добавлена.";			
	}

void show_books(){     // вывод библиотеки на экран
		for (int i = 0; i<count; i++){
			cout << i + 1<<"--------------------------------"<<endl<< "Название: " << books[i].name <<endl<< "Автор:" << books[i].author <<endl<< "Дата публикации: " << books[i].date <<endl;
		}
	}
void sort_dates(){     // сортировка по дате публикации
		for (int i = 0; i<count - 1; i++){
			for (int j = i + 1; j<count; j++)
			if (books[i].date>books[j].date) swap(books[i], books[j]);
		}
		cout << "Результат:" << endl;
		show_books();
	}

void sort_name(){      // сортировка по названию
		for (int i = 0; i<count - 1; i++){
			for (int j = i + 1; j<count; j++)
			if (books[i].name > books[j].name) swap (books[i], books[j]);
		}
		cout << "Результат:" << endl;
		show_books();
	}

void sort_author(){   // сортировка по автору
		for (int i = 0; i<count - 1; i++){
			for (int j = i + 1; j<count; j++)
			if (books[i].author > books[j].author) swap (books[i], books[j]);
		}
		cout << "Результат:" << endl;
		show_books();
	}

	
void delete_book(int k){  // удаление книги из библиотеки
		k--;
		for (int i = k; i<count - 1; i++){
			books[i] = books[i + 1];
		}
		count--;
		cout << "Книга удалена.";
	}

};

HomeLibrary library;    // создаём переменную описанного нами класса

void Work(){     // основная процедура действий
	cout << "   Меню" << endl;    // выводим меню
	cout << "1 Добавить книгу" << endl;
	cout << "2 Просмотр библиотеки" << endl;
	cout << "3 Удалить книгу" << endl;
	cout << "4 Сортировка книг по названию (по алфавиту):" << endl;
	cout << "5 Сортировка книг по дате публикации (по возрастанию):" << endl;
	cout << "6 Сортировка книг по автору (по алфавиту):" << endl;
	cout << "7 Выход" << endl;
	int t, k;
	cin >> t;  // считываем вариант введённый пользователем
	switch (t){   // смотрим что было введено
	case 1: {    // если введено 1, то
				library.add_book();   // в переменной класса библиотеки вызываем процедуру добавления книги
				cout << endl << endl;
				Work();    // ещё раз вызываем меню
	}
	case 2:{   // аналогично
			   library.show_books();  // вызываем процедуру вывода библиотеки на экран
			   cout << endl << endl;
			   Work();
	}
	case 3:{
			   cout << "Выберите номер";
			   cin >> k;
			   library.delete_book(k);    // удаляем книгу под введённым номером
			   cout << endl << endl;
			   Work();
	}
	case 4:{
			   library.sort_name();      // сортируем по названию
			   cout << endl << endl;
			   Work();
	}
	case 5:{
			   library.sort_dates();     // сортируем по дате публикации
			   cout << endl << endl;
			   Work();
	}
    case 6:{
			   library.sort_author();   // сортируем по автору
			   cout << endl << endl;
			   Work();
	}
	case 7:exit(0);          // выходим при выборе 7
	default: break;
	}
}


int _tmain(int argc, _TCHAR* argv[])
{

setlocale(LC_ALL, "Russian");
	library.set_count_books(0);   // задаём переменную count в переменной класса библиотеки равным нулю
	library.readinput();     // считываем данные с файла в созданную библиотеку
	Work();    // выводим меню и т.д.

	return 0;
}

