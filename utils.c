#include "main.h"

/**
 * gettoksdelim - get number of tokens for malloc
 * @line - single line read from stdin
 * @size: size of line
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
 * findxpath - find full path of an executable
 * @input: ptr to user's path
 * Return: full path of an exec or input
 */
char *findxpath(char *input)
{
	int i;
	char *key, *val, *pathexec, *tmpenv = NULL;

	if (*input == '/')
	{
		return (_strdup(input));
	}

	i = 0;
	while (environ && environ[i] != NULL)
	{
		tmpenv = _strdup(environ[i]);
		key = strtok(tmpenv, "=");
		val = strtok(NULL, "=");
		if (_strcmp(key, "PATH") == 0)
		{
			pathexec = makexpath(input, val);
			if (pathexec)
			{
				free(tmpenv);
				return (pathexec);
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

	while (tokens && tokens[i])
		free(tokens[i++]);
	free(tokens);
}

/**
 * readcmd - use getline func to read user input
 * @line: ptr to stdin
 * @len: length of elt
 * Return: chars read or exit -1
 */
/*int readcmd(char **line, size_t *len)
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
*/
char **get_inputs()
{
	char **toks;
	char buf[1024] = {'\0'};
	int size;
	char *line;

	size = read(STDIN_FILENO, buf, 1024);
	if (size == 0)
	{
		_printf("Exiting shell...\n");
		exit(0);
	}
	else if(size < 0)
	{
		_perror("Error: ");
		exit(1);
	}
	line = _strdup(buf);
	toks = _strtok(line, size, "\n;&");
	free(line);

	return (toks);
}

/**
 * makexpath - make full path to an exec
 * @input: user input, cmd,
 * @curpath: current token
 * Return: pointer to the path
 */
char *makexpath(char *input, char *curpath)
{
	char *path, *tmp, *tmpcat, *pathexec;
	struct stat buf;
	
	path = strtok(curpath, ":");
	while (path != NULL)
	{
		tmp = malloc((_strlen(path) + _strlen(input) + 2) * sizeof(char));
		if (!tmp)
		{
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
			return (pathexec);
		}
		path = strtok(NULL, ":");
		free(tmp);
	}

	return (NULL);
}
