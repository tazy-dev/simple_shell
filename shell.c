#include "shell.h"

/**
 * main - Custom simple shell
 *
 * @ac: The Argument Count.
 * @av: The Argument Vector.
 * Return: The exit code -status- of the last command
 */
int main(int ac, char  **av)
{
	int i;
	char *input = NULL;
	char **process = NULL;
	int status = 0;
	(void) ac;

	while (1)
	{
		input = read_command();
		if (input == NULL)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			return (status);
		}
		process = tokenize_command(input);
		if (!process)
			continue;
		i = _fork(process[0]);
		if (i == 1)
		{
			free_command(process);
			exit(status);
		}
		status = execute_command(process, av);
	}
	return (status);
}

