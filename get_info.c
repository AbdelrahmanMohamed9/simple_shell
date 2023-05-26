#include "shell.h"

/**
 * clear_info - This Function Initializes an info_t Structure.
 *
 * @info: The address structure.
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - This Function Initializes an info_t Structure.
 * @info: The address structure.
 *
 * @av: The Vector Of arg.
 */
void set_info(info_t *info, char **av)
{
	int n = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
	if (!info->argv)
	{

		info->argv = malloc(sizeof(char *) * 2);
		if (info->argv)
		{
			info->argv[0] = _strdup(info->arg);
			info->argv[1] = NULL;
		}
	}
	for (n = 0; info->argv && info->argv[n]; n++)

	info->argc = n;

	replace_alias(info);
	replace_vars(info);
	}
}

/**
 * free_info - This Function Deallocates Aield Of info_t Structure.
 * @info: The address structure.
 *
 * @all: The Function Return True If All Fields Have Been Deallocated.
 */
void free_info(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
	if (!info->cmd_buf)
		free(info->arg);
	if (info->env)
		free_list(&(info->env));
	if (info->history)
		free_list(&(info->history));
	if (info->alias)
		free_list(&(info->alias));
	ffree(info->environ);
		info->environ = NULL;
	bfree((void **)info->cmd_buf);
	if (info->readfd > 2)
		close(info->readfd);
	_putchar(BUF_FLUSH);
	}
}
