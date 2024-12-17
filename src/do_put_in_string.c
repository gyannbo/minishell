/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_put_in_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:42:07 by gbonis            #+#    #+#             */
/*   Updated: 2024/12/17 22:25:50 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	redpip_expand_check(t_values *v, char *s, t_tab_redpip *tab_redpip)
{
	size_t	y;
	size_t	step;

	y = 0;
	step = 0;
	while (s[y])
	{
		if (is_redpip(s[y]))
		{
			if (tab_is_redpip_valid(&s[y], &step, tab_redpip) != -1)
			{
				y += step;
				continue ;
			}
			v->redpip_counter = 0;
			return (false);
		}
		y++;
	}
	return (true);
}

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
		if (redpip_expand_check(v, var, v->tab_redpip) == false)			// protec ?
			return (false);
		(*i) += size_name_var + 1;   // verif ça
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
	if (*v->expand_pointer != v->cmd_str)				// noter ça quelque part. Dans ce cas la il n'y a que lors de l'expand normal que je dois faire quelque chose, pour les doubles quote je ne dois pas le faire, et pour le tab redpip bien sur je ne dois changer aucune string
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
