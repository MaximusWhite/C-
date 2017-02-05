// lab06_14.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"

#include <iostream>
#include <string>
#include <fstream> 

using namespace std;

class HomeLibrary{   // ����� �������� ����������   

private:     // ������� � ���� ��������� ������ ������ ������
	struct book{     // ��������� ��������� ������ ���������� �����
		string name; // �������� 
		string author; // �����
		int date;    // ���� ����������
	};
	book books[100];   // ������ �������� ����
    int count;       // ������ ����� � ������� ��������
public:    // ������� � ���� ��������� �������

void readinput(){    // ��������� ������ � ����� � ������ �������� ���� ������
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
void set_count_books(int p){ count = p; }   // ����� ������ ����� � ������� ��������

int get_count_books(){ return count; }      // ���������� ���� ������ ��� ��������� �������

void add_book(){          // ��������� ���������� ����� � ����� ����������
	//char name_tmp[100], author_tmp[100];
	//int date_tmp;
	cout << "��������: ";
	cin >> books[count].name;
	cout << "�����: ";
	cin >> books[count].author;
	cout << "���� ����������: ";
	cin >> books[count].date;
	count++;
	cout << "����� ���������.";			
	}

void show_books(){     // ����� ���������� �� �����
		for (int i = 0; i<count; i++){
			cout << i + 1<<"--------------------------------"<<endl<< "��������: " << books[i].name <<endl<< "�����:" << books[i].author <<endl<< "���� ����������: " << books[i].date <<endl;
		}
	}
void sort_dates(){     // ���������� �� ���� ����������
		for (int i = 0; i<count - 1; i++){
			for (int j = i + 1; j<count; j++)
			if (books[i].date>books[j].date) swap(books[i], books[j]);
		}
		cout << "���������:" << endl;
		show_books();
	}

void sort_name(){      // ���������� �� ��������
		for (int i = 0; i<count - 1; i++){
			for (int j = i + 1; j<count; j++)
			if (books[i].name > books[j].name) swap (books[i], books[j]);
		}
		cout << "���������:" << endl;
		show_books();
	}

void sort_author(){   // ���������� �� ������
		for (int i = 0; i<count - 1; i++){
			for (int j = i + 1; j<count; j++)
			if (books[i].author > books[j].author) swap (books[i], books[j]);
		}
		cout << "���������:" << endl;
		show_books();
	}

	
void delete_book(int k){  // �������� ����� �� ����������
		k--;
		for (int i = k; i<count - 1; i++){
			books[i] = books[i + 1];
		}
		count--;
		cout << "����� �������.";
	}

};

HomeLibrary library;    // ������ ���������� ���������� ���� ������

void Work(){     // �������� ��������� ��������
	cout << "   ����" << endl;    // ������� ����
	cout << "1 �������� �����" << endl;
	cout << "2 �������� ����������" << endl;
	cout << "3 ������� �����" << endl;
	cout << "4 ���������� ���� �� �������� (�� ��������):" << endl;
	cout << "5 ���������� ���� �� ���� ���������� (�� �����������):" << endl;
	cout << "6 ���������� ���� �� ������ (�� ��������):" << endl;
	cout << "7 �����" << endl;
	int t, k;
	cin >> t;  // ��������� ������� �������� �������������
	switch (t){   // ������� ��� ���� �������
	case 1: {    // ���� ������� 1, ��
				library.add_book();   // � ���������� ������ ���������� �������� ��������� ���������� �����
				cout << endl << endl;
				Work();    // ��� ��� �������� ����
	}
	case 2:{   // ����������
			   library.show_books();  // �������� ��������� ������ ���������� �� �����
			   cout << endl << endl;
			   Work();
	}
	case 3:{
			   cout << "�������� �����";
			   cin >> k;
			   library.delete_book(k);    // ������� ����� ��� �������� �������
			   cout << endl << endl;
			   Work();
	}
	case 4:{
			   library.sort_name();      // ��������� �� ��������
			   cout << endl << endl;
			   Work();
	}
	case 5:{
			   library.sort_dates();     // ��������� �� ���� ����������
			   cout << endl << endl;
			   Work();
	}
    case 6:{
			   library.sort_author();   // ��������� �� ������
			   cout << endl << endl;
			   Work();
	}
	case 7:exit(0);          // ������� ��� ������ 7
	default: break;
	}
}


int _tmain(int argc, _TCHAR* argv[])
{

setlocale(LC_ALL, "Russian");
	library.set_count_books(0);   // ����� ���������� count � ���������� ������ ���������� ������ ����
	library.readinput();     // ��������� ������ � ����� � ��������� ����������
	Work();    // ������� ���� � �.�.

	return 0;
}

