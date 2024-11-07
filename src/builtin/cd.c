/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:42:45 by msloot            #+#    #+#             */
/*   Updated: 2024/11/01 17:17:48 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(size_t argc, char **argv, char **envp)
{
	int	ret;

	ret = 0;
	if (argc > 2)
		return (error(argv[0], "too many arguments"), EX_ERR);
	if (argc == 1)
		// direct current position to HOME
	ret = chdir(argv[1]);
	if (ret == -1)
		return (perror(argv[0]), EX_ERR);
	return (EX_OK);
	// update pwd to the new location
	(void)envp; // compile
}
