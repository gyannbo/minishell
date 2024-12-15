/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redpip_tab_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 15:35:29 by gbonis            #+#    #+#             */
/*   Updated: 2024/12/15 15:35:31 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	tab_redir_case_equal(t_values *v, char*s, size_t *step)
{
	if (s[1])
	{
		if (is_redpip(s[2]) == 1)
			return (false);
	}
	v->redpip_counter += 1;
	(*step) += 2;
	return (true);
}

bool	tab_redir_case_r_n_s(t_values *v, char *s, size_t *step)
{
	if (is_redpip(s[2]) == 1)
		return (false);
	(*step) += 2;
	v->redpip_counter += 2;
	return (true);
}
