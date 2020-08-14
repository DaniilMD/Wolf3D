#include "wolf3d.h"

int			fill(int fd, int ***map)
{
	char	c;
	int		**m;
	int		i;
	int		j;

	i = 0;
	j = 0;
	m = *map;
	while (read(fd, &c, 1) && c != '@')
	{
		if (c == '\n')
		{
			j = 0;
			i++;
			continue ;
		}
		if ((c >= '0' && c <= '9') || c == 'D' || c == 'P')
			m[i][j++] = c - 48;
		if (c >= 97 && c <= 105)
			m[i][j++] = c;
		if (c == ' ')
			m[i][j++] = -1;
	}
	close(fd);
	return (1);
}

void		fill2(t_map *m)
{
	int		i;
	int		j;

	i = 0;
	while (i < m->height)
	{
		j = 0;
		while (j < m->length)
		{
			m->map[i][j] = -1;
			j++;
		}
		i++;
	}
}

int			count_of_sprites(int fd)
{
	char	c;
	int		n;

	n = 0;
	while (0 < read(fd, &c, 1))
	{
		c == '\n' ? n += 1 : 0;
	}
	close(fd);
	return (n);
}

int			check_available_wall(char c)
{
	if (c >= 48 && c <= 56)
		return (1);
	if (c >= 97 && c <= 104)
		return (1);
	if (c == 80 || c == 68)
		return (1);
	if (c == ' ' || c == '\n')
		return (1);
	return (0);
}

int			**create_map(int y)
{
	int		i;
	int		**map;

	if (!(map = (int**)malloc(sizeof(int*) * y)))
		return (NULL);
	i = 0;
	while (i < y)
	{
		map[i] = NULL;
		i++;
	}
	return (map);
}
