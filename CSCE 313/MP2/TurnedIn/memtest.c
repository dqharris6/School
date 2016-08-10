#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include "my_allocator.h"
#include "ackerman.h"

int main(int argc, char ** argv)
{
    int c;
    unsigned int b=128;
    unsigned int m=67108864;

    while ((c = getopt(argc, argv, "b:s:")) != -1){
        switch (c){

            case 'b':
                b=atoi(optarg);
                break;

            case 's':
                   m=atoi(optarg);
                break;
            
            default:
                abort ();
        }
    }

    init_allocator(b,m);
    ackerman_main();

    atexit((void(*)())release_allocator);
}