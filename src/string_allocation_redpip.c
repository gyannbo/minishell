/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_allocation_redpip.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:36:27 by gbonis            #+#    #+#             */
/*   Updated: 2024/12/23 00:09:43 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	allocate_string(char *s, int amount, t_tab_redpip *tab_redpip)
{
	size_t	size;
	char	*temp;

	size = 0;
	if (tab_redpip->valid == true)
	{
		(tab_redpip->i)++;
		tab_redpip->tab[tab_redpip->i].skip = false;
	}
	else
		tab_redpip->tab[tab_redpip->i].skip = true;
	if (!tab_redpip->tab[tab_redpip->i].s)
	{
		tab_redpip->tab[tab_redpip->i].s = malloc(sizeof(char) * (amount + 1));		// faire un bout de code pour gérer le placement dans le tableau en fonction de si c'est un token valide ou pas
		if (!tab_redpip->tab[tab_redpip->i].s)
			return (false);
		ft_memcpy(tab_redpip->tab[tab_redpip->i].s, s, amount);
		tab_redpip->tab[tab_redpip->i].s[amount] = 0;
		if (tab_redpip->valid)
			(tab_redpip->i)++;	// attention c'est faux ici je pense il faut incr seulement quand tab_redpip
		return (true);
	}
	size = ft_strlen(tab_redpip->tab[tab_redpip->i].s);
	temp = malloc(sizeof(char) * (amount + size  + 1));
	if (!temp)
		return (false);	
	ft_memcpy(temp, tab_redpip->tab[tab_redpip->i].s, size);								// Bien retester tout ça quand ça compilera c'est tellement un bordel tout ce qu'il se passe içi
	ft_memcpy(&temp[size], s, amount);
	temp[size + amount] = 0;
	free(tab_redpip->tab[tab_redpip->i].s);
	tab_redpip->tab[tab_redpip->i].s = temp;
	//if (tab_redpip->valid == true)		// normalement j'ai pas besoin de ça ici, car le true vont forcément passer dans le if en haut
//		(tab_redpip->i)++;
	return (true);
}
