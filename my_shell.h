#ifndef MY_SHELL_H
#define MY_SHELL_H
#endif

#define MAX_LINE 80 /* 80 chars per line, per command, should be enough. */
#define BUFFER_SIZE 80
#define HISTORY_SIZE 10

typedef struct CommandArguments {
    char **full_command;
    char *command;
    char firstL;
    int background;
} CommandArguments;

typedef struct CommandHistory {
    int size;
    CommandArguments *commandHistory[HISTORY_SIZE];
} CommandHistory;

typedef struct SelectedCommand {
    int i;
} SelectedCommand;

static char buffer[BUFFER_SIZE];
static CommandHistory *commandHistory;
//static CommandArguments *commandHistory[HISTORY_SIZE];
static int historyIndex = -1;

void runCommand(CommandArguments *);

int startsWith(char * str, char character) {
    return (str[0] == character);
}

void getCommandIndex(SelectedCommand *, char argument);

void getCommandIndex(SelectedCommand *selected, char argument) {
    int size = commandHistory->size;
    for (int i = 0; i < size; i++) {
        CommandArguments *c = commandHistory->commandHistory[i];
        if (c->full_command[0][0] == argument) {
            selected->i = i;
        }
    }
}

void init();