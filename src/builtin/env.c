/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:09:00 by msloot            #+#    #+#             */
/*   Updated: 2024/11/05 11:21:59 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i] && envp[i + 1] != NULL)
	{
		ft_putendl_fd(envp[i], STDOUT_FILENO);
		i++;
	}
	if (envp[i])
		ft_putendl_fd(envp[i], STDOUT_FILENO);
	return (EX_OK);
}
