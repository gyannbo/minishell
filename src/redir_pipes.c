/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:18:00 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/25 17:29:06 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_redpip(char *s, size_t *index)
{
	char	type;
	int		i;

	i = 1;
	type = s[0];
	while (s[i])
	{
		if (s[i] == type)
		{
			*index += i + 1;
			return ;
		}
		i++;
	}
	return ;
}

static int	is_pip(t_values *v, char *s, size_t *step)
{
	if (s[0] == '|')
	{
		if (s[1] == '|')
			return (-1);
		if (!ft_strncmp(s, "|>|", 3))
		{
			if (is_redpip(s[3]) == 1)
				return (-1);
			v->redpip_counter += 3;
			(*step) += 3;
			return (1);
		}
		if (is_redir(v, &s[1], step) == true)
		{
			v->redpip_counter++;
			(*step)++;
			return (1);
		}
		return (-1);
	}
	return (0);
}

bool	is_redir(t_values *v, char *s, size_t *step)
{
	if (!(*s))				//to protect wrong array access when is_pip uses this func
		return (true);
	if (s[0] == '<' || s[0] == '>')
	{
		if (s[0] == s[1])
		{
			if (redir_case_equal(v, s, step) == false)
				return (false);
			return (true);
		}
		if (s[0] == '>' && s[1]== '|')
		{
			if (redir_case_r_n_s(v, s, step) == false)
				return (false);
			return (true);
		}
		if (!is_redpip(s[1]) || is_redpip(s[1]) == -1)
		{
			(*step)++;
			v->redpip_counter++;
			return (true);
		}
		return (false);
	}
	return (true);
}

static ssize_t	is_redpip_valid(t_values *v, char *s, size_t *step)
{
	int	status;

	status = is_pip(v, s, step);
	if (status == -1)
		return (-1);
	else if (status == 1)
		return (1);
	if (is_redir(v, s, step) == false)
		return (-1);
	return (1);
}

bool	redpip_token_counter(t_values *v)
{
	size_t	i;
	size_t	step;

	i = 0;
	while (v->cmd_str[i])
	{
		step = 0;
		if (v->cmd_str[i] == '\'' || v->cmd_str[i] == '\"')
		{
			quote_redpip(&v->cmd_str[i], &i);
			continue ;
		}
		if (is_redpip(v->cmd_str[i]))
		{
			if (is_redpip_valid(v, &v->cmd_str[i], &step) != -1)
			{
				i += step;
				continue ;
			}
			v->redpip_counter = 0;
			return (false);
		}
		i++;
	}
	return (true);
}
