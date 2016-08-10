// Dalton Harris
// CSCE 121-509
// Due: October 26, 2014 (or whatever the due date is)
// hw7pr1.cpp (or whatever this file name is)

#include "std_lib_facilities_4.h"
#include "Simple_window.h"
#include "Graph.h"

int main()
try {
  if(H112 != 201401L)error("Error: incorrect std_lib_facilities_4.h version ",
		  	   H112);
		  	   
  Simple_window win1(Point(100,200),600,400,"Initials");

  Line DTop(Point(100,100),Point(200,100));  			// top line of the D
  	DTop.set_style(Line_style(Line_style::solid,4));	// make bold, black by default
  Line DLeft(Point(100,100),Point(100,250));    		// left line of the D
  	DLeft.set_style(Line_style(Line_style::solid,4));
  Line DBottom(Point(100,250),Point(200,250)); 			// bottom line of the D
  	DBottom.set_style(Line_style(Line_style::solid,4));
  Line DRight(Point(200,100),Point(200,250));			// right line of the D
  	DRight.set_style(Line_style(Line_style::solid,4));
  
  Line QTop(Point(250,100),Point(350,100));  			// top line of the Q
 	QTop.set_style(Line_style(Line_style::solid,4));	// make bold
 	QTop.set_color(Color::magenta);						// make magenta
  Line QLeft(Point(250,100),Point(250,250));     		// left line of the Q
 	QLeft.set_style(Line_style(Line_style::solid,4));
 	QLeft.set_color(Color::magenta);
  Line QBottom(Point(250,250),Point(350,250)); 			// bottom line of the Q
  	QBottom.set_style(Line_style(Line_style::solid,4));
  	QBottom.set_color(Color::magenta);
  Line QRight(Point(350,100),Point(350,250));			// right line of the Q
  	QRight.set_style(Line_style(Line_style::solid,4));
  	QRight.set_color(Color::magenta);
  Line QTail(Point(325,225),Point(325,275));			// tail of the Q
  	QTail.set_style(Line_style(Line_style::solid,4));
  	QTail.set_color(Color::magenta);
  Line QTail2(Point(325,275),Point(350,275));
  	QTail2.set_style(Line_style(Line_style::solid,4));
  	QTail2.set_color(Color::magenta);
  
  Line HLeft(Point(400,100),Point(400,250));			// left line of the H
   	HLeft.set_style(Line_style(Line_style::solid,4));	// make bold
 	HLeft.set_color(Color::red);						// make red
  Line HMiddle(Point(400,175),Point(500,175));			// middle line of the H
   	HMiddle.set_style(Line_style(Line_style::solid,4));	// make bold
 	HMiddle.set_color(Color::red);
  Line HRight(Point(500,100),Point(500,250)); 			// right line of the H
   	HRight.set_style(Line_style(Line_style::solid,4));	// make bold
 	HRight.set_color(Color::red);

  win1.attach(DLeft);	// attach the D elements to the window
  win1.attach(DTop);
  win1.attach(DBottom);
  win1.attach(DRight);
  
  win1.attach(QTop);	// attach the Q elements to the window
  win1.attach(QLeft);
  win1.attach(QBottom);
  win1.attach(QRight);
  win1.attach(QTail);
  win1.attach(QTail2);
  
  win1.attach(HLeft);	// attach the H elements to the window
  win1.attach(HMiddle);
  win1.attach(HRight);
  
 //  QTail.set_color(Color::magenta);
 //  QTail2.set_color(Color::magenta);
  
  win1.wait_for_button();
  return 0;
}
catch(exception& e) {
	cerr << "exception: " << e.what() << '\n';
	return 1;
}
catch (...) {
	cerr << "Some exception\n";
	return 2;
}
