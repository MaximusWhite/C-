// Trirectangle.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <math.h>
using namespace std;

class TFigure
{
    public:
    TFigure(int numPoints, const char *s = ""): name(s), ptsAmount(numPoints)
    {     
		setlocale(LC_ALL,"Russian");
        pts = new TPoint[ptsAmount];
		cout << name << ":" << endl;
        for(int i = 0; i < ptsAmount; i++)
        {
            TPoint p;
            cout << "Координаты вершины " << i+1 << ": "<< endl;
			cout<<"X: ";
            cin >> p.x;
			cout<<"Y: ";
			cin>> p.y;
            pts[i] = p;
        }

        max_x=pts[0].x, min_x=pts[0].x; 
		max_y=pts[0].y, min_y=pts[0].y;
         
		for (int i=0; i<ptsAmount; i++){
		
		       if (pts[i].x>max_x) max_x=pts[i].x;
		       if (pts[i].x<min_x) max_x=pts[i].x; 
			   if (pts[i].y>max_y) max_y=pts[i].y;
		       if (pts[i].y<min_y) max_y=pts[i].y;  
		}
        for (int i=0; i<ptsAmount-1; i++){

			if (pts[i+1].x<pts[i].x) swap(pts[i+1],pts[i]);   

		}

    }

    friend bool IsIntersect(TFigure *T1,TFigure *T2);
  
    void move_it(int step_x, int step_y)
    {
        cout << "На сколько сдвинуть " << name <<"?" << endl;
        cout << "По оси Х:";cin >> step_x;
        cout << "По оси Y:";cin >> step_y;
        for(int i = 0; i < ptsAmount; i++)
        {
            pts[i].x += step_x;
            pts[i].y += step_y;
        }
    }

    void show_position()
    {
        cout << name ;
        for(int i = 0;i < ptsAmount; i++)
        cout << " (" << pts[i].x << ";" << pts[i].y << ") ";
        cout << endl;
    }

    struct TPoint
    {
        TPoint(int px=0,int py=0):x(px),y(py)
        {
        }
        int x, y;
    };
    int max_x, min_x, min_y, max_y;
    
    private:
    
	const char *name;TPoint *pts;

    protected:
    int ptsAmount;
	

};

class TTriangle: public TFigure
{
    public:
    TTriangle(int numPoints = 3) : TFigure(numPoints, "Треугольник")
    {
    }
};

class TRectangle: public TFigure
{
    public:
    TRectangle(int numPoints = 4): TFigure(numPoints, "Прямоугольник")
    {
    }
};

float function(float x, int x0, int y0, int x1, int y1){

   float y = (x-x0)*(y1-y0)/(x1-x0) + y0;
   
   return y;
}

bool IsInside(int x, int y, int minx, int maxx, int miny, int maxy)
{
     if ( (x<=maxx) && (x>=minx) && (y<=maxy) && (y>=miny) ) return true; 
	 
	 return false;
      
}


bool IsIntersect(TFigure *Tri, TFigure *Rect)
{

	float y_t1, y_t2, y_t3;
    
    int maxr_x = Rect->max_x, minr_x = Rect->min_x, maxr_y = Rect->max_y, minr_y = Rect->min_y; 
    
	float mint = Tri->min_x, maxt = Tri->max_x;

    
	for (float i=mint; i<=maxt; i+=0.1){
           
		y_t1 = function(i,Tri->pts[0].x,Tri->pts[0].y,Tri->pts[1].x,Tri->pts[1].y);
		y_t2 = function(i,Tri->pts[1].x,Tri->pts[1].y,Tri->pts[2].x,Tri->pts[2].y);
	    y_t3 = function(i,Tri->pts[2].x,Tri->pts[2].y,Tri->pts[0].x,Tri->pts[0].y);

        if ( (IsInside(i,y_t1,minr_x, maxr_x, minr_y, maxr_y)) || (IsInside(i,y_t2,minr_x, maxr_x, minr_y, maxr_y)) || (IsInside(i,y_t3,minr_x, maxr_x, minr_y, maxr_y))) return true;


	}



    return false;
 }


TTriangle T1;
TRectangle T2;
void work()
{
    cout << "1 : Показать координаты" << endl;;
    cout << "2 : Передвинуть фигуру" << endl;
    cout << "3 : Проверить пересечение" << endl;
    cout << "4 : Выход" << endl;
    int t;
	cin>>t;
	switch(t){
	case 1:{
		T1.show_position();
		T2.show_position();
		work();
		   }
	case 2:{
		T1.move_it(1,1);
		T2.move_it(1,1);
        cout<< "------------------------------------------------------"<<endl;
		cout<< "Фигуры передвинуты"<<endl;
		cout<< "------------------------------------------------------"<<endl;
		work();
		   }
	case 3:{
		cout<< "------------------------------------------------------"<<endl;
		if (IsIntersect(&T1,&T2)) cout << "Фигуры пересекаются" ;
        else cout << "Фигуры не пересекаются";
		cout<<endl;
		cout<< "------------------------------------------------------"<<endl;
		work();
		   }
	case 4:{
		exit(0);
		   }
	}
}

int main()
{
	setlocale(LC_ALL,"Russian");
	work();
}
