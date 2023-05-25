#include "shell.h"

/**
 * is_cmd - function checks if a file is an executable command
 * @inf: info struct
 * @path: path to file
 * Return: 1 if true or 0 if not
 */

int is_cmd(info_t *inf, char *path)
{
	struct stat s;

	(void)inf;
	if (stat(path, &s) || !path)
		return (0);
	if (s.st_mode & S_IFREG)
		return (1);
	return (0);
}

/**
 * dup_chars - function duplicates characters
 * @path: PATH string
 * @start: the start index
 * @end: the end  index
 * Return: pointer to new buffer
 */
char *dup_chars(char *path, int start, int end)
{
	static char buffer[1024];
	int i, j;

	i = start;
	j = 0;
	while (i < end)
	{
		if (path[i] != ':')
			buffer[j++] = path[i];
		i++;
	}
	buffer[j] = 0;
	return (buffer);
}

/**
 * find_path - function finds cmd in PATH string
 * @inf: info struct
 * @str_path: PATH string
 * @cmd: cmd to find
 * Return: path of cmd if found or NULL
 */

char *find_path(info_t *inf, char *str_path, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!str_path)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(inf, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!str_path[i] || str_path[i] == ':')
		{
			path = dup_chars(str_path, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(inf, path))
				return (path);
			if (!str_path[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
