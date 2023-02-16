#ifndef MY_SHELL_H
#define MY_SHELL_H
#endif

#define MAX_LINE 80 /* 80 chars per line, per command, should be enough. */
#define BUFFER_SIZE 80
#define HISTORY_SIZE 10

typedef struct CommandArguments {
    char *command;
    char **full_command;
    int background;
} CommandArguments;

typedef struct CommandHistory {
    char command[MAX_LINE];
} CommandHistory;

static char buffer[BUFFER_SIZE];
static CommandHistory commandHistory[HISTORY_SIZE];
static int historyIndex = 0;

void remove_new_line(char* string) {
    int length = strlen(string);
    printf("%s ", string);
    if((length > 0) && (string[length-1] == '\n'))
    {
        string[length-1] ='\0';
    }
}