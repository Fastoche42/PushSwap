/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 19:18:09 by fl-hote           #+#    #+#             */
/*   Updated: 2022/07/28 21:31:17 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

void	free_all_list(t_glist *node)
{
	t_glist	*buffer;

	while (node)
	{
		buffer = node->next;
		free (node);
		node = buffer;
	}
}

/* Analyse string in the node
** start at "startc", position of the last \n found before, can be 0
** return 0 if no node, or if neither \n nor \0 in the string
** return 1 for \n ; 2 for \0
** ASCII '\n' = 10 , '\0' = 0
*/
int	stopcar_in_node(t_glist *node, t_gvar *var)
{
	int	c;
	int	car;

	c = node->startc;
	car = 0;
	while (c < BUFFER_SIZE)
	{
		if (node->string[0])
			car = (node->string[c]);
		if ((car == 10) || (car == 0))
		{
			node->endc = (c + (car / 10));
			var->eoleof = (2 - (car / 10));
			return (var->eoleof);
		}
		c++;
	}
	node->endc = c;
	var->eoleof = 0;
	return (0);
}

t_glist	*create_node(size_t *nb)
{
	t_glist	*new_node;
	int		i;

	new_node = malloc(sizeof(t_glist));
	new_node->startc = 0;
	new_node->endc = 0;
	new_node->next = NULL;
	i = -1;
	while (++i < BUFFER_SIZE)
		new_node->string[i] = 0;
	(*nb)++;
	return (new_node);
}
