#include "main.h"

/**
 * main - shell entry point
 * @ac: agr count
 * @argv: array of args
 * Return: 0 on success
 */
int main(int ac, char *argv[])
{
	int execres;

	if (ac < 1)
		return (-1);

	if (isatty(STDIN_FILENO) != 1)
	{
		execres = shelln_int(argv[0], argv[1]);
	}
	else
	{
		execres = shell_int(argv[0], argv[1]);
	}
	return (execres);
}
