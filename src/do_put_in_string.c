/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_put_in_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:42:07 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/25 17:11:33 by msloot           ###   ########.fr       */
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
