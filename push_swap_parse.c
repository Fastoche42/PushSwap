/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 17:00:15 by fl-hote           #+#    #+#             */
/*   Updated: 2022/09/25 22:15:51 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"

int	ok_parse(int *argc, char **argv, t_var *stack, int chk)
{
	if (*argc == 1)
		return (ft_putstr_fd("Error", STDERR_FILENO));
	if (*argc == 2)
		argv = ft_splitm(argv[1], argc);
	if (!ok_arg(argv, *argc, stack))
		return (0);
	if (*argc < 4 && !chk)
	{
		if (*argc == 3)
		{
			if (stack->beg_a->num > stack->beg_a->next->num)
				write (1, "sa\n", 3);
		}
		free_stack(stack->beg_a);
		return (0);
	}
	return (1);
}

/* check args from last to first
** check INT and twin numbers
*/
int	ok_arg(char **arg, int i, t_var *stack)
{
	int	num;

	stack->beg_a = NULL;
	stack->size_a = 0;
	stack->beg_b = NULL;
	stack->size_b = 0;
	while (--i)
	{
		if (arg[i] && is_int(arg[i], &num) && (!is_twice(num, (stack->beg_a))))
			fill_stack(num, &(stack->beg_a));
		else
		{
			free_stack(stack->beg_a);
			free_split(arg);
			return (ft_putstr_fd("Error", STDERR_FILENO));
		}
	}
	free_split(arg);
	return (1);
}

/* return 1 if number appear twice in the list
** return 0 if not
*/
int	is_twice(int num, t_list *list)
{
	t_list	*ptr;

	if (!list)
		return (0);
	ptr = list;
	while (1)
	{
		if (num == ptr->num)
			return (1);
		if (ptr->next == list)
			return (0);
		ptr = ptr->next;
	}
}

/* simplified "atoi"
** check limits of INT, double "-"
** return 0/1 if int, and return interger value if available
*/
int	is_int(char *str, int *resu)
{
	int		sign;
	size_t	buf;

	if (!(*str == '+' || *str == '-' || ('0' <= *str && *str <= '9')))
		return (0);
	if ((*str == '0' && *(str + 1)) || (*str == '-' && !*(str + 1)))
		return (0);
	sign = -2 * (*str == '-') + 1;
	buf = ((*str != '-') * (*str - '0'));
	while (*(++str))
	{
		if (*str < '0' || '9' < *str)
			return (0);
		if (*str == '0' && *(str - 1) == '-')
			return (0);
		buf = buf * 10 + *str - '0';
		if (buf - ((1 - sign) / 2) > INT_MAX)
			return (0);
	}
	*resu = (int)(buf * sign);
	return (1);
}

/* rank 1 to n, use for sorting
*/
void	add_rank(t_list *ptr, int size)
{
	int			i;
	t_scroll	v;

	i = 0;
	while (++i <= ((size + 1) / 2))
	{
		v.ptr = ptr;
		while (v.ptr->rank)
			v.ptr = v.ptr->next;
		v.ptr_min = v.ptr;
		v.ptr_max = v.ptr;
		while (1)
		{
			if (!v.ptr->rank && v.ptr->num <= v.ptr_min->num)
				v.ptr_min = v.ptr;
			else if (!v.ptr->rank && v.ptr->num >= v.ptr_max->num)
				v.ptr_max = v.ptr;
			if (v.ptr->next == ptr)
				break ;
			v.ptr = v.ptr->next;
		}
		v.ptr_min->rank = i;
		v.ptr_max->rank = (size + 1 - i);
	}
}
