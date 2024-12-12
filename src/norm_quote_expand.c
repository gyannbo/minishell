/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_quote_expand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:17:33 by gbonis            #+#    #+#             */
/*   Updated: 2024/11/19 13:17:38 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_for_invalid_envvar(t_values *v, size_t *i, int *tab_val)
{
	(*i)++;
	while (v->cmd_str_b[(*i)] != '\'')
	{
		if (v->cmd_str_b[(*i)] == '$')
			(*tab_val)++;
		(*i)++;
	}
	(*i)++;
}

int	d_manage_quote(t_values *v, size_t *i, int *tab_val, size_t *i_tab)
{
	if (v->cmd_str_b[(*i)] == '\'')
	{
		check_for_invalid_envvar(v, i, tab_val);
		return (1);
	}
	quote_redpip(&v->cmd_str_b[(*i)], i);
	(*i_tab)++;
	return (0);
}

void	check_special_char(t_values *v, size_t *i, int *tab)
{
	int	x;

	x = *i;
	if (!ft_isalnum(v->cmd_str_b[x + 1]) && v->cmd_str_b[x + 1] != '_')
		(*tab)++;
}
