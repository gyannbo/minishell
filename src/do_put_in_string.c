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
		if (put_in_string(&v->cmd_str, "", i, size_name_var) == false)
			return (false);
		return (true);
	}
	expand = get_expand(v->env[index]);
	if (!expand)
		return (false);
	if (put_in_string(&v->cmd_str, expand, i, size_name_var) == false)
	{
		free(expand);
		return (false);
	}
	free(expand);
	return (true);
}
