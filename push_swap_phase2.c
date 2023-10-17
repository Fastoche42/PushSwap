/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_phase2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 16:23:53 by fl-hote           #+#    #+#             */
/*   Updated: 2022/09/25 20:38:14 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

void	find_num_in_a(t_var *stk, t_score *s, t_combo c)
{
	s->scroll_a = stk->beg_a;
	s->i = 0;
	while (1)
	{
		if (s->scroll_a->rank < s->scroll_a->prev->rank)
		{
			if (c.num < s->scroll_a->rank)
				break ;
			if (c.num > s->scroll_a->prev->rank)
				break ;
		}
		else if (s->scroll_a->prev->rank < c.num && c.num < s->scroll_a->rank)
			break ;
		++s->i;
		s->scroll_a = s->scroll_a->next;
	}
}

void	put_best(t_score *s, t_combo *c, t_combo *best)
{
	if (c->qty == s->qty[3])
	{
		best->nb_rrr = is_min(c->nb_rra, c->nb_rrb);
		if (c->nb_rra > c->nb_rrb)
			best->nb_rra = (c->nb_rra - c->nb_rrb);
		else
			best->nb_rrb = (c->nb_rrb - c->nb_rra);
	}
	else if (c->qty == s->qty[2])
	{
		best->nb_rr = is_min(c->nb_ra, c->nb_rb);
		if (c->nb_ra > c->nb_rb)
			best->nb_ra = (c->nb_ra - c->nb_rb);
		else
			best->nb_rb = (c->nb_rb - c->nb_ra);
	}
	else
	{
		best->nb_rra = (c->qty == s->qty[1]) * c->nb_rra;
		best->nb_rb = (c->qty == s->qty[1]) * c->nb_rb;
		best->nb_ra = (c->qty == s->qty[0]) * c->nb_ra;
		best->nb_rrb = (c->qty == s->qty[0]) * c->nb_rrb;
	}
}

void	phase2_loop1(t_var *stk, t_score *s, t_combo *c, t_combo *best)
{
	c->num = s->scroll_b->rank;
	c->nb_rb = (stk->size_b + s->i1) % stk->size_b;
	c->nb_rrb = ((stk->size_b - c->nb_rb) * (c->nb_rb != 0));
	find_num_in_a(stk, s, *c);
	c->nb_ra = s->i;
	c->nb_rra = stk->size_a - s->i;
	s->qty[0] = s->nbtot - c->num + (c->nb_ra + c->nb_rrb);
	s->qty[1] = s->nbtot - c->num + (c->nb_rra + c->nb_rb);
	s->qty[2] = s->nbtot - c->num + is_max(c->nb_rb, c->nb_ra);
	s->qty[3] = s->nbtot - c->num + is_max(c->nb_rrb, c->nb_rra);
	c->qty = is_min(is_min(is_min(s->qty[0], s->qty[1]), s->qty[2]), s->qty[3]);
	if ((c->qty < best->qty) || (c->qty == best->qty && c->num > best->num))
	{
		best->qty = c->qty;
		best->num = c->num;
		best->nb_ra = 0;
		best->nb_rra = 0;
		best->nb_rb = 0;
		best->nb_rrb = 0;
		best->nb_rr = 0;
		best->nb_rrr = 0;
		put_best(s, c, best);
	}
	++s->i1;
	s->scroll_b = s->scroll_b->next;
}

void	phase2_mvt(t_var *stk, t_combo best)
{
	while (best.nb_rr-- > 0)
		do_mvt("rr", stk);
	while (best.nb_rrr-- > 0)
		do_mvt("rrr", stk);
	while (best.nb_ra-- > 0)
		do_mvt("ra", stk);
	while (best.nb_rra-- > 0)
		do_mvt("rra", stk);
	while (best.nb_rb-- > 0)
		do_mvt("rb", stk);
	while (best.nb_rrb-- > 0)
		do_mvt("rrb", stk);
	do_mvt("pa", stk);
}

void	sort_phase2(t_var *stk, size_t stop)
{
	t_score	s;
	t_combo	c;
	t_combo	best;

	while (stk->size_b > stop)
	{
		if (stk->size_a < stk->size_b)
			s.i = stk->size_a;
		else
			s.i = stk->size_b;
		s.i1 = -s.i / 2;
		s.i2 = s.i + s.i1;
		s.scroll_b = stk->beg_b;
		s.i = -s.i1;
		while (s.i--)
			s.scroll_b = s.scroll_b->prev;
		best.qty = INT_MAX;
		best.num = 0;
		s.nbtot = stk->size_a + stk->size_b;
		while (s.i1 < s.i2)
			phase2_loop1(stk, &s, &c, &best);
		phase2_mvt(stk, best);
	}
}
