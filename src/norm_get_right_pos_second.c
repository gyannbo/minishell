/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_get_right_pos_second.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 18:54:46 by gbonis            #+#    #+#             */
/*   Updated: 2024/11/16 18:54:47 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_loop(t_quote *q, t_var *var, t_other *other, int x)
{
	while (var->v->split_s[x][other->y])
	{
		if (other->y == q->pos)
		{
			if (y_eq_pos(q, var, other))
				continue ;
		}
		if (var->v->split_s[x][(other->y)]
			== q->type && var->sec_valid_q == true)
		{
			type_n_sec_valid_true(q, var, other, x);
			continue ;
		}
		if (other->betw_q == false)
			other->i++;
		other->y++;
	}
}

int	next_pos(t_values *v, t_quote *q, int x, int y)
{
	int	temp_tab_val;

	temp_tab_val = q->tab[q->z];
	y++;
	while (v->split_s[x][y])
	{
		if (if_pass_check(v->split_s[x][y], &temp_tab_val, q) == false)
		{
			q->pos = y;
			q->count_next_quote++;
			return (0);
		}
		y++;
	}
	q->pos = -1;
	return (-1);
}
