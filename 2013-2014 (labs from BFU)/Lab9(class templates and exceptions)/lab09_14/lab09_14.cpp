// lab09_14.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <list>
#include <string>
#include <iostream>
using namespace std;



template <class T>   //������ ������ � ��������� Deque
class Deque {
private:
	std::list<T> data;   // ���������� list ��� ��������� ���� ������
public: 
	
	void push(T const& dat){  // ��������� ����� �������

      data.push_back(dat);
	}
	
	void pop(){        // ������� �������
	
		if (data.empty()) { // ���� ������ �������, ���������� ����������
		throw error("Void Deque<T>::pop() -  �������� ��������������� ��������");
    }
	
    data.pop_back(); // ������� ��������� �������
	
	}
	T top(){
      
     if (data.empty()) {  // ���� ������ ����������, ���������� ����������
        throw error("Void Deque<T>::top() �������� ������ ������������");
    }
	
    return data.back();  // ���������� ����� ���������� ��������
	
	}
	bool empty() const{       // ���� ��� ���������, ���������� true    
        return data.empty();
    }
};

class error{     // ����� ������
	public:
       
		string issue;  // ��� ���������� ��� �� ������ ���������
		
		error(string s){   // �����������, � ��������� �������� ��� �������� ������� ������ ������� ������, � �� ������������ ��� ���������
            issue = s;
		}

	};



int _tmain(int argc, _TCHAR* argv[])
{    
	setlocale(LC_ALL,"Russian");
    
	try{
        Deque<int>         intDeque;  // ������ ������� ��������� ������� ��� ������ � ����� ������� ������ ������
        Deque<double>      doubleDeque;
        Deque<string>      stringDeque;
        
		// �������� � int

        //cout << intDeque.top() <<endl; //**** ����� ����������, ������ ��� ���� ��� ������

        intDeque.push(7);
        cout << intDeque.top() <<endl; 

        intDeque.pop();          // ��� ������� ������� int ������� ������ ��� �����, �� ���������
		intDeque.pop();        //*****����� ����������, ������ ��� �������� ������� ��, ���� ���

		// �������� c double 
        
  		//cout << doubleDeque.top() <<endl;     //******����������
       
		doubleDeque.push(0.1);
        cout << doubleDeque.top() <<endl;
        
        // �������� � string 
        stringDeque.push("hello");
        cout << stringDeque.top() <<endl;
        
		stringDeque.pop();
		//stringDeque.pop();              //  *****
	    
		system("pause");
	}
	catch(error er){
         
		cout<< "����������: "<< er.issue<< endl;
	    system("pause");
	  
	}

    
	return 0;
}

