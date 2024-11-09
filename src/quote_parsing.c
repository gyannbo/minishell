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
	q->pos = 0;
	q->count_next_quote = 0;
	q->count['\''] = 0;
	q->count['\"'] = 0;
}

bool	quote_parsing(t_values *v, int	*tab)
{
	t_quote q;

	init_quote(&q, tab);
	while (v->split_str[q.x])
	{
		q.y = 0;
		while (v->split_str[q.x][q.y])
		{
			if (if_pass_check(v->split_str[q.x][q.y], &tab[q.z], &q) == false)
			{
				if (manage_q_tok(v, &q) == false)
					return (false);
				break ;
			}
			q.y++;
		}
		q.x++;
	}
	return (true);
}
