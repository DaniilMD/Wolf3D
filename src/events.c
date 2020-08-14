#include "wolf3d.h"

void		close_window(t_param *param)
{
	free_everything(param);
	mlx_destroy_image(param->mlx_par.mlx_ptr, param->mlx_par.img_ptr);
	mlx_clear_window(param->mlx_par.mlx_ptr, param->mlx_par.win_ptr);
	mlx_destroy_window(param->mlx_par.mlx_ptr, param->mlx_par.win_ptr);
	(void)(param->map);
	(void)(param->look);
	(void)(param->mlx_par);
	(void)(param->fc_par.floor);
	(void)(param->fc_par.ceil);
	(void)(param->fc_par);
	(void)(param->spr_par);
	(void)param;
	exit(0);
}

int			red_cross(t_param *param)
{
	close_window(param);
	exit(0);
	return (0);
}

void		change_map(t_param *param)
{
	if (param->map.level != 1 && param->map.level != 2)
	{
		ft_putstr("Game finished\n\nNumber of points: ");
		ft_putnbr(param->points);
		ft_putstr("\n");
		close_window(param);
	}
	free_everything(param);
	if (param->map.level == 1)
	{
		param->map.map = define_map(JOJO, &param->map, param);
		param->map.level = 2;
	}
	else if (param->map.level == 2)
	{
		param->map.map = define_map(CROSSES, &param->map, param);
		param->map.level = 3;
	}
	if (param->map.map == NULL)
		finish_program(param);
	print_map(&param->map);
	(validate_map(&param->map) == 1) ? NULL : finish_program(param);
	initialize(param);
}

void		press_f(t_param *param)
{
	if (param->map.map[(int)(param->look.pos_y + param->look.cam_dir_y * 1)]
		[(int)(param->look.pos_x + param->look.cam_dir_x * 1)] == PORTAL)
	{
		change_map(param);
	}
	if (param->map.map[(int)(param->look.pos_y + param->look.cam_dir_y * 1)]
		[(int)(param->look.pos_x + param->look.cam_dir_x * 1)] >= 97 &&
			param->map.map[(int)(param->look.pos_y + param->look.cam_dir_y * 1)]
		[(int)(param->look.pos_x + param->look.cam_dir_x * 1)] <= 105)
	{
		param->map.map[(int)(param->look.pos_y + param->look.cam_dir_y * 1)]
		[(int)(param->look.pos_x + param->look.cam_dir_x * 1)] = 0;
	}
	if (param->map.map[(int)(param->look.pos_y + param->look.cam_dir_y * 1)]
		[(int)(param->look.pos_x + param->look.cam_dir_x * 1)] == DOOR)
	{
		create_thr_door(param, (int)(param->look.pos_x
	+ param->look.cam_dir_x * 1), (int)(param->look.pos_y
	+ param->look.cam_dir_y * 1));
	}
}

int			key_press_down(int key, void *void_param)
{
	t_param	*param;

	param = (t_param *)void_param;
	if (key == KB_UP || key == KB_DOWN)
		move_forw_back(key, param);
	else if (key == KB_LEFT || key == KB_RIGHT)
		move_left_right(key, param);
	else if (key == KB_Q || key == KB_E)
		rotate(key, param);
	else if (key == KB_ESC)
		close_window(param);
	else if (key == KB_F)
		press_f(param);
	else if (key == KB_M)
		param->mmp_flag *= -1;
	return (0);
}
