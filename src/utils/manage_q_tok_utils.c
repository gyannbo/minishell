/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_q_tok_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:31:31 by gbonis            #+#    #+#             */
/*   Updated: 2024/11/05 17:32:14 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_next_i(t_values *v, size_t c_nxt_q, size_t *cal_r_s, t_quote *q)
{
	t_next_i	data;

	init_struct_next_i(v, &data, q);
	while (v->cmd_str_b[data.i])
	{
		if (v->cmd_str_b[data.i] == '\'' || v->cmd_str_b[data.i] == '\"')
		{
			data.ret = if_type_is_i(v, &data, &c_nxt_q, cal_r_s);
			if (data.ret > 0)
				return (data.ret);
			if (data.ret < 0)
				continue ;
			if (!data.type)
			{
				data.type = v->cmd_str_b[data.i];
				data.i++;
				continue ;
			}
		}
		if (data.type)
			data.size++;
		data.i++;
	}
	return (data.size + 1);
}

static void	skip_char(char *new_tok, size_t *i)
{
	while (new_tok[(*i)])
		(*i)++;
	return ;
}

static void	copy_outside(t_values *v, int x, t_quote *q, char *new_tok)
{
	static size_t	calc_right_size;
	t_copy_outside	data;

	init_struct(&data, q, new_tok, x);
	while (v->split_s[data.x])
	{
		data.y = 0;
		while (v->split_s[data.x][data.y])
		{
			if (if_pos(q, &data))
				continue ;
			if (v->split_s[data.x][data.y] == q->type && data.sec_valid_q == true)
			{
				if_type_sec_valid(v, q, &data, &calc_right_size);
				continue ;
			}
			if_betw_q_false(v, q, &data);
		}
		if (data.end)
			break ;
		data.x++;
	}
	untemp_at_exit(q, &data, &calc_right_size);
	return ;
}

static void	copy_inside(t_values *v, int *count, t_quote *q, char *new_tok)
{
	size_t	i;
	size_t	y;
	char	type;
	size_t	tmp;

	y = 0;
	type = q->type;
	tmp = q->count_next_quote;
	i = get_right_pos(v, count, type);
	i++;
	skip_char(new_tok, &y);
	while (v->cmd_str_b[i] != type || q->count_next_quote)
	{
		if (v->cmd_str_b[i] == type && q->count_next_quote)
		{
			eq_type_n_next_q(v, q, &type, &i);
			skip_char(new_tok, &y);
			continue ;
		}
		new_tok[y] = v->cmd_str_b[i];
		y++;
		i++;
	}
	q->count_next_quote = tmp;
	return ;
}

void	copy_in_tok(t_values *v, char *s, int x, t_quote *q)
{
	copy_outside(v, x, q, s);
	copy_inside(v, q->count, q, s);
	s[(q->new_tok_size - 1)] = 0;
	return ;
}
