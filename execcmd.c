#include "main.h"

/**
 * execcmd - execute cmd,
 * @cmd: The cmd to be executed
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
 * @pname: program name, to print alongside error msg
 * Return: int indicating exec status
 */
int shell_int(char *pname)
{
	char **lines;
	pid_t child_pid;
	struct stat buf;

	while (1)
	{
		_printf("($) ");
		lines = get_inputs();

		runcmds(lines, pname, buf, &child_pid);

		free_toks(lines);
	}
	return (0);
}

/**
 * shelln_int - non interactive version of the shell
 * @pname: name of the program, print alongside error msg
 * Return: int, exec status
 */
int shelln_int(char *pname)
{
	int execres;
	pid_t child_pid;
	char **lines;
	struct stat buf;

	lines = get_inputs();

	execres = runcmds(lines, pname, buf, &child_pid);
	free_toks(lines);
	return (execres);
}

/**
 * statxcmd - read and execute program
 * @toks: tokenized cmd
 * @pname: name of the program
 * @buf: buffer, holds the result of stat
 * @child_pid: holds the pid of process
 * Return: int, exec status
 */
int statxcmd(char **toks, char *pname, struct stat buf, pid_t *child_pid)
{
	int status = 0;

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
			status = execcmd(toks, pname);
		}
		else
		{
			wait(NULL);
		}
	}

	return (status);
}

/**
 * runcmds - takes parsed cmd lines and run it
 * @lines: set of commands to be exec
 * @pname: name of the program
 * @buf: struct buf
 * @child_pid: pid of child process
 * Return: exec status
 */
int runcmds(char **lines, char *pname, struct stat buf, pid_t *child_pid)
{
	int size, i, (*btin)(char **, char *), status = 0;
	char *path, **toks;

	for (i = 0; lines && lines[i]; i++)
	{
		size = _strlen(lines[i]);
		toks = _strtok(lines[i], size, " \t");
		if (!toks || !toks[0])
		{
			_perror("Usage: [command] [arg]");
		}
		else
		{
			btin = is_btin(toks[0]);
			if (btin)
			{
				if (_strcmp(toks[0], "exit") == 0)
				{
					status = btin(toks, pname);
					if (status >= 0)
					{
						free_toks(lines);
						exit(status);
					}
					return (status);
				}
				status = btin(toks, pname);
			}
			else
			{
				path = findxpath(toks[0]);
				free(toks[0]);
				toks[0] = path;
				status = statxcmd(toks, pname, buf, child_pid);
			}
		}
		free_toks(toks);
	}
	return (status);
}
