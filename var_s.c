#include "shell.h"

/**
 * replace_alias - function replaces aliases in tokend string.
 * @inf: struct passed as a parametter.
 * Return: 1 if replaced or 0 if not
 */

int replace_alias(info_t *inf)
{
	int i = 0;
	list_t *node;
	char *p;

	while (i < 10)
	{
		node = node_starts_with(inf->alias, inf->argv[0], '=');
		if (!node)
			return (0);
		free(inf->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		inf->argv[0] = p;
		i++;
	}
	return (1);
}


/**
 * replace_vars - function replaces vars in tokened string
 * @inf: struct passed as a parametter
 * Return: 1 if replaced or 0 if not
 */

int replace_vars(info_t *inf)
{
	int i = 0;
	list_t *node;

	while (inf->argv[i])
	{
		if (inf->argv[i][0] != '$' || !inf->argv[i][1])
			continue;

		if (!_strcmp(inf->argv[i], "$?"))
		{
			replace_string(&(inf->argv[i]),
				_strdup(convert_number(inf->status, 10, 0)));
			continue;
		}
		if (!_strcmp(inf->argv[i], "$$"))
		{
			replace_string(&(inf->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(inf->env, &inf->argv[i][1], '=');
		if (node)
		{
			replace_string(&(inf->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&inf->argv[i], _strdup(""));
		i++;

	}
	return (0);
}


/**
 * check_chain - function checks chaining according to last status
 * @inf: struct passed as a parametter.
 * @buffer: buffer passed as a parametter
 * @p: pointer to curret position in buffer
 * @i: starting position in buffer
 * @len: length of buffer
 */

void check_chain(info_t *inf, char *buffer, size_t *p, size_t i, size_t len)
{
	size_t x = *p;

	if (inf->cmd_buf_type == CMD_OR)
	{
		if (inf->status)
		{
			buffer[i] = 0;
			x = len;
		}
	}
	if (inf->cmd_buf_type == CMD_OR)
	{
		if (!inf->status)
		{
			buffer[i] = 0;
			x = len;
		}
	}
	*p = x;
}

/**
 *  replace_string - function replaces string.
 *  @str: pointer to old string.
 *  @new: new string.
 *  Return: 1 if replaced or 0 if not
 */

int replace_string(char **str, char *new)
{
	free(*str);
	*str = new;
	return (1);
}

/**
 * is_chain - function checks if current char is chain delimeter
 * @inf: struct to be passed as a parametter.
 * @buffer: buffer
 * @p: pointer to current position in buffer
 * Return: 1 when cahin delimeter or 0 if not
 */

int is_chain(info_t *inf, char *buffer, size_t *p)
{
	size_t  i = *p;

	if (buffer[i] == '|' && buffer[i + 1] == '|')
	{
		buffer[i] = 0;
		i++;
		inf->cmd_buf_type = CMD_OR;
	}
	else if (buffer[i] == '&' && buffer[i + 1] == '&')
	{
		buffer[i] = 0;
		i++;
		inf->cmd_buf_type = CMD_AND;
	}
	else if (buffer[i] == ';')
	{
		buffer[i] = 0;
		inf->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = i;
	return (1);
}
