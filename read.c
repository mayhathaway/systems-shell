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
    char line[256];
    while(1){
        printf("\nhermit-crab: sasha$ ");
        if (fgets(line,256,stdin)!=NULL){
            int len = strlen(line);
            if (len > 0 && line[len-1] == '\n'){
                len--;
                line[len] = '\0';
            }
        }
        //running commands (for now). will need to sep by ; in the future, so making a separate function
        char ** args = parse_args(line);
        for(int n=0; args[n] != NULL; n++){
            execvp(args[0], args);
        }
        free(args);
    }
    return(0);
}
