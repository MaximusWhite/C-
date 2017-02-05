// lab06_14.cpp: ��।���� ��� �室� ��� ���᮫쭮�� �ਫ������.
//

#include "stdafx.h"

#include <iostream>
#include <string>
#include <fstream> 

using namespace std;

class HomeLibrary{   // ����� ����譥� ������⥪�   

private:     // �㭪樨 � ���� ����㯭� ⮫쪮 ����� �����
	struct book{     // ����뢠�� �������� ������ ������� �����
		string name; // �������� 
		string author; // ����
		int date;    // ��� �㡫���樨
	};
	book books[100];   // ���ᨢ ������� ����
    int count;       // ������ ����� � ���ன ࠡ�⠥�
public:    // �㭪樨 � ���� ����㯭� ᭠�㦨

void readinput(){    // ���뢠�� ����� � 䠩�� � ���ᨢ ������� ���� �����
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
void set_count_books(int p){ count = p; }   // ����� ������ ����� � ���ன ࠡ�⠥�

int get_count_books(){ return count; }      // �����頥� ��� ������ �� ���饭�� ᭠�㦨

void add_book(){          // ��楤�� ���������� ����� � ����� ������⥪�
	//char name_tmp[100], author_tmp[100];
	//int date_tmp;
	cout << "��������: ";
	cin >> books[count].name;
	cout << "����: ";
	cin >> books[count].author;
	cout << "��� �㡫���樨: ";
	cin >> books[count].date;
	count++;
	cout << "����� ���������.";			
	}

void show_books(){     // �뢮� ������⥪� �� �࠭
		for (int i = 0; i<count; i++){
			cout << i + 1<<"--------------------------------"<<endl<< "��������: " << books[i].name <<endl<< "����:" << books[i].author <<endl<< "��� �㡫���樨: " << books[i].date <<endl;
		}
	}
void sort_dates(){     // ���஢�� �� ��� �㡫���樨
		for (int i = 0; i<count - 1; i++){
			for (int j = i + 1; j<count; j++)
			if (books[i].date>books[j].date) swap(books[i], books[j]);
		}
		cout << "�������:" << endl;
		show_books();
	}

void sort_name(){      // ���஢�� �� ��������
		for (int i = 0; i<count - 1; i++){
			for (int j = i + 1; j<count; j++)
			if (books[i].name > books[j].name) swap (books[i], books[j]);
		}
		cout << "�������:" << endl;
		show_books();
	}

void sort_author(){   // ���஢�� �� �����
		for (int i = 0; i<count - 1; i++){
			for (int j = i + 1; j<count; j++)
			if (books[i].author > books[j].author) swap (books[i], books[j]);
		}
		cout << "�������:" << endl;
		show_books();
	}

	
void delete_book(int k){  // 㤠����� ����� �� ������⥪�
		k--;
		for (int i = k; i<count - 1; i++){
			books[i] = books[i + 1];
		}
		count--;
		cout << "����� 㤠����.";
	}

};

HomeLibrary library;    // ᮧ��� ��६����� ���ᠭ���� ���� �����

void Work(){     // �᭮���� ��楤�� ����⢨�
	cout << "   ����" << endl;    // �뢮��� ����
	cout << "1 �������� �����" << endl;
	cout << "2 ��ᬮ�� ������⥪�" << endl;
	cout << "3 ������� �����" << endl;
	cout << "4 ����஢�� ���� �� �������� (�� ��䠢���):" << endl;
	cout << "5 ����஢�� ���� �� ��� �㡫���樨 (�� �����⠭��):" << endl;
	cout << "6 ����஢�� ���� �� ����� (�� ��䠢���):" << endl;
	cout << "7 ��室" << endl;
	int t, k;
	cin >> t;  // ���뢠�� ��ਠ�� ������ ���짮��⥫��
	switch (t){   // ᬮ�ਬ �� �뫮 �������
	case 1: {    // �᫨ ������� 1, �
				library.add_book();   // � ��६����� ����� ������⥪� ��뢠�� ��楤��� ���������� �����
				cout << endl << endl;
				Work();    // ��� ࠧ ��뢠�� ����
	}
	case 2:{   // �������筮
			   library.show_books();  // ��뢠�� ��楤��� �뢮�� ������⥪� �� �࠭
			   cout << endl << endl;
			   Work();
	}
	case 3:{
			   cout << "�롥�� �����";
			   cin >> k;
			   library.delete_book(k);    // 㤠�塞 ����� ��� ������ ����஬
			   cout << endl << endl;
			   Work();
	}
	case 4:{
			   library.sort_name();      // ����㥬 �� ��������
			   cout << endl << endl;
			   Work();
	}
	case 5:{
			   library.sort_dates();     // ����㥬 �� ��� �㡫���樨
			   cout << endl << endl;
			   Work();
	}
    case 6:{
			   library.sort_author();   // ����㥬 �� �����
			   cout << endl << endl;
			   Work();
	}
	case 7:exit(0);          // ��室�� �� �롮� 7
	default: break;
	}
}


int _tmain(int argc, _TCHAR* argv[])
{

setlocale(LC_ALL, "Russian");
	library.set_count_books(0);   // ����� ��६����� count � ��६����� ����� ������⥪� ࠢ�� ���
	library.readinput();     // ���뢠�� ����� � 䠩�� � ᮧ������ ������⥪�
	Work();    // �뢮��� ���� � �.�.

	return 0;

	   //
}

