/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <jterrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:07:41 by jterrell          #+#    #+#             */
/*   Updated: 2020/10/20 19:36:29 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include <stdbool.h>
# include "libft.h"
# include "lem_in_types.h"

# define VERBOSE		0x1
# define PATHS_NUM		0x2
# define SHOW_PATHS		0x4
# define IGNORE_LINKS	0x8
# define OMMIT_INPUT	0x10
# define OMMIT_ALL		0x20

# define IOERROR		-3
# define GNL_ERROR		-2
# define MEMORY_ERROR	-1

# define OK				0

# define NUMBER_ERROR	1
# define SROOM_ERROR	2
# define EROOM_ERORR	3
# define NAME_ERROR		4
# define RBLOCK_ERROR	5
# define DROOM_ERROR	6
# define DCOORD_ERROR	7
# define IUNDEF_ERROR	8
# define LNAME1_ERROR	9
# define LNAME2_ERROR	10
# define LITSELF_ERROR	11
# define LEXISTS_ERROR	12
# define GRAPH_ERROR	13

# define DEFAULT_R		1024
# define DEFAULT_L		32
# define DEFAULT_P		32

# define START			data->start_room
# define END			data->end_room
# define LINE			((char*)data->input->tail->data)
# define ROOM(i)		((t_room*)data->rooms->data[(i)])
# define N_ROOMS		data->rooms->len

# define PRIMED			(origin->r->primed)
# define SUCC			(origin->succ)

/*
** INIT
*/

void		init_flags(int ac, char **av, t_data *data);
void		init_data(t_data *data);
void		init_prepare(t_data *data);
bool		init_ants(t_data *data);
bool		init_rooms(t_data *data);
bool		init_links(t_data *data);

void		init_ants_check(t_data *data);
void		init_rooms_check(t_data *data);
void		init_coord_check(t_data *data);
void		init_simple_check(t_data *data);

void		init_line_process(t_data *data, bool (*func)(t_data*));

/*
** INIT UTILITY
*/

int32_t		get_num(char *str, t_data *data);
uint64_t	count_ch(char *str, char ch);
uint64_t	count_words(char **words);
bool		comment(t_data *data);
t_room		*find_room(t_array *ar, char *name);

/*
** PROCESS
*/

void		process_data(t_data *data);
void		process_prepare(t_data *data);
void		process_mod_graph(t_data *data);
void		process_rest_graph(t_data *data);
bool		process_bhandari(t_data *data);
bool		process_dijkstra(t_data *data);
void		process_save_set(t_data *data);
void		process_choose_set(t_data *data);

/*
** PROCESS UTILITY
*/

int32_t		min_iter(t_data *data);
void		backtrack(t_data *data, void (*func)(t_node*, t_data*));

/*
** OUTPUT
*/

void		output_data(t_data *data);
void		output_prepare(t_data *data);
void		output_input(t_data *data);
bool		output_line(t_data *data);
void		output_short(t_data *data);

/*
** OUTPUT EXTRA
*/

void		show_paths(t_data *data);
void		show_total_0(void);
void		show_total_1(t_data *data);
void		show_total(t_data *data);

/*
** OUTPUT UTILITY
*/

void		ant_name(int32_t n, char *str);
void		buff_fill(const char *src, t_data *data);
void		buff_flush(t_data *data);

/*
** MESSAGES
*/

void		msg(int status, t_data *data);
void		msg_success(t_data *data);
void		msg_help(void);
void		msg_usage(void);
void		msg_error(int status, t_data *data);
void		msg_error_number(t_data *data);
void		msg_error_start_room(t_data *data);
void		msg_error_end_room(t_data *data);
void		msg_error_room_name(t_data *data);
void		msg_error_input_udefined(t_data *data);
void		msg_error_no_name1(t_data *data);
void		msg_error_no_name2(t_data *data);
void		msg_error_link_itself(t_data *data);
void		msg_error_link_exists(t_data *data);
void		msg_error_rooms_block(t_data *data);
void		msg_error_duplicate_room(t_data *data);
void		msg_error_duplicate_coord(t_data *data);
void		msg_error_graph(t_data *data);
void		msg_error_last_line(t_data *data);

/*
** ROOM
*/

void		room_add(t_data *data);
void		room_del(void *r);

/*
** NODE
*/

t_node		*node_new(t_room *r, uint32_t n_links);
void		node_del(t_node *n);

/*
** LINK
*/

t_link		*link_new(t_node *n, int32_t w);
void		link_add(t_room *r1, t_room *r2, int32_t w, t_data *data);
bool		link_exists(t_room *r1, t_room *r2);

/*
** PATH
*/

void		path_del(void *p);
void		*path_convert(void *p0);

/*
** SET
*/

t_set		*set_new(void);
void		set_del(t_set *s);

/*
** CMP
*/

int			cmp_names(void *r1, void *r2);
int			cmp_dist(void *n1, void *n2);
int			cmp_crd(void *crd1, void *crd2);
int			cmp_links(void *l1, void *l2);

/*
** UTILITY
*/

void		exit_(int status, t_data *data);
void		data_del(t_data *data);
void		words_del(char ***words);
t_lst		*lst_new(void *data);
void		lst_add(t_lst **first, t_lst *new);
void		lst_add_after(t_lst *prev, t_lst *new);
void		lst_del(t_lst **first, void (*del)(void*));
int			lst_push(t_lst **head, void *data);
void		*lst_pop(t_lst **head);
t_lst_ht	*lst_ht_new(void);
int			lst_ht_push(t_lst_ht *x, void *data);
int			lst_ht_push_back(t_lst_ht *x, void *data);
void		*lst_ht_pop(t_lst_ht *x);
void		lst_ht_del(t_lst_ht *x, void (*del)(void*));
void		lst_ht_clear(t_lst_ht *x, void (*del)(void*));
t_dlst		*dlst_new(void *data);
void		dlst_add_before(t_dlst *cur, t_dlst *new);
void		dlst_add_after(t_dlst *cur, t_dlst *new);
void		dlst_disconnect(t_dlst *cur);
void		dlst_del(t_dlst **head, void (*del)(void*));
void		dlst_init(t_dlst_cir *x);
int			dlst_cir_push(t_dlst_cir *x, void *data);
void		*dlst_cir_pop(t_dlst_cir *x);
t_array		*ar_new(uint32_t cap, void (*del)(void*));
int			ar_extend(t_array *ar, uint32_t extra_cap);
int			ar_add(t_array *ar, void *new);
void		ar_del(t_array **ar);
int			bh_add(t_array *ar, void *new);
void		*bh_extract(t_array *ar);
int			ar_quicksort(t_array *ar);
t_array		*ar_map(t_array *ar, void *(*func)(void*), void (*del)(void*));
t_array		*ar_new(uint32_t cap, void (*del)(void*));
int			ar_extend(t_array *ar, uint32_t extra_cap);
int			ar_add(t_array *ar, void *new);
void		ar_del(t_array **ar);
int			bh_add(t_array *ar, void *new);
void		*bh_extract(t_array *ar);
int			ar_quicksort(t_array *ar);
t_array		*ar_map(t_array *ar, void *(*func)(void*), void (*del)(void*));

#endif
