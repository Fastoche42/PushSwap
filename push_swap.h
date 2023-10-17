/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 15:29:19 by fl-hote           #+#    #+#             */
/*   Updated: 2023/07/14 00:03:28 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>

# ifndef SHARE1
#  define SHARE1 6
# endif

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

typedef struct s_combo
{
	size_t	nb_ra;
	size_t	nb_rra;
	size_t	nb_rb;
	size_t	nb_rrb;
	size_t	nb_rr;
	size_t	nb_rrr;
	size_t	qty;
	size_t	num;
}				t_combo;

typedef struct s_score
{
	t_list	*scroll_a;
	t_list	*scroll_b;
	size_t	qty[4];
	size_t	nbtot;
	int		i;
	int		i1;
	int		i2;
}				t_score;

typedef struct s_scroll
{
	struct s_list	*ptr;
	struct s_list	*ptr_min;
	struct s_list	*ptr_max;
}				t_scroll;

// main and sort
void	sort_inf5(t_var *stack);
int		sort_phase1(t_var *stack, size_t share);
int		loop_phase1(t_var *stk, int need_rb, size_t t1, size_t t2);
void	sort_final(t_var *stack);

// phase 2
void	sort_phase2(t_var *stack, size_t stop);
void	phase2_loop1(t_var *stk, t_score *s, t_combo *c, t_combo *best);
void	find_num_in_a(t_var *stk, t_score *s, t_combo c);
void	put_best(t_score *s, t_combo *c, t_combo *best);
void	phase2_mvt(t_var *stk, t_combo best);

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

// utils
void	do_mvt(char *mvt, t_var *stack);
int		is_min(int a, int b);
int		is_max(int a, int b);
void	find_minmax(t_list *ptr, size_t *min, size_t *max);

char	**ft_splitm(char *str, int *nb_words);
#endif
