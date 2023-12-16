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
 * Return: Array ptr to toks/lines
 */
char **get_inputs()
{
	char **toks;
	char buf[2048] = {'\0'};
	int size;
	char *line;

	size = read(STDIN_FILENO, buf, 2048);
	if (size == 0)
	{
		_printf("Exiting shell...\n");
		exit(0);
	}
	else if (size < 0)
	{
		_perror("Error: ");
		exit(1);
	}
	line = _strdup(buf);
	toks = _strtok(line, size, "\n;&");
	free(line);

	return (toks);
}
