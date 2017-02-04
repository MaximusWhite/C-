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

double function(double x, double y)       // �������, ������ � �������
{
	 double temp;
	 temp= ((y*y)/(x*x))+ y/x;                  // (x+y)^2
	 return temp;
}

double y_prop(double x)                  // ������ �������
{
   double temp;
   temp = (-x)/(log(x)-1);                     // y = tg(x)-x
   return temp;
}

double K1(double x, double y, double h)           //  K1 �������� �� ������� �� �������
{
	double temp;
	temp=function(x,y)*h;
	return temp;
}

double K2(double x, double y, double h)           //  K2 �������� �� ������� �� �������  
{
	double temp;
	temp=function(x+h/2,y+K1(x,y,h)/2)*h;
	return temp;
}
double K3(double x, double y, double h)           //  K3 �������� �� ������� �� �������
{
	double temp;
	temp=function(x+h/2,y+K2(x,y,h)/2)*h;
	return temp;
}
double K4(double x, double y, double h)           //  K4 �������� �� ������� �� �������
{
	double temp;
	temp=function(x+h,y+K3(x,y,h))*h;
	return temp;
} 
double delta_y(double x, double y, double h)      // ������ y, �������� �� ������� �� �������
{
	double temp;
	temp=(K1(x,y,h)+2*K2(x,y,h)+2*K3(x,y,h)+K4(x,y,h))/6;
	return temp;
}
void __fastcall TForm1::Button1Click(TObject *Sender)     // ��������� ������� ������ �� ����� (��� ���������� ��� � �������)
{
	if ((Edit1->Text=="")||(Edit2->Text=="")||(Edit3->Text=="")||(Edit4->Text=="")) {    // ������� ���������, ���� ���� ���� ���� �� ���������, �� ���� �� ��� ���������
	  ShowMessage("������! �� ��� ���� ���������!");
	}else
	{

	int steps = (Edit2->Text.ToDouble()- Edit1->Text.ToDouble())/(Edit3->Text.ToDouble());  // ������ ����������, � ������� ������� ���������� ����������� �����,
	                                                                                        // ��������� ���������� � ������ ������� � � ���� �������
	Label8->Caption=steps;                                                                  // ���������� ���������� ����� �� �����
	double x0 = Edit1->Text.ToDouble();      // ������ ���������� � ��������� ��������� �, ������ �� ���������� ��� ��� ����
	double y0 = Edit4->Text.ToDouble();      // ���� ����� � ��������� ��������� Y

	double h = Edit3->Text.ToDouble();       // ���� ����� � ����� h

	double *x_arr= new double[steps+1];      // �������� ������ ��� ������������ ������� ������������ ��������� � ���������� ����������� ����� (+1 ������ ��� �������� ������� ��������)
	                                         // ��� �������� �������� X � Y, ������� ����� �������������� ����� ��� ������� ������������ �������
	x_arr[0]=x0;                             // ������ �������� �������� ������������ � ��������� X � Y ������������ ����
	double *y_arr= new double[steps+1];
	y_arr[0]=y0;

	int str_num=1;                           // ���������� ��� �������� �������� ������ ������ � ������� ������������ ������� (���������� ������ ��� � ������ ���� ������� ���� ��� �� 5 ��������)

	for (int i = 0; i<=steps; i++)           // ������ ������� ���, ������� ����� ���������� �������, ������ ���������:
	{
		double xi=x_arr[i];                  // ������ ��������� ���������� ��� �������� ������� �������� X � Y 
		double yi=y_arr[i];

	  Series1->Add(y_prop(xi), xi, clGreen); // ��������� ����� � ������ ������� �������, ��������� � �������� Y ��������� ������� ������� ������� �� �������� X
	 
	  Series2->Add(yi,xi,clBlue);            // ��������� ����� � ������ ������������ �������, ��������� ������� X � Y
	  
	  StringGrid1->RowCount+=1;              // ��������� ��� � �������
	  
	 if (i==steps)                           // ���� ���� ����� �� �����
	 {

	   StringGrid1->Cells[0][str_num]=i;     // ���������� �������������� ��� (������ ��� ����� �� ����� �������� ���������� ���������� ����)
	  StringGrid1->Cells[1][str_num]=FormatFloat("0.######",xi);
	  StringGrid1->Cells[2][str_num]=FormatFloat("0.######",yi);
	   StringGrid1->RowCount-=6;             // ��������� ���������� ����� � �������, ����� ���� ���������
	  break;                           // ������� �� �����

	 }

      // ���� ��� ��� �� ���������, �� ����������:
	  StringGrid1->RowCount+=5;      // ��������� 5 ����� � ������� (4 ��� �������� + 1 ��� ����������� ������ Y)
            
      // ����� ������� �������� � ������ ������ ������� � �������� � 6 ������ ����� �������
	  StringGrid1->Cells[0][str_num]=i;                                              // ������ 1 
	  StringGrid1->Cells[1][str_num]=FormatFloat("0.######",xi);                     // X ������� � ���� �������
	  StringGrid1->Cells[2][str_num]=FormatFloat("0.######",yi);                     // Y ������� � ���� �������
	  StringGrid1->Cells[3][str_num]=FormatFloat("0.######",function(xi,yi));        // �������� ������� �� X � Y �� ���� �������
	  StringGrid1->Cells[4][str_num]=FormatFloat("0.######",K1(xi,yi,h));            // K �� X � Y �� ���� �������
	  StringGrid1->Cells[5][str_num]=FormatFloat("0.######",K1(xi,yi,h));            // ������ Y �� X � Y �� ���� ������� 
	  	 
	  StringGrid1->Cells[1][str_num+1]=FormatFloat("0.######",xi+h/2);               // ������ 2
	  StringGrid1->Cells[2][str_num+1]=FormatFloat("0.######",yi+K1(xi,yi,h)/2);
	  StringGrid1->Cells[3][str_num+1]=FormatFloat("0.#####0",function(xi+h/2,yi+K1(xi,yi,h)/2));
	  StringGrid1->Cells[4][str_num+1]=FormatFloat("0.#####0",K2(xi,yi,h));
	  StringGrid1->Cells[5][str_num+1]=FormatFloat("0.#####0",2*K2(xi,yi,h));
	  	
	  StringGrid1->Cells[1][str_num+2]=FormatFloat("0.######",xi+h/2);               // ������ 3
	  StringGrid1->Cells[2][str_num+2]=FormatFloat("0.######",yi+K2(xi,yi,h)/2);
	  StringGrid1->Cells[3][str_num+2]=FormatFloat("0.#####0",function(xi+h/2,yi+K1(xi,yi,h)/2));
	  StringGrid1->Cells[4][str_num+2]=FormatFloat("0.#####0",K3(xi,yi,h));
	  StringGrid1->Cells[5][str_num+2]=FormatFloat("0.#####0",2*K3(xi,yi,h));

	  StringGrid1->Cells[1][str_num+3]=FormatFloat("0.######",xi);                   // ������ 4
	  StringGrid1->Cells[2][str_num+3]=FormatFloat("0.######",yi+K3(xi,yi, h));
	  StringGrid1->Cells[3][str_num+3]=FormatFloat("0.#####0",function(xi+h,yi+K3(xi,yi,h)));
	  StringGrid1->Cells[4][str_num+3]=FormatFloat("0.#####0",K4(xi,yi,h));
	  StringGrid1->Cells[5][str_num+3]=FormatFloat("0.#####0",K4(xi,yi,h));

	  StringGrid1->Cells[5][str_num+4]=FormatFloat("0.#####0",delta_y(xi,yi,h));     // ����� ������ Y ��� �������� ����

	  str_num+=5;          // ����������� ���������� ����� ������ �� 5, ����� �� ��������� ����� �� ����������� ���������� ����������, ��� ���������� � ������� ������                                  
	  
	 x_arr[i+1]=xi+h;      // � ������� �������� X ��������� ������� ����������� �� ��� h ��� ��������� �� ��������� ����
	 y_arr[i+1]=yi+delta_y(xi,yi,h); //  � ������� �������� Y ��������� ������� ����������� �� ������ Y, ����������� ����

	}
	    // ������ ���������� ��������� ����, ���������� ������ ������� ��������� ������� � ������������ �������
		for (int i = 0; i<=steps; i++) // ������� ���, ������� ����� ���� �������, ������:
	{
		StringGrid2->RowCount+=1;      // ��������� ������ � �������

		double xi=x_arr[i];            // ������ ��������� ���������� ��� �������� ������� �������� X � Y   
		double yi=y_arr[i];

		// ������� �������� � ������ ������ ������� � �������� � 9 ������ ����� �������
		StringGrid2->Cells[0][i+1]=FormatFloat("0.#########",xi);  // ������� X  
		StringGrid2->Cells[1][i+1]=FormatFloat("0.#########",yi);  // ������� Y
		StringGrid2->Cells[2][i+1]=FormatFloat("0.#########",y_prop(xi));  // �������� ������� ������� �� �������� X
		StringGrid2->Cells[3][i+1]=FormatFloat("0.#########",fabs(y_prop(xi)-yi));  // ����������� ����: ������ �������� ����� ��������� ������� ������� �� �������� X � �������� Y
	}

	  StringGrid2->RowCount-=1;   // ����� ���� ���������� �� ������ ������� ������� ���� ������

	delete [] y_arr;      // ���������� ������ ���������� ��� ������� � X � Y
	delete [] x_arr;

	}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)   // ��� �������� �����
{           
// ������ "�����" ��� ������ � ������������
StringGrid1->Cells[0][0]="i";       
StringGrid1->Cells[1][0]="Xi";
StringGrid1->Cells[2][0]="Yi";
StringGrid1->Cells[3][0]="f(Xi,Yi)";
StringGrid1->Cells[4][0]="K=hf(x,y)";
StringGrid1->Cells[5][0]="Delta Yi";

StringGrid2->Cells[0][0]="X";       
StringGrid2->Cells[1][0]="Y";
StringGrid2->Cells[2][0]="Y ������";
StringGrid2->Cells[3][0]="E";

}
//---------------------------------------------------------------------------



