#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define BUF_SIZE 10

int     ft_strlen(char *c);

void    make_str(char **str_in, char *str_out, int ret);

int     nb_str(char *c);

void    solve_map(char *c);

char    **split_whsp(char *c);

int     is_tab(char c);

char    *make_str_arr(char *c, int len);

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
	char **map;

	map = split_whsp(c);
	printf("%s\n", map[0] - 5);
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
