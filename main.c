#include <stdio.h>
#include <fcntl.h>
#include "libft.h"

typedef struct		s_ant
{
	int 			index;
	int 			curr_room;
	struct s_ant	*next;
}					t_ant;

typedef struct		s_lem_in
{
	int 	*rooms;
	t_ant	*ants;
	char	**commands;
	char 	**comments;
	int 	cmd;
	int 	cmt;
	int 	count_of_ants;
	int 	**matrix;
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

void	print_ints(int N, int *str)
{
	int 	i;

	i = 0;
	while (i < N)
	{
		printf("%d ", str[i]);
		i++;
	}
	printf("\n");
}

void	RaiseError(int e)
{
	if (e == 0)
	{
		ft_putstr(">>Malloc error, sorry...\n");
		exit(1);
	}
}

int 	ft_is_int(char *str)
{
	int 	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int		ft_strsplit_len(char **line)
{
	int 	i;

	i = 0;
	while (line[i])
		i++;
	return (i);
}

int 	is_room_name(char *line)
{
	if (line && ft_strlen(line))
	{
		if (line[0] != 'L' && line[0] != '#')
			return (1);
	}
	return (0);
}

int 	isroom(char **line)
{
	if (ft_strsplit_len(line) == 3 && is_room_name(line[0]) && ft_is_int(line[1]) && ft_is_int(line[2]))
		return (1);
	else
		return (0);
}

int 	iscommand(char *line, int i)
{
	if ((ft_strlen(line) >= 2) && !ft_strncmp(line, "##", 2))
		return (1);
	return (0);
}

int 	iscomment(char *line, int i)
{
	if (ft_strlen(line) && !iscommand(line, i) && !ft_strncmp(line, "#", 1))
	return (1);
	return (0);
}

int 	isants(char *line, int i)
{
	if (ft_is_int(line))
		return (1);
	return (0);
}

t_lem_in	*ft_init_lem_in(void)
{
	t_lem_in	*lemin;

	if (!(lemin = (t_lem_in *)ft_memalloc(sizeof(t_lem_in))))
		RaiseError(0);
	lemin->ants = 0;
	lemin->commands = (char**)malloc(sizeof(char*) * 10);
	lemin->comments = (char**)malloc(sizeof(char*) * 10);
	lemin->rooms = NULL;
	lemin->cmd = 0;
	lemin->cmt = 0;
	lemin->ants = NULL;
	lemin->matrix = NULL;
	return (lemin);

}

void	add_comment(t_lem_in *lem_in, char *line, int i)
{
	int 	a;

	if (lem_in->cmt == 0)
		lem_in->comments[0] = ft_strjoin(ft_strdup(line), ft_itoa(i));
	else
	{
		a = 0;
		while (a < lem_in->cmt)
			a++;
		lem_in->commands[a] = ft_strjoin(ft_strdup(line), ft_itoa(i));
	}
}

void	add_command(t_lem_in *lem_in, char *line, int i)
{
	int 	a;

	if ((ft_strcmp(line, "##end") == 0) || (ft_strcmp(line, "##start") == 0))
		if (lem_in->cmd == 0)
			lem_in->commands[0] = ft_strjoin(ft_strdup(line), ft_itoa(i));
		else
		{
			a = 0;
			while (a < lem_in->cmd)
				a++;
			lem_in->commands[a] = ft_strjoin(ft_strdup(line), ft_itoa(i));
		}
}

void	add_ant(t_lem_in *lem_in, char *line, int k)
{
	int 	i;
	t_ant	*ants;

	lem_in->count_of_ants = ft_atoi(line);
	i = 0;
	ants = (t_ant*)malloc(sizeof(t_ant));
	lem_in->ants = ants;
	while (i < lem_in->count_of_ants)
	{
		ants->next = (t_ant*)malloc(sizeof(t_ant));
		ants->curr_room = 0;
		ants->index = i;
		ants = ants->next;
		i++;
	}
	ants->next = NULL;
}

void	add_stroke(t_lem_in *lem_in)
{
	lem_in->matrix = (int**)malloc(sizeof(int*) * 10);
}

void	add_room(t_lem_in *lem_in, char **line, int i)
{
	if (!(lem_in->matrix))
		add_stroke(lem_in);

}

int 	**init_matrix(int N, int M, char *symbols)
{
	int 	i;
	int 	j;
	int 	**res;
	char 	**ints;

	i = 0;
	res = (int**)malloc(sizeof(int*) * N);
	while (i < N)
	{
		res[i] = (int*)malloc(sizeof(int) * M);
		i++;
	}
	i = 0;
	ints = ft_strsplit(symbols, ' ');
	while (i < N)
	{
		j = 0;
		while (j < M)
		{
			res[i][j] = ft_atoi(ints[i * M + j]);
			j++;
		}
		i++;
	}
	return (res);
}

void	print_matrix(int N, int M, int **matrix)
{
	int 	i;
	int 	j;

	i = 0;
	while (i < N)
	{
		j = 0;
		while (j < M)
		{
			printf("%d ", matrix[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	execute(int **matrix, int end, int start)
{
	int 	i;
	int 	j;
	int 	*points;
	int 	min;
	int 	minindex;
	int 	*d;
	int 	*v;
	int 	tmp;
	int 	k;

	int		*ver;
	int 	weight;

	d = (int*)malloc(sizeof(int) * 5);
	v = (int*)malloc(sizeof(int) * 5);
	i = 0;
	while (i < 5)
	{
		d[i] = 1000;
		v[i] = 1;
		i++;
	}
	i = 0;
	points = (int*)malloc(sizeof(int) * 5);
	min = 0;
	minindex = 0;
	d[0] = 0;
	//Расстояния до точек
	do
	{
		min = 1000;
		minindex = 1000;
		i = 0;
		while (i < 5)
		{
			if (v[i] == 1 && d[i] < min)
			{
				min = d[i];
				minindex = i;
			}
			i++;
		}
		if (minindex != 1000)
		{
			j = 0;
			while (j < 5)
			{
				if (matrix[minindex][j] > 0)
				{
					tmp = min + matrix[minindex][j];
					if (tmp < d[j])
						d[j] = tmp;
				}
				j++;
			}
			v[minindex] = 0;
		}
	} while (minindex < 1000);
	printf("Minimal ranges to points : ");
	print_ints(5, d);
	// Кратчайший путь

	ver = (int*)malloc(sizeof(int) * 5);
	ver[0] = end;
	i = 1;
	weight = d[end];
	k = 1;
	while (end != start)
	{
		i = 0;
		while (i < 5)
		{
			if (matrix[i][end] != 0)
			{
				tmp = weight - matrix[i][end];
				if (tmp == d[i])
				{
					weight = tmp;
					end = i;
					ver[k] = i + 1;
					k++;
				}
			}
			i++;
		}
	}
	i = k - 1;
	while (i >= 0)
	{
		printf("%3d ", ver[i]);
		i--;
	}
}

int		main(int argc, char *argv[])
{
	int 	**matrix;
	char	str[49] = "0 1 1 0 0 1 0 0 0 1 1 0 0 1 0 0 0 1 0 1 0 1 0 1 0";

	matrix = init_matrix(5, 5, str);
	print_matrix(5, 5, matrix);
	execute(matrix, 4, 0);
//	int 		fd;
//	char		*line;
//	int 		i;
//	int 		count;
//	t_lem_in	*lem_in;
//
//	fd = open("kek.txt", O_RDONLY);
//	printf("%s\n", argv[1]);
//	i = 0;
//	lem_in = ft_init_lem_in();
////	printf("%s\n", ft_strsplit("lelkek", ' ')[0]);
//	while ((get_next_line(fd, &line)) == 1)
//	{
//		if (iscomment(line, i))
//		{
//			add_comment(lem_in, line, i);
//		}
//		if (iscommand(line, i))
//		{
//			add_command(lem_in, line, i);
//		}
//		if (isants(line, i))
//		{
//			add_ant(lem_in, line, i);
//		}
//		if (isroom(ft_strsplit(line, ' ')))
//		{
//			add_room(lem_in, ft_strsplit(line, " "), i);
//		}
//		i++;
//	}
	return 0;
}