/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:58:59 by msloot            #+#    #+#             */
/*   Updated: 2024/06/19 22:02:56 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

inline size_t	ft_umin(size_t a, size_t b)
{
	if (a < b)
		return (a);
	return (b);
}

inline ssize_t	ft_min(ssize_t a, ssize_t b)
{
	if (a < b)
		return (a);
	return (b);
}
