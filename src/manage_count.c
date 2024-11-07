/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:36:03 by gbonis            #+#    #+#             */
/*   Updated: 2024/11/04 14:36:09 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_count(t_quote *q)
{
//	size_t i;
//
//	i = 0;
//	while (cmd_str_b[i])
//	{
//		if (q->cmd_str_b[i] == '\'' || q->cmd_str_b[i] == '\"')
//			q->type == q->cmd_str_b[i];
//			
//
//	
//		
	(void)q;			// this func to increment count[] between calls to manage_q_tok with mutltiplt valid tquotes token
}



// ah ouai mais je dois aussi voir vis a vis du tab, non, parce que je regarde dans la cmd-str_b donc ça va jai pas besoin du tab, jai juste besoin
//d'avoir un count net uote accurate. Parce que je dois quand meme savoir si jamais il y a une env var, si jamais elle "accroche" des couple de quotes
// ou pas (si elle a un espace en elle en gros)
