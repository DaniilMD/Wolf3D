#include "wolf3d.h"

int			wrong_num_of_args(void)
{
	ft_putstr("Wrong number of arguments. \
You can send only 1 map to the wolf3d executable\n");
	return (-1);
}


void		initialize(t_param *param)
{
	param->map = NULL;

	param->look.pos_x = 22;
	param->look.pos_y = 12;
	param->look.cam_dir_x = -1;
	param->look.cam_dir_y = 0;
	param->look.plane_x = 0;
	param->look.plane_y = 0.66;

	param->time = 0;
	param->time_old = 0;
}
