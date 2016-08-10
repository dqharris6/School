#include "StopWatch.h"
#include <stdio.h>

int fib ( int i )
{
	if ( i == 1 )
		return 1;
	if ( i <= 0 )
		return 0;
	return fib ( i - 1 ) + fib ( i - 2 );
}

void main ( void )
{
	StopWatch t;

	t.start ( );
	printf ( "35th Fibonacci number is %d\n", fib ( 35 ) );
	t.stop ( );

	printf ( "Took %f milliseconds\n", t.ms ( ) );
}