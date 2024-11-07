/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 20:11:09 by msloot            #+#    #+#             */
/*   Updated: 2024/04/04 21:01:17 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef WITH_OPEN

# include "libft.h"

ssize_t	count_line(const char *path)
{
	int		fd;
	char	*line;
	ssize_t	count;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_puterr("could not open the file ");
		ft_putstr_fd(Y_B_MAG, STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(Y_RESET, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		return (-1);
	}
	line = get_next_line(fd);
	count = 0;
	while (line != NULL)
	{
		free(line);
		count++;
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

#endif
