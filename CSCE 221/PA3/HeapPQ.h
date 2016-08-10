#ifndef HEAPPQ_H
#define HEAPPQ_H

#include <exception>

using namespace std;


template <class Type>

class HeapPQ
{
private:
	Type* data;
	int size;
	int capacity;
	
	void resize()
	{
		int newc=2*capacity+1;
		
		Type* temp=new Type[newc];
		
		for(int i=0;i<capacity;i++)
		{
			temp[i]=data[i];
		}
		
		delete[] data;
		
		data=temp;
		capacity=newc;
	};
	
	void swap(int s1, int s2)
	{
		Type num=data[s1];
		data[s1]=data[s2];
		data[s2]=num;
	};
	void upheap(int child)
	{
		
		if(child==0)
			return;
			
		int parent=(child-1)/2;
		
		if(data[child]<data[parent])
		{
			swap(parent,child);
			upheap(parent);
		}
	
	};
	
	void downheap(int parent)
	{
		int left=(parent*2)+1;
		
		if(left>=size)
			return;
		
		int right;
		if(left+1>=size)
		{
			right=-1;
		}
		else
		{
			right=left+1;
		}
			
		if(data[left]<data[right]||right==-1)
		{
			if(data[left]<data[parent])
			{
				swap(parent,left);
				downheap(left);
			}
		}
		else
		{
			if(data[right<data[parent]])
			{
				swap(parent,right);
				downheap(right);
			}
		}
	
	};

public:

   HeapPQ(int cap)
   {
		for(capacity=1;capacity<cap;capacity=(capacity*2)+1);
		
		size=0;
		data=new Type[capacity];
   };

   ~HeapPQ(void){delete[] data;};

   bool isEmpty(void)
   {
		return size==0;
   };

   int length(void)
   {
	   return size;
   };

   void insertItem ( Type elem )
   {
		if(++size>capacity)
			resize();
		data[size-1]=elem;
		upheap(size-1);
   };

   Type removeMin ( void ) throw(exception)
   {
		if(isEmpty())
			throw exception();
		
		--size;
		swap(0,size);
		downheap(0);
		return data[size];
   
   };

   Type minValue ( void ) throw(exception){
		if(isEmpty())
			throw exception();
		
		return data[0];
   
   };
};

#endif