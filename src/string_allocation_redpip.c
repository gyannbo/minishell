/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_allocation_redpip.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:36:27 by gbonis            #+#    #+#             */
/*   Updated: 2024/12/15 18:36:28 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	allocate_string(char *s, int amount, t_tab_redpip *tab_redpip) 
{
	size_t	size;
	char	*temp;

	size = 0;
	if (!tab_redpip->tab[tab_redpip->i]->s)
	{
		tab_redpip->tab[tab_redpip->i]->s = malloc(sizeof(char) * (amount + 1));
		if (!tab_redpip->tab[tab_redpip->i]->s)
			return (false);
		ft_memcpy(tab_redpip->tab[tab_redpip->i]->s, s, amount);
		tab_redpip->tab[tab_redpip->i]->s[amount] = 0;
		return (true);
	}
	size = ft_strlen(tab_redpip->tab[tab_redpip->i]->s);
	temp = malloc(sizeof(char) * (amount + size  + 1);
	if (!temp)
		return (false);	
	ft_memcpy(temp, tab_redpip->tab[tab_redpip->i]->s, size);								// Bien retester tout ça quand ça compilera c'est tellement un bordel tout ce qu'il se passe içi
	ft_memcpy(&temp[size], s, amount);
	temp[size + amount] = 0;
	free(tab_redpip->tab[tab_redpip->i]->s);
	tab_redpip->tab[tab_redpip->i]->s = temp;
}




// je peux build maintenant un malloc dans le tab, mais je dois faire gaffe à pas oublier de build aussi un moyen de check si ya pas déjà quelque chose dans la string.


// Et aussi maintenant que j'y pense je dois faire gaffe à initialiser bien tout mes flags dans les struc skip_ , normalement je suis censé les set quand je fait le 
// tableau mais on sait jamais.

// Ah ouai mais meme pas, je devrais init tout a zéro, comme ça je peux juste check vite fait si ya déjà un pointeur dans la struct c'est plus simple
// (normalement c'est bon parce que j'ai fait bzero sur toutes les structs
