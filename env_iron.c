#include "shell.h"

/**
 * _myenv - That Outputs A Latest Conditions.
 * @info: That Struct Contain The Possible Argument.
 *
 * Return: That Will Return 0 always.
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - Retrieves the contents of an environment Variable.
 * @info: That Struct Contain The Possible Argume.
 * @name: That Is The Name Of A env var.
 *
 * Return:That Will Return A Value.
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node;
	char *b = NULL;

	for (node = info->env; node != NULL; node = node->next)
	{
		b = starts_with(node->str, name);
		if (b != NULL && *b != '\0')
		{
		return (b);
		}
	}

	return (NULL);
}

/**
 * _mysetenv - Add A New Variable to the Environment.
 * @info: That Struct Contain The Possible Argume.
 *
 *  Return: That Will Return 0 always.
 */

int _mysetenv(info_t *info)
{
	int argc = info->argc;
	char **argv = info->argv;
	int n = 0;
	int success = 1;

	if (argc != 3)
	{
		_eputs("Wrong argument Num\n");
		return (1);
	}

	while (n < argc)
	{
		if (_setenv(info, argv[1], argv[2]))
		{
		(success) = 0;

		break;
		}
		n++;
	}

	return (success);
}

/**
 * _myunsetenv - Delete A Variable From The Environment.
 * @info: That Struct Contain The Possible Argume.
 *
 *  Return: That Will Return 0 always.
 */
int _myunsetenv(info_t *info)
{
	int n;

	if (info->argc == 1)
	{
		_eputs("Deficient number of arguments .\n");
		return (1);
	}
	for (n = 1; n < info->argc; n++)
	{
	_unsetenv(info, info->argv[n]);

	}

	return (0);
}

/**
 * populate_env_list - Initializes the environment linked list.
 * @info: That Struct Contain The Possible Argume.
 *
 * Return: That Will Return 0 always.
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t n = 0;

	while (environ[n] != NULL)
	{
		add_node_end(&node, environ[n], 0);
		n++;
	}

	info->env = node;

	return (0);
}
