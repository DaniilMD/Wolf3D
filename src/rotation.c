#include "wolf3d.h"

void		rotate(int key, t_param *param)
{
	if (key == KB_Q)
		rotation_q(param);
	else if (key == KB_E)
		rotation_e(param);
}

void		rotation_q(t_param *param)
{
	double	old_cam_dir_x;
	double	old_plane_x;

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

void		rotation_e(t_param *param)
{
	double	old_cam_dir_x;
	double	old_plane_x;

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
