#include "shell.h"

/**
 * get_environ - Produces Copy Of Our Environment As str Array.
 * @info: This Structure Holds Potential arg.
 *
 * Return: This Will Return 0 always.
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - That Delete The Variable Of The Environment.
 * @info: This Structure Holds Potential arg.
 * @var: Property Of The Environment Variable's Str.
 *
 * Return: If The Deletion Is Successful Return 1; If Not Return 0.
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *nd = info->env;
	size_t n = 0;
	char *b;

	if (!nd || !var)
		return (0);

	while (nd)
	{
		b = starts_with(nd->str, var);
		if (b && *b == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), n);
			n = 0;
			nd = info->env;
			continue;
		}
		nd = nd->next;
		n++;
	}
	return (info->env_changed);
}

/**
 * _setenv - This Function Can Be Used For Set New Environment Variable.
 * @info: This Structure Holds Potential arg.
 * @var: Property Of The Env Variable's Str.
 * @value: The value of the environment variable as a str.
 *
 *  Return: This Will Return 0 always.
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buffer = NULL;
	list_t *nd;
	char *b;

	if (!var || !value)
		return (0);

	buffer = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, var);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	nd = info->env;
	while (nd)
	{
		b = starts_with(nd->str, var);
		if (b && *b == '=')
		{
			free(nd->str);
			nd->str = buffer;
			info->env_changed = 1;
			return (0);
		}
		nd = nd->next;
	}
	add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}
