#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

/**
 * main - entry point of the console program
 * @argc: Number of arguments passed to the program
 * @argv: array of pointer to a user input
 * @envp: environmental variables
 *
 * Return: 0 on success and 1 on failure
 */

int main(int argc, char *argv[], char *envp[])
{
	pid_t child;
	int status;
	ssize_t nread;
	char *line = NULL;
	size_t len = 0;

	if (argc != 1)
		return (1);
	if (isatty(STDIN_FILENO) == 1)
		printf("#cisfun$ ");
	nread = getline(&line, &len, stdin);
	while (nread != -1)
	{
		child = fork();
		if (child == -1)
			return (1);
		if (child == 0)
		{
			line[strcspn(line, "\n")] = '\0';
			if (execve(line, argv, envp) == -1)
				printf("%s: %s\n", argv[0], strerror(errno));
			return (1);
		}
		else
		{
			wait(&status);
			printf("#cisfun$ ");
			nread = getline(&line, &len, stdin);
		}
	}
	return (0);
}
