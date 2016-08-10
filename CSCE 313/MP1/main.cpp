#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <getopt.h>
#include "linked_list2.h"

int main(int argc, char ** argv) 
{
	const char* b;
	const char* s;
	const char* t;

	int bflag = 0;
	int sflag = 0;
	int tflag = 0;

	int temp;
	while((temp = getopt(argc,argv, "b:s:t:")) != -1)
	{
		switch(temp)
		{
			case 'b':
			b = optarg;
			++bflag;
			break;

			case 's':
			s = optarg;
			++sflag;
			break;

			case 't':
			t = optarg;
			++tflag;
			break;

			default:
			abort();
		}

	}

	if(bflag == 0) {b = "128";}
	if(sflag == 0) {s = "512000";}
	if(tflag == 0) {t = "4";}
	
	char buf [1024];
	memset (buf, 1, 1024);		// set each byte to 1
	
	const char * msg = "a sample message";
	
	Init(atoi(s), atoi(b), atoi(t)); // initialize
	
	// test operations
	// int testnums [] = {100,5,200,7,39,25,400,50,200,300};
	int testnums [] = {0, 1<<29 , (1<<29) + 5 , 50, (1<<30) + 5, (1<<30) - 500};
	int i = 0;
	// some sample insertions
	for (i=0; i< 6; i ++)
	{
		Insert(testnums [i], buf, 50);   // insert 50 bytes from the buffer as value for each of the insertions
	}
	PrintList();
	Delete(50);
	Delete(5);
	Delete(1073741829);
	std::cout << "\n---- AFTER DELETION ----\n";
	PrintList();
	// end test operations	
	Destroy();
	
}
