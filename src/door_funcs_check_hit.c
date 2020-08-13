/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_funcs_check_hit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximka <maximka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 20:09:49 by maximka           #+#    #+#             */
/*   Updated: 2020/05/11 20:09:50 by maximka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			check_door(t_param *param)
{
	int		i;

	i = 0;
	while (i < param->map.doors)
	{
		if (param->look.real_map_x == param->doors[i].door_x
			&& param->look.real_map_y == param->doors[i].door_y)
			return (i);
		i++;
	}
	return (NO_DOOR);
}

void		wall_x_and_per_dist_for_door(t_look_par *look)
{
	if (look->hit_side == X_SIDE)
		look->perp_dist_to_wall = (look->real_map_x - look->pos_x
			+ (1 - look->step_x) / 2) / look->dir_x;
	else
		look->perp_dist_to_wall = (look->real_map_y - look->pos_y
			+ (1 - look->step_y) / 2) / look->dir_y;
	if (look->hit_side == X_SIDE)
	{
		look->wall_x = look->pos_y + look->perp_dist_to_wall * look->dir_y;
		look->wall_x -= look->real_map_y;
		if ((look->cam_dir_y > 0 && look->cam_dir_x > 0) ||
		(look->cam_dir_y < 0 && look->cam_dir_x > 0))
			look->wall_x = 1 - look->wall_x;
	}
	else
	{
		look->wall_x = look->pos_x + look->perp_dist_to_wall * look->dir_x;
		look->wall_x -= look->real_map_x;
		if ((look->cam_dir_x > 0 && look->cam_dir_y < 0) ||
			(look->cam_dir_x < 0 && look->cam_dir_y < 0))
			look->wall_x = 1 - look->wall_x;
	}
}

int			check_hit(t_param *param)
{
	int			i;
	t_look_par	*look;

	look = &param->look;
	if ((i = check_door(param)) != -1)
	{
		wall_x_and_per_dist_for_door(look);
		if (param->doors[i].k <= look->wall_x)
			return (1);
		else
		{
			param->look.perp_dist_to_wall = -1;
			return (0);
		}
	}
	if (param->map.map[param->look.real_map_y][param->look.real_map_x] > 0)
		return (1);
	else
		return (0);
}

int			door_animation(t_param *param)
{
	int		dx;
	int		i;

	i = check_door(param);
	if (i == NO_DOOR)
		return (0);
	dx = 0;
	if (param->look.hit_side == X_SIDE)
		dx = ((param->look.cam_dir_x > 0 && param->look.cam_dir_y > 0) ||
	(param->look.cam_dir_x > 0 && param->look.cam_dir_y < 0)) ?
	-(int)(TEXTURE_WIDTH * param->doors[i].k)
	: (int)(TEXTURE_WIDTH * param->doors[i].k);
	else
		dx = ((param->look.cam_dir_x > 0 && param->look.cam_dir_y < 0) ||
	(param->look.cam_dir_x < 0 && param->look.cam_dir_y < 0)) ?
	-(int)(TEXTURE_WIDTH * param->doors[i].k)
	: (int)(TEXTURE_WIDTH * param->doors[i].k);
	return (dx);
}
