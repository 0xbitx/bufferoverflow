#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void BOF(){
    puts("Hacked!");
    exit(0);
}

void print_copy(char *arg){
    char buff[100];
    printf("%p\n", &buff[0]);
    strcpy(buff, arg);
}

int main(int argc, char *argv[]){
    print_copy(argv[1]);
    return 0;
}
