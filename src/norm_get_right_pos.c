/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_get_right_pos.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:51:57 by gbonis            #+#    #+#             */
/*   Updated: 2024/11/16 17:52:01 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	when_eq_type(char type, size_t *sec_q, int *count)
{
	if (*sec_q == 0)
		*sec_q = 1;
	else
	{
		*sec_q = 0;
		(count[(int)type])--;
	}
}

void	set_variables(t_values *v, t_quote *q, t_var *var, t_other *other)
{
	var->temp = q->pos;
	var->temp_type = q->type;
	var->temp_z = q->z;
	var->sec_valid_q = false;
	var->v = v;
	other->i = 0;
	other->end = false;
	other->betw_q = false;
}

void	temp_at_return(t_quote *q, t_var *var)
{
	q->pos = var->temp;
	q->type = var->temp_type;
	q->z = var->temp_z;
}

int	y_eq_pos(t_quote *q, t_var *var, t_other *other)
{
	var->sec_valid_q = true;
	q->pos = -1;
	if (other->betw_q == false)
	{
		other->betw_q = true;
		other->y++;
		return (1);
	}
	return (0);
}

void	type_n_sec_valid_true(t_quote *q, t_var *var, t_other *other, int x)
{
	var->sec_valid_q = false;
	if (next_pos(var->v, q, x, other->y) == -1)
		other->end = true;
	other->betw_q = false;
	other->y++;
}
