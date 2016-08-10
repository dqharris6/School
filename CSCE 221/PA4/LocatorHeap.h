#ifndef HEAP_H
#define HEAP_H

#include <exception>
#include <cstddef>

using namespace std;


// Note: this hape does not store elements of type Type but Type * instead.  
// It does not make a copy of the data you insert.  The heap makes the
// assumption have the operator < defined.
template <class Type>
class Heap
{
private:
	class HeapItem
	{
	public:
		int index;
		Type *data;

	public:
		HeapItem ( void ) : data ( NULL ), index ( -1 ) { }
		HeapItem ( Type *newData ) : data ( newData ), index ( -1 ) {}

		Type *getData ( void ) { return data; }
	};

public:
	typedef HeapItem* Locator;

private:
	vector <Locator> heap;

	int leftChild ( int i )
	{
		return 2 * i + 1;
	}

	int rightChild ( int i )
	{
		return 2 * i + 2;
	}

	int parent ( int i )
	{
		return ( i - 1 ) / 2;
	}

	bool exists ( int i )
	{
		return i >= 0 && i < heap.size ( );
	}

	void upheap ( int i )
	{
		while ( i > 0 && *(heap [ i ]->getData ( )) < *(heap [ parent ( i ) ]->getData ( )) ) // while not the root
		{
			swap ( heap [ i ]->index, heap [ parent ( i ) ]->index );
			swap ( heap [ i ], heap [ parent ( i ) ] );
			i = parent ( i );
		}
	}

	void downheap ( int i )
	{
		while ( exists ( leftChild ( i ) ) ) // while the current node has at least one child
		{
			int minChild = leftChild ( i );
			if ( exists ( rightChild ( i ) ) && *(heap [ rightChild ( i ) ]->getData ( )) < *(heap [ minChild ]->getData ( )) )
			{
				minChild = rightChild ( i );
			}

			if ( *(heap [ minChild ]->getData ( )) < *(heap [ i ]->getData ( )) )
			{
				swap ( heap [ i ]->index, heap [ minChild ]->index );
				swap ( heap [ i ], heap [ minChild ] );
				i = minChild;
			}
			else
			{
				break;
			}
		}
	}

public:
	Heap ( void ) 
	{
	}

	~Heap(void)
	{
		for ( int i = 0; i < heap.size ( ); i++ )
		{
			delete heap [ i ];
		}
	}

	bool isEmpty(void)
	{
		return heap.size ( ) == 0;
	}

	int size(void)
	{
		return heap.size ( );
	}

	Locator insertElement ( Type *data )
	{
		Locator rvalue = new HeapItem ( data );
		heap.push_back ( rvalue );

		heap [ heap.size ( ) - 1 ]->index = heap.size ( ) - 1;

		upheap ( heap.size ( ) - 1 );

		return rvalue;
	}

	Type *minElement ( void ) throw ( exception )
	{
		if ( isEmpty ( ) )
		{
			throw exception ();
		}
		return heap [ 0 ]->getData ( );
	}

	Type *removeMin ( void ) throw ( exception )
	{
		if ( isEmpty ( ) )
		{
			throw exception ();
		}
		HeapItem *toRemove = heap [ 0 ];
		Type *rvalue = toRemove->getData ( );

		heap [ 0 ] = heap [ heap.size ( ) - 1 ];
		heap.pop_back ( );
		if ( heap.size ( ) > 0 )
		{
			heap [ 0 ]->index = 0;
			downheap ( 0 );
		}

		delete toRemove;

		return rvalue;
	}

	// call this function if the relative ordering of item has changed
	void update ( Locator item )
	{
		int index = item->index;

		// could have become bigger... won't do anything if not bigger than children
		downheap ( index );

		// could have become smaller... won't do anything if not smaller than parent
		upheap ( index );
	}
};

#endif
