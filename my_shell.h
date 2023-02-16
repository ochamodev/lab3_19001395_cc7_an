#ifndef MY_SHELL_H
#define MY_SHELL_H
#endif

#define MAX_LINE 80 /* 80 chars per line, per command, should be enough. */
#define BUFFER_SIZE 80
#define HISTORY_SIZE 10

typedef struct CommandArguments {
    char **full_command;
    char *command;
    int background;
} CommandArguments;

static char buffer[BUFFER_SIZE];
static CommandArguments *commandHistory[HISTORY_SIZE];
static int historyIndex = 0;

void runCommand(CommandArguments *);
