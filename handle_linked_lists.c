#include "shell.h"

/**
 * append_alias - Append a node to the end of a link list.
 * @first_node: Pointer to the first node.
 * @alias_name: Name of the new alias.
 * @alias_value: Value of the new alias.
 *
 * Return: Pointer to the new node or NULL.
 */
alias_t *append_alias(alias_t **first_node, char *alias_name, char *alias_value)
{
	alias_t *tail;
	alias_t *n_node = malloc(sizeof(alias_t));

	if (!n_node)
		return (NULL);

	n_node->next = NULL;
	n_node->name = malloc(sizeof(char) * (_str_length(alias_name) + 1));
	if (!n_node->name)
	{
		free(n_node);
		return (NULL);
	}
	n_node->value = alias_value;
	_str_cpy(n_node->name, alias_name);
	if (*first_node)
	{
		tail = *first_node;
		while (tail->next != NULL)
			tail = tail->next;
		tail->next = n_node;
	}
	else
		*first_node = n_node;
	return (n_node);
}

/**
 * append_node - Append a node to the end.
 * @first_node: Pointer to the first node.
 * @dir: Path directory.
 * Return: Pointer to the new node or NULL.
 */
list_t *append_node(list_t **first_node, char *dir)
{
	list_t *tail;
	list_t *n_node = malloc(sizeof(list_t));

	if (!n_node)
		return (NULL);
	n_node->dir = dir;
	n_node->next = NULL;
	if (*first_node)
	{
		tail = *first_node;
		while (tail->next != NULL)
			tail = tail->next;
		tail->next = n_node;
	}
	else
		*first_node = n_node;
	return (n_node);
}

/**
 * list_alias_free - Frees the link list's alias.
 * @first_node: The first node in the link list.
 */
void list_alias_free(alias_t *first_node)
{
	alias_t *next;

	while (first_node)
	{
		next = first_node->next;
		free(first_node->name);
		free(first_node->value);
		free(first_node);
		first_node = next;
	}
}

/**
 * free_list - Clears the link list.
 * @head: First node.
 */
void free_list(list_t *head)
{
	list_t *next;

	while (head)
	{
		next = head->next;
		free(head->dir);
		free(head);
		head = next;
	}
}
