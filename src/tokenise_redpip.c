/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_redpip.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 13:37:15 by gbonis            #+#    #+#             */
/*   Updated: 2024/12/14 13:37:16 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	data_in_tab(t_values *v, t_skip_tok *tab)
{
	(void)v;
	(void)tab;
	return (true);
}

bool	build_tab(t_values *v, t_skip_tok **tab)
{
	*tab = malloc(sizeof(t_skip_tok) * (v->redpip_counter * 2 + 1));
	if (!(*tab))
		return (false);
	ft_bzero(*tab, sizeof(t_skip_tok) * (v->redpip_counter * 2 + 1));
	if (data_in_tab(v, *tab) == false)
		return (false);
	return (true);
}

bool tokenise_redpip(t_values *v)
{
	t_skip_tok *tab;

	if (!v->redpip_counter)
		return (true);
	v->abs_path_bin = NULL;
	v->db_var_count = 0;
	build_tab(v, &tab);
	free(tab);
	return (true);
}



//build tab to ignore wrong token, to do so build token parser

// ah ouai mais il va y avoir un probleme parce que dans les envvar ou quotes ils peut y avoir du gigabullshit et donc je dois pouvoir skip des trucs sans meme pouvuoir reconnaitre ou utiliser le parser de redpip,
// je dois plutot utiliser des strings pour matcher du coup ?
// ouai ça va etre plus compliqué que prévu finalement, meme avec des strings yaurait plein de probleme, sur lol=">>>><   |||>>>' par exemple, juste pour citer ça.
// oui non c'est pas grave en fait je dois juste mettre la data une par une dans quelque chose, y compris la data qui est viable pour les redpip

// peut etre je peux fonctionner comme ça, je met dans un tableau de nombre de charactere de redpip non valide, puis la case d'après si il y a des valides je mets les valides, et ainsi de suite, et normalement
// quand je parserais tout ça ça me suffira, et par exemple meme si ya plusieurs char de redpip valides meme si ils sont espacés ou pas c'est pas grave je peux les mettre dans la meme case du tableau ou quoi


// ah ouai mais attends yaura un probleme non, mon programme doit rejeter du bullshit de redpip meme quand c'est dnas les quotes non ?
// non c'est bon j'y ai déjà pensé.

// ouai aussi et on peut dire que si les tokens sont viables, de redpip, il ne seront ni dans des quotes, ni dans des envvar, donc ça facilite le parsing, ou  alors au moins je sais combien de case le tableau
// a besoin, et après je peux toujours faire un tableau de pointer sur tableau et get la size et malloc tout ça.
// mais après ça veut dire que je dois aussi faire des checks entre chaque redpip valid, non pas besoin pour allouer le tableau, je peux juste mettre des autant des cases que théoriquement besoin meme si ça
// sert a rien j'aurais qu'àmettre NULL dedans et puis voila (je parle du cas oujai quelque chose comme > 'lol' | ou je sais pas si ya quelque chose dans lol ('>lol' par exmple) mais c'est pas grave quand je mettrais
// la data je NULLerais cette partie la et je pense que pour le parsing ça ira

// ensuite pour le reste il reste plus qu'a get size, malloc et put data  et on est bon

// aussi pour ce qui est du parsing de redpip token, je pense que pour faire le tableau je peux juste jumble tous les redpip char ensemble sans les parser.
// ouai non ça me parait plus intelligent d'avoir le parser et de faire une case par token viable, comme ça j'ai pas besoin de build quelque chose qui garde en memoire ou on est dans la string

// attends mais j'ai le token counter donc j'ai meme pas besoin faire tout ça pour le tableau

// ah ouai par contre ya un autre probleme c'est comment je sais que je dois skipper ou prendre en compte pour la génération de token, je pourrais mettre une valeur avant les strings de char, mais ya peutetre 
// une méthode plus simple. pas vraiment chatgpt dit de faire une struct avec un bool, pas bete mais ça va pas changer grand chose.
