// lab04_14.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <tchar.h>
using namespace std;





char analize(string s);                            // функция анализирующая слова и возвращающая название текстового файла результата

void write (char type_abc, string s);             // процедура записи результата в текстовый файл
 
int _tmain(int argc, _TCHAR* argv[])
{
	ifstream source_f;                           // создаём поток типа ifstream для чтения данных из файла 
	
	source_f.open("C:/source.txt", ios::in);    // метод open открывает файл по указанному пути для чтения, в режиме для чтения ios::in

    char temp;

	string s="";	                          // строковая переменная для хранения слов
    
    while (!source_f.eof())                   // пока не закончится файл
	
	{
           
            source_f>>temp;                   // считываем посимвольно текст во временную переменную символьного типа
            
			
			if (temp==' ')                     // если эта переменная это пробел, значит предыдущие символы - одно слово, которое можно обработать
			{
              
                write(analize(s),s);           // записываем это слово в текстовый файл в зависимости от количества гласных и согласных
                s="";                          // обнуляем переменную со словом
			}
			else s+=temp;                      // если же символ не является пробелом - просто приклеиваем его к получившемуся ранее слову

			cout<<temp;                        // почему не выводит пробелы????


        }
	source_f.close();                         // закрываем файл источника
    system("pause");
	return 0;
}


char analize(string s)
{  
	int glas=0, soglas=0, len=s.length();      // переменные для количества гласных, согласных и длины проверяемого слова
   
	for (int i=0; i<len; i++)                  // пока слово не закончится, посимвольно проверяем его
   {      
       if ((tolower(s[i])=='a')||(tolower(s[i])=='e')||(tolower(s[i])=='u')||(tolower(s[i])=='i')||(tolower(s[i])=='o'))
           // если символ это гласная, то увеличиваем счётчик гласных, иначе - согласных
	   {   
		    glas++;  
	   }
	   else soglas++;  
   }     

   
   if (glas<soglas)return 'a';      //по итогам решаем в какой из текстовых файлов записать слово
   if (glas=soglas)return 'b';
   if (glas>soglas) return 'c';


}

void write(char type_abc, string s)
{
    
   if (type_abc=='a')             // в зависимости от итогов анализа слова, записываем его в нужный текстовый файл согласно условию
   {
       ofstream f;                // создаём поток для записи данных в файл
       
	   f.open("C:/a.txt", ios::app);   // открываем его, указывая путь к файлу записи и режим записи (ios::app добавляет данные в конец файла)

       f<<s<<endl;                    // записываем данные в файл

	   f.close();                     // закрываем файл

   }


   if (type_abc=='b')             // аналогично
   {
       ofstream f;
       
	   f.open("C:/b.txt", ios::app);

       f<<s<<endl;
	   f.close();

   }

   if (type_abc=='c')           // аналогично
   {
       ofstream f;
       
	   f.open("C:/c.txt", ios::app);

       f<<s<<endl; 
       f.close();
   }





}

