/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_rest_tok.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:15:35 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/25 16:26:58 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_type(char *s, char *type, int *q_cnter, t_quote *q)
{
	t_has_type	data;

	set_struct(&data, q, q_cnter);
	if (at_begin(q, s) == -1)
		return (-1);
	before_tok(q, &data.i, q_cnter, s);
	if (*type != s[data.i])
		if_type(q, s, data.i, type);
	while (s[data.i])
		do_loop_has_type(q, &data, s, type);
	if (data.flag)
		return (1);
	return (0);
}

static int	has_two_types(char *s, char type, t_quote *q)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == type)
		{
			if (count == 1)
			{
				if (next_q_exist(q))
					return (0);
				return (1);
			}
			else
				count++;
		}
		i++;
	}
	return (0);
}

static size_t	free_useless_tok(t_values *v, size_t x, t_quote *q)
{
	int	res;
	int	quote_counter;

	quote_counter = 0;
	if (q->count_next_quote)
		quote_counter = (q->count_next_quote * 2) + 1;
	if (q->two_type)
		quote_counter++;
	increment_q_counter_w_tab(&quote_counter, q);
	x++;
	res = has_type(v->split_s[x], &q->type, &quote_counter, q);
	while ((!res || quote_counter) && v->split_s[x])
	{
		free(v->split_s[x]);
		x++;
		res = has_type(v->split_s[x], &q->type, &quote_counter, q);
	}
	if (!v->split_s[x] && quote_counter)
		return (x - 1);
	free(v->split_s[x]);
	return (x);
}

static size_t	move_tokens(t_values *v, size_t x, size_t sec_q_tok)
{
	sec_q_tok++;
	x++;
	if (!(v->split_s[x]))
		return (x);
	while (v->split_s[sec_q_tok])
	{
		v->split_s[x] = v->split_s[sec_q_tok];
		sec_q_tok++;
		x++;
	}
	return (x);
}

void	manage_rest_tok(t_values *v, char *new_tok, t_quote *q)
{
	size_t	sec_q_tok;
	size_t	last_viable_tok;
	size_t	tmp;
	char	*old_tok;

	old_tok = v->split_s[q->x];
	if (has_two_types(&old_tok[q->pos], q->type, q))
	{
		v->split_s[q->x] = new_tok;
		free(old_tok);
		return ;
	}
	sec_q_tok = free_useless_tok(v, q->x, q);
	if (q->two_type)
		q->x++;
	else
		free(old_tok);
	last_viable_tok = move_tokens(v, q->x, sec_q_tok);
	tmp = last_viable_tok;
	v->split_s[tmp] = NULL;
	at_exit_free_useless(v, q, last_viable_tok, new_tok);
}
