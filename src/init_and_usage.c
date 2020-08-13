/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_usage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximka <maximka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 20:10:06 by maximka           #+#    #+#             */
/*   Updated: 2020/06/12 16:20:35 by maximka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			usage(void)
{
	ft_putstr("Wrong number of arguments or wrong filename.\n\
You can send only 1 map to the wolf3d executable.\n\
There are 3 connected maps: 1) labirynth -> 2) jojo -> \
3) crosses.\nIf you finish 1 map, you get to the 2nd one, \
3rd goes after the 2nd.\nAs soon as you finish last map, \
you finish the game and get the number of coins collected \
(points).\nIf you open a map that is not following the rules\n\
you get an error.\nIf a chosen map is correct it is not \
one of the chained ones, you finish the game right after finishing \
the chosen map.\n");
	return (-1);
}

int			free_space(t_look_par *look, t_map *map)
{
	int		i;
	int		j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->length)
		{
			if (map->map[i][j] == 0)
			{
				look->pos_x = (double)j + 0.3;
				look->pos_y = (double)i + 0.3;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void		initialize(t_param *param)
{
	int		i;

	if (free_space(&param->look, &param->map) == 0)
		finish_program(param);
	if (!(param->doors = (t_door*)malloc(sizeof(t_door) * param->map.doors)))
		finish_program(param);
	i = 0;
	while (i < param->map.doors)
	{
		param->doors[i].map = param->map.map;
		param->doors[i].door_x = -1;
		param->doors[i].door_y = -1;
		i++;
	}
	param->sec_rmmbr = -1;
	param->look.cam_dir_x = -1;
	param->look.cam_dir_y = 0;
	param->look.plane_x = 0;
	param->look.plane_y = 0.66;
	param->look.perp_dist_to_wall = -1;
	param->time = 0;
	param->time_old = 0;
	param->mmp_flag = -1;
	param->ms = MOVEMENT_SPEED;
	param->rot_speed = ROTATION_SPEED;
}

void		create_images_walls(t_param *param)
{
	int width;
	int	height;

	width = 1;
	height = 1;
	param->imgs_walls[0] = mlx_xpm_file_to_image(param->mlx_par.mlx_ptr,
		"textures/wood.xpm", &width, &height);
	param->imgs_walls[1] = mlx_xpm_file_to_image(param->mlx_par.mlx_ptr,
		"textures/redbrick.xpm", &width, &height);
	param->imgs_walls[2] = mlx_xpm_file_to_image(param->mlx_par.mlx_ptr,
		"textures/purplestone.xpm", &width, &height);
	param->imgs_walls[3] = mlx_xpm_file_to_image(param->mlx_par.mlx_ptr,
		"textures/mossy.xpm", &width, &height);
	param->imgs_walls[4] = mlx_xpm_file_to_image(param->mlx_par.mlx_ptr,
		"textures/greystone.xpm", &width, &height);
	param->imgs_walls[5] = mlx_xpm_file_to_image(param->mlx_par.mlx_ptr,
		"textures/eagle.xpm", &width, &height);
	param->imgs_walls[6] = mlx_xpm_file_to_image(param->mlx_par.mlx_ptr,
		"textures/colorstone.xpm", &width, &height);
	param->imgs_walls[7] = mlx_xpm_file_to_image(param->mlx_par.mlx_ptr,
		"textures/bluestone.xpm", &width, &height);
	param->imgs_walls[8] = mlx_xpm_file_to_image(param->mlx_par.mlx_ptr,
		"textures/door.xpm", &width, &height);
	param->imgs_walls[9] = mlx_xpm_file_to_image(param->mlx_par.mlx_ptr,
		"textures/portal.xpm", &width, &height);
}

void		create_images_sprites(t_param *param)
{
	int width;
	int	height;

	width = 1;
	height = 1;
	param->imgs_sprites[0] = mlx_xpm_file_to_image(param->mlx_par.mlx_ptr,
		"textures/greenlight.xpm", &width, &height);
	param->imgs_sprites[1] = mlx_xpm_file_to_image(param->mlx_par.mlx_ptr,
		"textures/pillar.xpm", &width, &height);
	param->imgs_sprites[2] = mlx_xpm_file_to_image(param->mlx_par.mlx_ptr,
		"textures/barrel.xpm", &width, &height);
	param->imgs_sprites[3] = mlx_xpm_file_to_image(param->mlx_par.mlx_ptr,
		"textures/coin.xpm", &width, &height);
	param->imgs_walls[10] = mlx_xpm_file_to_image(param->mlx_par.mlx_ptr,
		"textures/P.xpm", &width, &height);
}
