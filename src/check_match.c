/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_match.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:36:38 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/25 17:49:28 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check(t_values *values, char *path)
{
	struct stat	s_stat;

	if (!path)
		return (NULL);
	if (stat(path, &s_stat))
		return (NULL);
	if (!S_ISREG(s_stat.st_mode))
	{
		values->prev_ret_val = 126;
		return (NULL);
	}
	if (access(path, X_OK) == -1)
	{
		values->prev_ret_val = 126;
		return (NULL);
	}
	return (path);
}

char	*is_dir(t_values *values, char *path)
{
	struct stat	s_stat;

	if (!path)
		return (NULL);
	if (stat(path, &s_stat))
	{
		values->prev_ret_val = 127;
		return (NULL);
	}
	if (S_ISREG(s_stat.st_mode))				// need to have this when ./a.out ad no perm to have right $?
	{
		values->prev_ret_val = 126;
		return (NULL);
	}
	if (S_ISDIR(s_stat.st_mode))
	{
		values->prev_ret_val = 126;
		return (NULL);
	}
	values->prev_ret_val = 127;
	return (NULL);
}

// should just check if return 126 on /./././././ and 127 on no existing file

