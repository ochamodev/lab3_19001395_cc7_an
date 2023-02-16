#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

#include "my_shell.h"

void setup(char inputBuffer[], CommandArguments *command_args) { 
    int length; /* # of characters in the command line */
   //read what the user enters on the command line
    length = read(STDIN_FILENO, inputBuffer, MAX_LINE);
    inputBuffer[length -1] = '\0';
    strcpy(command_args->command, inputBuffer);
    char *parsed;
    char *separator = " ";
    int index = 0;
    int argsIndex = 0;

    command_args->firstL = inputBuffer[0];

    parsed = strtok(inputBuffer, separator);
    while (parsed != NULL) {
        if (strcmp(parsed, "&") == 0) {
            command_args->background = 1;
        } else {
            command_args->full_command[index] = parsed;
        }
        parsed = strtok(NULL, separator);
        index++;
    }

    if(command_args->background == 1) {
        command_args->full_command[index] = "";
    } else {
        command_args->full_command[index +1] = "\n";
    }

    commandHistory[historyIndex] = command_args;
} 

/*
    Calls exec
*/

void handle_SIGINT() {
    strcpy(buffer,"\nImprimiendo historial de comandos\n");
    write(STDOUT_FILENO, buffer, strlen(buffer));
    for (int i = 0; i < historyIndex; i++) {
        CommandArguments *c = commandHistory[i];
        char *cmd = strcat(c->command, "\n");
        write(STDOUT_FILENO, cmd, strlen(cmd));
    }
    strcpy(buffer, "Seleccione el comando que desea ejecutar->\n");
    write(STDOUT_FILENO, buffer, strlen(buffer));
    int length = read(STDIN_FILENO, buffer, MAX_LINE);
    buffer[length -1] = '\0';
    printf("%d ", strlen(buffer));

    char *parsed;
    char *separator = " ";
    int index = 0;

    // length 1 si solo ponen r

    if (strlen(buffer) == 1) {
        CommandArguments *c = commandHistory[historyIndex];
        char *cmd = strcat(c->command, "\n");
        write(STDOUT_FILENO, cmd, strlen(cmd));
    } else {
        // length 3 si ponen r x
    }

    exit(0);
}

int main(int argc, char *argv[]) {
	char inputBuffer[MAX_LINE];
    CommandArguments *commandArgs;
    // setear funcion de historial.
    struct sigaction handler;
    handler.sa_handler = &handle_SIGINT;
    sigaction(SIGINT, &handler, NULL);
    
    pid_t child_pid;

    while (1) {
        printf("COMMAND->\n");
        if (historyIndex == 9) {
            historyIndex = 0;
        }

        commandArgs = malloc(sizeof(CommandArguments));
        commandArgs->command = (char *) malloc(sizeof(char *));
        commandArgs->full_command = malloc (((MAX_LINE / 2) - 1) * sizeof(char *));
        setup(inputBuffer, commandArgs);
        historyIndex++;
        child_pid = fork();

        if (child_pid == 0) {
            if (commandArgs->background == 0) {
                execvp(commandArgs->full_command[0], commandArgs->full_command);    
            } else {
                execvp(commandArgs->full_command[0], commandArgs->full_command);
                waitpid(child_pid, NULL, 0);
            }
        }
    }
    free(commandArgs);
	return 0;
}