/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_common.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 21:57:03 by fl-hote           #+#    #+#             */
/*   Updated: 2022/09/25 22:14:16 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

/* rot stack A or B, witch are circular chained lists
** !reverse = ra/rb ; reverse = rra/rrb
*/
int	op_rot(t_list **beg, size_t size, int reverse)
{
	if (size < 2)
		return (0);
	if (reverse)
		*beg = (*beg)->prev;
	else
		*beg = (*beg)->next;
	return (1);
}

/* swap 1st & 2nd element of stack
** by moving content
*/
int	op_swap(t_list **beg, size_t size)
{
	int		bufnum;
	size_t	bufrank;	

	if (size < 2)
		return (0);
	if (size > 2)
	{
		bufnum = (*beg)->next->num;
		bufrank = (*beg)->next->rank;
		(*beg)->next->num = (*beg)->num;
		(*beg)->next->rank = (*beg)->rank;
		(*beg)->num = bufnum;
		(*beg)->rank = bufrank;
		return (1);
	}
	*beg = (*beg)->next;
	return (1);
}

/* push stack1 -> stack2
** can be A->B or B->A
** move pointers
*/
int	op_push(t_list **beg1, size_t *size1, t_list **beg2, size_t *size2)
{
	t_list	*new1;

	new1 = (*beg1)->next;
	new1->prev = (*beg1)->prev;
	new1->prev->next = new1;
	if (!*size2)
	{
		(*beg1)->prev = *beg1;
		(*beg1)->next = *beg1;
	}
	else
	{
		(*beg1)->prev = (*beg2)->prev;
		(*beg1)->next = *beg2;
		(*beg2)->prev = *beg1;
		(*beg1)->prev->next = *beg1;
	}
	*beg2 = *beg1;
	*beg1 = new1;
	--*size1;
	if (!*size1)
		*beg1 = NULL;
	++*size2;
	return (1);
}

int	ft_putstr_fd(char *s, int fd)
{
	while (s && *s)
		write(fd, s++, 1);
	write(fd, "\n", 1);
	return (0);
}

int	cmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
