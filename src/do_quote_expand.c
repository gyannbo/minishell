/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_quote_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:52:11 by gbonis            #+#    #+#             */
/*   Updated: 2024/12/12 18:52:21 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	change_spl_tok(t_values *v, size_t x, int *i)
{
	(*i)++;
	(void)v;
	(void)x;
	return (true);
}

bool	do_quote_expand(t_values *v, int *tab)
{
	size_t x;
	size_t y;
	int	i;

	x = 0;
	i = 0;
	while(v->split_s[x])
	{
		y = 0;
		while(v->split_s[x][y])
		{
			if (v->split_s[x][y] == '$')
			{
				if (tab[i])
					tab[i]--;
				else if (change_spl_tok(v, x, &i) == false)
					return (false);
			}
			y++;
		}
		x++;
	}
	return (true);
}


// pour l'instant aller au bon token
// copier dans le token
