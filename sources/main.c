/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <jterrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:02:56 by jterrell          #+#    #+#             */
/*   Updated: 2020/10/20 19:05:39 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	main(int ac, char **av)
{
	t_data data;

	init_flags(ac, av, &data);
	init_data(&data);
	process_data(&data);
	output_data(&data);
	exit_(OK, &data);
}
