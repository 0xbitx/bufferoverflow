#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void rop(char *input){
    char buf[256];
    memcpy(buf, input, strlen(input));
}

int main(int argc, char **argv){
    rop(argv[1]);
    return 0;
}
