/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:46:48 by msloot            #+#    #+#             */
/*   Updated: 2024/10/25 17:20:26 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	other_quote(t_values *v, char *s, char type)
{
	size_t	i;

	i = 1;				// one here because otherwise it is on the quote if it found it
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
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			if (other_quote(v, &s[i], s[i]) == true)
				return (true);
			return (false);			// careful this false return is only for testing  // IMPORTANT: if I kept comments like this it is because I didnt check thoroughly enough and planned to do it later
		}
		i++;
	}
	return (true);
}

bool	parse(t_values *values)
{
	char	**split_str;

	values->isquote = 0;
	if (check_quote(values, values->cmd_str) == false)	// this function check if quotes are valid or not in the whole cmd_str
		return (false);
	if (redpip_token_counter(values) == false)
		return (false);
	if (expand(values) == false)
		return (false);
	split_str = ft_split_whitespace(values->cmd_str);
	if (!split_str || !split_str[0])		// !split[0] otherwise segfault if cmd_str is only spaces
	{
		free(values->cmd_str);
		if (split_str)
			free(split_str);
		return (false);
	}
	values->split_str = split_str;
	if (do_quotes(values) == false)
		return (false);
//	if (tokenise_redpip(values) == false)
//		return (false);
	return (true);
}
