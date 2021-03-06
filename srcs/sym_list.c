#include <stdlib.h>
#include <stdio.h>
#include "ft_nm.h"

static uint8_t		is_lower(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (0);
	else
		return (1);
}

static uint8_t		is_not_alphanum(char *s)
{
	if (!*s)
		return (0);
	if ((*s >= 'a' && *s <= 'z')
			|| (*s >= 'A' && *s <= 'Z')
			|| (*s >= '0' && *s <= '9'))
	{
		return (0);
	}
	return (1);
}

static uint8_t		is_sort(char *s1, char *s2, uint64_t v1, uint64_t v2)
{
	char 	c1;
	char 	c2;

	if (!s1)
		return (0);
	if (!s2)
		return (1);
	while (*s1 && *s2)
	{
		while (is_not_alphanum(s1))
			s1++;
		while (is_not_alphanum(s2))
			s2++;
		c1 = is_lower(*s1) ? *s1 : *s1 + 32;
		c2 = is_lower(*s2) ? *s2 : *s2 + 32;
		if (c1 < c2)
			return (1);
		if (c1 > c2)
			return (0);
		if (!c1 || !c2)
			break ;
		s1++;
		s2++;
	}
	if (!*s1 && *s2)
		return (1);
	if (!*s1 && !*s2)
		if (v1 <= v2)
			return (1);
	return (0);
}

static t_symbol	*insert_sort_list(t_symbol *lst, t_symbol *new)
{
	t_symbol	*cur;
	t_symbol	*head;

	head = lst;
	cur = lst;
	if (!is_sort(head->name, new->name, head->value, new->value))
	{
		new->next = head;
		return (new);
	}
	while ((lst = lst->next))
	{
		if (!is_sort(lst->name, new->name, lst->value, new->value))
		{
			cur->next = new;
			new->next = lst;
			return (head);
		}
		cur = lst;
	}
	cur->next = new;
	return (head);
}

int8_t		create_lst_symbol(t_symbol **begin, t_symbol *elem)
{
	t_symbol *new;

	if (!(new = malloc(sizeof(t_symbol))))
	{
		fprintf(stderr, "%s: Critical error : malloc failed\n", NAME);
		return (E_CRITICAL);
	}
	*new = *elem;
	new->next = NULL;
	if (*begin)
		*begin = insert_sort_list(*begin, new);
	if (!*begin)
		*begin = new;
	return (SUCCESS);
}

void		clean_lst_symbol(t_symbol **begin)
{
	t_symbol	*lst;

	while (*begin)
	{
		lst = (*begin)->next;
		free(*begin);
		*begin = lst;
	}
	*begin = NULL;
}
