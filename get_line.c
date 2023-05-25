#include "shell.h"


/**
 * input_buffer - stores a sequence of commands in a buf.
 * @info: structure containing parameters.
 * @buffer: memory location of the buf.
 * @length: memory location of the length variable.
 *
 * Return:amount of data that has been read.
 */

ssize_t input_buffer(info_t *info, char **buffer, size_t *length)
{
	ssize_t v = 0;
	size_t ln = 0;

	if (!*length)
	{

		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		v = getline(buffer, &ln, stdin);
#else
		v = _getline(info, buffer, &ln);
#endif
		if (v > 0)
		{
			if ((*buffer)[v - 1] == '\n')
			{
				(*buffer)[v - 1] = '\0';
				v--;
			}
			info->linecount_flag = 1;
			remove_comments(*buffer);
			build_history_list(info, *buffer, info->histcount++);

			{
				*length = v;
				info->cmd_buf = buffer;
			}
		}
	}
	return (v);
}

/**
 * get_input - reads The line of text excluding a Newline char.
 * @info: structure containing parameters.
 *
 * Return: the number of Bytes that have been Read.
 */

ssize_t get_input(info_t *info)
{
	static char *buffer;
	static size_t n, k, len;
	ssize_t v = 0;
	char **bf_p = &(info->arg), *b;

	_putchar(BUF_FLUSH);
	v = input_buffer(info, &buffer, &len);
	if (v == -1)
		return (-1);
	if (len)
	{
		k = n;
		b = buffer + n;

		check_chain(info, buffer, &k, n, len);
		while (k < len)
		{
			if (is_chain(info, buffer, &k))
				break;
			k++;
		}

		n = k + 1;
		if (n >= len)
		{
			n = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*bf_p = b;
		return (_strlen(b));
	}

	*bf_p = buffer;
	return (v);
}

/**
 * read_buffer - copies data from a buf.
 * @info: structure containing parameters.
 * @buffer:That Is The buf.
 * @i:That Is The Size.
 *
 * Return: V.
 */

ssize_t read_buffer(info_t *info, char *buffer, size_t *i)
{
	ssize_t v = 0;

	if (*i)
		return (0);
	v = read(info->readfd, buffer, READ_BUF_SIZE);
	if (v >= 0)
		*i = v;
	return (v);
}


/**
 * _getline - That reads A Next Line of Input From Standard Input Stream.
 * @info: structure containing parameters.
 * @p: Memory Location Of PTR Pointing To buf.
 * @len: That Is The size of buf PTR.
 *
 * Return: c.
 */

int _getline(info_t *info, char **p, size_t *len)
{
	static char buf[READ_BUF_SIZE];
	static size_t n, ln;
	size_t t;
	ssize_t v = 0, c = 0;
	char *b = NULL, *n_p = NULL, *x;

	b = *p;
	if (b && len)
		c = *len;
	if (n == ln)
		n = ln = 0;

	v = read_buffer(info, buf, &ln);
	if (v == -1 || (v == 0 && ln == 0))
		return (-1);

	x = _strchr(buf + n, '\n');
	t = x ? 1 + (unsigned int)(x - buf) : ln;
	n_p = _realloc(b, c, c ? c + t : t + 1);
	if (!n_p)
		return (b ? free(b), -1 : -1);
	if (c)
		_strncat(n_p, buf + n, t - n);
	else
		_strncpy(n_p, buf + n, t - n + 1);

	c += t - n;
	n = t;
	b = n_p;

	if (len)
		*len = c;
	*p = b;
	return (c);
}


/**
 * sigintHandler - sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
