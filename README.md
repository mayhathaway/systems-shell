<b>Hermit Crab Shell<b>\n
by Sasha Wald and May Hathaway\n
TNPG: Team Hermit Crab!\n

<b>Features:</b>
- Executes commands of up to 255 chars!
  - Executes commands within a child process
  - Commands may be input one at a time, or separated by a semicolon (;)
  - Strips commands with improperly formatted spaces, or added newlines and tabs, allowing them to be run
- Allows you to redirect using < and >
- Allows piping with |

<b>Bugs:</b>
- Sasha found an issue where the run_process function (which executes commands) would only function correctly when the user's inputted command was first printed. 
