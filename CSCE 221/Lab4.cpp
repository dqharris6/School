#include <iostream>
#include <cmath>
using namespace std;

template <class T>
class point
{
	private:
		T* v;
		int sz;
		
	public:
		point(int s) { v = new T [sz = s]; }		// constructor
		~point() { delete[] v; }					// destructor
		T& operator[] (int i) { return v[i]; }
		void set(int index, T t) { v[index-1] = t; } // sets value of point (2 or 3) dimensional
		int size() { return sz; }
};

template<class T> double EuclDist(T& t1, T& t2)  	// passing 2 point arguments
{
   float rval = 0;

   for ( int i = 0; i < t1.size(); i++ ) 
   {
   		double tmp = (t1[i] - t2[i]);
    	rval += tmp * tmp;
   }
   return sqrt(rval);
}

int main()
{
	point<double> point1(2);
	point<double> point2(2);
	
	point1.set(1,0.5);
	point1.set(2,0.5);
	
	point2.set(1,10.5);
	point2.set(2,16.5);
	
	cout << "Euclidian Distance is " << EuclDist(point1, point2) << endl;
	
	return 0;
}