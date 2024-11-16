/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:36:03 by gbonis            #+#    #+#             */
/*   Updated: 2024/11/04 14:36:09 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_tab(t_quote *q)
{
	q->z += q->count_next_quote;
	q->tab[q->z] -= q->decr_tab;
	q->decr_tab = 0;
}

void	increment_q_counter_w_tab(int *counter, t_quote *q)
{
	int	temp_next_quote;
	int	z;

	z = q->z;
	*counter += q->q_before_tok;
	temp_next_quote = q->count_next_quote;
	while (temp_next_quote)
	{
		*counter += q->tab[z];
		temp_next_quote--;
		z++;
	}
}

void	manage_count(t_values *v, t_quote *q)
{
	size_t	i;
	bool	after_first;

	i = get_right_pos(v, q->count, q->first_type);
	after_first = false;
	q->count_next_quote++;
	while (v->cmd_str_b[i] && q->count_next_quote)
	{
		if (v->cmd_str_b[i] == '\'' || v->cmd_str_b[i] == '\"')
		{
			if (after_first)
			{
				after_first = false;
				i++;
				continue ;
			}
			(q->count[(int)v->cmd_str_b[i]])++;
			q->count_next_quote--;
			after_first = true;
		}
		i++;
	}
}
