#include "shell.h"

/**
 * free_list - function that frees all node in the list.
 * @head: pointer to head of the list
 */

void free_list(list_t **head)
{
	list_t *temp;

	if (!head)
		return;
	while (*head)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp);
	}
	*head = NULL;
}

/**
 * print_list_str -  function that prints  elements of a list_t list
 * @h: linked list.
 * Return: number of nodes.
 */

size_t print_list_str(const list_t *h)
{
	size_t i;

	i = 0;
	if (h == NULL)
		return (0);
	while (h)
	{
		if (!h->str)
			_puts("(nil)");
		else
			_puts(h->str);
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * add_node - function that adds a new node at the beginning of a list_t list.
 * @head: head of the new list
 * @str: new string to add the node
 * @n: index to node
 * Return: the address of the new element, or NULL if it failed
 */

list_t *add_node(list_t **head, const char *str, int n)
{
	list_t *new;

	if (!head)
		return (NULL);
	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);
	_memset((void *)new, 0, sizeof(list_t));
	if (str)
	{
		new->str = _strdup(str);
	}
	else
		return (NULL);
	new->num = n;
	new->next = *head;
	*head = new;
	return (new);
}

/**
 * add_node_end -  function that adds a new node
 * at the end of a listint_t list.
 * @head: head of list
 * @str: str of node.
 * @n: integer.
 * Return: address of the new element, or NULL if it failed.
 */

list_t *add_node_end(list_t **head, const char *str, int n)
{
	list_t *s1;
	list_t *s2 = *head;
	unsigned int i;

	i = 0;
	while (str[i])
		i++;

	s1 = malloc(sizeof(list_t));
	if (!s1)
		return (NULL);

	s1->str = _strdup(str);
	s1->num = n;
	s1->next = NULL;

	if (*head == NULL)
	{
		*head = s1;
		return (s1);
	}

	while (s2->next)
		s2 = s2->next;

	s2->next = s1;

	return (s2);
}
/**
 * delete_node_at_index - function that deletes
 * the node at index index of a listint_t linked list
 * @head: double pointer head.
 * @index: unsigned int.
 * Return: 1 if it succeeded, -1 if it failed
 */

int delete_node_at_index(list_t **head, unsigned int index)
{
	unsigned int i;
	list_t *tmp1;
	list_t *tmp2;

	i = 0;
	tmp1 = *head;
	tmp2 = NULL;
	if (!*head)
		return (-1);
	if (index == 0)
	{
		*head = (*head)->next;
		free(tmp1);
		return (1);
	}
	while (i < index - 1)
	{
		if (tmp1->next == NULL)
			return (-1);
		tmp1 = tmp1->next;
		i++;
	}
	tmp2 = tmp1->next;
	tmp1->next = tmp2->next;
	free(tmp2);
	return (1);
}
