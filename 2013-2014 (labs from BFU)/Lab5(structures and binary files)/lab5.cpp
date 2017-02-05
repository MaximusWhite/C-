

#pragma hdrstop

#include "stdafx.h"
#include <tchar.h>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

ifstream input ("note.txt");       // создаём глобальную переменную потока для входного файла данных
int kolvo = 0;

struct notebook{               // описываем структуру ноутбука

	char model[21];          // модель
	struct size{          // подструктура для габаритов
		float x;          // длина
		float y;          // ширина
		float z;          // высота
	};
	size xyz;        // создаём переменную габаритов внутри структуры
	float w;              // вес
	int price;            // цена

};

int countstrings(ifstream &temp);    //функция, возвращающая количество строк в данном на входе файловом потоке
void read(notebook *note, int total);   // процедура чтения данных о ноутбуках из входного файла данных в массив ноутбуков
bool condition(notebook note, int total);  // процедура проверки выполнения условия (диагональ больше 11 дюймов)
void writetobin(notebook *note, int total, int kolvo);  // процедура записи структур подходящих ноутбуков в бинарный файл


int main(){


	int	total = countstrings(input);  // создаём переменную total для хранения количества строк во входном файле, или количества ноутбуков

	// notebook *note = new notebook [total]; // создаём динамический массив из [total] элементов типа notebook
    notebook note[20];

	read(note,total);   // процедура чтения из файла

	writetobin (note, total, kolvo);   // процедура записи в бинарный файл

	system("pause");
	return 0;
}



int countstrings(ifstream &temp){

 string s;         // переменная типа "строка"
 int result=0;     // результат, изначально равен нулю
 while (getline(temp,s)){   // пока можем считывать файл построчно:
 result++;                  // увеличиваем результат на 1
}

 return result;              // возвращаем результат
}

void read (notebook *note, int total){

	 char price[4], x[4], y[5], z[4], w[3];  // временные переменные для хранения данных о цене, размерах и весе ноутбуков из строки в формате типа "char" (необходимо для работы использованных далее функций)
	 string s;    // временная переменная типа "строка", в которую будут считываться одна за другой строки из файла

	 ifstream input("note.txt"); // опять создаём поток привязанный к файлу с исходными данными
								 // потому что по какой-то причине обращение к глобальной переменной этого потока не даёт результата
	 int t=0;  // временная переменная для хранения индекса текущей обрабатываемой строки или же порядковый номер ноутбука в массиве
	 while (getline(input,s)){  // пока поток "input" может построчно записываться в s, делаем следующее:

		 t++;  // увеличиваем индекс
		 char temp[80]; // создаём символьный массив, для хранения в нём символов каждой строки (76 элементов, потому что из условия в каждой строке по 76 символов)
		 strcpy(temp, s.c_str());  // копируем строку считанную из файла посимвольно в массив описанный выше

		 strncpy(note[t].model, temp, 20); // используя функцию копирования символьных массивов,
										   // копируем первые 21 элемент в поле "model" элемента массива типа notebook под индексом t
										   // ТО ЕСТЬ, присваиваем ноутбуку под порядковым номером t соответствующее ему название
		 note[t].model[20] = '\0';

		 strncpy(price, temp+20, sizeof(price));       //  используя ту же функцию, копируем значение 21-25 элементов во временную переменную для цены типа char
		 note[t].price = atoi(price);      //  далее, переводим эту переменную в тип "int" и записываем в поле "price" ноутбука под индексом t

		 strncpy(w, temp+25, sizeof(w));           // аналогично с другими полями
		 note[t].w = atof(w);

		 strncpy(z, temp+29, sizeof(z));
		 note[t].xyz.z = atof(z);

		 strncpy(x, temp+34, sizeof(x));
		 note[t].xyz.x = atof(x);

		 strncpy(y, temp+39, sizeof(y));
		 note[t].xyz.y = atof(y);


		cout << "model " << note[t].model<< endl;            // вывод на экран данных для проверки: НЕ ИЗ ФАЙЛА ИЛИ СТРОК, А НЕПОСРЕДСТВЕННО ИЗ СТРУКТУРЫ НОУТБУКОВ!
		cout << " sizes " << note[t].xyz.z << " z " << note[t].xyz.x<< " x "<< note[t].xyz.y<<" y "<< endl;
		cout << " weight " << note[t].w<< endl;
		cout << " price " << note[t].price<<endl;

		// то есть на данном этапе структуры ноутбуков в массиве содержат какие-то данные
	 }
	  input.close(); // закрываем поток входного файла
}

bool condition(notebook note, int total){

	float d = sqrt(pow(note.xyz.x,2)+pow(note.xyz.y,2));   // создаём переменную в которую записываем формулу диагонали на основе длины и ширины данного элемента массива ноутбуков
	//cout<<"---------"<<d<<endl;                 // эта строка для проверки того, пустой или нет подаётся элемент массива ноутбуков
														   // выясняется, что он всегда пустой!!!
	if (d>11) {
	return true;}     // если диагональ больше 11, вернуть 1, иначе 0
	else return 0;


}

void writetobin(notebook *note, int total, int kolvo){
	FILE *outbin;
	outbin = fopen("data.out", "w+b");    // создаём бинарный файл для вывода обработанных данных
    
	

    
    for (int i = 1; i <= total; i++){ 
     if (condition(note[i], total)) kolvo++;
	}
		fwrite(&kolvo, sizeof kolvo, 1, outbin);       // считаем количество ПОДХОДЯЩИХ ПО УСЛОВИЮ ноутбуков
		//cout<< "kolvo ----------"<< kolvo<< endl;

	for (int i = 1; i <= total; i++){       // далее от 1 до total

		  //cout<<"---------"<<note[i].xyz.z<<endl;     // данная строка, как и в предыдущей описанной функции
														// служит для проверки того, пустой ли подаётся в качестве аргумента массив ноутбуков или нет
														// выясняется, что пустой!!!
														// поэтому следующее условие не выполняется никогда, и кроме количества ноутбуков в бинарный файл вывода не записывается больше ничего
		if (condition(note[i], total)){      // если для i-го элемента массива ноутбуков выполняется
			fwrite(&note[i], sizeof note[i], 1, outbin);   // то записываем его в бинарный файл
		}
	}
	
	
	
	fclose(outbin);        // закрываем бинарный файл
}



