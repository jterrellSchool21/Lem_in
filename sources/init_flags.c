/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <jterrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:02:07 by jterrell          #+#    #+#             */
/*   Updated: 2020/10/20 19:05:48 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_flags(int ac, char **av, t_data *data)
{
	data->flags = 0;
	while (--ac)
	{
		if (ft_strequ(av[ac], "-h"))
			msg_help();
		else if (ft_strequ(av[ac], "-v"))
			data->flags |= VERBOSE;
		else if (ft_strequ(av[ac], "-t"))
			data->flags |= PATHS_NUM;
		else if (ft_strequ(av[ac], "-p"))
			data->flags |= SHOW_PATHS;
		else if (ft_strequ(av[ac], "-i"))
			data->flags |= IGNORE_LINKS;
		else if (ft_strequ(av[ac], "-x"))
			data->flags |= OMMIT_INPUT;
		else if (ft_strequ(av[ac], "-xx"))
			data->flags |= OMMIT_ALL;
		else
			msg_usage();
	}
}
