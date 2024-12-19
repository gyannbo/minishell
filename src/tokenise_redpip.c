/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_redpip.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 13:37:15 by gbonis            #+#    #+#             */
/*   Updated: 2024/12/19 23:53:17 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	expand_for_redpip(t_values *v, size_t *i, t_tab_redpip *tab_redpip)
{
	int	status;

	v->tab_redpip = tab_redpip;		// DO NOT FORGET TO SET TO NULL AT EXIT ?  // je pense que c'est pas grave comme c'est set a chaque fois ici, normalement ya pas de risque quon utilise du bullshit
	v->just_a_check = true;
	v->expand_pointer = NULL;
	status = do_retval(v, &v->cmd_str_b[(*i)], i);
	if (status == 1)
	{
		v->just_a_check = false;
		return (true);			//verifier / test
	}
	if (status == -1)
	{
		v->just_a_check = false;
		return (false);
	}
	else 
	{
		v->indice_redpip = i;
		if (do_expand(v, &v->cmd_str_b[(*i)], i) == false)
		{
			v->just_a_check = false;
			return (false);
		}
	}
	v->just_a_check = false;
	return (true);
}

bool	data_in_tab(t_values *v, t_tab_redpip *tab_redpip)
{
	size_t	i;
	size_t	step;

	i = 0;
	while (v->cmd_str_b[i])
	{
		step = 0;
		if (v->cmd_str_b[i] == '\'' || v->cmd_str_b[i] == '\"')
		{
			tab_redpip->valid = false;
			if (tab_quote_redpip(v, &v->cmd_str_b[i], &i, tab_redpip) == false)
				return (false);
			continue ;
		}
		if (is_redpip(v->cmd_str_b[i]))
		{
			tab_redpip->valid = true;
			if (tab_is_redpip_valid(&v->cmd_str_b[i], &step, tab_redpip) != -1)
			{
				i += step;
				continue ;
			}
			v->redpip_counter = 0;
			return (false);
		}
		if(v->cmd_str_b[i] == '$')
		{
			tab_redpip->valid = false;
			if (expand_for_redpip(v, &i, tab_redpip) == false)
				return (false);
			continue ;			// c'est bon ici ?
		}
		i++;
	}
	return (true);
}

bool	build_tab(t_values *v, t_tab_redpip *tab_redpip)
{
	tab_redpip->tab = malloc(sizeof(t_skip_tok) * (v->redpip_counter * 2 + 2));		// + 2 c'est pour allouer le end après la dernière "case"
	if (!(tab_redpip->tab))
		return (false);
	ft_bzero(tab_redpip->tab, sizeof(t_skip_tok) * (v->redpip_counter * 2 + 2));
	tab_redpip->tab[v->redpip_counter * 2 + 1].end = true;
	tab_redpip->tab[0].skip = true;
	if (data_in_tab(v, tab_redpip) == false)
		return (false);
	return (true);
}

bool tokenise_redpip(t_values *v)
{
	t_tab_redpip tab_redpip;
	size_t	i;

	i = 0;
	if (!v->redpip_counter)
		return (true);
	tab_redpip.i = 0;
	tab_redpip.valid = false;	// prob pas besoin de ça
	v->abs_path_bin = NULL;
	v->db_var_count = 0;
	build_tab(v, &tab_redpip);
//	tokeniser();
	while (tab_redpip.tab[i].end != true)
	{
		if (tab_redpip.tab[i].s)
			free(tab_redpip.tab[i].s);
		i++;
	}
	free(tab_redpip.tab);
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




//--------------------------------


// Donc la maintenant en gros pour faire le tableau je vais devoir avoir un parser de redpip
// je rappelle, on part du postulat que si ça va jusqu'a la fonction tokenize redpip c'est que les redpip tok sont valide (oui, ceux dans les quotes ou envvar ne bloqueront pas le programme si ils sont invalides)




// je pense que je peux très probablement reprendre totalement le code de mon parsing pour le redpip counter, en changeant juste pour qu'il remplisse le tab et en plus qu'il check aussi les envvar pour des characteres de token
// (je vais devoir faire des counter de redpip char pour les envvar, et globalement aussi pour les quotes, enfin tout ce qui est redpip invalide, afin de pouvoir malloc les strings.

// ce serati pas une bonne idée de faire pas en mode fosse commune pour les invalides ? Non je pense que ce sera pas trop difficile d'avoir deux indices, un peu la cmd_str_b et un autre pour la strings dans le tab.
// Non je pense que c'est pas mal de fonctionner comme ça parce que je pourrais skipper les chars des invalides, par contre quand ça sera un valid normalement ce sera déjà parsé, ouai et puis je pense que c'est pas
// mal de malloc le tab comme ça, plutot que d'aller voir si ya ou pas des invalides entre les valides.

// en fiat je viens de me dire que comme ça j'ai meme pas besoin vraiment de mettre le contenu des valides ? je peux juste mettre pas skip et faire confiance à la fonction qui va parser ? Après honnêtement c'est pas
// mal d'avoir les strings déjà prête comme ça je peux direct mettre les pointeurs dans la tokenised strings sans remalloc quelque chose.

// ouai je pense que c'est pas mal de fonctionner comme ça, j'aurais pas besoin de faire un "cehcksum" des viables contrairement aux non viables car je ferais confiance au parser. Comme j'aurais le parser pour incrémenter
// ainsi que le fait que pour les valides j'aurais une case par token contrairement aux invalides.




// TO DO

// regarder si je peux réutiliser les fonctions pour le redpip counter
// si c'est le cas build pour checker les envvar aussi, puis changer les fonctions pour mettre dans le tab plutot que incrémenter le redpip counter, et il faudra aussi changer les fonctions sur les quotes pour pas qu'eller
// skip totalement mais regarder dedans pour les redpip char eventuels








// ah ouai mais il y a un probleme, si jamais il y a des redpip non valide avantdes valides par exemple dans des quotes, puis après dans une envvar, puis après des valides, ça veut dire que je vais devoir realloc la string
// si ya déjà quelque chose dedans ?
// ouai comme je dois checker pour deux choses différentes, l'intérieur des env var ainsi que dans les quotes (d'ailleurs quand on est dans les quotes je dois pas checker l'interieur si ya des envvar, mais si en fait merde,
// parce que si ya une envvar dans une double ça va se retrouver dans les token de split mais il faudra pas que je l'interprête ? Donc je dois faire une fonction spéciale dans les double quotes ? normalement je peux utiliser
// les fonctions de check pour les envar normalement et puis voila, mais par contre je vais toujours devoir avoir une fonction qui check si ya deja quelque chose dans la string et donc calculer la size et realloc tout ça etc..



// pour manipuler les tab je peux peutetre faire une structure qui enveloppe tout et qui posséde aussi les indices qu'on utilise pour accéder à la structure aussi, juste pour gagner de la place sur les arguments pour la norme.
// J'allais dire que j'ai pas besoin d'indice, car si jamais je dois refaire une string pour mettre des non valides j'ai pas besoin d'indice je dois juste faire size. Par contre je dois avoir un indice pour savoir ou je suis 
// dans le tableau.
// J'allais dire que j'ai pas besoin d'indice, car si jamais je dois refaire une string pour mettre des non valides j'ai pas besoin d'indice je dois juste faire size. Par contre je dois avoir un indice pour savoir ou je suis 
// dans le tableau.




// dans allocate string je devrais probalement avoir un booleen qui me dit c'est une skippable ou pas afin de savoir dans quelle case du tableau je mets les choses.



// en fait pour parler de comment je vais incrémenter l'indice du tableau, je pense que simplement dès que j'arrive sur un redpip tok valid, j'incrémente avant et puis après sur la sortie une fois que j'ai fait le travail.
// Ouai, je pense que faire comme ça ça va fonctionner.





// VERIFIER QUE LE BZERO SET BIEN TOUT A ZERO UNE FOIS QUE LE PROGRAMME POURRA COMPILER CETTE PARTIE.
