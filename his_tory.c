#include "shell.h"

/**
 * get_history_file - retrieves a path to a history file.
 *
 * @info: pointer to a info_t structure containing a shell info.
 *
 * Return: On success returns the pointer to str containing
 *	a history file path.On failure returns NULL.
 */

char *get_history_file(info_t *info)
{
	char *buffer, *cdo;
	int n;

	cdo = _getenv(info, "HOME=");

	if (!cdo)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(cdo) + _strlen(HIST_FILE) + 2));

	if (!buffer)
		return (NULL);

	buffer[0] = 0;
	_strcpy(buffer, cdo);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);


	for (n = 0; buffer[n]; n++)
	{
		if (buffer[n] == '\n')
		{
			buffer[n] = '\0';

			break;
		}
	}

	return (buffer);
}

/**
 * write_history - This Function Either Creat A New File.
 * @info: The Structure Containing The Barameter.
 * Return: return 1 if success, if not return -1 .
 */
int write_history(info_t *info)
{
	char *fn = get_history_file(info);
	ssize_t cc;
	list_t *nd = NULL;

	if (!fn)
		return (-1);
	cc = open(fn, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fn);
	if (cc == -1)

		return (-1);
	nd = info->history;
	while (nd)
	{
		_putsfd(nd->str, cc);
		_putfd('\n', cc);
		nd = nd->next;
	}
	_putfd(BUF_FLUSH, cc);
	close(cc);
	return (1);
}
/**
 * read_history - This Function Will Read The History From The File.
 * @info: The Structure Containing The Barameter.
 * Return: The function returns the value of Histcount If success,
 *	If Not return 0 .
 */
int read_history(info_t *info)
{
	int n = 0, end = 0, lc = 0;
	ssize_t cc, rn;
	struct stat sst;
	char *buffer = NULL, *fn = get_history_file(info);

	if (!fn)
		return (0);
	cc = open(fn, O_RDONLY);
	free(fn);
	if (cc == -1 || fstat(cc, &sst) == -1)
		return (close(cc), 0);
	buffer = malloc(sst.st_size + 1);
	if (!buffer)
		return (close(cc), 0);
	rn = read(cc, buffer, sst.st_size);
	if (rn <= 0)
		return (close(cc), free(buffer), 0);
	buffer[sst.st_size] = '\0';
	close(cc);
	n = 0;
	while (buffer[n])
	{
		if (buffer[n] == '\n')
		{
			buffer[n] = 0;
			build_history_list(info, buffer + end, lc++);
			end = n + 1;
		}
		n++;
	}
	if (end != n)
		build_history_list(info, buffer + end, lc++);
	free(buffer);
	info->histcount = lc;
	for (; info->histcount >= HIST_MAX; info->histcount--)
	{
		delete_node_at_index(&(info->history), 0);
	}
	renumber_history(info);
	return (info->histcount);
}
/**
 * build_history_list - This Function That Add An Entry To
 *	A Linked List For The History.
 * @info: This Structure Is Used To Hold Potential Arg.
 * @buf: This Is The Buffer.
 * @linecount: The Variable Histcount Contains
 *	The Number Of Lines In The History.
 * Return: That Will Return 0 always.
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *nd = NULL;

	while (info->history)
	{
		nd = info->history;
		info->history = nd->next;
	}
	add_node_end(&nd, buf, linecount);

	while (!info->history)
	{
		info->history = nd;
	}
	return (0);
}
/**
 * renumber_history - renumbers the history linked list after changes
 * @info: This Structure Is Used To Hold Potential Arg.
 * Return: That Will Return The Updated Value Of Histcount.
 */
int renumber_history(info_t *info)
{
	list_t *nd = info->history;
	int n = 0;

	for (; nd; nd = nd->next)
	{
		nd->num = n++;
	}
	info->histcount = n;

	return (n);
}
