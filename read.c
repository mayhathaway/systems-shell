#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>

char *args[5];

char ** parse_args(char *line){
    char *copy = line;
    int n = 0;
    while(copy){
        args[n]=strsep(&copy, " ");
        n++;
    }
    return(args);
}

int main(){
    int f = fork();
    char line[] = "ls -a -l";
    char ** args = parse_args(line);
    if (f){
        printf("fork\n");
        execvp(args[0], args);
        return(0);
    }
    return(0);
}
