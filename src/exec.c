/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 14:39:26 by gbonis            #+#    #+#             */
/*   Updated: 2024/11/01 17:10:50 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	exec_builtin(t_values *v)
{
	if (!builtin(ft_2d_size((const void **)v->split_s), v->split_s, v->env))
		return (false);
	return (true);
}

int	exec(t_values *v)
{
	pid_t		pid;
	int			status;
	extern int	g_sig;

	pid = fork();
	if (pid == -1)		// check this for potential mistakes, I did this quickly without trying to have robust code.
		return (0);
	else if (pid == 0)
	{
		if (execve(v->abs_path_bin, v->split_s, v->env) == -1)
		{
			if (v->abs_path_bin)
			{
				if (!ft_strchr(*v->split_s, '/'))			// all of this is the same "free" code as parse(), it is to protect everything is execve fail (the child proc would still run and mess everything)(happens is given a bin without the perms)
					free(v->abs_path_bin);
			}
			ft_free_2d((void ***)&v->split_s,
				ft_2d_size((const void **)v->split_s));
			free(v->cmd_str);
		}
		rl_clear_history();
		exit (0);
	}
	else
	{
		if (!ft_strcmp(v->abs_path_bin, "./minishell"))		// g_signals for minishell in minishell
			g_sig = -2;
		else
			g_sig = -1;		// for signals special cases functions in order to manage cat<enter><signal> adequately
		waitpid(-1, &status, 0);
		if (!ft_strcmp(v->abs_path_bin, "./minishell"))			// g_signals for minishell in minishell
			g_sig = 0;
		v->prev_ret_val = WEXITSTATUS(status);
	}
	return (0);
}
