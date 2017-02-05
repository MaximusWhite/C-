// lab08_14.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "math.h"
#include <iostream>
#include <cstdio>
#include <string>
#include <iostream>

using namespace std;

class Pair{       // ������������ ����� Pair
  
public:
virtual	void mul()=0;      // ������ ����������� ������� ��� �������������� ��������
virtual	void add()=0;
virtual void sub()=0;
virtual void div()=0;
virtual void equ()=0;

};


class Money: public Pair     // ����� Money, ��������� Pair
{
private:
	double a, b,c, d;      // ���������� ��� �������� ������ � ������
    double value1, value2;  // ��������� ���������� ��� �������� �������� �������� �����
	double endr, endk;   // �������� �������� ������ � ������
public:
	Money(double rub, double kop, double rub1, double kop1)  // ����������� 
	{
		a = rub; 
		b=kop;
		c=rub1;
		d=kop1;
	    
		value1=a+b/100;       // ����� ���������� ��������, ����� � ���� �������� (�� ���� ��� 5 ���. 12 ���. value1 = 5.12)
	    value2=c+d/100;
	}
    
	void mul(){    // ���������
      
     double result=value1*value2; 
      
     endk = modf(result, &endr);  // ��������� ����� � ���������� �����
     
	 cout<<endr<<" ������ "<< endk*100<< " ������"<< endl;

	}; 
	void add(){    // ��������
      
     double result=value1+value2;
      
     endk = modf(result, &endr);
     
	 cout<<endr<<" ������ "<< endk*100<< " ������"<< endl;
      
	};
    void sub()    // ��������� 
	{
	 double result=value1-value2;
      
     endk = modf(result, &endr);
     
	 cout<<endr<<" ������ "<< endk*100<< " ������"<< endl;	
	};
	void div()   // ������� 
	{
	 double result=value1/value2;
      
     endk = modf(result, &endr);
     
	 cout<<endr<<" ������ "<< endk*100<< " ������"<< endl;
	};
	void equ()   // ���������
	{
	   if ((a==c)&&(b==d))cout<< "����� �����"; else cout<<"����� �� �����" << endl;
	
	};
};

class Complex: public Pair  // ����� Complex, ��������� Pair
{   
    private:
    double a, b, c, d;  // ���������� ��� �������� �����

    public:
	Complex(double a1, double b1, double c1, double d1){a=a1; b=b1; c=c1; d=d1;} // �����������
	
	void mul(){  // ���������
	   cout<<"("<<a*c-b*d<<","<<a*d+b*c<<")"<<endl; 
	}; 
	void add(){ // ����������� 
       cout<<"("<<a+b<<","<<c+d<<")"<<endl; 
	};
	void sub() // ��������� 
	{
	   cout<<"("<<a-b<<","<<c-d<<")"<<endl; 
	};
	void div() // ������� 
	{
	    cout<<"("<<(a*c+b*d)/(c*c+d*d)<<","<<(a*d-b*c)/(c*c+d*d)<<")"<<endl; 
	};
	void equ()  // �������� �� ���������
	{
		if((a==c)&&(b==d)) cout<< "����� �����"; else cout<<"����� �� �����" << endl;
	
	};
};


int _tmain(int argc, _TCHAR* argv[])
{  
	setlocale(LC_ALL,"Russian");
    
   Pair* mon = new Money(80,10,1,20); // ������ ��������� � ������ �� ���-�� ���� Pair, ��� ���� � �������� ������� ���� ���������� ������� ����������� �������
   Pair* comp = new Complex(1,2,1,2); // � ������� ������� ������ ��� ������������
    
	cout<< "Money::mul = "; mon->mul();   // ������ � ������ ���������� �������� ���������� ������
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

