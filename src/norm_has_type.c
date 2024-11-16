/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_has_copy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 19:23:54 by gbonis            #+#    #+#             */
/*   Updated: 2024/11/16 19:29:56 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_struct(t_has_type *data, t_quote *q, int *q_cnter)
{
	data->flag = false;
	data->temp_z = q->z;
	data->temp_value = q->tab[data->temp_z];
	data->i = 0;
	data->q_cnter = q_cnter;
}

void	if_type(t_quote *q, char *s, size_t i, char *type)
{
	if ((q->q_before_tok % 2 == 0 && q->has_b_tok)
		&& (s[i] == '\'' || s[i] == '\"'))
		*type = s[i];
}

int	at_begin(t_quote *q, char *s)
{
	if (q->temp_c_n_quote == -1)
		q->temp_c_n_quote = q->count_next_quote;
	if (!s)
		return (-1);
	return (0);
}

void	do_next_quote_n_mod_2(t_quote *q, t_has_type *data, char *s)
{
	skip_non_v_quote(s, &data->temp_value, data->q_cnter, &data->i);
	data->temp_z++;
	data->temp_value = q->tab[data->temp_z];
	q->temp_c_n_quote--;
}

void	do_loop_has_type(t_quote *q, t_has_type *data, char *s, char *type)
{
	if ((*data->q_cnter % 2 == 0 && *data->q_cnter)
		&& (s[data->i] == '\'' || s[data->i] == '\"'))
	{
		if (s[data->i] == '\'' || s[data->i] == '\"')
			*type = s[data->i];
	}	
	if (s[data->i] == *type)
	{
		if (q->temp_c_n_quote && *data->q_cnter % 2 != 0)
			do_next_quote_n_mod_2(q, data, s);
		data->flag = true;
		if (*data->q_cnter)
			(*data->q_cnter)--;
	}
	data->i++;
	if (*type != s[data->i])
	{
		if ((q->q_before_tok % 2 == 0 && q->has_b_tok)
			&& (s[data->i] == '\'' || s[data->i] == '\"'))
			*type = s[data->i];
	}
}
