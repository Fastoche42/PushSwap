/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 18:14:53 by fl-hote           #+#    #+#             */
/*   Updated: 2022/09/25 18:50:00 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_glist
{
	int				startc;
	int				endc;
	char			string[BUFFER_SIZE];
	struct s_glist	*next;
}				t_glist;

typedef struct s_gvar
{
	size_t	bytes_read;
	size_t	nb_nodes;
	int		eoleof;
}				t_gvar;

void	free_all_list(t_glist *node);
int		node_to_str(size_t nb_nodes, t_glist **stash_ptr, char **str);
char	*stash_to_out(t_glist **ptr, size_t nb_nodes, int eoleof);
int		stopcar_in_node(t_glist *node, t_gvar *var);
t_glist	*create_node(size_t *nb);
t_glist	*fill_nodes(t_glist **sptr, int fd, t_gvar *var);
char	*get_next_line(int fd);

#endif
