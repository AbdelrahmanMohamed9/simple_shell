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
	list_t *nd = info->env;
	char *b;

	while (nd)
	{
		b = starts_with(nd->str, name);
		if (b && *b)
			return (b);
		nd = nd->next;
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
	if (info->argc != 3)
	{
		_eputs("An Incorrect num Of Arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
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
		_eputs("An Too Few Arguements.\n");
		return (1);
	}
	for (n = 1; n <= info->argc; n++)
		_unsetenv(info, info->argv[n]);

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
	list_t *nd = NULL;
	size_t n;

	for (n = 0; environ[n]; n++)
		add_node_end(&nd, environ[n], 0);
	info->env = nd;
	return (0);
}
