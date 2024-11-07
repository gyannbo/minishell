/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:03:10 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/25 16:56:20 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// when relative path, need to append exec name to dir if exec ///
/// found in a dir.											    ///

static char	*append_exec_to_path(char *exec_dir, char *executable)
{
	char	*appended;
	size_t	size_dir;
	size_t	size_exec;

	if (!ft_strcmp(".", executable))		// special case, . is a builtin (source), just return this otherwise segfault (won't have the same $? as in bash but this is not required)
		return (executable);
	size_dir = ft_strlen(exec_dir);
	size_exec = ft_strlen(executable);
	appended = malloc(sizeof(char) * (size_dir + size_exec + 2));
	if (!appended)
		return (NULL);
	ft_memcpy(appended, exec_dir, size_dir);
	ft_memcpy(&appended[size_dir + 1], executable, size_exec);
	appended[size_dir] = '/';
	appended[size_dir + size_exec + 1] = 0;
	return (appended);
}

/// cut the dir part of the string (../../.),from the exec name ///

static char	**cut_exec_string(char *executable)
{
	char	**result;
	ssize_t	tmp;
	size_t	i;

	i = 0;
	tmp = -1;
	result = malloc(sizeof(char *) * 2);
	if (!result)
		return (NULL);
	while (executable[i])
	{
		if (executable[i] == '/')
			tmp = i;
		i++;
	}
	if (tmp == -1)
	{
		free(result);
		return (NULL);
	}
	if (!separate(&result, executable, tmp))
		return (NULL);
	return (result);
}

static char	*search_abs_path(t_values *values, char *executable)
{
	DIR				*directory;
	struct dirent	*dirent;
	char			**cut;

	cut = cut_exec_string(executable);
	if (!cut)
		return (NULL);
	directory = opendir(cut[0]);			// if there is an error there, just dont set prev_ret_val, or to -1 idk
	if (!directory)
	{
		free_cut_n_close_dir(cut, directory);
		return (NULL);
	}
	dirent = readdir(directory);
	while (dirent)
	{
		if (!ft_strcmp(cut[1], dirent->d_name))
		{
			free_cut_n_close_dir(cut, directory);
			return (check(values, executable));
		}
		dirent = readdir(directory);
	}
	free_cut_n_close_dir(cut, directory);
	return (is_dir(values, executable));					/// problem with /././././././ i should somehow use the check func
}

static char	*search_relative_path(char **env_pths, char *executable)
{
	DIR				*directory;
	struct dirent	*dirent;
	size_t			i;

	i = 0;
	while (env_pths[i])
	{
		directory = opendir(env_pths[i]);
		if (directory == NULL)
		{
			i++;
			continue ;
		}
		dirent = readdir(directory);
		while (dirent)
		{
			if (compare_exec_to_entry(executable, dirent->d_name, directory))
				return (env_pths[i]);
			dirent = readdir(directory);
		}
		closedir(directory);
		i++;
	}
	return (NULL);			///should set prev_ret_val to 127 if nothing found
}

/// two possibilities: relative path (use PATH), or absolute (cut the ///
/// dir and then search trough it)									 ///

char	*search_for_dir(t_values *values, char	**env_pths, char	*executable)
{
	char	*exec_dir;
	char	*append;

	if (ft_strchr(executable, '/'))
	{
		if (!ft_strcmp("/", executable))
			return (check(values, executable));
		exec_dir = search_abs_path(values, executable);		// here exec_dir is actually the abs path
		if (exec_dir == NULL)
			return (is_dir(values, executable));				//func here in the return
		return (exec_dir);
	}
	else
	{
		if (!env_pths)
			return (NULL);
		exec_dir = search_relative_path(env_pths, executable);
		if (exec_dir == NULL)
			return (set_ret_val(values));			// func here in the return to gain some lines ?
		append = append_exec_to_path(exec_dir, executable);					// mettre check ici
		if (!check(values, append))				// append is protected in check
			return (NULL);
		return (append);
	}
	return (exec_dir);
}
