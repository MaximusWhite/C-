// lab08_14.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "math.h"
#include <iostream>
#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

class Pair{       // родительский класс Pair
  
public:
virtual	void mul()=0;      // чистые виртуальные функции для математических операций
virtual	void add()=0;
virtual void sub()=0;
virtual void div()=0;
virtual void equ()=0;

};


class Money: public Pair     // класс Money, наследник Pair
{
private:
	double a, b,c, d;      // переменные для хранения рублей и копеек
    double value1, value2;  // временные переменные для хранения дробного значения денег
	double endr, endk;   // итоговое значение рублей и копеек
public:
	Money(double rub, double kop, double rub1, double kop1)  // конструктор 
	{
		a = rub; 
		b=kop;
		c=rub1;
		d=kop1;
	    
		value1=a+b/100;       // задаём десятичные значения, чтобы с ними работать (то есть для 5 руб. 12 коп. value1 = 5.12)
	    value2=c+d/100;
	}
    
	void mul(){    // умножение
      
     double result=value1*value2; 
      
     endk = modf(result, &endr);  // разделяем целую и десятичную части
     
	 cout<<endr<<" рублей "<< endk*100<< " копеек"<< endl;

	}; 
	void add(){    // сложение
      
     double result=value1+value2;
      
     endk = modf(result, &endr);
     
	 cout<<endr<<" рублей "<< endk*100<< " копеек"<< endl;
      
	};
    void sub()    // вычитание 
	{
	 double result=value1-value2;
      
     endk = modf(result, &endr);
     
	 cout<<endr<<" рублей "<< endk*100<< " копеек"<< endl;	
	};
	void div()   // деление 
	{
	 double result=value1/value2;
      
     endk = modf(result, &endr);
     
	 cout<<endr<<" рублей "<< endk*100<< " копеек"<< endl;
	};
	void equ()   // сравнение
	{
	   if ((a==c)&&(b==d))cout<< "суммы равны"; else cout<<"суммы не равны" << endl;
	
	};
};

class Complex: public Pair  // класс Complex, наследник Pair
{   
    private:
    double a, b, c, d;  // переменные для хранения чисел

    public:
	Complex(double a1, double b1, double c1, double d1){a=a1; b=b1; c=c1; d=d1;} // конструктор
	
	void mul(){  // умножение
	   cout<<"("<<a*c-b*d<<","<<a*d+b*c<<")"<<endl; 
	}; 
	void add(){ // прибавление 
       cout<<"("<<a+b<<","<<c+d<<")"<<endl; 
	};
	void sub() // вычитание 
	{
	   cout<<"("<<a-b<<","<<c-d<<")"<<endl; 
	};
	void div() // деление 
	{
	    cout<<"("<<(a*c+b*d)/(c*c+d*d)<<","<<(a*d-b*c)/(c*c+d*d)<<")"<<endl; 
	};
	void equ()  // проверка на равенство
	{
		if((a==c)&&(b==d)) cout<< "числа равны"; else cout<<"числа не равны" << endl;
	
	};
};


int _tmain(int argc, _TCHAR* argv[])
{  
	setlocale(LC_ALL,"Russian");
    
   Pair* mon = new Money(80,10,1,20); // создаём указатель в памяти на что-то типа Pair, при этом в качестве объекта туда записываем объекты производных классов
   Pair* comp = new Complex(1,2,1,2); // в скобках входные данные для конструктора
    
	cout<< "Money::mul = "; mon->mul();   // теперь в разных указателях вызываем одинаковые методы
    cout<< "Money::add = "; mon->add();		
	cout<< "Money::sub = "; mon->sub(); 
    cout<< "Money::div = "; mon->div(); 
	cout<< "Money::equ = "; mon->equ(); 
    cout<< "-------------"<<endl;
	cout<< "Complex::mul = "; comp->mul(); 
    cout<< "Complex::add= "; comp->add();
	cout<< "Complex::sub = "; comp->sub(); 
    cout<< "Complex::div = "; comp->div();
	cout<< "Complex::equ = "; comp->equ(); 


    cout<<endl;
    system("pause");
	return 0;
}

