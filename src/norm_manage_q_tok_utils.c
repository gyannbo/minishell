/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_manage_q_tok_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 20:15:21 by gbonis            #+#    #+#             */
/*   Updated: 2024/11/16 20:15:23 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	eq_type_n_next_q(t_values *v, t_quote *q, char *type, size_t *i)
{
	(*i)++;
	while (v->cmd_str_b[(*i)] != '\'' && v->cmd_str_b[(*i)] != '\"')
		(*i)++;
	*type = v->cmd_str_b[(*i)];
	(*i)++;
	q->count_next_quote--;
}

void	init_struct(t_copy_outside *data, t_quote *q, char *new_tok, int x)
{
	data->temp = q->pos;
	data->temp_z = q->z;
	data->temp_type = q->type;
	data->end = false;
	data->betw_q = false;
	data->sec_valid_q = false;
	data->i = 0;
	data->new_tok = new_tok;
	data->x = x;
}

void untemp_at_exit(t_quote *q, t_copy_outside *data, size_t *calc_right_size)
{
	q->pos = data->temp;
	q->z = data->temp_z;
	q->type = data->temp_type;
	*calc_right_size = 0;
}

void	if_betw_q_false(t_values *v, t_quote *q, t_copy_outside *data)
{
	if (data->betw_q == false)
	{
		if (data->end && (v->split_s[data->x][data->y] == '\''
			|| v->split_s[data->x][data->y] == '\"'))
			q->decr_tab++;
		data->new_tok[data->i] = v->split_s[data->x][data->y];
		data->i++;
	}
	data->y++;
}

void	if_type_sec_valid(t_values *v, t_quote *q, t_copy_outside *data, size_t *calc_right_size)
{
	data->sec_valid_q = false;
	data->i += get_next_i(v, q->count_next_quote, calc_right_size, q);
	data->betw_q = false;
	if (next_pos(v, q, data->x, data->y) == -1)
		data->end = true;
	data->y++;
}
