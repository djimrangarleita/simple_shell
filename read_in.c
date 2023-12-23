#include "main.h"

/**
 * get_inputs - read user inputs from stdin and parse lines
 * @status: ptr to last execution status
 * @fd: file descriptor to read cmds from, if any
 * Return: Array ptr to toks/lines
 */
char **get_inputs(int *status, int fd)
{
	int size, hasred = 0, buffsize = 1025;
	int insrc = STDIN_FILENO;
	char *tmp, *buffer, **toks;

	buffer = malloc(buffsize * sizeof(char));
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	if (fd > 0)
		insrc = fd;
	do {
		tmp = malloc(sizeof(char) * 1025);
		size = read(insrc, tmp, 1024);
		if (size < 0)
		{
			_preaderr(buffer, tmp);
			exit(1);
		}
		if (size == 0 && !hasred)
		{
			free(tmp);
			free(buffer);
			if (fd > 0)
				return (NULL);
			_printf("Exiting shell...\n");
			exit(*status);
		}
		tmp[size] = '\0';
		buffer = _strcat(buffer, tmp);
		if (size >= 1024)
		{
			buffer = _realloc(buffer, buffsize, buffsize + size);
			buffsize += size;
		}
		free(tmp);
		hasred = 1;
	} while (size >= 1024);
	toks = _strtok(buffer, size, "\n;&");
	free(buffer);
	return (toks);
}

/**
 * _preaderr - free buffer and print error msg when read() fails
 * @buffer: ptr to buffer
 * @tmp: tmp mem for read ops
 * Return: 1 for error
 */
int _preaderr(char *buffer, char *tmp)
{
	free(buffer);
	free(tmp);
	perror("Error");

	return (1);
}
