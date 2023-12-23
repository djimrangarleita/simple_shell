#include "main.h"

/**
 * filter_toks - check for special char $ and replace before execve
 * @toks: list of toks to check
 * @prevstatus: previous exec status
 * Return: toks, altered or not
 */
char **filter_toks(char **toks, int *prevstatus)
{
	int i;
	char buffer[12] = {'\0'};
	char **tmp = NULL;

	i = 0;
	while (toks && toks[i])
	{
		if (toks[i][0] == '$' && _strcmp(toks[i], "$") != 0)
		{
			if (_strcmp(toks[i], "$$") == 0)
			{
				sprintf(buffer, "%d", getpid());
				free(toks[i]);
				toks[i] = _strdup(buffer);
			}
			else if (_strcmp(toks[i], "$?") == 0)
			{
				sprintf(buffer, "%d", *prevstatus);
				free(toks[i]);
				toks[i] = _strdup(buffer);
			}
			else
			{
				tmp = _strtok(toks[i], _strlen(toks[i]), "$");
				free(toks[i]);
				toks[i] = _getenv(tmp[0]);
				free_toks(tmp);
				if (toks[i] == NULL && toks[i + 1] != NULL)
				{
					shift_toks(toks, i);
					filter_toks(toks, prevstatus);
				}
			}
		}
		i++;
	}
	return (toks);
}

/**
 * shift_toks - shift tokens to the left if _getenv returns null
 * @toks: toks list
 * @pos: position where null was found
 * Return: shifted tokens
 */
char **shift_toks(char **toks, int pos)
{
	int init = 0;

	while (toks && toks[pos + 1])
	{
		if (init)
			free(toks[pos]);
		toks[pos] = _strdup(toks[pos + 1]);
		init = 1;
		pos++;
	}
	free(toks[pos]);
	toks[pos] = NULL;

	return (toks);
}
