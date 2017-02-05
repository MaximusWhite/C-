

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

ifstream input ("note.txt");       // ������ ���������� ���������� ������ ��� �������� ����� ������
int kolvo = 0;

struct notebook{               // ��������� ��������� ��������

	char model[21];          // ������
	struct size{          // ������������ ��� ���������
		float x;          // �����
		float y;          // ������
		float z;          // ������
	};
	size xyz;        // ������ ���������� ��������� ������ ���������
	float w;              // ���
	int price;            // ����

};

int countstrings(ifstream &temp);    //�������, ������������ ���������� ����� � ������ �� ����� �������� ������
void read(notebook *note, int total);   // ��������� ������ ������ � ��������� �� �������� ����� ������ � ������ ���������
bool condition(notebook note, int total);  // ��������� �������� ���������� ������� (��������� ������ 11 ������)
void writetobin(notebook *note, int total, int kolvo);  // ��������� ������ �������� ���������� ��������� � �������� ����


int main(){


	int	total = countstrings(input);  // ������ ���������� total ��� �������� ���������� ����� �� ������� �����, ��� ���������� ���������

	// notebook *note = new notebook [total]; // ������ ������������ ������ �� [total] ��������� ���� notebook
    notebook note[20];

	read(note,total);   // ��������� ������ �� �����

	writetobin (note, total, kolvo);   // ��������� ������ � �������� ����

	system("pause");
	return 0;
}



int countstrings(ifstream &temp){

 string s;         // ���������� ���� "������"
 int result=0;     // ���������, ���������� ����� ����
 while (getline(temp,s)){   // ���� ����� ��������� ���� ���������:
 result++;                  // ����������� ��������� �� 1
}

 return result;              // ���������� ���������
}

void read (notebook *note, int total){

	 char price[4], x[4], y[5], z[4], w[3];  // ��������� ���������� ��� �������� ������ � ����, �������� � ���� ��������� �� ������ � ������� ���� "char" (���������� ��� ������ �������������� ����� �������)
	 string s;    // ��������� ���������� ���� "������", � ������� ����� ����������� ���� �� ������ ������ �� �����

	 ifstream input("note.txt"); // ����� ������ ����� ����������� � ����� � ��������� �������
								 // ������ ��� �� �����-�� ������� ��������� � ���������� ���������� ����� ������ �� ��� ����������
	 int t=0;  // ��������� ���������� ��� �������� ������� ������� �������������� ������ ��� �� ���������� ����� �������� � �������
	 while (getline(input,s)){  // ���� ����� "input" ����� ��������� ������������ � s, ������ ���������:

		 t++;  // ����������� ������
		 char temp[80]; // ������ ���������� ������, ��� �������� � �� �������� ������ ������ (76 ���������, ������ ��� �� ������� � ������ ������ �� 76 ��������)
		 strcpy(temp, s.c_str());  // �������� ������ ��������� �� ����� ����������� � ������ ��������� ����

		 strncpy(note[t].model, temp, 20); // ��������� ������� ����������� ���������� ��������,
										   // �������� ������ 21 ������� � ���� "model" �������� ������� ���� notebook ��� �������� t
										   // �� ����, ����������� �������� ��� ���������� ������� t ��������������� ��� ��������
		 note[t].model[20] = '\0';

		 strncpy(price, temp+20, sizeof(price));       //  ��������� �� �� �������, �������� �������� 21-25 ��������� �� ��������� ���������� ��� ���� ���� char
		 note[t].price = atoi(price);      //  �����, ��������� ��� ���������� � ��� "int" � ���������� � ���� "price" �������� ��� �������� t

		 strncpy(w, temp+25, sizeof(w));           // ���������� � ������� ������
		 note[t].w = atof(w);

		 strncpy(z, temp+29, sizeof(z));
		 note[t].xyz.z = atof(z);

		 strncpy(x, temp+34, sizeof(x));
		 note[t].xyz.x = atof(x);

		 strncpy(y, temp+39, sizeof(y));
		 note[t].xyz.y = atof(y);


		cout << "model " << note[t].model<< endl;            // ����� �� ����� ������ ��� ��������: �� �� ����� ��� �����, � ��������������� �� ��������� ���������!
		cout << " sizes " << note[t].xyz.z << " z " << note[t].xyz.x<< " x "<< note[t].xyz.y<<" y "<< endl;
		cout << " weight " << note[t].w<< endl;
		cout << " price " << note[t].price<<endl;

		// �� ���� �� ������ ����� ��������� ��������� � ������� �������� �����-�� ������
	 }
	  input.close(); // ��������� ����� �������� �����
}

bool condition(notebook note, int total){

	float d = sqrt(pow(note.xyz.x,2)+pow(note.xyz.y,2));   // ������ ���������� � ������� ���������� ������� ��������� �� ������ ����� � ������ ������� �������� ������� ���������
	//cout<<"---------"<<d<<endl;                 // ��� ������ ��� �������� ����, ������ ��� ��� ������� ������� ������� ���������
														   // ����������, ��� �� ������ ������!!!
	if (d>11) {
	return true;}     // ���� ��������� ������ 11, ������� 1, ����� 0
	else return 0;


}

void writetobin(notebook *note, int total, int kolvo){
	FILE *outbin;
	outbin = fopen("data.out", "w+b");    // ������ �������� ���� ��� ������ ������������ ������
    
	

    
    for (int i = 1; i <= total; i++){ 
     if (condition(note[i], total)) kolvo++;
	}
		fwrite(&kolvo, sizeof kolvo, 1, outbin);       // ������� ���������� ���������� �� ������� ���������
		//cout<< "kolvo ----------"<< kolvo<< endl;

	for (int i = 1; i <= total; i++){       // ����� �� 1 �� total

		  //cout<<"---------"<<note[i].xyz.z<<endl;     // ������ ������, ��� � � ���������� ��������� �������
														// ������ ��� �������� ����, ������ �� ������� � �������� ��������� ������ ��������� ��� ���
														// ����������, ��� ������!!!
														// ������� ��������� ������� �� ����������� �������, � ����� ���������� ��������� � �������� ���� ������ �� ������������ ������ ������
		if (condition(note[i], total)){      // ���� ��� i-�� �������� ������� ��������� �����������
			fwrite(&note[i], sizeof note[i], 1, outbin);   // �� ���������� ��� � �������� ����
		}
	}
	
	
	
	fclose(outbin);        // ��������� �������� ����
}



