#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "header_bsq.h"

#define BUF_SIZE 10

int main(int argc, char **argv)
{
        int     fd;
        int     ret;
        char    buf[BUF_SIZE + 1];
	char	*c;

		c = 0;
        fd = open(argv[1], O_RDONLY);
        if (fd == -1)
        {
                printf("open() error");
                return (1);
        }
	if (argc > 1)
	{
        	while ((ret = read(fd, buf, BUF_SIZE)))
        	{
				buf[ret] = '\0';
            	make_str(&c, buf, ret);
        	}
	}
        if (close(fd) == -1)
        {
                printf("close() error");
                return (1);
        }
	solve_map(c);
        return (0);
}

void	solve_map(char *c)
{
	char	**map;
	int		**arr;
	int		i;
	int		j;
	t_bsq	map_bsq;

	i = 0;
	j = 0;
	arr = (int **)malloc(sizeof(int *) * (nb_str(c)));
	map = split_whsp(c);
	while (i < nb_str(c))
      {
        arr[i] = (int*)malloc(sizeof(int) * ft_strlen(map[0]));
        i++;
      }
      i = 0;
	arr = arr_clc(map, arr);
	print_map(arr, map);
	printf("\n");
	map_bsq.max = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (i != 0 && j != 0 && arr[i][j] > 0)
			{
				arr[i][j] = 1 + min(arr[i - 1][j], arr[i][j - 1], arr[i - 1][j - 1]);
			}
			if (arr[i][j] > map_bsq.max)
			{
				map_bsq.max = arr[i][j];
				map_bsq.col = j;
				map_bsq.row = i;
			}
			j++;
		}
		i++;
		j = 0;
	}
	print_map(arr, map);
	print_map_bsq(map, map_bsq);
}

void	print_map_bsq(char **map, t_bsq map_bsq)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (i >= map_bsq.row - map_bsq.max && j > map_bsq.col - map_bsq.max
				&& i <= map_bsq.row && j <= map_bsq.col)
			{
				printf("x");
			}
			else
				printf("%c", map[i][j]);
			j++;
		}
		i++;
		printf("\n");
		j = 0;
	}
}

int		min(int a, int b, int c)
{
	int min;

	min = a;
	if (b < a)
	{
		min = b;
	}
	if (c < a)
	{
		if (c < b)
			min = c;
	}
	return (min);
}

void	print_map(int	**c, char	**map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			printf("%d ", c[i][j]);
			j++;
		}
		printf("\n");
		i++;
		j = 0;
	}
}

int		**arr_clc(char **map, int **tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == '.')
			{
				tmp[i][j] = 1;
			}
			else
			{
				tmp[i][j] = 0;
			}
			j++;
		}
		i++;
		j = 0;
	}
	return (tmp);
}

char	**split_whsp(char *c)
{
	int	count;
	char	**map;
	int	i;

	count = 0;
	i = 0;
	map = (char**)malloc(sizeof(char*) * (nb_str(c) + 1));
	while (*c)
	{
		while (!is_tab(*c) && *c)
		{
			c++;
			count++;
		}
		map[i] = make_str_arr(c - count, count);
		i++;
		count = 0;
		c++;
	}
	map[i] = 0;
	return (map);
}

int	nb_str(char *c)
{
	int	count;

	count = 1;
	while (*c)
	{
		if (is_tab(*c))
		{
			count++;
		}
		c++;
	}
	return (count);
}

int	is_tab(char c)
{
	if (c == '\n')
		return (1);
	return (0);
}

char	*make_str_arr(char *c, int len)
{
	char *tmp;

	tmp = (char*)malloc(sizeof(char) * (len + 1));
	while (*c != '\n' && *c)
	{
		*tmp = *c;
		c++;
		tmp++;
	}
	*tmp = '\0';
	tmp = tmp -len;
	printf("%s \n", tmp);
	return (tmp);
}

void	make_str(char **str_in, char *str_out, int ret)
{
	char	*tmp;
	int	i;
	int	l;

	i = 0;
	l = ft_strlen(*str_in);
	tmp =(char*)malloc(sizeof(char) * (l + ret + 1));
	if (l)
	{
		while (**str_in)
		{
			tmp[i] = **str_in;
			(*str_in)++;
			i++;
		}
	}
	while (*str_out)
	{
		tmp[i] = *str_out;
		i++;
		str_out++;
	}
	tmp[i] = '\0';
	*str_in = tmp;
}

int	ft_strlen(char *c)
{
	int	count;

	count = 0;
	if(c == 0)
		return (0);
	while (*c)
	{
		count++;
		c++;
	}
	return (count);
}
