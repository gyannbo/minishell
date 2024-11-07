/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_any_of.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 11:53:23 by msloot            #+#    #+#             */
/*   Updated: 2024/05/13 22:33:19 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strlen_until_sep(const char *str, const char *sep)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && !ft_is_in(sep, str[i]))
		i++;
	return (i);
}

static void	ft_skip(const char *str, size_t *i, const char *sep, bool in)
{
	while (str[*i] != '\0' && in == ft_is_in(sep, str[*i]))
		*i += 1;
}

static bool	process_word(char **split,
						ssize_t split_i,
						const char *str,
						char *sep)
{
	if (!split)
		return (true);
	split[split_i] = ft_strndup(str, ft_strlen_until_sep(str, sep));
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

static ssize_t	process(char **split, const char *str, char *sep)
{
	ssize_t	split_i;
	size_t	i;

	split_i = 0;
	i = 0;
	while (str[i] != '\0')
	{
		ft_skip(str, &i, sep, true);
		if (str[i] != '\0')
		{
			if (!process_word(split, split_i, &str[i], sep))
				return (-1);
			split_i++;
		}
		ft_skip(str, &i, sep, false);
	}
	return (split_i);
}

char	**ft_split_any_of(char const *str, char *sep)
{
	char	**ret;
	size_t	word_count;

	if (!str)
		return (NULL);
	word_count = process(NULL, str, sep);
	ret = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!ret)
		return (NULL);
	if (process(ret, str, sep) == -1)
		return (NULL);
	ret[word_count] = NULL;
	return (ret);
}
