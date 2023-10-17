/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 16:01:43 by fl-hote           #+#    #+#             */
/*   Updated: 2022/09/25 20:38:54 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

/* sort for short list
** specific algorithm for 3 elements in A
*/
void	sort_inf5(t_var *stk)
{
	size_t	min;
	size_t	max;

	while (stk->size_a > 3)
		do_mvt("pb", stk);
	find_minmax(stk->beg_a, &min, &max);
	if (stk->beg_a->rank == max)
		do_mvt("ra", stk);
	else if (stk->beg_a->next->rank == max)
		do_mvt("rra", stk);
	if (stk->beg_a->next->rank == min)
		do_mvt("sa", stk);
}

/* Considere stack A is sorted and B is empty
** Just put lower elem in 1st position
*/
void	sort_final(t_var *stk)
{
	int	sens;

	sens = (stk->beg_a->rank > (stk->size_a / 2));
	while (stk->beg_a->rank != 1)
	{
		if (sens)
			do_mvt("ra", stk);
		else
			do_mvt("rra", stk);
	}
}

int	loop_phase1(t_var *stk, int need, size_t t1, size_t t2)
{
	int		need_rb;

	need_rb = need;
	if (stk->beg_a->rank <= (stk->size_a + stk->size_b - t1))
	{
		if (need_rb)
		{
			do_mvt ("rb", stk);
			need_rb = 0;
		}
		do_mvt("pb", stk);
		if (((stk->size_b > 1) && (stk->size_a > 3))
			&& (stk->beg_b->rank <= (stk->size_a + stk->size_b - t1 - t2)))
			need_rb = 1;
	}
	else
	{
		if (need_rb)
			do_mvt ("rr", stk);
		else
			do_mvt("ra", stk);
		need_rb = 0;
	}
	return (need_rb);
}

int	sort_phase1(t_var *stk, size_t share)
{
	size_t	t1;
	size_t	t2;
	int		need_rb;
	int		sorted;

	t2 = (stk->size_a + 1) / share;
	if (stk->size_a < 16)
		t2 = (stk->size_a + 1) / 3;
	t1 = stk->size_a - (2 * t2);
	need_rb = 0;
	sorted = 0;
	while (stk->size_a > 3 && stk->size_a >= t1 + 1 && !sorted)
	{
		need_rb = loop_phase1(stk, need_rb, t1, t2);
		sorted = is_sorted(stk->beg_a);
	}
	if (need_rb)
		do_mvt ("rb", stk);
	return (sorted);
}

int	main(int argc, char **argv)
{
	t_var	stack;
	size_t	share;
	int		sorted;

	if (!ok_parse(&argc, argv, &stack, 0))
		return (0);
	if (!is_sorted(stack.beg_a))
	{
		stack.size_a = argc - 1;
		add_rank(stack.beg_a, stack.size_a);
		share = SHARE1;
		sorted = 0;
		while (stack.size_a > 3)
		{
			if (share < 3 || share > 12 || stack.size_a < 13)
				share = 3;
			sorted = sort_phase1(&stack, share--);
		}
		if (!sorted)
			sort_inf5(&stack);
		sort_phase2(&stack, 0);
		sort_final(&stack);
	}
	free_stack(stack.beg_a);
	return (0);
}
