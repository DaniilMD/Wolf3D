#include "wolf3d.h"

int			hard_stuck(t_param *param, double y, double x)
{
	if (param->map.map[(int)(y + 1.1)][(int)x] == DOOR)
		param->look.pos_y += 1.1;
	else if (param->map.map[(int)(y - 1.1)][(int)x] == DOOR)
		param->look.pos_y -= 1.1;
	else if (param->map.map[(int)y][(int)(x + 1.1)] == DOOR)
		param->look.pos_x += 1.1;
	else if (param->map.map[(int)y][(int)(x - 1.1)] == DOOR)
		param->look.pos_x -= 1.1;
	return (1);
}

int			stuck_in_door(t_param *param)
{
	double			x;
	double			y;

	x = param->look.pos_x;
	y = param->look.pos_y;
	if (param->map.map[(int)y][(int)x] == DOOR)
	{
		ft_putstr("Stuck in door\n");
		if (param->map.map[(int)(y + 1.1)][(int)x] == 0)
			param->look.pos_y += 1.1;
		else if (param->map.map[(int)y][(int)(x - 1.1)] == 0)
			param->look.pos_x -= 1.1;
		else if (param->map.map[(int)(y - 1.1)][(int)x] == 0)
			param->look.pos_y -= 1.1;
		else if (param->map.map[(int)y][(int)(x + 1.1)] == 0)
			param->look.pos_x += 1.1;
		else
			hard_stuck(param, y, x);
	}
	return (1);
}

int			render(t_param *param)
{
	stuck_in_door(param);
	floor_and_ceiling_casting(param);
	wall_casting(param);
	param->coin_hit = NO_COIN_HIT;
	check_object_collision(param, param->look.pos_x, param->look.pos_y);
	if (param->coin_hit != NO_COIN_HIT)
	{
		param->spr_par.sprites[param->coin_hit].texture = -1;
		param->points++;
		ft_putstr("Points: ");
		ft_putnbr(param->points);
		ft_putstr("\n");
	}
	param->time_old = param->time;
	param->time = (double)clock();
	param->frame_time = (param->time - param->time_old) / CLOCKS_PER_SEC;
	if ((int)(clock() / CLOCKS_PER_SEC) % SEC_BETW_FPS == 0
		&& (int)(clock() / CLOCKS_PER_SEC) > param->sec_rmmbr)
	{
		param->sec_rmmbr = (int)(clock() / CLOCKS_PER_SEC);
		ft_putstr("FPS: ");
		ft_putnbr(1.0 / param->frame_time);
		ft_putstr("\n");
	}
	return (0);
}

int			choose_level(t_param *param, char *name)
{
	int fd;

	fd = open(name, O_RDONLY);
	if (fd < 0)
		return (0);
	if (ft_strcmp(name, LABIRYNTH) == 0)
		param->map.level = 1;
	else if (ft_strcmp(name, JOJO) == 0)
		param->map.level = 2;
	else if (ft_strcmp(name, CROSSES) == 0)
		param->map.level = 3;
	else
		param->map.level = -1;
	return (1);
}

int			main(int argc, char **argv)
{
	t_param	param;

	if (argc != 2)
		return (usage());
	if (choose_level(&param, argv[1]) == 0)
		return (usage());
	if (!(param.map.map = define_map(argv[1], &(param.map), &param)))
		finish_program(&param);
	(validate_map(&param.map) == 1) ? NULL : finish_program(&param);
	initialize(&param);
	print_map(&param.map);
	param.points = 0;
	param.mlx_par.mlx_ptr = mlx_init();
	param.mlx_par.win_ptr = mlx_new_window(param.mlx_par.mlx_ptr,
		WINDOW_WIDTH, WINDOW_HEIGHT, "Wolf3D");
	param.mlx_par.img_ptr = mlx_new_image(param.mlx_par.mlx_ptr,
		WINDOW_WIDTH, WINDOW_HEIGHT);
	create_images_walls(&param);
	create_images_sprites(&param);
	mlx_loop_hook(param.mlx_par.mlx_ptr, &render, &param);
	mlx_hook(param.mlx_par.win_ptr, 2, 1L << 0, &key_press_down, (void*)&param);
	mlx_hook(param.mlx_par.win_ptr, 17, 1L << 17, red_cross, &param);
	mlx_loop(param.mlx_par.mlx_ptr);
	return (0);
}
