/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:19:30 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/02 15:20:53 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// split PATH string into char ** to be usable ///

static char	**split_env_path(void)
{
	char		**split;
	char		*path;

	path = getenv("PATH");
	if (!path)
		return (NULL);
	split = ft_split(path, ':');
	if (!split)
		return (NULL);
	return (split);
}

///  getting absolute path of executable for execve() ///

char	*get_abs_path(t_values *values)
{
	char	**paths;
	char	*dir;

	paths = split_env_path();					// no protection here, because still need to go to search dir func, protection is there	// keep this right until eval, i will forget why i did this otherwise
	dir = search_for_dir(values, paths, *values->split_s);
	if (!dir)
	{
		ft_free_2d((void ***)&paths, ft_2d_size((const void **)paths));
		return (NULL);
	}
	ft_free_2d((void ***)&paths, ft_2d_size((const void **)paths));
	return (dir);
}
