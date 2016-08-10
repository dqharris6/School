#include <iostream>
#include "std_lib_facilities_4.h"
using namespace std;

struct Point 
{
	float m_x, m_y;
	void Set ( float x, float y )
	{
		m_x = x; 
		m_y = y;
	}
};

class Shape
{
	protected:
		Color m_c;
		
	public:
		Shape(Color c) : m_c(c) {}
   
	virtual void Draw() 
	{/*do nothing*/}
};

class Circle : public Shape 
{
	float m_radius;
	
	public:
		Circle(Color c, float r) : Shape(c),   
		m_radius(r) {}
	
	void Draw()
	{/*draw circle of radius r*/}
};

class Square : public Shape 
{
	float m_side;
	
	public:
		Square(Color c, float s) : Shape(c), 
      	m_side(s) {}
      	
   	void Draw()
   	{/*draw circle of radius r*/}
};

int main()
{
	return 0;
}