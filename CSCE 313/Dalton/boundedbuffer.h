// CHANGE THIS

#include <pthread.h>
#include <queue>
#include <string>
#include "semaphore.h"


class String_out
{
	public:
		string 	ds_response;
		int 	client_request;
		int 	counter;

	String_out(string s, int r, int c)
	{
		ds_response 	= s;
		client_request 	= r;
		counter 		= c;
	}
};

class boundedbuffer
{
	private:
		int 				buff_size;
		queue<String_out> 	queue_out;
		Semaphore * 		lock;
		Semaphore * 		full;
		Semaphore * 		empty;

	public:
		boundedbuffer(int _buff_size)
		{
			buff_size 	= _buff_size;
			lock 		= new Semaphore(1);
			full 		= new Semaphore(0);
			empty 		= new Semaphore(buff_size);
		}


	~boundedbuffer()
	{
		delete 	lock;
		delete 	full;
		delete 	empty;
	}

	void my_push(String_out _string_out)
	{
		empty 	-> P();
		lock 	-> P();
		queue_out.push(_string_out);
		lock 	-> V();
		full 	-> V();
	}

	String_out my_pop()
	{
		full 			-> P();
		lock 			-> P();
		String_out r 	= queue_out.front();
		queue_out.pop();
		lock 			-> V();
		empty 			-> V();
		
		return r;
	}
};

	/*

	We bound the buffer so it doesn't take too much RAM.
	*/



	/*
		This is a blocking function, it tries to push and waits until there is enough space to succesfully do so. 
		If the buffer is full, the push will keep trying to push until there is enough space.

	producer goes in, consumer comes out of the buffer. 

	incorrect implementations:
		while(buf is full){
			sleep(10);
		}
		
		buf.push_back(_str);
	*/



	/*

	*/