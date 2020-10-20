/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utility.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <jterrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:02:47 by jterrell          #+#    #+#             */
/*   Updated: 2020/10/20 19:05:41 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int32_t	atoi_lem_in(char *str)
{
	uint64_t	x;

	x = 0;
	while (*str && x <= INT32_MAX)
		x = (x << 3) + (x << 1) + *str++ - '0';
	if (x > INT32_MAX)
		return (-1);
	else
		return (x);
}

int32_t			get_num(char *str, t_data *data)
{
	char	*tmp;
	int32_t	num;

	tmp = str;
	if (!tmp || !*tmp)
		exit_(NUMBER_ERROR, data);
	while (*tmp)
		if (!ft_isdigit(*tmp++))
			exit_(NUMBER_ERROR, data);
	if ((num = atoi_lem_in(str)) < 0)
		exit_(NUMBER_ERROR, data);
	return (num);
}

uint64_t		count_ch(char *str, char ch)
{
	uint64_t	i;

	i = 0;
	while (*str)
	{
		if (*str == ch)
			i++;
		str++;
	}
	return (i);
}

uint64_t		count_words(char **words)
{
	uint64_t	i;

	i = 0;
	if (words)
		while (words[i])
			i++;
	return (i);
}

bool			comment(t_data *data)
{
	return (LINE[0] == '#');
}
