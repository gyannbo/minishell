/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:56:31 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/25 17:34:47 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_retval(t_values *v, char *s, size_t *i)
{
	char	*c_retval;

	if (s[1] == '?')
	{
		c_retval = ft_itoa(v->prev_ret_val);
		if (!c_retval)
			return (false);
		if (put_in_string(v->expand_pointer, c_retval, i, 1) == false)
		{
			free(c_retval);
			return (-1);
		}
		free(c_retval);
		return (1);
	}
	return (0);
}

size_t	get_len_till_eq(char *s)
{
	size_t	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i] != '=')
		i++;
	return (i);
}

static void	copy_end(char *dest, char *from)
{
	int	i;

	i = 0;
	while (from[i])
	{
		dest[i] = from[i];
		i++;
	}
}

static void	copy_until(char *dest, char *from, size_t pos)
{
	size_t	i;

	i = 0;
	while (pos)
	{
		dest[i] = from[i];
		pos--;
		i++;
	}
}

bool	put_in_string(char **s, char *var, size_t *pos, int s_n_var)
{
	char	*new;
	size_t	s_var;
	size_t	s_s;
	size_t	tmp_pos;

	tmp_pos = *pos;
	s_var = ft_strlen(var);
	s_s = ft_strlen(*s);
	if ((*s)[tmp_pos] != '$')
		return (false);
	new = malloc(sizeof(char) * (s_s - (s_n_var + 1) + s_var + 1));
	copy_until(new, *s, tmp_pos);
	copy_until(&new[tmp_pos], var, s_var);
	copy_end(&new[tmp_pos + s_var], &(*s)[tmp_pos + s_n_var + 1]);
	free(*s);
	*pos = tmp_pos + s_var;
	new[s_s - (s_n_var + 1) + s_var] = 0;
	*s = new;
	return (true);
}
