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

void	quote_redpip_tab_amt(char *s, size_t *index, size_t *tab_amt)
{
	char	type;
	int		i;

	i = 1;
	type = s[0];
	while (s[i])
	{
		if (s[i] == '$')
			(*tab_amt)++;
		if (s[i] == type)
		{
			*index += i + 1;
			return ;
		}
		i++;
	}
	return ;
}

bool	change_spl_tok(t_values *v, size_t x, size_t *y, int *i)
{
	int	status;

	(*i)++;								// ouai je pense que ça fonctionne pas avec l'incrémentation automatique du i ici, si les $ sont dans le meme token on fait quoi, ou alors peut etre que le tab fonctionne comme ça ? checker. (si pour chaque $ ya une case alors ca va
	v->expand_pointer = &v->split_s[x];
	status = do_retval(v, &v->split_s[x][(*y)], y);
	if (status == 1)
		return (true);
	if (status == -1)
		return (false);
	else if (do_expand(v, &v->split_s[x][(*y)], y) == false)
		return (false);
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
				{
					y++;
					tab[i]--;
				}
				else if (change_spl_tok(v, x, &y, &i) == false)
					return (false);
				continue ;
			}
			y++;
		}
		x++;
	}
	return (true);
}


// pour l'instant aller au bon token
// copier dans le token

// yes but what happens when there is something like "$HOME$HOME"
// ça veut peut etre dire que je dois incrémenter le y de size name var ou quelque chose comme ça, parce que
// sinon si ya un autre $ dans la var ça va etre interprété.


// faire attention il faut aussi gerer le $?


// ouai normalement je peux reprendre le code de ce que j'ai fait avant, car si je me débrouille bien ça va juste
// rewrite le token et voila.
