#include "shell.h"

/**
 * input_buf - function stores a sequence of commands in a buf.
 * @info: structure containing parameters.
 * @buf: the memory location of the buf.
 * @len: the memory location of the length variable.
 * Return:the amount of data that has been read.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t f = 0;
	size_t ln_b = 0;

	if (!*len)
	{

		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		f = getline(buf, &ln_b, stdin);
#else
		f = _getline(info, buf, &ln_b);
#endif
		if (f > 0)
		{
			if ((*buf)[f - 1] == '\n')
			{
				(*buf)[f - 1] = '\0';
				f--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);

			{
				*len = f;
				info->cmd_buf = buf;
			}
		}
	}
	return (f);
}

/**
 * get_input - function reads line of text excluding a Newline char.
 * @info: structure parameters.
 * Return: number of Bytes that have been Read.
 */
ssize_t get_input(info_t *info)
{
	static char *buffer;
	static size_t n, k, ln;
	ssize_t f = 0;
	char **buffer_b = &(info->arg), *b;

	_putchar(BUF_FLUSH);
	f = input_buf(info, &buffer, &ln);
	if (f == -1)
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

		*buffer_b = b;
		return (_strlen(b));
	}

	*buffer_b = buffer;
	return (f);
}

/**
 * read_buf - function copies data from a buf.
 * @info: structure containing parameters.
 * @buf: Is The buf.
 * @i:  That Is The Size.
 * Return: n.
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t f = 0;

	if (*i)
		return (0);
	f = read(info->readfd, buf, READ_BUF_SIZE);
	if (f >= 0)
		*i = f;
	return (f);
}

/**
 * _getline - function reads Next Line of Input From Standard Input Stream.
 * @info: structure  parameters.
 * @ptr: Memory Location Of PTR Pointing To buf.
 * @length: That Is The size of buf PTR.
 * Return: s.
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buffer[READ_BUF_SIZE];
	static size_t n, ln;
	size_t w;
	ssize_t f = 0, c = 0;
	char *b = NULL, *n_b = NULL, *s;

	b = *ptr;
	if (b && length)
		c = *length;
	if (n == ln)
		n = ln = 0;

	f = read_buf(info, buffer, &ln);
	if (f == -1 || (f == 0 && ln == 0))
		return (-1);

	s = _strchr(buffer + n, '\n');
	w = s ? 1 + (unsigned int)(s - buffer) : ln;
	n_b = _realloc(b, c, c ? c + w : w + 1);
	if (!n_b)
		return (b ? free(b), -1 : -1);

	if (c)
		_strncat(n_b, buffer + n, w - n);
	else
		_strncpy(n_b, buffer + n, w - n + 1);

	c += w - n;
	n = w;
	b = n_b;

	if (length)
		*length = c;
	*ptr = b;
	return (c);
}

/**
 * sigintHandler - function blocks ctrl-C
 * @sig_num: signal number
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
