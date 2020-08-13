/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_and_ceiling_casting.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximka <maximka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 15:23:25 by openelop          #+#    #+#             */
/*   Updated: 2020/05/22 15:44:50 by maximka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		get_floor_and_ceil_params(t_param *param, int y)
{
	t_fc_par	*fc_par;
	t_look_par	*look;

	look = &(param->look);
	fc_par = &(param->fc_par);
	fc_par->dir_x_left = look->cam_dir_x - look->plane_x;
	fc_par->dir_y_left = look->cam_dir_y - look->plane_y;
	fc_par->dir_x_right = look->cam_dir_x + look->plane_x;
	fc_par->dir_y_right = look->cam_dir_y + look->plane_y;
	fc_par->p = y - WINDOW_HEIGHT / 2;
	fc_par->row_dist = 0.5 * WINDOW_HEIGHT / fc_par->p;
	fc_par->floor_step_x = fc_par->row_dist
		* (fc_par->dir_x_right - fc_par->dir_x_left) / WINDOW_WIDTH;
	fc_par->floor_step_y = fc_par->row_dist
		* (fc_par->dir_y_right - fc_par->dir_y_left) / WINDOW_HEIGHT;
	if (y < WINDOW_HEIGHT / 2)
	{
		fc_par->floor_x = -look->pos_x + fc_par->row_dist * fc_par->dir_x_left;
		fc_par->floor_y = -look->pos_y + fc_par->row_dist * fc_par->dir_y_left;
	}
	else
	{
		fc_par->floor_x = look->pos_x + fc_par->row_dist * fc_par->dir_x_left;
		fc_par->floor_y = look->pos_y + fc_par->row_dist * fc_par->dir_y_left;
	}
}

void		fill_horizontal_line(t_param *param, int y)
{
	double		dist;
	int			x;
	t_fc_par	*fc_par;

	fc_par = &(param->fc_par);
	x = 0;
	dist = WINDOW_HEIGHT / (2 * (double)abs((y - WINDOW_HEIGHT / 2)));
	while (x < WINDOW_WIDTH)
	{
		fc_par->cell_x = (int)fc_par->floor_x;
		fc_par->cell_y = (int)fc_par->floor_y;
		fc_par->txtr_x = (int)((double)TEXTURE_WIDTH
	* (fc_par->floor_x - fc_par->cell_x)) & (TEXTURE_WIDTH - 1);
		fc_par->txtr_y = (int)((double)TEXTURE_HEIGHT
	* (fc_par->floor_y - fc_par->cell_y)) & (TEXTURE_HEIGHT - 1);
		fc_par->floor_x += fc_par->floor_step_x;
		fc_par->floor_y += fc_par->floor_step_y;
		if (y < WINDOW_HEIGHT / 2)
			param->mlx_par.d_addr[y * WINDOW_WIDTH + x] = apply_fog(fc_par->
	floor.addr[TEXTURE_WIDTH * fc_par->txtr_y + fc_par->txtr_x], dist, 0);
		else
			param->mlx_par.d_addr[y * WINDOW_WIDTH + x] = apply_fog(fc_par->
	ceil.addr[TEXTURE_WIDTH * fc_par->txtr_y + fc_par->txtr_x], dist, 0);
		x++;
	}
}

void		floor_and_ceiling_casting(t_param *param)
{
	t_fc_par	*fc_par;
	int			y;

	y = 0;
	fc_par = &(param->fc_par);
	fc_par->floor.addr = (int*)mlx_get_data_addr(param->imgs_walls[3],
		&(fc_par->floor.bpp), &(fc_par->floor.stride), &(fc_par->floor.endian));
	fc_par->ceil.addr = (int*)mlx_get_data_addr(param->imgs_walls[4],
	&(fc_par->ceil.bpp), &(fc_par->ceil.stride), &(fc_par->ceil.endian));
	param->mlx_par.d_addr = (int*)mlx_get_data_addr(param->mlx_par.img_ptr,
		&param->mlx_par.bpp, &param->mlx_par.size_line, &param->mlx_par.endian);
	while (y < WINDOW_HEIGHT)
	{
		get_floor_and_ceil_params(param, y);
		fill_horizontal_line(param, y);
		y++;
	}
}
