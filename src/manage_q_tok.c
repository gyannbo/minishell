/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_q_tok.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:52:04 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/25 16:37:24 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_right_pos(t_values *v, int *count, char type)
{
	size_t	i;
	size_t	sec_q;
	int		temp;

	i = 0;
	sec_q = 0;
	temp = count[(int)type];
	while (v->cmd_str_b[i])
	{
		if (v->cmd_str_b[i] == type && count[(int)type] == 0)
		{
			count[(int)type] = temp;
			return (i);
		}
		if (v->cmd_str_b[i] == type)
			when_eq_type(type, &sec_q, count);
		i++;
	}
	count[(int)type] = temp;
	return (i);
}

static size_t	get_outside_q_size(t_values *v, int x, t_quote *q)
{
	t_var	var;
	t_other	other;

	set_variables(v, q, &var, &other);
	while (v->split_s[x])
	{
		other.y = 0;
		do_loop(q, &var, &other, x);
		if (other.end)
			break ;
		x++;
	}
	temp_at_return(q, &var);
	return (other.i);
}

size_t	get_inside_q_size(t_values *v, char type, int *count, t_quote *q)
{
	size_t	i;
	size_t	size;

	size = 0;
	i = get_right_pos(v, count, type);
	i++;
	while (v->cmd_str_b[i] != type || q->count_next_quote)
	{
		if (v->cmd_str_b[i] == type && q->count_next_quote)
		{
			i++;
			while (v->cmd_str_b[i] && v->cmd_str_b[i]
				!= '\'' && v->cmd_str_b[i] != '\"')
				i++;
			type = v->cmd_str_b[i];
			if (v->cmd_str_b[i])
				i++;
			q->count_next_quote--;
			continue ;
		}
		size++;
		i++;
	}
	return (size);
}

static size_t	get_size(t_values *v, t_quote *q)
{
	size_t	out_size;
	size_t	in_size;
	size_t	new_tok_size;

	out_size = get_outside_q_size(v, q->x, q);
	in_size = get_inside_q_size(v, q->type, q->count, q);
	new_tok_size = out_size + in_size + 1;
	q->new_tok_size = new_tok_size;
	return (new_tok_size);
}

bool	manage_q_tok(t_values *v, t_quote *q)
{
	char	*new_tok;
	size_t	size;

	q->first_type = q->type;
	if (q->q_before_tok)
		q->has_b_tok = 1;
	size = get_size(v, q);
	new_tok = malloc(sizeof(char) * size);
	if (!new_tok)
		return (false);
	ft_bzero(new_tok, size);
	copy_in_tok(v, new_tok, q->x, q);
	manage_rest_tok(v, new_tok, q);
	manage_tab(q);
	manage_count(v, q);
	q->first_type = 0;
	q->count_next_quote = 0;
	q->has_b_tok = 0;
	q->temp_c_n_quote = -1;
	return (true);
}
