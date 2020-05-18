#ifndef HEAD_H
# define HEAD_H

typedef struct         	s_bsq
{
  int      		max;
  int                  	row;
  int			col;
}                       t_bsq;

int     ft_strlen(char *c);

void    make_str(char **str_in, char *str_out, int ret);

int     nb_str(char *c);

void    solve_map(char *c);

char    **split_whsp(char *c);

int     is_tab(char c);

char    *make_str_arr(char *c, int len);

int		**arr_clc(char **c, int **tmp);

void	print_map(int	**c, char	**map);

int		min(int a, int b, int c);

void	print_map_bsq(char **map, t_bsq map_bsq);

#endif
