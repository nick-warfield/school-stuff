#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_LINE        80 /* 80 chars per line, per command, should be enough. */
#define MAX_COMMANDS    5 /* size of history */

char history[MAX_COMMANDS][MAX_LINE];
int command_count = 0;

int toDisplayNum(int num)
{
	num = num - command_count + 1;
	if (num <= 0) { num += MAX_COMMANDS; }
	return num;
}
int toHistoryNum(int num)
{
	num = num + command_count - 1;
	if (num >= MAX_COMMANDS) { num -= MAX_COMMANDS; }
	return num;
}
void addtohistory(char command[])
{
	for (int i = 0; i < MAX_LINE; ++i)
	{
		history[command_count][i] = command[i];
		if (command[i] == '\0') { i = MAX_LINE; }
	}
	if (++command_count >= MAX_COMMANDS) { command_count = 0; }
	return;
}
void loadHistory(char cmdNum, char command[])
{
	int num = cmdNum - '0' - 1;
	if ((num < 0 || num > MAX_COMMANDS) && cmdNum != '!') { return; }
	num = toHistoryNum(num);
	if (cmdNum == '!') { num = command_count - 1; }
	
	for (int i = 0; i < MAX_LINE; ++i)
	{
		command[i] = history[num][i];
		if (history[num][i] == '\0') { i = MAX_LINE; }
	}
}
void signature(void)
{
	// replace later, needs to get from system
	printf("Program run by %s at %s\n", "userID", "Current Time");
}

int setup(char command[], char *args[], int *runBG)
{
    int length;			/* # of characters in the command line */

    /* read what the user enters on the command line */
	do
	{
		printf("comp322> ");
		fflush(stdout);
		length = read(STDIN_FILENO,command,MAX_LINE); 
	}
	while (command[0] == '\n');

    if ( (length < 0) && (errno != EINTR) )
	{
		perror("error reading the command");
		exit(-1);
    }

	if (command[0] == '!' && command[1] != '\0')
	{ loadHistory(command[1], command); }

	addtohistory(command);
	
	int argPos = 0, end = 0;
	char arg[MAX_LINE];
	for (int i = 0; i < length; ++i)
	{ 
        switch (command[i])
		{
			case ' ':
			case '\n':
			case '\t':
				arg[end] = '\0';
				end = 0;
				args[argPos] = arg;
				argPos++;
				break;

			case '&':
				if (i + 2 == length) { *runBG = 1; }
				break;
			case '-':
			default:
				arg[end] = command[i];
				end++;
				break;
		}
	}
	args[argPos] = NULL;
	printf("%s\n", args[0]);
	return 1;
}

int main(void)
{
	char command[MAX_LINE];
//	char *args[MAX_LINE/2 + 1];
	char **args;
	args = malloc((MAX_LINE/2 + 1) * sizeof(char*));
	for (int i = 0; i < MAX_LINE/2 + 1; ++i)
	{ args[i] = malloc(MAX_LINE * sizeof(char)); }
	pid_t child;
	int status;
	int shouldrun = 1, runBG = 0;

	/* Program terminates normally inside setup */
	while (shouldrun)
	{  
		shouldrun = setup(command, args, &runBG);
		printf("%s\n", args[0]);

		child = fork();
		if (child < 0)
		{

		}
		else if (child > 0)
		{
			printf("Parent: %s\n", args[0]);
			wait(NULL);
			signature();
		}
		else if (child == 0)
		{
			child = getpid();
			// check '&' later
			printf("Child: %s\n", args[0]);
			assert(strcmp(args[0], "ls") == 1);

			status = execvp(args[0], args);
			printf("You shouldn't see this\n");
			exit(0);
		}
	}
	return 0;
}
