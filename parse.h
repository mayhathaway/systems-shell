char *strip_spaces(char *line);
char ** parse_args(char *line, char *sep);
char ** redirect_in(char ** args);
char ** redirect_out(char ** args);
void run_process(char *cmd);