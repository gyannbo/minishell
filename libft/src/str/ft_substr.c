/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 10:36:12 by msloot            #+#    #+#             */
/*   Updated: 2024/03/04 16:13:44 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, size_t start, size_t len)
{
	size_t	new_len;
	char	*ret;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup("\0"));
	new_len = ft_strlen(&s[start]);
	if (len < new_len)
		new_len = len;
	ret = (char *)malloc(sizeof(char) * (new_len + 1));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, &s[start], new_len + 1);
	return (ret);
}
