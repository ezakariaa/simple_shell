#include "shell.h"

/**
 * r_line - Gets input(line) from the end user.
 *
 * Return: A pointer to the line.
 */
char *r_line(void)
{
	char *line_ptr = NULL;
	char *prompt = "$ ";
	size_t size = 0;
	int bytes_read;

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, prompt, 2);

	bytes_read = getline(&line_ptr, &size, stdin);
	if (bytes_read == -1)
	{
		free(line_ptr);
		return (NULL);
	}

	return (line_ptr);
}
