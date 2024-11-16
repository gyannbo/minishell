/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_manage_rest_tok.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 19:11:54 by gbonis            #+#    #+#             */
/*   Updated: 2024/11/16 19:12:10 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	at_exit_free_useless(t_values *v, t_quote *q, int last_viable_tok, char *new_tok)
{
	while (v->split_s[last_viable_tok])
	{
		free(v->split_s[last_viable_tok]);
		last_viable_tok++;
	}
	v->split_s[q->x] = new_tok;
	q->two_type = false;
}

int	next_q_exist(t_quote *q)
{
	if (q->count_next_quote)
	{
		q->x--;
		q->two_type = true;
		return (1);
	}
	return (0);
}
