#include "wolf3d.h"
#include "keys.h"

void		close_window(t_param *param)
{
	// mlx_clear_window(param->mlx_par.mlx_ptr, param->mlx_par.win_ptr);
	// mlx_destroy_image(param->mlx_par.mlx_ptr, param->mlx_par.img_ptr);
	// mlx_destroy_window(param->mlx_par.mlx_ptr, param->mlx_par.win_ptr);
	// free_char_starstar(param->token.token_map);
	// free_char_starstar(param->map);
	// (void)(param->token);
	// (void)(param->runner);
	// (void)(param->psns);
	// (void)(param->mass_p_en);
	// (void)(param->mass_p_me);
	// (void)(param->mlx_par);
	(void)param;
	exit(0);
}

void	move(int key, t_param *param)
{
	if (key == KEY_UP)
	{
		if (param->map[(int)(param->look.pos_y)]
		[(int)(param->look.pos_x + param->look.cam_dir_x * param->ms)] == 0)
			param->look.pos_x += param->look.cam_dir_x * param->ms;
		if (param->map[(int)(param->look.pos_y + param->look.cam_dir_y * param->ms)]
		[(int)(param->look.pos_x)] == 0)
			param->look.pos_y += param->look.cam_dir_y * param->ms;
	}
	else if (key == KEY_DOWN)
	{
		if (param->map[(int)(param->look.pos_y)]
		[(int)(param->look.pos_x - param->look.cam_dir_x * param->ms)] == 0)
			param->look.pos_x -= param->look.cam_dir_x * param->ms;
		if (param->map[(int)(param->look.pos_y - param->look.cam_dir_y * param->ms)]
		[(int)(param->look.pos_x)] == 0)
			param->look.pos_y -= param->look.cam_dir_y * param->ms;
	}
}

void	rotate(int key, t_param *param)
{
	double	old_cam_dir_x;
	double	old_plane_x;

	if (key == KEY_LEFT)
	{
		old_cam_dir_x = param->look.cam_dir_x;
		param->look.cam_dir_x = param->look.cam_dir_x * cos(param->rot_speed)
			- param->look.cam_dir_y * sin(param->rot_speed);
		param->look.cam_dir_y = old_cam_dir_x * sin(param->rot_speed)
			+ param->look.cam_dir_y * cos(param->rot_speed);

		old_plane_x = param->look.plane_x;
		param->look.plane_x = param->look.plane_x * cos(param->rot_speed)
			- param->look.plane_y * sin(param->rot_speed);
		param->look.plane_y = old_plane_x * sin(param->rot_speed)
			+ param->look.plane_y * cos(param->rot_speed);
	}
	else if (key == KEY_RIGHT)
	{
		old_cam_dir_x = param->look.cam_dir_x;
		param->look.cam_dir_x = param->look.cam_dir_x * cos(-param->rot_speed)
			- param->look.cam_dir_y * sin(-param->rot_speed);
		param->look.cam_dir_y = old_cam_dir_x * sin(-param->rot_speed)
			+ param->look.cam_dir_y * cos(-param->rot_speed);

		old_plane_x = param->look.plane_x;
		param->look.plane_x = param->look.plane_x * cos(-param->rot_speed)
			- param->look.plane_y * sin(-param->rot_speed);
		param->look.plane_y = old_plane_x * sin(-param->rot_speed)
			+ param->look.plane_y * cos(-param->rot_speed);
	}
}

int		key_press_down(int key, void *void_param)
{
	t_param	*param;

	param = (t_param *)void_param;
	if (key == KEY_UP || key == KEY_DOWN)
		move(key, param);
	else if (key == KEY_LEFT || key == KEY_RIGHT)
		rotate(key, param);
	else if (key == KEY_ESCAPE)
		close_window(param);
	return (0);
}