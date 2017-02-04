//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Chart"
#pragma link "TeEngine"
#pragma link "TeeProcs"
#pragma link "Series"
#pragma resource "*.dfm"
#include "math.h"
TForm1 *Form1;
//---------------------------------------------------------------------------


__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

double function(double x, double y)       // функция, данная в условии
{
	 double temp;
	 temp= ((y*y)/(x*x))+ y/x;                  // (x+y)^2
	 return temp;
}

double y_prop(double x)                  // точное решение
{
   double temp;
   temp = (-x)/(log(x)-1);                     // y = tg(x)-x
   return temp;
}

double K1(double x, double y, double h)           //  K1 заданный по формуле из условия
{
	double temp;
	temp=function(x,y)*h;
	return temp;
}

double K2(double x, double y, double h)           //  K2 заданный по формуле из условия  
{
	double temp;
	temp=function(x+h/2,y+K1(x,y,h)/2)*h;
	return temp;
}
double K3(double x, double y, double h)           //  K3 заданный по формуле из условия
{
	double temp;
	temp=function(x+h/2,y+K2(x,y,h)/2)*h;
	return temp;
}
double K4(double x, double y, double h)           //  K4 заданный по формуле из условия
{
	double temp;
	temp=function(x+h,y+K3(x,y,h))*h;
	return temp;
} 
double delta_y(double x, double y, double h)      // дельта y, заданная по формуле из условия
{
	double temp;
	temp=(K1(x,y,h)+2*K2(x,y,h)+2*K3(x,y,h)+K4(x,y,h))/6;
	return temp;
}
void __fastcall TForm1::Button1Click(TObject *Sender)     // процедура нажатия кнопки на форме (что происходит при её нажатии)
{
	if ((Edit1->Text=="")||(Edit2->Text=="")||(Edit3->Text=="")||(Edit4->Text=="")) {    // сначала проверяем, если хоть одно поле не заполнено, то надо их все заполнить
	  ShowMessage("Ошибка! Не все поля заполнены!");
	}else
	{

	int steps = (Edit2->Text.ToDouble()- Edit1->Text.ToDouble())/(Edit3->Text.ToDouble());  // создаём переменную, в которой считаем количество необходимых шагов,
	                                                                                        // используя информацию о концах отрезка и о шаге функции
	Label8->Caption=steps;                                                                  // отображаем количество шагов на форме
	double x0 = Edit1->Text.ToDouble();      // создаём переменную с начальным значением Х, взятым из отведённого под это поле
	double y0 = Edit4->Text.ToDouble();      // тоже самое с начальным значением Y

	double h = Edit3->Text.ToDouble();       // тоже самое с шагом h

	double *x_arr= new double[steps+1];      // выделяем память под динамические массивы вещественных элементов в количестве необходимых шагов (+1 потому что включаем нулевые значения)
	                                         // для хранения значений X и Y, которые будут использоваться потом для графика приближённого решения
	x_arr[0]=x0;                             // первые элементы массивов приравниваем к начальным X и Y обозначенные выше
	double *y_arr= new double[steps+1];
	y_arr[0]=y0;

	int str_num=1;                           // переменная для хранения текущего номера строки в таблице приближённого решения (необходимо потому что в каждом шаге функции есть ещё по 5 подшагов)

	for (int i = 0; i<=steps; i++)           // теперь столько раз, сколько шагов необходимо сделать, делаем следующее:
	{
		double xi=x_arr[i];                  // вводим временные переменные для хранения текущих значений X и Y 
		double yi=y_arr[i];

	  Series1->Add(y_prop(xi), xi, clGreen); // добавляем точку в график точного решения, используя в качестве Y результат функции точного решения от текущего X
	 
	  Series2->Add(yi,xi,clBlue);            // добавляем точку в график приближённого решения, используя текущие X и Y
	  
	  StringGrid1->RowCount+=1;              // добавляем ряд в таблицу
	  
	 if (i==steps)                           // если цикл дошёл до конца
	 {

	   StringGrid1->Cells[0][str_num]=i;     // доделываем дополнительный шаг (потому что иначе не будут выведены результаты последнего шага)
	  StringGrid1->Cells[1][str_num]=FormatFloat("0.######",xi);
	  StringGrid1->Cells[2][str_num]=FormatFloat("0.######",yi);
	   StringGrid1->RowCount-=6;             // уменьшаем количество строк в таблице, чтобы было правильно
	  break;                           // выходим из цикла

	 }

      // если шаг ещё не последний, то продолжаем:
	  StringGrid1->RowCount+=5;      // добавляем 5 рядов в таблице (4 для подшагов + 1 для отображения дельты Y)
            
      // далее выводим значения в каждую ячейку таблицы с форматом в 6 знаков после запятой
	  StringGrid1->Cells[0][str_num]=i;                                              // подшаг 1 
	  StringGrid1->Cells[1][str_num]=FormatFloat("0.######",xi);                     // X текущие в этом подшаге
	  StringGrid1->Cells[2][str_num]=FormatFloat("0.######",yi);                     // Y текущие в этом подшаге
	  StringGrid1->Cells[3][str_num]=FormatFloat("0.######",function(xi,yi));        // значение функции от X и Y на этом подшаге
	  StringGrid1->Cells[4][str_num]=FormatFloat("0.######",K1(xi,yi,h));            // K от X и Y на этом подшаге
	  StringGrid1->Cells[5][str_num]=FormatFloat("0.######",K1(xi,yi,h));            // дельта Y от X и Y на этом подшаге 
	  	 
	  StringGrid1->Cells[1][str_num+1]=FormatFloat("0.######",xi+h/2);               // подшаг 2
	  StringGrid1->Cells[2][str_num+1]=FormatFloat("0.######",yi+K1(xi,yi,h)/2);
	  StringGrid1->Cells[3][str_num+1]=FormatFloat("0.#####0",function(xi+h/2,yi+K1(xi,yi,h)/2));
	  StringGrid1->Cells[4][str_num+1]=FormatFloat("0.#####0",K2(xi,yi,h));
	  StringGrid1->Cells[5][str_num+1]=FormatFloat("0.#####0",2*K2(xi,yi,h));
	  	
	  StringGrid1->Cells[1][str_num+2]=FormatFloat("0.######",xi+h/2);               // подшаг 3
	  StringGrid1->Cells[2][str_num+2]=FormatFloat("0.######",yi+K2(xi,yi,h)/2);
	  StringGrid1->Cells[3][str_num+2]=FormatFloat("0.#####0",function(xi+h/2,yi+K1(xi,yi,h)/2));
	  StringGrid1->Cells[4][str_num+2]=FormatFloat("0.#####0",K3(xi,yi,h));
	  StringGrid1->Cells[5][str_num+2]=FormatFloat("0.#####0",2*K3(xi,yi,h));

	  StringGrid1->Cells[1][str_num+3]=FormatFloat("0.######",xi);                   // подшаг 4
	  StringGrid1->Cells[2][str_num+3]=FormatFloat("0.######",yi+K3(xi,yi, h));
	  StringGrid1->Cells[3][str_num+3]=FormatFloat("0.#####0",function(xi+h,yi+K3(xi,yi,h)));
	  StringGrid1->Cells[4][str_num+3]=FormatFloat("0.#####0",K4(xi,yi,h));
	  StringGrid1->Cells[5][str_num+3]=FormatFloat("0.#####0",K4(xi,yi,h));

	  StringGrid1->Cells[5][str_num+4]=FormatFloat("0.#####0",delta_y(xi,yi,h));     // вывод дельты Y для текущего шага

	  str_num+=5;          // увеличиваем порядковый номер строки на 5, чтобы на следующих шагах не происходила перезапись предыдущих, уже выведенных в таблицу данных                                  
	  
	 x_arr[i+1]=xi+h;      // в массиве значений X следующий элемент увеличиваем на шаг h для обработки на следующем шаге
	 y_arr[i+1]=yi+delta_y(xi,yi,h); //  в массиве значений Y следующий элемент увеличиваем на дельту Y, вычисленную выше

	}
	    // теперь аналагично действиям выше, записываем данные таблицы сравнения точного и приближённого решений
		for (int i = 0; i<=steps; i++) // столько раз, сколько шагов надо сделать, делаем:
	{
		StringGrid2->RowCount+=1;      // добавляем строку в таблицу

		double xi=x_arr[i];            // вводим временные переменные для хранения текущих значений X и Y   
		double yi=y_arr[i];

		// выводим значения в каждую ячейку таблицы с форматом в 9 знаков после запятой
		StringGrid2->Cells[0][i+1]=FormatFloat("0.#########",xi);  // текущая X  
		StringGrid2->Cells[1][i+1]=FormatFloat("0.#########",yi);  // текущая Y
		StringGrid2->Cells[2][i+1]=FormatFloat("0.#########",y_prop(xi));  // значение точного решения от текущего X
		StringGrid2->Cells[3][i+1]=FormatFloat("0.#########",fabs(y_prop(xi)-yi));  // погрешность шага: модуль разности между значением точного решения от текущего X и текущего Y
	}

	  StringGrid2->RowCount-=1;   // после всех вычислений во второй таблице удалить одну строку

	delete [] y_arr;      // освободить память выделенную под массивы с X и Y
	delete [] x_arr;

	}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)   // при создании формы
{           
// создаём "шапки" для таблиц с результатами
StringGrid1->Cells[0][0]="i";       
StringGrid1->Cells[1][0]="Xi";
StringGrid1->Cells[2][0]="Yi";
StringGrid1->Cells[3][0]="f(Xi,Yi)";
StringGrid1->Cells[4][0]="K=hf(x,y)";
StringGrid1->Cells[5][0]="Delta Yi";

StringGrid2->Cells[0][0]="X";       
StringGrid2->Cells[1][0]="Y";
StringGrid2->Cells[2][0]="Y точное";
StringGrid2->Cells[3][0]="E";

}
//---------------------------------------------------------------------------



