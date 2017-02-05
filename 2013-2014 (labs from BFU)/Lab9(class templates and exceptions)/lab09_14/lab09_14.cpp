// lab09_14.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <list>
#include <string>
#include <iostream>
using namespace std;



template <class T>   //создаём шаблон с названием Deque
class Deque {
private:
	std::list<T> data;   // используем list для помещения туда данных
public: 
	
	void push(T const& dat){  // добавляем новый элемент

      data.push_back(dat);
	}
	
	void pop(){        // удаляем элемент
	
		if (data.empty()) { // если нечего удалять, генерируем исключение
		throw error("Void Deque<T>::pop() -  удаление несуществующего элемента");
    }
	
    data.pop_back(); // удаляем последний элемент
	
	}
	T top(){
      
     if (data.empty()) {  // если нечего возвращать, генерируем исключение
        throw error("Void Deque<T>::top() вызывает пустое пространство");
    }
	
    return data.back();  // возвращаем копию последнего элемента
	
	}
	bool empty() const{       // если нет элементов, возвращаем true    
        return data.empty();
    }
};

class error{     // класс ошибки
	public:
       
		string issue;  // тут записываем что за ошибка произошла
		
		error(string s){   // конструктор, в аргументы которому при создании объекта ошибки задаётся строка, в неё записывается что произошло
            issue = s;
		}

	};



int _tmain(int argc, _TCHAR* argv[])
{    
	setlocale(LC_ALL,"Russian");
    
	try{
        Deque<int>         intDeque;  // создаём объекты шаблонных классов для работы с тремя разными типами данных
        Deque<double>      doubleDeque;
        Deque<string>      stringDeque;
        
		// работаем с int

        //cout << intDeque.top() <<endl; //**** вызов исключения, потому что лист ещё пустой

        intDeque.push(7);
        cout << intDeque.top() <<endl; 

        intDeque.pop();          // тут удаляем элемент int который только что ввели, всё нормально
		intDeque.pop();        //*****вызов исключения, потому что пытаемся удалить то, чего нет

		// работаем c double 
        
  		//cout << doubleDeque.top() <<endl;     //******аналогично
       
		doubleDeque.push(0.1);
        cout << doubleDeque.top() <<endl;
        
        // работаем с string 
        stringDeque.push("hello");
        cout << stringDeque.top() <<endl;
        
		stringDeque.pop();
		//stringDeque.pop();              //  *****
	    
		system("pause");
	}
	catch(error er){
         
		cout<< "Исключение: "<< er.issue<< endl;
	    system("pause");
	  
	}

    
	return 0;
}

