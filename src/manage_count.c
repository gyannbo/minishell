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

void	manage_tab(t_quote *q)
{
	q->tab[q->z] -= q->decr_tab;
	q->decr_tab = 0;
}


// ON MANAGERA INCREMENTER TAB DANS DCETTE FUNC APRES



void	increment_q_counter_w_tab(size_t *counter, t_quote *q)
{
	size_t temp_next_quote;
	int	z;

	z = q->z;
	temp_next_quote = q->count_next_quote;
	while(temp_next_quote)
	{
		*counter += q->tab[z];
		temp_next_quote--;
		z++;
	}
	*counter += q->tab[z];
}

void	manage_count(t_values *v, t_quote *q)
{
	size_t i;
	bool after_first;

	i = get_right_pos(v, q->count, q->first_type); 		// fait gaffe je dois voir si le i ici c'est direct sur la prochaine quote que l'on doit prendre en compte ou pas.
	after_first = false;
	q->count_next_quote++;
	while (v->cmd_str_b[i] && q->count_next_quote)										// non je suis con en fait je dois utiliser first type pour avoir le bon i, et ensuite je compte les tokens, peut etre je peux utiliser 
	{
		if (v->cmd_str_b[i] == '\'' || v->cmd_str_b[i] == '\"')
		{
			if (after_first)
			{
				after_first = false;
				i++;
				continue;
			}
			(q->count[(int)v->cmd_str_b[i]])++;
			q->count_next_quote--;
			after_first = true;
		}
		i++;
	}
}



// ah ouai mais je dois aussi voir vis a vis du tab, non, parce que je regarde dans la cmd-str_b donc ça va jai pas besoin du tab, jai juste besoin
//d'avoir un count net uote accurate. Parce que je dois quand meme savoir si jamais il y a une env var, si jamais elle "accroche" des couple de quotes
// ou pas (si elle a un espace en elle en gros)
//
//
//
//
//
// verif si type change pas jusqua manage_count comme ça on est sur que le type est le first type, comme ça je peux juste temp le count du type
//
//
//
//
//
//
//
// je crois que jai built tout ce qu'il faut, je dois commit et tout tester a nouveau
