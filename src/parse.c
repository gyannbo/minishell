/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:46:48 by msloot            #+#    #+#             */
/*   Updated: 2024/12/17 17:50:47 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	other_quote(t_values *v, char *s, char type)
{
	size_t	i;

	i = 1;
	while (s[i])
	{
		if (s[i] == type)
		{
			if (check_quote(v, &s[++i]) == true)
			{
				v->isquote = 1;
				return (true);
			}
			return (false);
		}
		i++;
	}
	return (false);
}

bool	check_quote(t_values *v, char *s)
{
	size_t	i;

	i = 0;
	v->just_a_check = false;		// içi c'est juste pour une histoire de norm, car je dois initialiser ce flag tot sinon dans l'expand ça va tout péter
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			if (other_quote(v, &s[i], s[i]) == true)
				return (true);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	parse(t_values *values)
{
	char	**split_s;

	values->isquote = 0;
	values->expand_pointer = &values->cmd_str;
	if (check_quote(values, values->cmd_str) == false)
		return (false);
	if (redpip_token_counter(values) == false)
		return (false);
	if (expand(values) == false)
		return (false);
	split_s = ft_split_whitespace(values->cmd_str);
	if (!split_s || !split_s[0])		// !split[0] otherwise segfault if cmd_str is only spaces
	{
		free(values->cmd_str);
		if (split_s)
			free(split_s);
		return (false);
	}
	values->split_s = split_s;
	if (do_quotes(values) == false)
		return (false);
	if (tokenise_redpip(values) == false)
		return (false);
	return (true);
}
