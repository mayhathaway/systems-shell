# Hermit Crab Shell
##### by Sasha Wald and May Hathaway
##### TNPG: Team Hermit Crab!

## Features:
- Executes commands of up to 255 chars!
  - Executes commands within a child process
  - Commands may be input one at a time, or separated by a semicolon (;)
  - Strips commands with improperly formatted spaces, or added newlines and tabs, allowing them to be run
- Allows you to redirect using < and >
- Allows piping with |

## Bugs:
- Sasha found an issue where the run_process function (which executes commands) would only function correctly when the user's inputted command was first printed. This is visible when running commands.
- Sasha attempted creating run_pipe - was able to get a function that forks and creates an unnamed pipe, but ran into a looping error which prevented the "write" side of the pipe from working. Tried many fixes but not sure where this function went wrong. Ending up switching to using popen which was much quicker!
- Pipe function is somewhat vulnerable. Doing something like $ls | wc ; echo hello will work, but the results are printed two times. It does support additional spaces, but not exit/cd commands

## Files:
parse.c
- handles line parsing functions, redirection and piping functions
 ```
      char *strip_spaces(char *line)
      Function: strips white space, tabs and newlines from the function to ensure it runs correctly
      
      char ** parse_args(char *line, char *sep)
      Function: parses line into a char ** array based on a given separator (char * sep)
      
      char ** redirect_in(char ** args)
      Function: redirects stdin from a file
      
      char ** redirect_out(char ** args)
      Function: redirects stdout to a file
      
      void run_pipe(char * line)
      Function: runs pipes!
      
      void run_process(char *cmd)
      Function: forks and runs command in a child process (unless a pipe is used). Contain exit cases for cd and exit functions
```
main.c
- handles user input + creating shell prompt
