/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redpip_tab_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:37:41 by gbonis            #+#    #+#             */
/*   Updated: 2024/12/15 18:37:51 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tab_quote_redpip(char *s, size_t *index, t_tab_redpip *tab_redpip)
{
	char	type;
	int		i;

	i = 1;
	type = s[0];
	while (s[i])
	{
		if (s[i] == type)							//ouai ici plutot que rien faire rajouter un check pour les char redpip, peut etre juste la fonction is redpip_valid ca suffit je sais pas.
		{
			*index += i + 1;
			return ;
		}
		i++;
	}
	return ;
}

int	tab_is_pip(t_values *v, char *s, size_t *step, t_tab_redpip *tab_redpip)
{
	if (s[0] == '|')
	{
		if (s[1] == '|')
			return (-1);
		if (!ft_strncmp(s, "|>|", 3))
		{
			if (tab_is_redpip(s[3]) == 1)
				return (-1);
			if (allocate_string(s, 3, tab_redpip) == false)
				return (-1);		// ici je peux juste mettre -1 parce que c'est le code pour return le programme, la seul difference avec le code pour le redpip counter c'est que la lorsque je call le code pour le tab je dois juste mettre le free plus haut dans les fun call quand ça renvoie -1
//			v->redpip_counter += 3;			// mettre ici fonction qui check si ya deja une strings et sinon qui append
			(*step) += 3;
			return (1);
		}
		if (tab_is_redir(v, &s[1], step) == true)
		{
			v->redpip_counter++;
			(*step)++;
			return (1);
		}
		return (-1);
	}
	return (0);
}

bool	tab_is_redir(t_values *v, char *s, size_t *step, t_tab_redpip *tab_redpip)
{
	if (!(*s))				//to protect wrong array access when is_pip uses this func
		return (true);
	if (s[0] == '<' || s[0] == '>')
	{
		if (s[0] == s[1])
		{
			if (tab_redir_case_equal(v, s, step) == false)
				return (false);
			return (true);
		}
		if (s[0] == '>' && s[1] == '|')
		{
			if (tab_redir_case_r_n_s(v, s, step) == false)
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

int	tab_is_redpip_valid(t_values *v, char *s, size_t *step, t_tab_redpip *tab_redpip)
{
	int	status;

	status = tab_is_pip(v, s, step, tab_redpip);
	if (status == -1)
		return (-1);
	else if (status == 1)
		return (1);
	if (tab_is_redir(v, s, step, tab_redpip) == false)
		return (-1);
	return (1);
}
