/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:43:49 by msloot            #+#    #+#             */
/*   Updated: 2023/11/21 19:57:16 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_i;
	size_t	dst_i;
	size_t	src_len;
	size_t	dst_len;

	src_len = ft_strlen(src);
	if (dst)
		dst_len = ft_strlen(dst);
	else
		dst_len = 0;
	dst_i = dst_len;
	src_i = 0;
	if (dst_len < size - 1 && size > 0)
	{
		while (dst_len + src_i < size - 1 && src[src_i] != '\0')
		{
			dst[dst_i] = src[src_i];
			dst_i++;
			src_i++;
		}
		dst[dst_i] = '\0';
	}
	if (dst_len >= size)
		dst_len = size;
	return (dst_len + src_len);
}
