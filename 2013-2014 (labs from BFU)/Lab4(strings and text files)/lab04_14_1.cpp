// lab04_14.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <tchar.h>
using namespace std;





char analize(string s);                            // ������� ������������� ����� � ������������ �������� ���������� ����� ����������

void write (char type_abc, string s);             // ��������� ������ ���������� � ��������� ����
 
int _tmain(int argc, _TCHAR* argv[])
{
	ifstream source_f;                           // ������ ����� ���� ifstream ��� ������ ������ �� ����� 
	
	source_f.open("C:/source.txt", ios::in);    // ����� open ��������� ���� �� ���������� ���� ��� ������, � ������ ��� ������ ios::in

    char temp;

	string s="";	                          // ��������� ���������� ��� �������� ����
    
    while (!source_f.eof())                   // ���� �� ���������� ����
	
	{
           
            source_f>>temp;                   // ��������� ����������� ����� �� ��������� ���������� ����������� ����
            
			
			if (temp==' ')                     // ���� ��� ���������� ��� ������, ������ ���������� ������� - ���� �����, ������� ����� ����������
			{
              
                write(analize(s),s);           // ���������� ��� ����� � ��������� ���� � ����������� �� ���������� ������� � ���������
                s="";                          // �������� ���������� �� ������
			}
			else s+=temp;                      // ���� �� ������ �� �������� �������� - ������ ����������� ��� � ������������� ����� �����

			cout<<temp;                        // ������ �� ������� �������????


        }
	source_f.close();                         // ��������� ���� ���������
    system("pause");
	return 0;
}


char analize(string s)
{  
	int glas=0, soglas=0, len=s.length();      // ���������� ��� ���������� �������, ��������� � ����� ������������ �����
   
	for (int i=0; i<len; i++)                  // ���� ����� �� ����������, ����������� ��������� ���
   {      
       if ((tolower(s[i])=='a')||(tolower(s[i])=='e')||(tolower(s[i])=='u')||(tolower(s[i])=='i')||(tolower(s[i])=='o'))
           // ���� ������ ��� �������, �� ����������� ������� �������, ����� - ���������
	   {   
		    glas++;  
	   }
	   else soglas++;  
   }     

   
   if (glas<soglas)return 'a';      //�� ������ ������ � ����� �� ��������� ������ �������� �����
   if (glas=soglas)return 'b';
   if (glas>soglas) return 'c';


}

void write(char type_abc, string s)
{
    
   if (type_abc=='a')             // � ����������� �� ������ ������� �����, ���������� ��� � ������ ��������� ���� �������� �������
   {
       ofstream f;                // ������ ����� ��� ������ ������ � ����
       
	   f.open("C:/a.txt", ios::app);   // ��������� ���, �������� ���� � ����� ������ � ����� ������ (ios::app ��������� ������ � ����� �����)

       f<<s<<endl;                    // ���������� ������ � ����

	   f.close();                     // ��������� ����

   }


   if (type_abc=='b')             // ����������
   {
       ofstream f;
       
	   f.open("C:/b.txt", ios::app);

       f<<s<<endl;
	   f.close();

   }

   if (type_abc=='c')           // ����������
   {
       ofstream f;
       
	   f.open("C:/c.txt", ios::app);

       f<<s<<endl; 
       f.close();
   }





}

