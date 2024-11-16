/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_manage_q_tok_utils_second.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 21:21:21 by gbonis            #+#    #+#             */
/*   Updated: 2024/11/16 21:21:23 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_pos(t_quote *q, t_copy_outside *data)
{
	if (data->y == q->pos)
	{
		data->sec_valid_q = true;
		q->pos = -1;
		if (data->betw_q == false)
		{
			data->betw_q = true;
			data->y++;
			return (1);
		}
	}
	return (0);
}

void	init_struct_next_i(t_values *v, t_next_i *data, t_quote *q)
{
	data->i = get_right_pos(v, q->count, q->first_type);
	data->size = 0;
	data->type = 0;
	data->ret = 0;
}

int	if_type_is_i(t_values *v, t_next_i *data, size_t *c_nxt_q, size_t *cal_r_s)
{
	if (data->type && data->type == v->cmd_str_b[data->i])
	{
		if (!(*c_nxt_q))
		{
			data->temp = data->size;
			data->size -= *cal_r_s;
			*cal_r_s = data->temp;
			return (data->size);
		}
		(*c_nxt_q)--;
		data->type = 0;
		data->i++;
		return (-1);
	}
	return (0);
}
