#include "shell.h"

/**
 * input_buf - stores a sequence of commands in a buf.
 * @info: structure containing parameters.
 * @buf: memory location of the buf.
 * @len: memory location of the length variable.
 *
 * Return:amount of data that has been read.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t v = 0;
	size_t lP = 0;

	while (!*len)
	{

		free(*buf);
		*buf = NULL;

		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		v = getline(buf, &lP, stdin);
#else
		v = _getline(info, buf, &lP);
#endif
	if (v > 0)
	{
		if ((*buf)[v - 1] == '\n')
		{
			(*buf)[v - 1] = '\0';
			v--;
		}
		info->linecount_flag = 1;
		remove_comments(*buf);
		build_history_list(info, *buf, info->histcount++);

		while (_strchr(*buf, ';'))
		{
			*len = v;
			info->cmd_buf = buf;
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
	static size_t n, k, ln;
	ssize_t v = 0;
	char **bp = &(info->arg), *b;

	n = 0;
	k = 0;
	ln = 0;
	_putchar(BUF_FLUSH);
	while (1)
	{	v = input_buf(info, &buffer, &ln);

		if (v == -1)
		return (-1);
		if (ln)
		{
			k = n;
			b = buffer + n;
			check_chain(info, buffer, &k, n, ln);
			while (k < ln)
			{
				if (is_chain(info, buffer, &k))
					break;
				k++;
			}
			n = k + 1;
			if (n >= ln)
			{
				n = ln = 0;
				info->cmd_buf_type = CMD_NORM;
			}
			*bp = b;
			return (_strlen(b));
		}
		else
		{
			*bp = buffer;
			return (v);
		}
	}
}

/**
 * read_buf - copies data from a buf.
 * @info: structure containing parameters.
 * @buf:That Is The buf.
 * @i:That Is The Size.
 *
 * Return: V.
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t v = 0;

	while (!(*i))
	{
		v = read(info->readfd, buf, READ_BUF_SIZE);
		if (v >= 0)
		*i = v;
		else
			break;
	}

	return (v);
}

/**
 * _getline - That reads A Next Line of Input From Standard Input Stream.
 * @info: structure containing parameters.
 * @ptr: Memory Location Of PTR Pointing To buf.
 * @length: That Is The size of buf PTR.
 *
 * Return: c.
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buffer[READ_BUF_SIZE];
	static size_t n, ln;
	size_t t = 0;
	ssize_t v = 0, c = 0;
	char *b = NULL, *np = NULL, *x;

	n = 0;
	ln = 0;

	b = *ptr;

	if (b && length)
		c = *length;

	while (n == ln)
	{
		v = read_buf(info, buffer, &ln);

		if (v == -1 || (v == 0 && ln == 0))
			return (-1);
		n = 0;
	}

	x = _strchr(buffer + n, '\n');
	t = x ? 1 + (unsigned int)(x - buffer) : ln;
	np = _realloc(b, c, c ? c + t : t + 1);

	if (!np)
		return (b ? free(b), -1 : -1);
	if (c)
		_strncat(np, buffer + n, t - n);
	else
		_strncpy(np, buffer + n, t - n + 1);
	c += t - n;
	n = t;
	b = np;
	if (length)
		*length = c;
	*ptr = b;
	return (c);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
