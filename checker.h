/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 15:29:19 by fl-hote           #+#    #+#             */
/*   Updated: 2022/09/25 22:19:03 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CHECKER_H
# define CHECKER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>
# include <fcntl.h>
# include "get_next_line.h"

typedef struct s_list
{
	int				num;
	size_t			rank;
	struct s_list	*prev;
	struct s_list	*next;
}				t_list;

typedef struct s_var
{
	struct s_list	*beg_a;
	size_t			size_a;
	struct s_list	*beg_b;
	size_t			size_b;
}				t_var;

// main and sort
int		check_input(char *strmvt, t_var *stk);

// stack
void	fill_stack(int num, t_list **ptr);
void	free_stack(t_list *ptr);
int		is_sorted(t_list *ptr);
void	free_split(char **arg);

// parse
int		is_twice(int num, t_list *list);
int		is_int(char *str, int *resu);
int		ok_arg(char **arg, int c, t_var *ptr);
int		ok_parse(int *argc, char **argv, t_var *stack, int chk);
void	add_rank(t_list *ptr, int size);

// common
int		op_rot(t_list **beg, size_t size, int rev);
int		op_swap(t_list **beg, size_t size);
int		op_push(t_list **beg1, size_t *size1, t_list **beg2, size_t *size2);
int		cmp(const char *str1, const char *str2);
int		ft_putstr_fd(char *c, int fd);

char	**ft_splitm(char *str, int *num_words);

#endif
