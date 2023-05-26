#include "shell.h"
/**
 * is_chain - function checks if current char is chain delimeter
 * @inf: struct to be passed as a parametter.
 * @buffer: buffer
 * @p: pointer to current position in buffer
 * Return: 1 when cahin delimeter or 0 if not
 */

int is_chain(info_t *inf, char *buffer, size_t *p)
{
	size_t i = *p;

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
/**
 * check_chain - function checks chaining according to last status
 * @inf: struct passed as a parametter.
 * @buffer: buffer passed as a parametter
 * @ptr: pointer to curret position in buffer
 * @i: starting position in buffer
 * @len: length of buffer
 */
void check_chain(info_t *inf, char *buffer, size_t *ptr, size_t i, size_t len)
{
	size_t n = *ptr;

	if (inf->cmd_buf_type == CMD_AND)
	{
		if (inf->status)
		{
			buffer[i] = 0;
			n = len;
		}
	}
	if (inf->cmd_buf_type == CMD_OR)
	{
		if (!inf->status)
		{
			buffer[i] = 0;
			n = len;
		}
	}

	*ptr = n;
}

/**
 * replace_alias - function replaces aliases in tokend string.
 * @inf: struct passed as a parametter.
 * Return: 1 if replaced or 0 if not
 */

int replace_alias(info_t *inf)
{
	int i;
	list_t *node;
	char *ptr;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(inf->alias, inf->argv[0], '=');
		if (!node)
			return (0);
		free(inf->argv[0]);
		ptr = _strchr(node->str, '=');
		if (!ptr)
			return (0);
		ptr = _strdup(ptr + 1);
		if (!ptr)
			return (0);
		inf->argv[0] = ptr;
	}
	return (1);
}
/**
 * replace_vars - replaces vars in tokened string
 * @inf: struct passed as a parametter
 * Return: 1 if replaced and  0 not
 */
int replace_vars(info_t *inf)
{
	int i = 0;
	list_t *node;

	for (i = 0; inf->argv[i]; i++)
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

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @oldstr: address of old string
 * @newstr: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **oldstr, char *newstr)
{
	free(*oldstr);
	*oldstr = newstr;
	return (1);
}
