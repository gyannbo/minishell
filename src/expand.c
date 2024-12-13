/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:12:53 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/25 17:31:23 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var(char *s, size_t *size)
{
	char	*var;
	size_t	i;
	size_t	y;

	i = 0;
	while (ft_isalnum(s[i]) || s[i] == '_')
		i++;
	if (ft_isdigit(s[0]))
		i = 1;
	var = malloc(sizeof(char) * (i + 1));
	if (!var)
		return (NULL);
	y = 0;
	while (i)
	{
		var[y] = s[y];
		i--;
		y++;
	}
	*size = i;
	var[y] = 0;
	return (var);
}

bool	check_var_exist(t_values *v, char *var, size_t *index)
{
	int	i;

	i = 0;
	while (v->env[i])
	{
		if (!ft_strncmp(var, v->env[i],
				get_len_till_eq(v->env[i])) && !ft_strncmp(var, v->env[i],
				ft_strlen(var)))
		{
			*index = i;
			free(var);
			return (true);
		}
		i++;
	}
	free(var);
	return (false);
}

char	*get_expand(char *s)
{
	char	**split;
	char	*temp;

	split = ft_split(s, '=');
	if (!split)
		return (NULL);
	temp = split[1];
	free(split[0]);
	free(split);
	if (!temp)
	{
		temp = malloc(sizeof(char) * 2);
		if (!temp)
			return (NULL);
		temp[0] = ' ';
		temp[1] = 0;
	}
	return (temp);
}

bool	do_expand(t_values *v, char *s, size_t *i)
{
	char	*var;
	size_t	size_name_var;

	if (s[1] == '\"' || s[1] == '\'')
	{
		if (cut_dollar(v, i) == false)
			return (false);
		return(true);
	}
	var = get_var(&s[1], &size_name_var);
	if (!var)
		return (false);
	if (!var[0])
	{
		free(var);
		(*i)++;
		return (true);
	}
	size_name_var = ft_strlen(var);
	if (do_put_in_string(v, var, i, size_name_var) == false)
		return (false);
	return (true);
}

bool	expand(t_values *v)
{
	size_t	i;
	int		status;

	i = 0;
	while (v->cmd_str[i])
	{
		if (v->cmd_str[i] == '\'' || v->cmd_str[i] == '\"')
		{
			quote_redpip(&v->cmd_str[i], &i);
			continue ;
		}
		if (v->cmd_str[i] == '$')
		{
			status = do_retval(v, &v->cmd_str[i], &i);
			if (status == 1)
				continue ;
			if (status == -1)
				return (false);
			else if (do_expand(v, &v->cmd_str[i], &i) == false)
				return (false);
			continue ;
		}
		i++;
	}
	return (true);
}
