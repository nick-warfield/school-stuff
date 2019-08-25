#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_CMD_LENGTH 80
#define CMD_HISTORY 5

void signature(void)
{
	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	printf("Program run by %s at %s\n", getenv("USER"), asctime(timeinfo));
}

#define DELIMS " \t\r\n\a"
char ** parse(char *line)
{
	char **tokens = malloc(MAX_CMD_LENGTH * sizeof(char*));
	if (!tokens)
	{
		fprintf(stderr, "memory allocation error\n");
		exit(EXIT_FAILURE);
	}

	int index = 0;
	char *token = strtok(line, DELIMS);
	while (token != NULL)
	{
		tokens[index] = token;
		++index;

		if (index >= MAX_CMD_LENGTH)
		{
			printf("Command too long\n");
			return NULL;
		}

		token = strtok(NULL, DELIMS);
	}
	tokens[index] = NULL;
	return tokens;
}

int launch(char **args)
{
	pid_t pid, wpid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		execvp(args[0], args);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("lsh");
	}
	else
	{
		do
		{
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));

		signature();
	}

	return 1;
}

int execute(char **args)
{
	if (args[0] == NULL) { return 1; }
	
	if (strcmp(args[0], "quit") == 0) { return 0; }

	// history
	// if (args[0][0] == '!') { return 1; }

	return launch(args);
}

void shell_loop(void)
{
	char *line = NULL;		// user input
	char **args;			// for execvp() later
	int status;

	do
	{
		printf("comp322> ");
		fflush(stdout);

		size_t s = 0;
		getline(&line, &s, stdin);
		args = parse(line);
		status = execute(args);

		free(line);
		free(args);
	}
	while (status);

}

int main(void)
{

	shell_loop();
	return 0;
}
