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

static int	has_type(char *s, char *type, size_t *quote_counter)
{
	size_t	i;
	bool	flag;

	flag = false;
	i = 0;
	if (!s)				// for NULL term
		return (-1);
	while (s[i])
	{
		if (*quote_counter % 2 == 0 && *quote_counter)
		{
			if (s[i] == '\'' || s[i] == '\"')
				*type = s[i];
		}	
		if (s[i] == *type)
		{
			flag = true;
			if (*quote_counter)
				(*quote_counter)--;				// faire gaffe ici a cause du type peut etre probleme si decrementé mais == 0;
		}
		i++;
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

static size_t	free_useless_tok(t_values *v, size_t x, t_quote *q)		//ATTENTION JE DOIS CHANGER LE TYPE LORSQUE YA QUOTE COUNTER > 0 // ouai aussi faudra voir sur le changement de type en fonction des skip de tab
{
	int	res;
	size_t quote_counter;

	quote_counter = 0;	
	if (q->count_next_quote)
		quote_counter = (q->count_next_quote * 2) + 1; // +1 because second quote of first quote, otherwise last token not freed
	if (q->two_type)
		quote_counter++;
	x++;
	res = has_type(v->split_str[x], &q->type, &quote_counter);
	while (!res || quote_counter)  // will have to add tab check for env var (just put the value in quote counter with q->count i guess
	{
		free(v->split_str[x]);
		x++;
		res = has_type(v->split_str[x], &q->type, &quote_counter);
	}
	free(v->split_str[x]);
	(void)q;
	return (x);
}

static size_t	move_tokens(t_values *v, size_t x, size_t sec_q_tok)
{
	sec_q_tok++;
	x++;
	if (!(v->split_str[x]))
		return (x);
	while (v->split_str[sec_q_tok])			//with multiple quote in single tok this func becomes more complicated, because between quote can be env var quotes, so i should use tab, but first build withut envar suport
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
	if (has_two_types(&old_tok[q->pos], q->type, q))		// this only needs to check with the tab (for envvar quotes), if the count in a single split token is two, i think this func is alright. Anyway dont touch this for now, well see when envvar testing multiple quotes in sinlge token and multiple tok
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
//	q->x = sec_q_tok - 1;
	q->two_type = false;
	return ;
}
