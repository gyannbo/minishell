/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_pipes_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:06:55 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/25 17:21:44 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redpip(char c)
{
	if (!c)
		return (-1);
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

// this function is unused
int	pip_case_s(t_values *v, char *s, size_t *step)
{
	if (is_redir(v, &s[2], step) == true)
	{
		if (s[2] == '|')
			return (-1);
		v->redpip_counter += 2;
		(*step) += 2;
		return (1);
	}
	return (-1);
}

bool	redir_case_equal(t_values *v, char*s, size_t *step)
{
	if (s[1])
	{
		if (is_redpip(s[2]) == 1)
			return (false);
	}
	v->redpip_counter += 1;
	(*step) += 2;
	return (true);
}

bool	redir_case_r_n_s(t_values *v, char *s, size_t *step)
{
	if (is_redpip(s[2]) == 1)
		return (false);
	(*step) += 2;
	v->redpip_counter += 2;
	return (true);
}
