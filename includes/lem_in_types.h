/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <jterrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:07:36 by jterrell          #+#    #+#             */
/*   Updated: 2020/10/20 19:37:26 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_TYPES_H
# define LEM_IN_TYPES_H

# define BUFF_LINE	32192
# define BUFF_ANT	16

# define BH_LEFT(i)		(((i) << 1) + 1)
# define BH_RIGHT(i)	(((i) << 1) + 2)
# define BH_PARENT(i)	(((i) - 1) / 2)

typedef struct s_node	t_node;

typedef struct		s_point
{
	int32_t			x;
	int32_t			y;
}					t_point;

typedef struct		s_room
{
	char			*name;
	t_point			coord;
	t_node			*origin;
	t_node			*primed;
	bool			is_path;
}					t_room;

typedef struct		s_link
{
	t_node			*n;
	int32_t			w;
}					t_link;

struct				s_node
{
	t_room			*r;
	t_array			*links;
	t_array			*links_saved;
	int32_t			dist;
	struct s_node	*d_pred;
	struct s_node	*pred;
	struct s_node	*succ;
	t_link			*itself;
};

typedef struct		s_set
{
	t_array			*paths;
	int32_t			length;
	int32_t			iter;
	int32_t			div;
	int32_t			mod;
}					t_set;

typedef	struct		s_chk_crd
{
	uint64_t		crd;
	t_room			*r;
}					t_chk_crd;

typedef struct		s_ant
{
	char			name[BUFF_ANT];
	int32_t			r;
}					t_ant;

typedef struct		s_path
{
	t_room			**rooms;
	t_ant			*ants;
	int32_t			n_rooms;
	int32_t			n_ants;
	int32_t			n_s_ants;
	int32_t			n_f_ants;
	int32_t			i_ant;
}					t_path;

typedef struct		s_data
{
	int32_t			n_ants;
	t_array			*rooms;
	t_room			*start_room;
	t_room			*end_room;
	int32_t			error_r;
	double			n_ants_average;
	t_set			*best_set;
	t_set			*curr_set;
	t_set			*prev_set;
	char			**words;
	t_lst_ht		*input;
	char			buff_line[BUFF_LINE];
	uint64_t		i_buff;
	int16_t			flags;
	t_array			*heap;
}					t_data;

#endif
