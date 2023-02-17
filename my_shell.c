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
        command_args->full_command[index];
        command_args->full_command[index + 1] = NULL;
    } else {
        command_args->full_command[index +1] = NULL;
    }

    commandHistory->commandHistory[commandHistory->size] = command_args;
} 

/*
    Calls exec
*/

void handle_SIGINT() {
    strcpy(buffer,"\nImprimiendo historial de comandos\n");
    write(STDOUT_FILENO, buffer, strlen(buffer));
    for (int i = 0; i < commandHistory->size; i++) {
        CommandArguments *c = commandHistory->commandHistory[i];
        char *cmd = strcat(c->command, "\n");
        write(STDOUT_FILENO, cmd, strlen(cmd));
    }
    strcpy(buffer, "Seleccione el comando que desea ejecutar->\n");
    char read_buffer[BUFFER_SIZE];
    write(STDOUT_FILENO, buffer, strlen(buffer));
    int length = read(STDIN_FILENO, read_buffer, MAX_LINE);
   
    read_buffer[length -1] = '\0';

    char *parsed;
    char *separator = " ";
    int index = 0;

    // length 1 si solo ponen r

    

    if (strlen(read_buffer) == 1) {
        int size = commandHistory->size;
        CommandArguments *c = commandHistory->commandHistory[size -1];
        char *cmd = strcat(c->command, "\n");
        
        strcpy(read_buffer, cmd);
        write(STDOUT_FILENO, read_buffer, strlen(read_buffer));
        execvp(c->full_command[0], c->full_command);
    } else {
        // length 3 si ponen r x
        char start = read_buffer[2];
        SelectedCommand *selected = malloc(sizeof(SelectedCommand));
        getCommandIndex(selected, start);
        CommandArguments *c = commandHistory->commandHistory[selected->i];
        char *cmd = strcat(c->command, "\n");
        write(STDOUT_FILENO, cmd, strlen(cmd));
        execvp(c->full_command[0], c->full_command);
    }

    exit(0);
}

int main(int argc, char *argv[]) {
	char inputBuffer[MAX_LINE] = {'\0'};
    CommandArguments *commandArgs;
    commandHistory = malloc(sizeof(CommandHistory));
    commandHistory->size = 0;
    pid_t child_pid;

    struct sigaction handler;
    handler.sa_handler = &handle_SIGINT;
    sigaction(SIGINT, &handler, NULL);

    int x = 0;

    while (1) {
        printf("COMMAND->\n");
        if (commandHistory->size == 9) {
            commandHistory->size = 0;
        }
        commandArgs = malloc(sizeof(CommandArguments));
        commandArgs->command = (char *) malloc(sizeof(char *));
        commandArgs->full_command = malloc (((MAX_LINE / 2) - 1) * sizeof(char *));
        setup(inputBuffer, commandArgs);
        commandHistory->size++;
        
        pid_t p = getpid();
        child_pid = fork();
        if (child_pid == 0) {
            if (commandArgs->background == 0) {
                execvp(commandArgs->full_command[0], commandArgs->full_command);    
            } else {
                execvp(commandArgs->full_command[0], commandArgs->full_command);
                waitpid(p, NULL, 0);
            }
        }
    }
    free(commandArgs);
    free(commandHistory);
	return 0;
}