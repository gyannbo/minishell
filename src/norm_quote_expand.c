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

void	check_for_invalid_envvar(t_values *v, size_t *i, size_t *i_tab)
{
	(*i)++;
	while (v->cmd_str_b[(*i)] != '\"')
	{
		if (v->cmd_str_b[(*i)] == '$')
			(*i_tab)++;
		(*i)++;
	}
	(*i)++;
}

int	d_manage_quote(t_values *v, size_t *i, size_t *i_tab)
{
	check_for_invalid_envvar(v, i, i_tab);
	return (0);
}

void	check_special_char(t_values *v, size_t *i, int *tab)
{
	int	x;
	char a;

	x = *i;
	a = v->cmd_str_b[x + 1];
	if (!ft_isalnum(a) && a != '_' && a != '?')
		(*tab)++;
}

void	check_for_singles(t_values *v, size_t *i, size_t *i_tab, int **tab)
{
	if (v->cmd_str_b[(*i)] == '\'')
	{
		(*i)++;
		while (v->cmd_str_b[(*i)] != '\'')
		{
			if (v->cmd_str_b[(*i)] == '$')
				((*tab)[(*i_tab)])++;
			(*i)++;
		}
	}
}

char	*get_prev_name(t_values *v)
{
	int	i;
	bool	betw_quotes;
	int	count;

	i = 0;
	count = v->db_var_count;
	betw_quotes = false;
	while(v->cmd_str_b[i])
	{
		if (v->cmd_str_b[i] == '"')
			betw_quotes = !betw_quotes;
		if (v->cmd_str_b[i] == '$' && !count && betw_quotes)
			return (&v->cmd_str_b[i]);
		else if (v->cmd_str_b[i] == '$' && count && betw_quotes)
			count--;
		i++;
	}
	return (NULL);
}
