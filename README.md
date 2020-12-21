# Hermit Crab Shell
##### by Sasha Wald and May Hathaway
##### TNPG: Team Hermit Crab!

## Features:
- Executes commands of up to 255 chars!
  - Executes commands within a child process
  - Commands may be input one at a time, or separated by a semicolon (;)
  - Strips commands with improperly formatted spaces, or added newlines and tabs, allowing them to be run
- Allows you to redirect using < and >
- (Almost) Allows piping with |

## Bugs:
- Sasha found an issue where the run_process function (which executes commands) would only function correctly when the user's inputted command was first printed. This is visible when running commands.
- Sasha attempted creating run_pipe - was able to get a function that forks and creates an unnamed pipe, but ran into a looping error which prevented the "write" side of the pipe from working. Tried many fixes but not sure where this function went wrong

## Files:
parse.c
- handles line parsing functions, redirection and piping functions

main.c
- handles user input + creating shell prompt
