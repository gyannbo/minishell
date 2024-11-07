/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 11:53:23 by msloot            #+#    #+#             */
/*   Updated: 2024/03/06 18:09:24 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strlen_until_sep(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

static bool	process_word(char **split, ssize_t split_i, const char *s, char c)
{
	if (!split)
		return (true);
	split[split_i] = ft_strndup(s, ft_strlen_until_sep(s, c));
	if (split[split_i])
		return (true);
	split_i--;
	while (split_i >= 0)
	{
		free(split[split_i]);
		split_i--;
	}
	free(split);
	return (false);
}

static ssize_t	process(char **split, const char *s, char c)
{
	ssize_t	split_i;
	size_t	i;

	split_i = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			if (!process_word(split, split_i, &s[i], c))
				return (-1);
			split_i++;
		}
		while (s[i] != '\0' && s[i] != c)
			i++;
	}
	return (split_i);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	size_t	word_count;

	if (!s)
		return (NULL);
	word_count = process(NULL, s, c);
	ret = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!ret)
		return (NULL);
	if (process(ret, s, c) == -1)
		return (NULL);
	ret[word_count] = NULL;
	return (ret);
}
