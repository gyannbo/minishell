/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redpip_tab_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 15:35:29 by gbonis            #+#    #+#             */
/*   Updated: 2024/12/16 19:53:01 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	tab_redir_case_equal(char *s, size_t *step, t_tab_redpip *tab_redpip)
{
	if (s[1])
	{
		if (is_redpip(s[2]) == 1)
			return (false);
	}
	if (allocate_string(s, 1, tab_redpip) == false)
		return (false);
	//v->redpip_counter += 1;
	(*step) += 2;
	return (true);
}

bool	tab_redir_case_r_n_s(char *s, size_t *step, t_tab_redpip *tab_redpip)
{
	if (is_redpip(s[2]) == 1)
		return (false);
	(*step) += 2;
	if (allocate_string(s, 2, tab_redpip) == false)
		return (false);
	//v->redpip_counter += 2;
	return (true);
}
