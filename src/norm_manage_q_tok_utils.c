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

void	untemp_at_exit(t_quote *q, t_copy_outside *data, size_t *c_right_size)
{
	q->pos = data->temp;
	q->z = data->temp_z;
	q->type = data->temp_type;
	*c_right_size = 0;
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

void	if_t_sec_valid(t_values *v, t_quote *q, t_copy_outside *d, size_t *c)
{
	d->sec_valid_q = false;
	d->i += get_next_i(v, q->count_next_quote, c, q);
	d->betw_q = false;
	if (next_pos(v, q, d->x, d->y) == -1)
		d->end = true;
	d->y++;
}

/// for type sec valid le dernier arg c'est calc right size
