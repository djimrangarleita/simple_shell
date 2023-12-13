#include "main.h"

/**
 * main - shell entry point
 * @ac: agr count
 * @argv: array of args
 * Return: 0 on success
 */
int main(int ac, char *argv[])
{
	size_t len = 0;
	char *line = NULL;
	int execres;

	if (ac < 1)
		return (-1);

	if (isatty(STDIN_FILENO) != 1)
	{
		execres = shelln_int(&line, &len, argv[0]);
		if (execres != 0)
			return (-1);
	}
	else
	{
		shell_int(&line, &len, argv[0]);
	}
	return (0);
}
