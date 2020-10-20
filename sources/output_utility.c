/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_utility.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <jterrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:04:10 by jterrell          #+#    #+#             */
/*   Updated: 2020/10/20 19:05:20 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	nbr_recursion(int32_t n, char **str)
{
	if (n / 10 > 0)
		nbr_recursion(n / 10, str);
	*(*str)++ = n % 10 + '0';
}

void		ant_name(int32_t n, char *str)
{
	*str++ = 'L';
	nbr_recursion(n, &str);
	*str++ = '-';
	*str = '\0';
}

void		buff_flush(t_data *data)
{
	if (write(STDOUT_FILENO, data->buff_line, data->i_buff) < 0)
		exit_(IOERROR, data);
	data->i_buff = 0;
}

void		buff_fill(const char *src, t_data *data)
{
	char	*buff;

	buff = data->buff_line + data->i_buff;
	while (data->i_buff < BUFF_LINE && *src)
	{
		*buff++ = *src++;
		data->i_buff++;
	}
	if (*src)
	{
		buff_flush(data);
		buff_fill(src, data);
	}
}
