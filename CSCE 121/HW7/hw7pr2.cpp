// Dalton Harris
// CSCE 121-509
// Due: October 26, 2014 (or whatever the due date is)
// hw7pr2.cpp (or whatever this file name is)

#include "std_lib_facilities_4.h"
#include "Simple_window.h"
#include "Graph.h"

int main()
{
	try 
	{
  		if(H112 != 201401L)error("Error: incorrect std_lib_facilities_4.h version ",
		  	   H112);
		  	   
  		Simple_window win1(Point(100,200),600,400,"Big Dalton's House");  // create window

		Closed_polyline house;						// create a new polygon, house
		house.add(Point(200,150));					// add new points to the polygon house
		house.add(Point(200,300));
		house.add(Point(400,300));
		house.add(Point(400,150));
		house.set_fill_color(Color::red);			// set house color to red
		win1.attach(house);							// attach house to the window
		
		Closed_polyline roof;						// create new polygon, roof
		roof.add(Point(200,150));					// add new points to the polygon roof
		roof.add(Point(400,150));
		roof.add(Point(300,50));
		roof.set_fill_color(Color::black);			// set roof color to black
  		win1.attach(roof);							// attach roof to window
  		
  		Closed_polyline chimney;					// create new polygon, chimney
  		chimney.add(Point(220,50));					// add new points to chimney
  		chimney.add(Point(220,150));
  		chimney.add(Point(240,150));
  		chimney.add(Point(240,50));
  		chimney.set_fill_color(Color::black);		// set chimney color to black
  		win1.attach(chimney);						// attach chimney to window
  		
   		Closed_polyline door;						// create new polygon, door
  		door.add(Point(280,300));					// add new points to door
  		door.add(Point(320,300));
  		door.add(Point(320,240));
  		door.add(Point(280,240));
  		door.set_fill_color(Color::black);			// set door color to black
  		win1.attach(door);							// attach door to window 	
  		
  		Closed_polyline window1;					// create new polygon, window1
  		window1.add(Point(220,170));					// add new points to window1
  		window1.add(Point(220,220));
  		window1.add(Point(270,220));
  		window1.add(Point(270,170));
  		window1.set_fill_color(Color::blue);		// set window2 color to blue
  		win1.attach(window1);						// attach window2 to window	
  		
  		Closed_polyline window2;					// create new polygon, window2
  		window2.add(Point(330,170));					// add new points to window2
  		window2.add(Point(330,220));
  		window2.add(Point(380,220));
  		window2.add(Point(380,170));
  		window2.set_fill_color(Color::blue);		// set window2 color to blue
  		win1.attach(window2);						// attach window2 to window	
  		
  		Text smoke(Point(220,50), "SMOKE");
  		win1.attach(smoke);
  		  		
  		win1.wait_for_button();
 		return 0;
	}
	
	catch(exception& e) {
		cerr << "exception: " << e.what() << '\n';
		return 1;}
		
	catch (...) {
		cerr << "Some exception\n";
		return 2;}
}