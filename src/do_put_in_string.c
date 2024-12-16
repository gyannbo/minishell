/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_put_in_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:42:07 by gbonis            #+#    #+#             */
/*   Updated: 2024/12/16 23:52:19 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	do_put_in_string(t_values *v, char *var, size_t *i, int size_name_var)
{
	char	*expand;
	size_t	index;

	if (check_var_exist(v, var, &index) == false)
	{
		if (put_in_string(v->expand_pointer, "", i, size_name_var) == false)
			return (false);
		return (true);
	}
	expand = get_expand(v->env[index]);
	if (!expand)
		return (false);
	if (v->just_a_check)
	{
		
		// ATTENTION ICI JE DOIS MANAGER L'INCREMENTATION DU I SUR LA SIZE DU NOM DE LA VAR // probablement ce sera quelque chose comme size_var + 1 (pour aller après la size var parce que j'utilise jamais cette valeur pour une incrementation cest tj pour dautre chose (acces tableaux etc) afin d'avoir le i sur le charactere apres la var (attenation a pas s'emmeler les pinceaux entre ce qui est la avant et ce qui serala après lorsque le parsing des quotes est terminé
		// ici je peux peut etre réutiliser le code du tableau, je devrais pouvoir, le seul truc c'est de mettre redpip_tab dans v pour communiquer entre les code path
		free(expand);
		return (true);		// check with this early return to see if no prob, dont forget to initialise this flag to false before parsing, normalement pas de prob sur early return et les free
	}
	if (put_in_string(v->expand_pointer, expand, i, size_name_var) == false)
	{
		free(expand);
		return (false);
	}
	free(expand);
	return (true);
}

void	do_at_exit(char *new, t_values *v)
{
	free(v->cmd_str);
	free(v->cmd_str_b);
	v->cmd_str = new;
}

bool	cut_dollar(t_values *v, size_t *i)
{
	char	*new;
	size_t	y;
	size_t	z;

	y = 0;
	z = 0;
	if (*v->expand_pointer != v->cmd_str)
	{
		(*i)++;
		return (true);
	}
	new = malloc(sizeof(char) * ft_strlen(v->cmd_str));
	if (!new)
		return (false);
	while (v->cmd_str[y])
	{
		if (z == *i)
		{
			z++;
			continue ;
		}
		new[y] = v->cmd_str[z];
		y++;
		z++;
	}
	do_at_exit(new, v);
	v->cmd_str_b = ft_strdup(new);
	if (!v->cmd_str_b)
		return (false);
	return (true);
}
