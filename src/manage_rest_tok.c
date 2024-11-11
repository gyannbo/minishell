/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_rest_tok.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:15:35 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/25 16:26:58 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_type(char *s, char *type, size_t *quote_counter, t_quote *q)
{
	size_t	i;
	bool	flag;
	int temp_z;
	int temp_value;
	size_t temp_c_n_quote;

	flag = false;
	temp_z = q->z;
	temp_value = q->tab[temp_z];
	temp_c_n_quote = q->count_next_quote;
	i = 0;
	if (!s)				// for NULL term
		return (-1);
	before_tok(q, &i, quote_counter, s);
	if (*type != s[i])
	{
		if (q->q_before_tok % 2 == 0 && q->has_b_tok)
			*type = s[i];
	}
	while (s[i])
	{
		if (*quote_counter % 2 == 0 && *quote_counter)
		{
			if (s[i] == '\'' || s[i] == '\"')
				*type = s[i];
		}	
		if (s[i] == *type)   // apparemment ici c'est quand on est sur la deuxieme quote directement que je dois passer la, jsp pk je suis pas dessus avec les espaces
		{
			if (temp_c_n_quote && *quote_counter % 2 != 0)
			{
				skip_non_v_quote(s, &temp_value, quote_counter, &i);
				temp_z++;
				temp_value = q->tab[temp_z];		//normalement pour ça j'ai pas besoin de faire de if ou quoi que ce soit, car le seul moment ou jai besoin de switcher le z c'est quand on a completement passé les quotes de l'env var, car si c'est pas le cas normalement la fonction sarrete. et comme les variables que jutilise son auto pas besoin de gerer une sortie que peux juste les incr comme ça
				temp_c_n_quote--;
			}
			flag = true;
			if (*quote_counter)
			{
				(*quote_counter)--;
			}
		}
		i++;
		if (*type != s[i])
		{
			if (q->q_before_tok % 2 == 0 && q->has_b_tok)
				*type = s[i];
		}
	}
	if (flag)
		return (1);
	return (0);
}

static int	has_two_types(char *s, char type, t_quote *q)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == type)
		{
			if (count == 1)
			{
				if (q->count_next_quote)
				{
					q->x--;
					q->two_type = true;
					return(0);
				}
				return (1);
			}
			else
				count++;
		}
		i++;
	}
	return (0);
}

static size_t	free_useless_tok(t_values *v, size_t x, t_quote *q)
{
	int	res;
	size_t quote_counter;

	quote_counter = 0;
	if (q->count_next_quote)
		quote_counter = (q->count_next_quote * 2) + 1; // +1 because second quote of first quote, otherwise last token not freed
	if (q->two_type)
		quote_counter++;
	increment_q_counter_w_tab(&quote_counter, q);
	x++;
	res = has_type(v->split_str[x], &q->type, &quote_counter, q);
	while ((!res || quote_counter) && v->split_str[x])
	{
		free(v->split_str[x]);
		x++;
		res = has_type(v->split_str[x], &q->type, &quote_counter, q);
	}
	if (!v->split_str[x] && quote_counter)
		return (x - 1);
	free(v->split_str[x]);
	return (x);
}

static size_t	move_tokens(t_values *v, size_t x, size_t sec_q_tok)
{
	sec_q_tok++;
	x++;
	if (!(v->split_str[x]))
		return (x);
	while (v->split_str[sec_q_tok])
	{
		v->split_str[x] = v->split_str[sec_q_tok];
		sec_q_tok++;
		x++;
	}
	return (x);
}
void	manage_rest_tok(t_values *v, char *new_tok, t_quote *q)
{
	size_t	sec_q_tok;
	size_t	last_viable_tok;
	size_t	tmp;
	char	*old_tok;

	old_tok = v->split_str[q->x];
	if (has_two_types(&old_tok[q->pos], q->type, q))
	{
		v->split_str[q->x] = new_tok;
		free(old_tok);
		return ;
	}
	sec_q_tok = free_useless_tok(v, q->x, q);
	if (q->two_type)
		q->x++;
	else
		free(old_tok);
	last_viable_tok = move_tokens(v, q->x, sec_q_tok);
	tmp = last_viable_tok;
	v->split_str[tmp] = NULL;
	while (v->split_str[last_viable_tok])
	{
		free(v->split_str[last_viable_tok]);
		last_viable_tok++;
	}
	v->split_str[q->x] = new_tok;
	q->two_type = false;
}
