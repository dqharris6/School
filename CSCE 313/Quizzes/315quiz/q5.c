//
// Created by Clayton Petty on 3/31/16.
//

#include <fcntl.h>
#include <zconf.h>

int main(){
    char buf[] = "abc";
    int r = open("file.txt", O_RDWR);
    int r1 = 0;
    int r2 = open("file.txt", O_RDWR);
    dup2(r, r1);
    read(r, buf, 1);
    read(r2, buf, 2);
    write(r, buf, 3);
    read(r2, buf, 1);
    write(r1, buf, 1);
    return 0;

}
