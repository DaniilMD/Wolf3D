#include "wolf3d.h"

int			norm_sprite(int fd, char *line, int *n)
{
	*n = 0;
	while (get_next_line(fd, &line) > 0 && line[0] != '@')
		free(line);
	if (line[1] != '\0')
	{
		free(line);
		return (0);
	}
	free(line);
	while (get_next_line(fd, &line) > 0 && line[0] != '@')
	{
		free(line);
		*n += 1;
	}
	free(line);
	close(fd);
	return (1);
}

int			norm_sprite2(int fd, char *line, int *i_now, t_param *param)
{
	int		i;

	i = 0;
	while (get_next_line(fd, &line) > 0 && line[0] != '@')
	{
		if (validate_sprite_par(line) == 0)
		{
			free(line);
			return (0);
		}
		*i_now = 0;
		param->spr_par.sprites[i].x = ft_atoi_for_double(line, i_now);
		param->spr_par.sprites[i].y = ft_atoi_for_double(line, i_now);
		param->spr_par.sprites[i].texture = ft_atoi(&line[*i_now]);
		if (param->spr_par.sprites[i].texture > 3)
		{
			free(line);
			return (0);
		}
		i++;
		free(line);
	}
	free(line);
	return (1);
}

void		print_map(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->length)
		{
			if (map->map[i][j] != -1)
				ft_putnbr(map->map[i][j]);
			else
				ft_putstr(" ");
			j++;
			ft_putstr("  ");
		}
		ft_putstr("\n");
		i++;
	}
}
