/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_stack.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 16:19:22 by fl-hote           #+#    #+#             */
/*   Updated: 2022/09/25 20:37:59 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

/* create new node and link before 1st elem
** generate loop chained
*/
void	fill_stack(int num, t_list **ptr_a)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
	{
		free_stack(*ptr_a);
		exit(EXIT_FAILURE);
	}
	node->num = num;
	node->rank = 0;
	if (!(*ptr_a))
	{
		*ptr_a = node;
		node->next = node;
		node->prev = node;
	}
	else
	{
		node->next = *ptr_a;
		node->prev = (*ptr_a)->prev;
		(*ptr_a)->prev->next = node;
		(*ptr_a)->prev = node;
		*ptr_a = node;
	}
}

/* first undo loop chained, then free all nodes
*/
void	free_stack(t_list *ptr)
{
	t_list	*buf;

	if (ptr)
	{
		ptr->prev->next = NULL;
		while (ptr->next)
		{
			buf = ptr;
			ptr = ptr->next;
			free (buf);
		}
		free(ptr);
	}
}

/* check if input list is already sorted
** supposed list > 2 elem
*/
int	is_sorted(t_list *ptr)
{
	int		ok;
	t_list	*p;

	ok = 1;
	p = ptr;
	while (p->next != ptr && ok)
	{
		p = p->next;
		if (p->num < p->prev->num)
			ok = 0;
	}
	return (ok);
}

void	free_split(char **arg)
{
	int	i;

	i = 0;
	if (arg[0][0] == 'd')
	{
		while (arg[i])
			free(arg[i++]);
		free(arg);
	}
}
