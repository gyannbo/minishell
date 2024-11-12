/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:25:05 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/25 17:47:47 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	if_pass_check(char c, int *tab, t_quote *q)
{
	if (c == '\'' || c == '\"')
	{
		if (*tab == 0)
		{
			(q->z)++;
			q->pos = q->y;
			q->type = c;
			return (false);
		}
		else
		{
			(*tab)--;
			return (true);
		}
	}
	return (true);
}

static void	init_quote(t_quote *q, int *tab)
{
	q->x = 0;
	q->y = 0;
	q->z = 0;
	q->two_type = false;
	q->type = 0;
	q->first_type = 0;
	q->tab = tab;
	q->q_before_tok = 0;
	q->has_b_tok = 0;
	q->decr_tab = 0;
	q->pos = 0;
	q->count_next_quote = 0;
	q->count['\''] = 0;
	q->count['\"'] = 0;
	q->temp_c_n_quote = 0;
}

bool	quote_parsing(t_values *v, int	*tab)
{
	t_quote q;
	int temp_val[2];

	init_quote(&q, tab);
	temp_val[0] = q.tab[0];
	temp_val[1] = q.z;
	while (v->split_str[q.x])
	{
		q.y = 0;
		while (v->split_str[q.x][q.y])
		{
			if (temp_val[1] != q.z)
			{
				temp_val[0] = q.tab[q.z];
				temp_val[1] = q.z;
			}
			if (if_pass_check(v->split_str[q.x][q.y], &temp_val[0], &q) == false)
			{
				if (manage_q_tok(v, &q) == false)
					return (false);
				break ;
			}
			if (v->split_str[q.x][q.y] == '\'' || v->split_str[q.x][q.y] == '\"')
				q.q_before_tok++;
			q.y++;
		}
		q.q_before_tok = 0;
		q.x++;
	}
	return (true);
}


// peut etre que pour temp le tableau je peux juste checker si le z a changé et à ce moment là je change la value temp avec le nouveau z
