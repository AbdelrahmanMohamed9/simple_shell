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
	char *buffer, *dr;

	dr = _getenv(info, "HOME=");
	if (!dr)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(dr) + _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, dr);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * write_history - This Function Either Creat A New File.
 * @info: The Structure Containing The Barameter.
 * Return: return 1 if success, if not return -1 .
 */
int write_history(info_t *info)
{
	ssize_t vb;
	char *fnm = get_history_file(info);
	list_t *nd = NULL;

	if (!fnm)
		return (-1);

	vb = open(fnm, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fnm);
	if (vb == -1)
		return (-1);
	for (nd = info->history; nd; nd = nd->next)
	{
		_putsfd(nd->str, vb);
		_putfd('\n', vb);
	}
	_putfd(BUF_FLUSH, vb);
	close(vb);
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
	int n, lt = 0, lncnt = 0;
	ssize_t vb, rln, fz = 0;
	struct stat sst;
	char *buffer = NULL, *fnm = get_history_file(info);

	if (!fnm)
		return (0);

	vb = open(fnm, O_RDONLY);
	free(fnm);
	if (vb == -1)
		return (0);
	if (!fstat(vb, &sst))
		fz = sst.st_size;
	if (fz < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fz + 1));
	if (!buffer)
		return (0);
	rln = read(vb, buffer, fz);
	buffer[fz] = 0;
	if (rln <= 0)
		return (free(buffer), 0);
	close(vb);
	for (n = 0; n < fz; n++)
		if (buffer[n] == '\n')
		{
			buffer[n] = 0;
			build_history_list(info, buffer + lt, lncnt++);
			lt = n + 1;
		}
	if (lt != n)
		build_history_list(info, buffer + lt, lncnt++);
	free(buffer);
	info->histcount = lncnt;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
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

	if (info->history)
		nd = info->history;
	add_node_end(&nd, buf, linecount);

	if (!info->history)
		info->history = nd;
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

	while (nd)
	{
		nd->num = n++;
		nd = nd->next;
	}
	return (info->histcount = n);
}
