/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:19:24 by gbonis            #+#    #+#             */
/*   Updated: 2024/11/19 11:19:25 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	d_count_q_expand(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '$')
			count++;
		i++;
	}
	return (count);
}

bool	d_put_in_counter(t_values *v, char *s, size_t *i, int *tab)
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
		check_special_char(v, i, tab);
		return (true);
	}
	expand = get_expand(v->env[index]);
	if (!expand)
		return (false);
	*tab += d_count_q_expand(expand);
	free (expand);
	return (true);
}

bool	d_allocate_tab(t_values *v, int **tab)
{
	size_t	i;
	size_t	tab_amt;

	i = 0;
	tab_amt = 1;
	while (v->cmd_str_b[i])
	{
		if (v->cmd_str_b[i] == '\"')
		{
			quote_redpip_tab_amt(&v->cmd_str_b[i], &i, &tab_amt);
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

static bool	d_get_counter(t_values *v, int **tab)
{
	size_t	i;
	size_t	i_tab;

	i = 0;
	i_tab = 0;
	if (d_allocate_tab(v, tab) == false)
		return (false);
	while (v->cmd_str_b[i])
	{
		if (v->cmd_str_b[i] == '\"')
		{
			d_manage_quote(v, &i, &i_tab);
			continue ;
		}
		check_for_singles(v, &i, &i_tab, tab);
		if (v->cmd_str_b[i] == '$')
		{
			if (!d_put_in_counter(v, &v->cmd_str_b[i], &i, &(*tab)[i_tab]))
				return (false);
		}
		i++;
	}
	return (true);
}

bool	quote_expand(t_values *v)
{
	int	*tab;

	tab = NULL;
	if (!d_get_counter(v, &tab))
		return (false);
	if (do_quote_expand(v, tab) == false)    // gerer la protection
	{
		free(tab);
		v->expand_pointer = NULL;
		return (false);
	}
	v->expand_pointer = NULL;
	free(tab);
	return (true);
}
