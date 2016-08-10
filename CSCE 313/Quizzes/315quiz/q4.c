#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    char buf[] = "ab";
    int r = open("file.txt", O_RDONLY);
    int r1, r2, pid;
    r1 = dup(r);
    read(r, buf, 1);
    if ((pid = fork()) == 0){
        r1 = open("file.txt", O_RDONLY); 
    } else {
        waitpid(pid, NULL, 0);
    }
    read(r1, buf, 1);
    printf("*%s", buf);
    printf("\n");

    return 0;
}
