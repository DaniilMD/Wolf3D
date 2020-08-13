/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximka <maximka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 13:15:27 by maximka           #+#    #+#             */
/*   Updated: 2020/06/11 23:02:23 by maximka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			valid_norm(t_map *map, int i, int j)
{
	if ((walls(map->map[i][j])) &&
		(map->map[i - 1][j] == -1
			|| map->map[i + 1][j] == -1
				|| map->map[i][j + 1] == -1
					|| map->map[i][j - 1] == -1))
		return (1);
	return (0);
}

int			**valid_define(char *name, int **map, t_param *param)
{
	int		fd;

	if ((fd = open(name, O_RDONLY)) < 0)
		return (NULL);
	fill(fd, &map);
	if ((fd = open(name, O_RDONLY)) < 0)
		return (NULL);
	if (sprite(fd, param, name) == 0)
	{
		if (param->map.map != NULL)
		{
			if (param->spr_par.numb_of_sprites > 0)
				free(param->spr_par.sprites);
			free_int_starstar(param->map.map, param->map.height);
		}
		return (NULL);
	}
	param->doors = NULL;
	return (map);
}

int			column(int fd)
{
	int		a;
	char	c;
	int		x;

	x = 0;
	a = 0;
	while (read(fd, &c, 1) && c != '@')
	{
		if (c == '\n' || c == '\0')
		{
			(a < x) ? a = x : 0;
			x = 0;
		}
		x++;
	}
	x = a;
	close(fd);
	return (x);
}

int			line(int fd, t_map *map)
{
	char	c;
	int		k;
	int		y;

	y = 0;
	while ((k = read(fd, &c, 1)) && c != '@')
	{
		if (!check_available_wall(c))
		{
			close(fd);
			return (-1);
		}
		if (c == 'D')
			map->doors++;
		(c == '\n' || c == '\0') ? y += 1 : 0;
	}
	y += k == 0 ? 1 : 0;
	close(fd);
	return (y);
}

void		init_p(t_parse *p)
{
	p->x = 0;
	p->y = 0;
	p->fd = -1;
	p->map = NULL;
}
