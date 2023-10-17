/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 16:01:43 by fl-hote           #+#    #+#             */
/*   Updated: 2022/09/25 22:03:27 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "checker.h"

int	check_input(char *mvt, t_var *stk)
{
	if (cmp(mvt, "ra\n") && cmp(mvt, "rb\n") && cmp(mvt, "rr\n")
		&& cmp(mvt, "rra\n") && cmp(mvt, "rrb\n") && cmp(mvt, "rrr\n")
		&& cmp(mvt, "sa\n") && cmp(mvt, "sb\n") && cmp(mvt, "ss\n")
		&& cmp(mvt, "pa\n") && cmp(mvt, "pb\n"))
		return (0);
	if (!cmp(mvt, "ra\n") || !cmp(mvt, "rr\n"))
		op_rot(&stk->beg_a, stk->size_a, 0);
	if (!cmp(mvt, "rb\n") || !cmp(mvt, "rr\n"))
		op_rot(&stk->beg_b, stk->size_b, 0);
	if (!cmp(mvt, "rra\n") || !cmp(mvt, "rrr\n"))
		op_rot(&stk->beg_a, stk->size_a, 1);
	if (!cmp(mvt, "rrb\n") || !cmp(mvt, "rrr\n"))
		op_rot(&stk->beg_b, stk->size_b, 1);
	if (!cmp(mvt, "sa\n") || !cmp(mvt, "ss\n"))
		op_swap(&stk->beg_a, stk->size_a);
	if (!cmp(mvt, "sb\n") || !cmp(mvt, "ss\n"))
		op_swap(&stk->beg_b, stk->size_b);
	if ((!cmp(mvt, "pa\n")) && (stk->beg_b))
		op_push(&stk->beg_b, &stk->size_b, &stk->beg_a, &stk->size_a);
	if ((!cmp(mvt, "pb\n")) && (stk->beg_a))
		op_push(&stk->beg_a, &stk->size_a, &stk->beg_b, &stk->size_b);
	return (1);
}

static int	read_mvt(t_var *stack)
{
	int		ok;
	char	*mvt;

	ok = 1;
	while (ok)
	{
		mvt = get_next_line(STDIN_FILENO);
		if (!mvt)
			break ;
		if (!cmp(mvt, "\n"))
		{
			free(mvt);
			break ;
		}
		ok = check_input(mvt, stack);
		free(mvt);
		mvt = 0;
	}
	return (ok);
}

int	main(int argc, char **argv)
{
	t_var	stack;
	int		ok;

	if (argc < 2)
		return (1);
	if (!ok_parse(&argc, argv, &stack, 1))
		return (0);
	stack.size_a = argc - 1;
	add_rank(stack.beg_a, stack.size_a);
	ok = read_mvt(&stack);
	if (ok)
	{
		if (is_sorted(stack.beg_a) && !stack.size_b)
			ft_putstr_fd("OK", STDOUT_FILENO);
		else
			ft_putstr_fd("KO", STDOUT_FILENO);
	}
	else
		ft_putstr_fd("Error", STDERR_FILENO);
	free_stack(stack.beg_a);
	free_stack(stack.beg_b);
	return (0);
}
