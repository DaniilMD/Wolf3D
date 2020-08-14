#include "wolf3d.h"

int			check_object_collision(t_param *param, double pos_x, double pos_y)
{
	double	dist;
	int		i;

	i = 0;
	while (i < param->spr_par.numb_of_sprites)
	{
		dist = sqrt(((param->spr_par.sprites[i].x - pos_x) *
	(param->spr_par.sprites[i].x - pos_x)) + ((param->spr_par.sprites[i].y
	- pos_y) * (param->spr_par.sprites[i].y - pos_y)));
		if (dist < 0.4 && param->spr_par.sprites[i].texture > 0
		&& param->spr_par.sprites[i].texture < 3)
			return (i);
		if (dist < 0.4 && param->spr_par.sprites[i].texture == COIN)
			param->coin_hit = i;
		i++;
	}
	return (-1);
}

int			check_collisions(t_param *param, double pos_x, double pos_y, char f)
{
	int		obj_num;
	double	delta;

	obj_num = -1;
	delta = MOVEMENT_SPEED - 0.1;
	if ((obj_num = check_object_collision(param, pos_x, pos_y)) != -1)
		return (obj_num);
	if ((param->map.map[(int)(pos_y + delta)][(int)pos_x] != 0) && f == 'y')
		return (-1);
	if ((param->map.map[(int)(pos_y - delta)][(int)pos_x] != 0) && f == 'y')
		return (-1);
	if ((param->map.map[(int)pos_y][(int)(pos_x + delta)] != 0) && f == 'x')
		return (-1);
	if ((param->map.map[(int)pos_y][(int)(pos_x - delta)] != 0) && f == 'x')
		return (-1);
	return (0);
}

void		move_forw_back(int key, t_param *param)
{
	if (key == KB_UP)
	{
		if (param->map.map[(int)(param->look.pos_y)][(int)(param->look.pos_x +
param->look.cam_dir_x * param->ms)] == 0 && check_collisions(param, param->
look.pos_x + param->look.cam_dir_x * param->ms, param->look.pos_y, 'x') == 0)
			param->look.pos_x += param->look.cam_dir_x * param->ms;
		if (param->map.map[(int)(param->look.pos_y + param->look.cam_dir_y *
param->ms)][(int)(param->look.pos_x)] == 0 && check_collisions(param, param->
look.pos_x, param->look.pos_y + param->look.cam_dir_y * param->ms, 'y') == 0)
			param->look.pos_y += param->look.cam_dir_y * param->ms;
	}
	else if (key == KB_DOWN)
	{
		if (param->map.map[(int)(param->look.pos_y)]
	[(int)(param->look.pos_x - param->look.cam_dir_x * param->ms)] == 0
	&& check_collisions(param, param->look.pos_x - param->look.cam_dir_x
	* param->ms, param->look.pos_y, 'x') == 0)
			param->look.pos_x -= param->look.cam_dir_x * param->ms;
		if (param->map.map[(int)(param->look.pos_y - param->look.cam_dir_y
	* param->ms)][(int)(param->look.pos_x)] == 0
	&& check_collisions(param, param->look.pos_x,
	param->look.pos_y - param->look.cam_dir_y * param->ms, 'y') == 0)
			param->look.pos_y -= param->look.cam_dir_y * param->ms;
	}
}

void		move_left_right(int key, t_param *param)
{
	if (key == KB_RIGHT)
	{
		if (param->map.map[(int)(param->look.pos_y)][(int)(param->look.pos_x +
param->look.plane_x * param->ms)] == 0 && check_collisions(param, param->
look.pos_x + param->look.plane_x * param->ms, param->look.pos_y, 'x') == 0)
			param->look.pos_x += param->look.plane_x * param->ms;
		if (param->map.map[(int)(param->look.pos_y + param->look.plane_y *
param->ms)][(int)(param->look.pos_x)] == 0 && check_collisions(param, param->
look.pos_x, param->look.pos_y + param->look.plane_y * param->ms, 'y') == 0)
			param->look.pos_y += param->look.plane_y * param->ms;
	}
	else if (key == KB_LEFT)
	{
		if (param->map.map[(int)(param->look.pos_y)]
	[(int)(param->look.pos_x - param->look.plane_x * param->ms)] == 0
	&& check_collisions(param, param->look.pos_x
	- param->look.plane_x * param->ms, param->look.pos_y, 'x') == 0)
			param->look.pos_x -= param->look.plane_x * param->ms;
		if (param->map.map[(int)(param->look.pos_y - param->look.plane_y
	* param->ms)][(int)(param->look.pos_x)] == 0
	&& check_collisions(param, param->look.pos_x,
	param->look.pos_y - param->look.plane_y * param->ms, 'y') == 0)
			param->look.pos_y -= param->look.plane_y * param->ms;
	}
}
