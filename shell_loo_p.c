#include "shell.h"

#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define BLUE    "\x1B[34m"
#define BOLD    "\x1B[1m"
#define RESET   "\x1B[0m"


/**
 * fork_cmd - function forks execution thread to un cmd
 * @inf: struct passed as a parametter
 */

void fork_cmd(info_t *inf)
{
	pid_t child_id;

	child_id = fork();
	if (child_id == -1)
	{
		perror("Error:");
		return;
	}
	if (child_id == 0)
	{
		if (execve(inf->path, inf->argv, get_environ(inf)) == -1)
		{
			free_info(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(inf->status));
		if (WIFEXITED(inf->status))
		{
			inf->status = WEXITSTATUS(inf->status);
			if (inf->status == 126)
				print_error(inf, "Permission denied\n");
		}
	}
}

/**
 * find_builtin - function find the built in command
 * @inf: struct passed as a parametter
 * Return: 0 if builtin found and excluded
 * 1 if found and not excluded
 * -1 if not found
 * -2 if signal exit
 */

int find_builtin(info_t *inf)
{
	int i, ret;

	i = 0;
	ret = -1;
	builtin_table builtin[] = {
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{NULL, NULL}
	};

	while (builtin[i].type)
	{
		if (_strcmp(inf->argv[0], builtin[i].type) == 0)
		{
			inf->line_count++;
			ret = builtin[i].func(inf);
			break;
		}
		i++;
	}
	return (ret);
}

/**
 * find_cmd - functions to find command in PATH
 * @inf: struct to be passed as a parametter
 */

void find_cmd(info_t *inf)
{
	int i, j;
	char *path = NULL;

	i = 0;
	j = 0;
	if (inf->linecount_flag == 1)
	{
		inf->line_count++;
		inf->linecount_flag = 0;
	}
	while (inf->arg[i])
	{
		if (!is_delim(inf->arg[i], "\t\n"))
			j++;
		i++;
	}
	if (!j)
		return;
	inf->path = inf->argv[0];
	path = find_path(inf, _getenv(inf, "PATH="), inf->argv[0]);
	if (path)
	{
		inf->path = path;
		fork_cmd(inf);
	}
	else
	{
		if ((interactive(inf) || _getenv(inf, "PATH=")
			|| inf->argv[0][0] == '/') && is_cmd(inf, inf->argv[0]))
			fork_cmd(inf);
		else if (*(inf->arg) != '\n')
		{
			inf->status = 127;
			print_error(inf, "not found\n");
		}
	}
}

/**
 * hsh - functions represtents the shell koop
 * @inf: struct passed as a parametter
 * @av: arguments passed from the main function
 * Return: 0 success, 1 error
 */


int hsh(info_t *inf, char **av)
{
	ssize_t i;
	int ret;
	char *prompt;

	i = 0;
	ret = 0;
	prompt = BLUE BOLD "[posh]-" RESET RED BOLD "$ " RESET;

	while (ret != -2 && i != -1)
	{
		clear_info(inf);
		if (interactive(inf))
			_puts(prompt);
		_putchar(BUF_FLUSH);
		i = get_input(inf);
		if (i != -1)
		{
			set_info(inf, av);
			ret = find_builtin(inf);
			if (ret == -1)
				find_cmd(inf);
		}
		else if (interactive(inf))
			_putchar('\n');
		free_info(inf, 0);
	}
	write_history(inf);
	free_info(inf, 1);
	if (!interactive(inf) && inf->status)
		exit(inf->status);
	if (ret == -2)
	{
		if (inf->err_num == -1)
			exit(inf->status);
		exit(inf->err_num);
	}
	return (ret);
}
