#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>

char *args[5];

char *strip_spaces(char *line){
    int i = 0;
    int c = strlen(line)-1;
    while(line[i]==' '){
        i++;
    }
    while(line[c]==' '){
        line[c]=0;
        c--;
    }
    return(line+i);
}

char ** parse_args(char *line, char *sep){
    char *copy = line;
    int n = 0;
    int c = c;
    for (int i = 0; i < strlen(line);i++){
        if(line[i] == *sep){
            c++;
        }
    }
    char **args = malloc((c+1)*sizeof(char *));
    args[c] = NULL;
    while(copy){
        copy=strip_spaces(copy);
        args[n]=malloc(sizeof(char));
        args[n]=strsep(&copy, sep);
        n++;
    }
    return(args);
}

void run_process(char *cmd){
    //only works when printing? not sure why...
    printf("%s\n",cmd);
    char ** args = parse_args(cmd," ");
    if (strcmp(args[0],"exit") == 0){
        exit(0);
    }
    else if (strcmp(args[0],"cd") == 0){
        chdir(args[1]);
    }
    else{
        int f = fork();
        if (f){
            int status;
            wait(&status);
            if(WEXITSTATUS(status)!=0){
                printf("%s\n", strerror(WEXITSTATUS(status)));
            }
        }
        else{
            int n = execvp(args[0],args);
        }
    } 
    free(args);
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
        char ** args = parse_args(line, ";");
        for (int i = 0; args[i]!=NULL; i++){
            run_process(args[i]);
        }
        free(args);
    }
    printf("\n");
    return(0);
}
