// SIMPLE SHELL PROGRAM
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LINE 80 /* 80 chars per line, per command, should be enough. */
/**
 * setup() reads in the next command line, separating it into distinct tokens
 * using whitespace as delimiters. setup() sets the args parameter as a 
 * null-terminated string.
 */
void setup(char inputBuffer[], char *args[],int *background)
{ int length; /* # of characters in the command line */
   //read what the user enters on the command line
    length = read(STDIN_FILENO, inputBuffer,MAX_LINE);  
   //         Implement me   <<<------
} 

//SIGNAL HANDLING EXAMPLE
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define BUFFER_SIZE 50
static char buffer[BUFFER_SIZE];
/* the signal handler function */
void handle_SIGINT() {
	write(STDOUT_FILENO,buffer,strlen(buffer));
	exit(0);
}
int main(int argc, char *argv[])  {
	/* set up the signal handler */
	struct sigaction handler;
	handler.sa_handler = handle_SIGINT; 
	sigaction(SIGINT, &handler, NULL);
	strcpy(buffer,"Caught <ctrl><c>\n");
	/* wait for <control> <C> */
	while (1);
	return 0;
}