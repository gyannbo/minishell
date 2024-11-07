/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:36:38 by msloot            #+#    #+#             */
/*   Updated: 2024/03/04 17:30:01 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ret;

	ret = (char *)malloc(sizeof(char) * (ft_strlen((char *)s) + 1));
	if (!ret)
		return (NULL);
	ft_strcpy(ret, s);
	return (ret);
}
