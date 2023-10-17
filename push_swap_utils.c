/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 16:16:00 by fl-hote           #+#    #+#             */
/*   Updated: 2022/09/25 21:44:24 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

void	do_mvt(char *mvt, t_var *stk)
{
	int	ok;

	ok = 0;
	if (!cmp(mvt, "ra") || !cmp(mvt, "rr"))
		ok = op_rot(&stk->beg_a, stk->size_a, 0);
	if (!cmp(mvt, "rb") || !cmp(mvt, "rr"))
		ok = op_rot(&stk->beg_b, stk->size_b, 0);
	if (!cmp(mvt, "rra") || !cmp(mvt, "rrr"))
		ok = op_rot(&stk->beg_a, stk->size_a, 1);
	if (!cmp(mvt, "rrb") || !cmp(mvt, "rrr"))
		ok = op_rot(&stk->beg_b, stk->size_b, 1);
	if (!cmp(mvt, "sa") || !cmp(mvt, "ss"))
		ok = op_swap(&stk->beg_a, stk->size_a);
	if (!cmp(mvt, "sb") || !cmp(mvt, "ss"))
		ok = op_swap(&stk->beg_b, stk->size_b);
	if ((!cmp(mvt, "pa")) && (stk->beg_b))
		ok = op_push(&stk->beg_b, &stk->size_b, &stk->beg_a, &stk->size_a);
	if ((!cmp(mvt, "pb")) && (stk->beg_a))
		ok = op_push(&stk->beg_a, &stk->size_a, &stk->beg_b, &stk->size_b);
	if (ok)
		ft_putstr_fd(mvt, STDOUT_FILENO);
}

int	is_min(int a, int b)
{
	if (a > b)
		return (b);
	return (a);
}

int	is_max(int a, int b)
{
	if (a >= b)
		return (a);
	return (b);
}

void	find_minmax(t_list *ptr, size_t *min, size_t *max)
{
	t_list	*n;

	n = ptr;
	*min = n->rank;
	*max = n->rank;
	while (1)
	{
		if (n->rank < *min)
			*min = n->rank;
		if (n->rank > *max)
			*max = n->rank;
		n = n->next;
		if (n == ptr)
			break ;
	}
}
