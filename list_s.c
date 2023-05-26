#include "shell.h"

/**
 * add_node - function that adds a new node at the beginning of a list_t list.
 * @h: head of the new list
 * @str: new string to add the node
 * @num: index to node
 * Return: the address of the new element, or NULL if it failed
 */
list_t *add_node(list_t **h, const char *str, int num)
{
	list_t *new;

	if (!h)
		return (NULL);
	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);
	_memset((void *)new, 0, sizeof(list_t));
	new->num = num;
	if (str)
	{
		new->str = _strdup(str);
		if (!new->str)
		{
			free(new);
			return (NULL);
		}
	}
	new->next = *h;
	*h = new;
	return (new);
}

/**
 * add_node_end -  function that adds a new node
 * at the end of a listint_t list.
 * @h: head of list
 * @str: str of node.
 * @num: integer.
 * Return: address of the new element, or NULL if it failed.
 */

list_t *add_node_end(list_t **h, const char *str, int num)
{
	list_t *new, *node;

	if (!h)
		return (NULL);

	node = *h;
	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);
	_memset((void *)new, 0, sizeof(list_t));
	new->num = num;
	if (str)
	{
		new->str = _strdup(str);
		if (!new->str)
		{
			free(new);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new;
	}
	else
		*h = new;
	return (new);
}

/**
 * print_list_str -  function that prints  elements of a list_t list
 * @h: linked list.
 * Return: number of nodes.
 */

size_t print_list_str(const list_t *h)
{
	size_t n = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		n++;
	}
	return (n);
}

/**
 * delete_node_at_index - function that deletes
 * the node at index index of a listint_t linked list
 * @head: double pointer head.
 * @n: unsigned int.
 * Return: 1 if it succeeded, -1 if it failed
 */

int delete_node_at_index(list_t **head, unsigned int n)
{
	list_t *node, *prv_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!n)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == n)
		{
			prv_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prv_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - function that frees all node in the list.
 * @head_p: pointer to head of the list
 */

void free_list(list_t **head_p)
{
	list_t *node, *nxt_node, *head;

	if (!head_p || !*head_p)
		return;
	head = *head_p;
	node = head;
	while (node)
	{
		nxt_node = node->next;
		free(node->str);
		free(node);
		node = nxt_node;
	}
	*head_p = NULL;
}
