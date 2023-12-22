#include "main.h"

/**
 * gettoksnum - get number of tokens for malloc
 * @line: single line read from stdin
 * @size: size of line
 * @delim: delimiters
 * Return: Int, number of toks
 */
int gettoksnum(char *line, int size, char *delim)
{
	int toksnum = 0;
	char *cpstr, *tok;

	if (size <= 0 || !line || !line[0])
		return (0);

	cpstr = _strdup(line);
	if (!cpstr)
		return (0);
	tok = strtok(cpstr, delim);
	while (tok != NULL)
	{
		if (tok[0] == '#')
			break;
		tok = strtok(NULL, delim);
		toksnum++;
	}
	free(cpstr);

	return (toksnum);
}

/**
 * _strtok - tokenize user inputs
 * @line: cmd red from stdin
 * @size: size of @line
 * @delim: token delimiter
 * Return: array of ptrs to tokens
 */
char **_strtok(char *line, int size, char *delim)
{
	int i, j, toksnum;
	char *tok, **toks;

	toksnum = gettoksnum(line, size, delim);
	if (toksnum <= 0)
		return (NULL);

	toks = malloc(sizeof(char *) * (toksnum + 1));
	if (!toks)
		return (NULL);

	tok = strtok(line, delim);
	i = 0;
	while (tok != NULL)
	{
		if (tok[0] == '#')
			break;
		toks[i] = _strdup(tok);
		if (!toks[i])
		{
			for (j = 0; j < i; j++)
			{
				free(toks[i]);
			}
			free(toks);
			return (NULL);
		}
		tok = strtok(NULL, delim);
		i++;
	}
	toks[i] = NULL;

	return (toks);
}

/**
 * free_toks - free mem allocated to tokens
 * @tokens: array of toks
 */
void free_toks(char **tokens)
{
	int i = 0;

	while (tokens && tokens[i])
		free(tokens[i++]);
	free(tokens);
}

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
			free(buffer);
			free(tmp);
			_printerr(1, NULL, "Error", NULL);
			exit(1);
		}
		if (size == 0 && !hasred)
		{
			free(tmp);
			free(buffer);
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
 * _realloc - reallocate mem
 * @old_size: old size of ptr
 * @newsize: size of new mem block
 * @ptr: pointer to old block
 * Return: char pointer or NULL
 */
char *_realloc(char *ptr, int old_size, int newsize)
{
	char *newptr;

	if (newsize == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	if (newsize == old_size)
		return (ptr);

	newptr = malloc(newsize);
	if (ptr == NULL)
		return (newptr);

	newptr = _strcpy(newptr, ptr);
	free(ptr);

	return (newptr);
}
