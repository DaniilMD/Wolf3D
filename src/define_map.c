#include "wolf3d.h"

double		ft_atoi_for_double(char *line, int *i_now)
{
	double	dec;
	int		i;
	double	n;

	i = *i_now;
	n = ft_atoi(&line[i]);
	while (line[i] != '.')
		i++;
	i++;
	*i_now = i;
	dec = ft_atoi(&line[i]);
	while (line[i] != ',')
		i++;
	n += dec / pow(10, i - *i_now);
	*i_now = i + 1;
	return (n);
}

int			sprite(int fd, t_param *param, char *name)
{
	int		i_now;
	int		n;
	char	*line;

	line = NULL;
	if (!norm_sprite(fd, line, &n))
		return (0);
	if ((fd = open(name, O_RDONLY)) < 0)
		return (0);
	param->spr_par.numb_of_sprites = n;
	if (n > 0)
		param->spr_par.sprites = (t_sprite*)malloc(sizeof(t_sprite) * n);
	while (get_next_line(fd, &line) > 0 && line[0] != '@')
		free(line);
	free(line);
	if (!norm_sprite2(fd, line, &i_now, param))
		return (0);
	close(fd);
	return (1);
}

int			validate_map(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->length)
		{
			if (walls(map->map[i][j]) && i == 0)
				return (0);
			if (walls(map->map[i][j]) && i == map->height - 1)
				return (0);
			if (walls(map->map[i][j]) && j == 0)
				return (0);
			if (walls(map->map[i][j]) && j == map->length - 1)
				return (0);
			if (valid_norm(map, i, j))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int			validate_file(char *name)
{
	int		fd;
	char	c;
	int		dog_cnt;
	char	prev_sym;

	prev_sym = '\0';
	if ((fd = open(name, O_RDONLY)) < 0)
		return (0);
	dog_cnt = 0;
	while (read(fd, &c, 1) > 0)
	{
		if (c == '\n' && prev_sym == '\n')
			return (0);
		if (dog_cnt == 2)
			return (0);
		if (!(norm_valid_file(c, prev_sym, &dog_cnt)))
			return (0);
		prev_sym = c;
	}
	if (dog_cnt < 2)
		return (0);
	return (1);
}

int			**define_map(char *name, t_map *m, t_param *param)
{
	t_parse	p;

	init_p(&p);
	if (validate_file(name) == 0)
		return (NULL);
	if ((p.fd = open(name, O_RDONLY)) < 0)
		return (NULL);
	m->doors = 0;
	if ((p.y = line(p.fd, m)) == -1)
		return (NULL);
	if ((p.fd = open(name, O_RDONLY)) < 0)
		return (NULL);
	if (!(p.map = create_map(p.y)))
		return (NULL);
	p.x = column(p.fd) - 1;
	m->height = p.y;
	m->length = p.x;
	while (p.y--)
	{
		if (!(p.map[p.y] = (int*)malloc(sizeof(int) * p.x)))
			return (NULL);
	}
	m->map = p.map;
	fill2(m);
	return (valid_define(name, p.map, param));
}
