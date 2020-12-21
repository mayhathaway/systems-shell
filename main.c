#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include "parse.h"

char *args[5];

int main(){
    char line[256];
    while(1){
        //making prompt
        printf("\nhermit-crab: sasha$ ");
        if (fgets(line,256,stdin)!=NULL){
            int len = strlen(line);
            if (len > 0 && line[len-1] == '\n'){
                len--;
                line[len] = '\0';
            }
        }
        //extra code for pipes
        char nl[256];
        strcpy(nl,line);
        char *pipecopy = nl;
        int count = 1;
        while(*pipecopy){
            if(*pipecopy == '|'){
                count++;
            }
            *pipecopy++;
        }
        //run commands
        char ** args = parse_args(line, ";");
        for (int i = 0; args[i]!=NULL; i++){
            if(count>1){
                run_pipe(nl);
            }
            else{
                args[i] = strip_spaces(args[i]);
                run_process(args[i]);
            }
        }
    }
    free(args);
    return(0);
}
