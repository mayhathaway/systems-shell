#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>

char *strip_spaces(char *line){
    int i = 0;
    int c = strlen(line)-1;
    while(line[i]==' '){
        if(line[i]=='\t' || line[i]=='\n'){
            line[i]=' ';
        }
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
    int c = 0;
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

char ** redirect_in(char ** args){
    for (int i = 0; args[i] != NULL; i++){
        if(strcmp(args[i],"<") == 0){
            int fd = open(args[i+1],O_RDONLY,0644);
            dup2(fd,0);
            args[i]=NULL;
        }
    }
    return(args);
}
//finicky...
char ** redirect_out(char ** args){
    for (int i = 0; args[i] != NULL; i++){
        if(strcmp(args[i],">") == 0){
            int fd = open(args[i+1],O_TRUNC|O_RDWR|O_CREAT, 0644);
            dup2(fd,1);
            args[i]=NULL;
        }
    }
    return(args);
}

void run_process(char *cmd){
    //only works when printing? not sure why...
    printf("%s\n",cmd);
    char **args = parse_args(cmd," ");
    //edge cases for exit and cd
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
            args=redirect_in(args);
            args=redirect_out(args);
            int n = execvp(args[0],args);
        }
    } 
    free(args);
}