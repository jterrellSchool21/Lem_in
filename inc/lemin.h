/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslave <jslave@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 19:59:29 by jslave            #+#    #+#             */
/*   Updated: 2020/07/15 19:59:29 by jslave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef LEMIN_H
# define LEMIN_H
# include "libft.h"
# include <stdarg.h>
# include <string.h>
# include <stdio.h>
# include <limits.h>
# include <float.h>
# include <fcntl.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/stat.h>

typedef struct		s_ant
{
    int 			index;
    int 			curr_room;
    struct s_ant	*next;
}					t_ant;

typedef struct		s_lem_in
{
    int             *rooms;
    t_ant           *ants;
    char            **commands;
    char            **comments;
    int             cmd;
    int             cmt;
    int             count_of_ants;
    int             **matrix;
    int             count_rooms;
    int             start;
    int             end;
}					t_lem_in;

typedef struct		s_room
{
    int 			ant;
    int				x;
    int				y;
    int 			name;
    int 			*output;
    int 			*input;
    struct s_room	*next;
}					t_room;

typedef struct      s_parsed_room
{
    int             ants;//quant of ants
    int             x;//coord x
    int             y;//coord y
    char            *name;//name of room
    int             type;//type -1 -error, type 1 start,type 2 normal,type3 end
    char            **conn;//array with all connections of this room

}                   t_parsed_room;
typedef struct s_indexes
{
    int             start_room;
    int             end_room;
    int             paths;
    int             commented_lines;
    int             paths_count;
    int             ants;
    int             rooms;
}                   t_indexes;
/*
 * errors.c
 */
void                free_parsing_structs(t_parsed_room **rooms, t_indexes *indexes, char **data);
void	            raise_error(int e);
void                throw_parse_err(int e, t_parsed_room **rooms, t_indexes *indexes, char **data);
void	            more_parse_errs(int e);
/*
 * parse-validity-utils.c
 */

t_parsed_room       **memory_allocate_for_rooms_array(t_parsed_room **rooms, int qnt_rooms);
int                 if_all_coordinates_is_zero(t_parsed_room **rooms);
int                 **print_rooms_array(t_parsed_room **rooms, t_lem_in *lemin);
int                 this_room_is_appeared(char *room, t_parsed_room **rooms);
/*
 * parse-validity-main.c
 */
t_parsed_room       **check_validity_of_input_data(char **data, int lines);
int				    coordinates_is_repeated(t_parsed_room **rooms_array);
void                print_map_and_free_parse_structs(t_indexes *indexes, char **data);
int		            fill_room_by_line(char *data, t_parsed_room *room);
int                 fill_rooms_name_and_coords(char **data, t_indexes *indexes, t_parsed_room **rooms_array);
/*
 * parse-validity-indexes.c
 */
t_indexes           *find_indexes(char **data, t_indexes *indexes);
t_indexes           *find_indexes_to_parse(char **data, t_indexes *indexes);
void			    find_start_end_commented_indexes(char **data, 
t_indexes *indexes);
void			    find_path_index(char **data, t_indexes *indexes);
int				    check_data_for_bad_comments(char **data);

/*
 * parse-validity-connections.c
 */
void                fill_connections_for_rooms(int i, t_parsed_room **rooms_array, char **data, t_indexes *indexes);
void	            calculate_needed_size(char **data, int i, t_parsed_room **rooms_array, t_indexes *indexes);
int		            calculate_ind(char *data, t_parsed_room **rooms_array);
int		            check_errors_for_current_line_path(char *datai, char *dataj, t_parsed_room **rooms_array, t_indexes *indexes);///del indexes????;
/*
 * parse-validity-connections_2.c 
 */
char	            *create_string_with_connections(char *conn, t_parsed_room **rooms, 
t_parsed_room *curr_room);
void                check_connections_for_rooms(t_parsed_room **rooms, char **data, t_indexes *indexes);
int		            increment_index(t_parsed_room *room, char **splited_line, int ind);
void                create_connections_for_this_room(t_parsed_room *room, int j, char **data, int size);


int                 count_rooms(t_parsed_room **rooms);
void                print_tab(int **tab, int size);

# endif
