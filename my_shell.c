#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

#include "my_shell.h"

void runCommand(CommandArguments *);

void runCommand(CommandArguments *commandArgs) {
    char *command = commandArgs->full_command[0];
    execvp(commandArgs->full_command[0], commandArgs->full_command);
}

void setup(char inputBuffer[], CommandArguments *command_args) { 
    int length; /* # of characters in the command line */
   //read what the user enters on the command line
    length = read(STDIN_FILENO, inputBuffer, MAX_LINE);
    inputBuffer[length -1] = '\0';
    //remove_new_line(inputBuffer);
    strcpy(commandHistory[historyIndex].command, inputBuffer);


    char *parsed;
    char *separator = " ";
    int index = 0;
    int argsIndex = 0;

    parsed = strtok(inputBuffer, separator);
    while (parsed != NULL) {
        if (parsed[index] == 38) {
            command_args->background = 1;
        } else {
            command_args->full_command[index] = parsed;
        }
        parsed = strtok(NULL, separator);
        index++;
    }
    runCommand(command_args);
        /*if (index == 0) {
            command_args->command = parsed;
            index++;
        } else {
            char x = parsed[0];
            int result = x == 38;
            if (result) {
                command_args->background = 1;
            } else {
                command_args->args[argsIndex] = parsed;
                argsIndex++;
            }
        }/
        parsed = strtok(NULL, separator);
        index++;
    }

    runCommand(command_args);

    /*pid_t child_pid = fork();
        if (child_pid == 0) {
            
        }

        if (command_args->background == 1) {

        } else {
            waitpid(child_pid, NULL, 0);
        }
    */
   //         Implement me   <<<------
} 

/*
    Calls exec
*/


void handle_SIGINT() {
    strcpy(buffer,"\nImprimiendo historial de comandos\n");
    write(STDOUT_FILENO, buffer, strlen(buffer));
    for (int i = 0; i < HISTORY_SIZE; i++) {
        CommandHistory c = commandHistory[i];
        strcpy(buffer, c.command);
        write(STDOUT_FILENO, buffer, strlen(buffer));
    }
    strcpy(buffer, "Seleccione el comando que desea ejecutar->\n");
    write(STDOUT_FILENO, buffer, strlen(buffer));
    char inputBuffer[MAX_LINE];
    exit(0);
}

int main(int argc, char *argv[]) {
	char inputBuffer[MAX_LINE];
    CommandArguments *commandArgs = malloc(sizeof(CommandArguments));
    commandArgs->full_command = malloc (((MAX_LINE / 2) - 1) * sizeof(char *));
    struct sigaction handler;
    handler.sa_handler = &handle_SIGINT;
    sigaction(SIGINT, &handler, NULL);
    while (1) {
        printf("COMMAND->\n");
        if (historyIndex == 9) {
            historyIndex = 0;
        }
        
        setup(inputBuffer, commandArgs);
        historyIndex++;


    }
    free(commandArgs);
	return 0;
}