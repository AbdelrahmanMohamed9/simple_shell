#include "shell.h"

/**
* strtow - function breaks string str to a series of tokens using a delimiter.
* @s: string to be spilited to words.
* @c: delimiter used to split the string.
* Return: evry word in the string
*/

char **strtow(char *s, char *c)
{
	int i, j, k, m;
	int count_words = 0;
	char **tmp;

	if (!s)
		return (NULL);
	if (!c)
		c = " ";
	for (i = 0; s[i]; i++)
		if (!is_delim(s[i], c) && (is_delim(s[i + 1], c) || !s[i + 1]))
			count_words++;
	if (count_words == 0)
		return (NULL);
	tmp = malloc((1 + count_words) * sizeof(char *));
	if (!tmp)
		return (NULL);
	i = 0;
	j = 0;
	while (j < count_words)
	{
		while (is_delim(s[i], c))
			i++;
		k = 0;
		while (!is_delim(s[i + k], c) && s[i + k])
			k++;
		tmp[j] = malloc((k + 1) * sizeof(char));
		if (!tmp[j])
		{
			for (k = 0; k < j; k++)
				free(tmp[k]);
			free(tmp);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			tmp[j][m] = s[i++];
		tmp[j][m] = 0;
		j++;
	}
	tmp[j] = NULL;
	return (tmp);
}


/**
* strtow2 - function breaks string str to a series of tokens using a delimiter.
* @s: string to be spilited to words.
* @c: delimiter used to split the string.
* Return: evry word in the string
*/

char **strtow2(char *s, char c)
{
	int i, j, k, m;
	int count_words = 0;
	char **tmp;

	if (!s)
		return (NULL);
	for (i = 0; s[i]; i++)
		if ((s[i] != c && s[i + 1] == c) ||
		    (s[i] != c && !s[i + 1]) || s[i + 1] == c)
			count_words++;
	if (count_words == 0)
		return (NULL);
	tmp = malloc((1 + count_words) * sizeof(char *));
	if (!tmp)
		return (NULL);
	i = 0;
	j = 0;
	while (j < count_words)
	{
		while (s[i] == c && s[i] != c)
			i++;
		k = 0;
		while (s[i + k] != c && s[i + k] && s[i + k] != c)
			k++;
		tmp[j] = malloc((k + 1) * sizeof(char));
		if (!tmp[j])
		{
			for (k = 0; k < j; k++)
				free(tmp[k]);
			free(tmp);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			tmp[j][m] = s[i++];
		tmp[j][m] = 0;
		j++;
	}
	tmp[j] = NULL;
	return (tmp);
}
