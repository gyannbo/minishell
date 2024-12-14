/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:05:10 by gbonis            #+#    #+#             */
/*   Updated: 2024/11/01 17:10:48 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sig(int	*sig, t_values *v)
{
	if (*sig == 1)
		v->prev_ret_val = 130;
	if (*sig == 2)
		v->prev_ret_val = 131;	// 131 set only if ^\ interrupt a binary (in second if (sig in handle_cmd_str, not the first one)
	*sig = 0;
}

static bool	abs_path_in_values(t_values *values)
{
	values->abs_path_bin = get_abs_path(values);
	if (!values->abs_path_bin)
	{
		ft_free_2d((void ***)&values->split_s,
			ft_2d_size((const void **)values->split_s));
		free(values->cmd_str);
		return (false);
	}
	return (true);
}

static bool	get_struct_values(t_values *values)
{
	if (abs_path_in_values(values) == false)
		return (false);
	return (true);
}

bool	handle_cmd_str(t_values *v)
{
	extern int	g_sig;

	if (g_sig == 1 || g_sig < 0)
	{
		handle_sig(&g_sig, v);
		return (false);				// return here because if given "ls ^C" ls will be executed, when it shouldnt be
	}
	v->redpip_counter = 0;
	if (!parse(v))
		return (false);
	if (!exec_builtin(v))
		return (false);
	if (!get_struct_values(v))
		return (false);
	exec(v);
	v->redpip_counter = 0;
	if (v->abs_path_bin)	// should put all this in a handle_parse_exit()
	{
		if (!ft_strchr(*v->split_s, '/'))			// if rel path, needed to append exec to path, so need to free only in this case, otherwise it is freed in split_s later
			free(v->abs_path_bin);
	}
	ft_free_2d((void ***)&v->split_s,
		ft_2d_size((const void **)v->split_s));
	free(v->cmd_str);
	if (g_sig)			// need to check on exit also for an edge case (if g_sig is caught while a bin is running, then a call to readline would fail after and also $? wouldn't be accurate)
		handle_sig(&g_sig, v);
	return (true);
}
