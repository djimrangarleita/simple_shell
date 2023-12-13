#include "main.h"

/**
 * execcmd - execute cmd,
 * @cmd: the cmd to be executed
 * @errormsg: error msg to print in case execve fails
 * Return: exec code indicating error
 */
int execcmd(char **cmd, char *errormsg)
{
	int execode;

	execode = execve(cmd[0], cmd, environ);
	_perror(errormsg);

	return (execode);
}

/**
 * shell_int - interactive shell
 * @line: ptr to list of args
 * @len: ptr to size_t var, length of line
 * @pname: program name, to print alongside error msg
 * Return: int indicating exec status
 */
int shell_int(char **line, size_t *len, char *pname)
{
	char *path, **toks;
	int (*btin)(char **, char *);
	pid_t child_pid;
	struct stat buf;

	while (1)
	{
		_printf("($) ");
		readcmd(line, len);
		if (*line[0] != '\n')
		{
			toks = _strtok(*line, " \t\n");
			btin = is_btin(toks[0]);

			if (btin)
			{
				btin(toks, pname);
			}
			else
			{
				path = findxpath(toks[0]);
				free(toks[0]);
				toks[0] = path;

				readx(toks, pname, buf, &child_pid);
			}
			free_toks(toks);
		}
	}
	free(*line);

	return (0);
}

/**
 * shelln_int - non interactive version of the shell
 * @line: ptd to stdin inputs
 * @len: size_t var, length of stdin
 * @pname: name of the program, print alongside error msg
 * Return: int, exec status
 */
int shelln_int(char **line, size_t *len, char *pname)
{
	char *path, **toks;
	int execres, (*btin)(char **, char *);
	pid_t child_pid;
	struct stat buf;

	readcmd(line, len);
	toks = _strtok(*line, " \t\n");

	btin = is_btin(toks[0]);
	if (!toks[0])
	{
		_printf("Usage: %s: [command] [argument]\n", pname);
		return (-1);
	}
	if (btin)
	{
		execres = btin(toks, pname);
	}
	else
	{
		path = findxpath(toks[0]);
		free(toks[0]);
		toks[0] = path;

		execres = readx(toks, pname, buf, &child_pid);
	}

	free_toks(toks);
	free(*line);

	return (execres);
}

/**
 * readx - read and execute program
 * @toks: tokenized cmd
 * @pname: name of the program
 * @buf: buffer, will hold result of stat
 * @child_pid: will hold the pid of process
 * Return: int, exec status
 */
int readx(char **toks, char *pname, struct stat buf, pid_t *child_pid)
{
	if (stat(toks[0], &buf) != 0)
	{
		_perror(pname);
		return (-1);
	}
	else
	{
		*child_pid = fork();
		if (*child_pid == -1)
		{
			_perror("Error:");
			return (-1);
		}
		else if (*child_pid == 0)
		{
			execcmd(toks, pname);
		}
		else
		{
			wait(NULL);
		}
	}

	return (0);
}
