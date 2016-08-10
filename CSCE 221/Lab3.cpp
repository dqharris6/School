#include <iostream>
using namespace std;

// Class to represent points.
class Point {
private:
        double xval, yval;
public:
        // Constructor uses default arguments to allow calling with zero, one,
        // or two values.
        Point(double x = 0.0, double y = 0.0) {
                xval = x;
                yval = y;
        }

        // Extractors.
        double x() { return xval; }
        double y() { return yval; }
		
		void print(ostream &strm)
        {
                strm << "(" << xval << "," << yval << ")";
        }
};

int main()
{
	// ON THE STACK
	// Define a new Point
	Point point1(0,1);
	
	// Define an array with 10 slots
	Point array1[10];			
	
	// Declare each of the array slots with a non-zero point
	for(int loop = 0; loop < 10; ++loop)
	{
		array1[loop] = point1;
		array1[loop].print(cout);
		cout << endl;
	}
	
	// Code here to delete this array // 
	cout << "Array1 has been deleted." << endl;
	
	// ON THE HEAP
	// Define a new Point
	Point point2(1,2);
	
	// Define an array with 10 slots (on the heap)
	Point *array2 = new Point[10];
	
	// Declare each of the array slots with a non-zero point
	for(int loop2 = 0; loop2 < 10; ++loop2)
	{
		array2[loop2] = point2;
		array2[loop2].print(cout);
		cout << endl;
	}	
	
	// After use, delete the array
	delete [] array2;
	cout << "Array2 has been deleted" << endl;
	
	return 0;
}