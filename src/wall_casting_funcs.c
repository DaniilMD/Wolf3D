#include "wolf3d.h"

void		initialize_look_vert_line(t_param *param, int x)
{
	double	point_on_plane;

	point_on_plane = x * 2 / (double)WINDOW_WIDTH - 1;
	param->look.dir_x = param->look.cam_dir_x
		+ param->look.plane_x * point_on_plane;
	param->look.dir_y = param->look.cam_dir_y
		+ param->look.plane_y * point_on_plane;
	param->look.real_map_x = (int)param->look.pos_x;
	param->look.real_map_y = (int)param->look.pos_y;
	param->look.d_dist_x = fabs(1 / param->look.dir_x);
	param->look.d_dist_y = fabs(1 / param->look.dir_y);
}

void		get_steps_and_d_distances(t_param *param)
{
	if (param->look.dir_x < 0)
	{
		param->look.step_x = -1;
		param->look.dist_to_side_x = (param->look.pos_x -
			param->look.real_map_x) * param->look.d_dist_x;
	}
	else
	{
		param->look.step_x = 1;
		param->look.dist_to_side_x = (param->look.real_map_x + 1.0
		- param->look.pos_x) * param->look.d_dist_x;
	}
	if (param->look.dir_y < 0)
	{
		param->look.step_y = -1;
		param->look.dist_to_side_y = (param->look.pos_y -
			param->look.real_map_y) * param->look.d_dist_y;
	}
	else
	{
		param->look.step_y = 1;
		param->look.dist_to_side_y = (param->look.real_map_y
			+ 1.0 - param->look.pos_y) * param->look.d_dist_y;
	}
}

void		dda_alg(t_param *param)
{
	param->look.hit = 0;
	while (param->look.hit == 0)
	{
		if (param->look.dist_to_side_x < param->look.dist_to_side_y)
		{
			param->look.dist_to_side_x += param->look.d_dist_x;
			param->look.real_map_x += param->look.step_x;
			param->look.hit_side = X_SIDE;
		}
		else
		{
			param->look.dist_to_side_y += param->look.d_dist_y;
			param->look.real_map_y += param->look.step_y;
			param->look.hit_side = Y_SIDE;
		}
		if (check_hit(param))
			param->look.hit = 1;
	}
}

void		get_perp_dist_and_line_prop(t_param *param)
{
	if (param->look.perp_dist_to_wall == -1)
	{
		if (param->look.hit_side == X_SIDE)
			param->look.perp_dist_to_wall = (param->look.real_map_x -
param->look.pos_x + (1 - param->look.step_x) / 2) / param->look.dir_x;
		else
			param->look.perp_dist_to_wall = (param->look.real_map_y -
param->look.pos_y + (1 - param->look.step_y) / 2) / param->look.dir_y;
	}
	param->look.line_h = (int)(WINDOW_HEIGHT / param->look.perp_dist_to_wall);
	param->look.draw_start = WINDOW_HEIGHT / 2 - param->look.line_h / 2;
	if (param->look.draw_start < 0)
		param->look.draw_start = 0;
	param->look.draw_end = WINDOW_HEIGHT / 2 + param->look.line_h / 2;
	if (param->look.draw_end >= WINDOW_HEIGHT)
		param->look.draw_end = WINDOW_HEIGHT - 1;
}

void		get_txtr_par(t_param *param)
{
	t_look_par	*look;

	look = &(param->look);
	look->txtr_num = choose_wall(param->map.map
		[look->real_map_y][look->real_map_x]);
	if (look->hit_side == X_SIDE)
	{
		look->wall_x = look->pos_y + look->perp_dist_to_wall * look->dir_y;
		look->wall_x -= look->real_map_y;
	}
	else
	{
		look->wall_x = look->pos_x + look->perp_dist_to_wall * look->dir_x;
		look->wall_x -= look->real_map_x;
	}
	look->txtr_x = (int)(look->wall_x * (double)TEXTURE_WIDTH);
	if (look->txtr_num == DOOR_TXTR)
		look->txtr_x -= door_animation(param);
	if (look->hit_side == X_SIDE && look->dir_x > 0)
		look->txtr_x = (TEXTURE_WIDTH - look->txtr_x - 1);
	if (look->hit_side == Y_SIDE && look->dir_y < 0)
		look->txtr_x = (TEXTURE_WIDTH - look->txtr_x - 1);
	look->txtr_step = 1.0 * TEXTURE_HEIGHT / look->line_h;
	look->txtr_pos = (look->draw_start - WINDOW_HEIGHT / 2
		+ look->line_h / 2) * look->txtr_step;
}
