/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unbr_convert_base.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:10:20 by msloot            #+#    #+#             */
/*   Updated: 2023/11/21 19:57:16 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// n_len is the calculated len of n in base b
// it should be calculated thanks to ft_nbrlen_base
char	*ft_unbr_convert_base(
	char *dst,
	size_t n,
	size_t n_len,
	const t_base *b
)
{
	if (n == 0)
	{
		dst[0] = b->base[0];
		dst[1] = '\0';
		return (dst);
	}
	dst[n_len] = '\0';
	n_len--;
	while (n != 0)
	{
		dst[n_len] = b->base[n % b->len];
		n /= b->len;
		n_len--;
	}
	return (dst);
}
