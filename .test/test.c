#include <unistd.h>
#include <stdio.h>

int main(void){

#include <unistd.h>
    if (access("/usr/bin/revvv", F_OK) == 0)
        printf("Binary exists");
    else
        printf("Binary does not exists");

    return 0;
}