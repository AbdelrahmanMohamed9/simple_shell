#include "shell.h"

/**
 * list_to_strings - function returns array of strings
 * of list str
 * @h: pointer to the first node.
 * Return: array of strings.
 */
char **list_to_strings(list_t *h)
{
	list_t *new = h;
	size_t len = list_len(h);
	size_t i;
	char **str;
	char *s;

	i = 0;
	if (!h || !len)
		return (NULL);
	str = malloc(sizeof(char *) * (len + 1));
	if (!str)
		return (NULL);
	while (new)
	{
		new = new->next;
		s = malloc(_strlen(new->str) + 1);
		if (!s)
		{
			while (i < len)
				free(str[i++]);
			free(str);
			return (NULL);
		}
		s = _strcpy(s, new->str);
		str[i] = s;
		i++;
	}
	str[i] == NULL;
	return (str);
}

/**
 *  print_list - function prints the elements of a listint_t list.
 *  @head: linked list
 *  Return: number of nodes
 */

size_t print_list(const list_t *head)
{
	size_t i;

	for (i = 0; head; i++)
	{
		_puts(convert_number(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
	}
	return (i);
}

/**
 * get_node_index - function that gets the index of the node.
 * @head: pointer to list head.
 * @node: pointer to node.
 * Return: index of the node or -1 if fails.
 */

ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	for (i = 0; head; i++)
	{
		if (head == node)
			return (i);
		head = head->next;
	}
	return (-1);
}

/**
 * node_starts_with - function returns node which string starts with str.
 * @head: pointer to list head.
 * @s: string to match with.
 * @c: the next character afer str to match
 * Return: the matched node or NULL
 */

list_t *node_starts_with(list_t *head, char *s, char c)
{
	char *p = NULL;

	while (head)
	{
		p = starts_with(head->str, s);
		if (p && ((c == -1) || (*p == c)))
			return (head);
		head = head->next;
	}
	return (NULL);
}

/**
 * list_len -  function that returns the number of
 * elements in a linked listint_t list.
 * @h: linked list
 * Return: number of elements.
 */

size_t list_len(const list_t *h)
{
	int len;

	len = 0;
	while (h)
	{
		h = h->next;
		len++;
	}
	return (len);
}
