/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <jterrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:03:20 by jterrell          #+#    #+#             */
/*   Updated: 2020/10/20 19:05:35 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	msg_help(void)
{
	int		fd;
	char	*line;

	fd = open("./resources/help", O_RDONLY);
	while (ft_gnl(fd, &line) > 0)
	{
		ft_dprintf(STDERR_FILENO, "%s\n", line);
		free(line);
	}
	close(fd);
	exit(0);
}
