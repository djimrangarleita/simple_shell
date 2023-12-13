#include "main.h"

/**
 * _strtok - tokenize user inputs
 * @str: cmd red from stdin
 * @delim: token delimiter
 * Return: array of ptrs to tokens
 */
char **_strtok(char *str, char *delim)
{
	int i, j, toksnum = 0;
	char *tok, *dupstr, **toks;

	if (!str || !str[0])
		return (NULL);
	dupstr = _strdup(str);
	tok = strtok(dupstr, delim);
	while (tok != NULL)
	{
		tok = strtok(NULL, delim);
		toksnum++;
	}
	toks = malloc(sizeof(char *) * toksnum + 1);
	free(dupstr);

	tok = strtok(str, delim);
	for (i = 0; i < toksnum; i++)
	{
		toks[i] = malloc(sizeof(char) * _strlen(tok) + 1);
		if (!toks[i])
		{
			for (j = 0; j < i; j++)
			{
				free(toks[i]);
			}
			free(toks);
			return (NULL);
		}
		_strcpy(toks[i], tok);
		tok = strtok(NULL, delim);
	}
	toks[i] = NULL;

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
				tmp = _strdup(path);
				tmp = _strcat(tmp, "/");
				tmpcat = _strcat(tmp, input);
				if (stat(tmpcat, &buf) == 0)
				{
					pathexec = malloc(_strlen(tmpcat) * sizeof(char));
					pathexec = _strcpy(pathexec, tmpcat);
					free(tmp);
					free(tmpenv);
					return (pathexec);
				}
				path = strtok(NULL, ":");
			}
		}
		i++;
	}
	free(tmp);
	free(tmpenv);
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
