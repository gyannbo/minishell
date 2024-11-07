/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:16:27 by gbonis            #+#    #+#             */
/*   Updated: 2024/11/05 17:27:08 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handl_z(int x)
{
	x++;
}

char	*set_ret_val(t_values *values)
{
	values->prev_ret_val = 127;
	return (NULL);
}

bool	compare_exec_to_entry(char *executable, char *entry, DIR *directory)
{
	if (!ft_strcmp(executable, entry))
	{
		closedir(directory);
		return (true);
	}
	return (false);
}

void	free_cut_n_close_dir(char **cut, DIR *directory)
{
	free(cut[0]);
	free(cut[1]);
	free(cut);
	closedir(directory);
	return ;
}

bool	separate(char ***result, char *executable, int temp)
{
	(*result)[0] = ft_strndup(executable, temp + 2);
	if (!(*result)[0])
		return (false);
	(*result)[0][temp + 1] = 0;
	(*result)[1] = ft_strdup(executable + (temp + 1));		// do not change this, this is pointer arithm
	if (!result[1])
	{
		free((*result)[0]);
		free(*result);
		return (false);
	}
	return (true);
}
