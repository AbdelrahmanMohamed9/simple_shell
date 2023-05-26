#include "shell.h"

/**
 * is_cmd - function checks if a file is an executable command
 * @inf: info struct
 * @path: path to file
 * Return: 1 if true or 0 if not
 */

int is_cmd(info_t *inf, char *path)
{
	struct stat s_t;

	(void)inf;
	if (!path || stat(path, &s_t))
		return (0);

	if (s_t.st_mode & S_IFREG)
	{
		return (1);
	}
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
	int i = 0, k = 0;

	for (k = 0, i = start; i < end; i++)
		if (path[i] != ':')
			buffer[k++] = path[i];
	buffer[k] = 0;
	return (buffer);
}

/**
 * find_path - function finds cmd in PATH string
 * @inf: info struct
 * @path_str: PATH string
 * @cmd: cmd to find
 * Return: path of cmd if found or NULL
 */

char *find_path(info_t *inf, char *path_str, char *cmd)
{
	int i = 0, current_pos = 0;
	char *path;

	if (!path_str)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(inf, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!path_str[i] || path_str[i] == ':')
		{
			path = dup_chars(path_str, current_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(inf, path))
				return (path);
			if (!path_str[i])
				break;
			current_pos = i;
		}
		i++;
	}
	return (NULL);
}
