/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:28:34 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/25 16:12:57 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_q_expand(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			count++;
		i++;
	}
	return (count);
}

static bool	put_in_counter(t_values *v, char *s, size_t *i, int *tab)
{
	char	*var;
	size_t	index;
	char	*expand;
	size_t	name_size;

	var = get_var(&s[1], &name_size);
	if (!var)
		return (false);
	if (check_var_exist(v, var, &index) == false)
	{
		(*i)++;
		return (true);		// return false only for malloc fail
	}
	expand = get_expand(v->env[index]);
	if (!expand)
		return (false);
	*tab += count_q_expand(expand);
	free (expand);
	return (true);
}

static bool	allocate_tab(t_values *v, int **tab)
{
	size_t	i;
	size_t	tab_amt;

	i = 0;
	tab_amt = 1;
	while (v->cmd_str_b[i])
	{
		if (v->cmd_str_b[i] == '\'' || v->cmd_str_b[i] == '\"')
		{
			quote_redpip(&v->cmd_str_b[i], &i);
			tab_amt++;
			continue ;
		}
		i++;
	}
	*tab = malloc(sizeof(int) * (tab_amt + 1));
	if (!(*tab))
		return (false);
	ft_bzero(*tab, sizeof(int) * tab_amt);
	(*tab)[tab_amt] = -1;
	return (true);
}

static bool	get_counter(t_values *v, int **tab)
{
	size_t	i;
	size_t	i_tab;

	i = 0;
	i_tab = 0;
	if (allocate_tab(v, tab) == false)
		return (false);
	while (v->cmd_str_b[i])
	{
		if (v->cmd_str_b[i] == '\'' || v->cmd_str_b[i] == '\"')
		{
			quote_redpip(&v->cmd_str_b[i], &i);
			i_tab++;
			continue ;
		}
		if (v->cmd_str_b[i] == '$')			//je dois juste regarder si ya des quotes dans les env var et leurs nombres
		{
			if (!put_in_counter(v, &v->cmd_str_b[i], &i, &(*tab)[i_tab]))
				return (false);
		}
		i++;
	}
	return (true);
}

bool	do_quotes(t_values *values)
{
	int	*tab;

	tab = NULL;
	if (values->isquote == 0)
		return (true);
	if (get_counter(values, &tab) == false)
		return (false);
	if (quote_parsing(values, tab) == false)
		return (false);
	free(tab);
	values->isquote = 0;
	return (true);
}

