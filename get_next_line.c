/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:47:16 by fl-hote           #+#    #+#             */
/*   Updated: 2022/09/25 19:51:59 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

int	node_to_str(size_t nb_nodes, t_glist **stash_ptr, char **str)
{
	int		i;
	int		j;
	t_glist	*to_free;

	i = 0;
	while (nb_nodes-- > 0)
	{
		j = (*stash_ptr)->startc;
		while (j < (*stash_ptr)->endc)
			(*str)[i++] = (*stash_ptr)->string[j++];
		if (!nb_nodes)
			break ;
		to_free = *stash_ptr;
		*stash_ptr = (*stash_ptr)->next;
		free (to_free);
	}
	return (i);
}

/* copy chained list to malloced str
** minimum nb_nodes is 1
** inside while, last node is 0
** loop on nodes, then loop on strings of node
** if \0 free all, otherwise free all but last
*/
char	*stash_to_out(t_glist **stash_ptr, size_t nb_nodes, int eoleof)
{
	char	*str;
	int		i;

	str = malloc((BUFFER_SIZE * nb_nodes + 1) * sizeof(char));
	if (!str)
	{
		free_all_list (*stash_ptr);
		return (NULL);
	}
	i = node_to_str(nb_nodes, stash_ptr, &str);
	if (eoleof == 2 || ((*stash_ptr)->endc >= BUFFER_SIZE))
	{
		free (*stash_ptr);
		*stash_ptr = NULL;
	}
	else
		(*stash_ptr)->startc = (*stash_ptr)->endc;
	if (!i)
	{
		free (str);
		return (NULL);
	}
	str[i] = 0;
	return (str);
}

t_glist	*fill_nodes(t_glist **liste, int fd, t_gvar *var)
{
	t_glist	*stash_ptr;

	stash_ptr = *liste;
	while (var->bytes_read)
	{
		if (var->nb_nodes > 0)
		{
			if (stopcar_in_node(stash_ptr, var))
				break ;
			stash_ptr->next = create_node(&var->nb_nodes);
			stash_ptr = stash_ptr->next;
		}
		else
		{
			*liste = create_node(&var->nb_nodes);
			stash_ptr = *liste;
		}
		var->bytes_read = read(fd, stash_ptr->string, BUFFER_SIZE);
		if ((var->bytes_read < BUFFER_SIZE) && var->bytes_read)
			stash_ptr->string[var->bytes_read] = 0;
	}
	return (stash_ptr);
}

char	*get_next_line(int fd)
{
	static t_glist	*ptrfd;
	t_glist			*stash_ptr;
	t_gvar			var;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	var.nb_nodes = (ptrfd != NULL);
	var.bytes_read = 1;
	var.eoleof = 0;
	stash_ptr = fill_nodes(&ptrfd, fd, &var);
	if (var.nb_nodes == 1 && !(var.bytes_read))
	{
		free (ptrfd);
		ptrfd = NULL;
		return (NULL);
	}
	if (!var.bytes_read)
	{
		free (stash_ptr);
		(var.nb_nodes)--;
	}
	return (stash_to_out(&ptrfd, var.nb_nodes, var.eoleof));
}
