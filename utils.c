#include "main.h"

char *DELIMS = " \t\n;'&&'";

/**
 * _strtok - tokenize user inputs
 * @str: cmd red from stdin
 * @delim: token delimiter
 * Return: array of ptrs to tokens
 */
char **_strtok(char *str, int size)
{
	int i, j, toksnum = 0;
	char *tok, *cpstr, **toks;

	if (!str || !str[0])
		return (NULL);
	/*copy chars read instead of _strdup*/
	cpstr = malloc((size + 1) * sizeof(char));
	if (!cpstr)
	{
		_perror("Error: Memory allocation");
		return (NULL);
	}
	_strcpy(cpstr, str);
	tok = strtok(cpstr, DELIMS);
	while (tok != NULL)
	{
		if (tok[0] == '#')
			break;
		_printf("Token: %s\n", tok);
		tok = strtok(NULL, DELIMS);
		toksnum++;
	}
	_printf("Num of tokens is: %d\n", toksnum);
	toks = malloc(sizeof(char *) * (toksnum + 1));

	tok = strtok(str, DELIMS);
	for (i = 0; i < toksnum; i++)
	{
		if (tok[0] == '#')
			break;
		toks[i] = malloc(sizeof(char) * _strlen(tok) + 1);
		if (!toks[i])
		{
			for (j = 0; j < i; j++)
			{
				free(toks[i]);
			}
			free(cpstr);
			free(toks);
			return (NULL);
		}
		_strcpy(toks[i], tok);
		tok = strtok(NULL, DELIMS);
	}
	toks[i] = NULL;
	free(cpstr);
	free(str);
	return (toks);
}

/**
 * findxpath - find full path of an executable
 * @input: ptr to user's path
 * Return: full path of an exec or input
 */
char *findxpath(char *input)
{
	int i;
	char *key, *val, *path, *tmp = NULL, *tmpcat, *pathexec, *tmpenv = NULL;
	struct stat buf;

	if (*input == '/')
	{
		return (_strdup(input));
	}

	i = 0;
	while (environ[i] != NULL)
	{
		tmpenv = _strdup(environ[i]);
		key = strtok(tmpenv, "=");
		val = strtok(NULL, "=");
		if (_strcmp(key, "PATH") == 0)
		{
			path = strtok(val, ":");
			while (path != NULL)
			{
				tmp = malloc((_strlen(path) + _strlen(input) + 2) * sizeof(char));
				if (!tmp)
				{
					free(tmpenv);
					return (_strdup(input));
				}
				tmp = _strcpy(tmp, path);
				tmp = _strcat(tmp, "/");
				tmpcat = _strcat(tmp, input);
				if (stat(tmpcat, &buf) == 0)
				{
					pathexec = malloc((_strlen(tmpcat) + 1) * sizeof(char));
					pathexec = _strcpy(pathexec, tmpcat);
					free(tmp);
					free(tmpenv);
					return (pathexec);
				}
				path = strtok(NULL, ":");
				free(tmp);
			}
		}
		free(tmpenv);
		i++;
	}
	return (_strdup(input));
}

/**
 * free_toks - free mem allocated to tokens
 * @tokens: array of toks
 */
void free_toks(char **tokens)
{
	int i = 0;

	while (tokens && tokens[i] != NULL)
		free(tokens[i++]);
	free(tokens);
}

/**
 * readcmd - use getline func to read user input
 * @line: ptr to stdin
 * @len: length of elt
 * Return: chars read or exit -1
 */
int readcmd(char **line, size_t *len)
{
	int rchars;

	rchars = getline(line, len, stdin);
	if (rchars == -1)
	{
		_perror("Exiting shell...");
		free(*line);
		exit(-1);
	}

	return (rchars);
}
