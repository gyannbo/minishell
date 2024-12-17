/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redpip_tab_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:37:41 by gbonis            #+#    #+#             */
/*   Updated: 2024/12/17 23:01:05 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	tab_quote_redpip(t_values *v, char *s, size_t *index, t_tab_redpip *tab_redpip)
{
	char	type;
	int		i;
	size_t	step;

	i = 1;
	type = s[0];
	while (s[i])
	{
		step = 0;
		if (s[i] == type)			// ici je dois juste faire quelque chose comme si if type == '"' et après si $ call le code pour les envar
		{
			*index += i + 1;
			return true;
		}
		if (type == '"' && s[i] == '$')
		{
			(*index) += i;		// icic je dois faire ç apour le code d'après sur l'envvar, normalement l'incrémentation se fait auto donc je dois juste "continue" après
			if (expand_for_redpip(v, index, tab_redpip) == false)   // verif ici de l'arythmetic de index + i
				return (false);
			continue ;
		}
		if (is_redpip(s[i]))
		{
			if (tab_is_redpip_valid(&s[i], &step, tab_redpip) != -1)
			{
				i += step;
				continue ;
			}
			v->redpip_counter = 0;
			return (false);
		}
		i++;
	}
	return true;
}

int	tab_is_pip(char *s, size_t *step, t_tab_redpip *tab_redpip)
{
	if (s[0] == '|')
	{
		if (s[1] == '|')
			return (-1);
		if (!ft_strncmp(s, "|>|", 3))
		{
			if (is_redpip(s[3]) == 1)
				return (-1);
			if (allocate_string(s, 3, tab_redpip) == false)
				return (-1);
			(*step) += 3;
			return (1);
		}
		if (tab_is_redir(&s[1], step, tab_redpip) == true)
		{
			if (allocate_string(s, 1, tab_redpip) == false)
				return (false);
			(*step)++;
			return (1);
		}
		return (-1);
	}
	return (0);
}

bool	tab_is_redir(char *s, size_t *step, t_tab_redpip *tab_redpip)
{
	if (!(*s))				//to protect wrong array access when is_pip uses this func
		return (true);
	if (s[0] == '<' || s[0] == '>')
	{
		if (s[0] == s[1])
		{
			if (tab_redir_case_equal(s, step, tab_redpip) == false)
				return (false);
			return (true);
		}
		if (s[0] == '>' && s[1] == '|')
		{
			if (tab_redir_case_r_n_s(s, step, tab_redpip) == false)
				return (false);
			return (true);
		}
		if (!is_redpip(s[1]) || is_redpip(s[1]) == -1)
		{
			if (allocate_string(s, 1, tab_redpip) == false)
				return (false);
			(*step)++;
			return (true);
		}
		return (false);
	}
	return (true);
}

int	tab_is_redpip_valid(char *s, size_t *step, t_tab_redpip *tab_redpip)
{
	int	status;

	status = tab_is_pip(s, step, tab_redpip);
	if (status == -1)
		return (-1);
	else if (status == 1)
		return (1);
	if (tab_is_redir(s, step, tab_redpip) == false)
		return (-1);
	return (1);
}
