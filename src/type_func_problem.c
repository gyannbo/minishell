/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_func_problem.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:24:32 by gbonis            #+#    #+#             */
/*   Updated: 2024/11/10 18:24:37 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void before_tok(t_quote *q, size_t *i, size_t *quote_counter, char *s)
{
	if (!q->count_next_quote)
	{
		*quote_counter -= q->q_before_tok;				//special case when q begin tok but no count next quote, need to ignore this func, otherwise wrong return on has_type
		return ;
	}
	while(s[(*i)] && q->q_before_tok)			//a priori les q_begin_tok sont forcément dans le meme split que les valid quotes
	{
		if (s[(*i)] == '\'' || s[(*i)] == '\"')
		{
			q->q_before_tok--;
			(*quote_counter)--;
		}
		(*i)++;
	}
}
