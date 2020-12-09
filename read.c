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
    char line[] = "ls -l -a";
    char ** args = parse_args(line);
    execvp(args[0], args);
    return(0);
}
