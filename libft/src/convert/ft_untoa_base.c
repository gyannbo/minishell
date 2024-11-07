/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_untoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 12:31:06 by msloot            #+#    #+#             */
/*   Updated: 2023/11/21 19:57:16 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_untoa_base(size_t n, const t_base *b)
{
	char	*ret;
	size_t	n_len;

	n_len = ft_unbrlen_base(n, b->len);
	ret = (char *)malloc(sizeof(char) * (n_len + 1));
	if (!ret)
		return (NULL);
	return (ft_unbr_convert_base(ret, n, n_len, b));
}
