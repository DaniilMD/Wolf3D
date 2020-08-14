#include "wolf3d.h"

int				choose_wall(int a)
{
	if (a == PORTAL)
		return (9);
	if (a == DOOR)
		return (8);
	if (a >= 'a' && a <= 'h')
		return (a - 97);
	return (a - 1);
}

void			walk_through_stripes(t_param *param)
{
	int			x;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		initialize_look_vert_line(param, x);
		get_steps_and_d_distances(param);
		dda_alg(param);
		get_perp_dist_and_line_prop(param);
		get_txtr_par(param);
		draw_wall_sprite(param, x);
		param->spr_par.z_for_stripes[x] = param->look.perp_dist_to_wall;
		x++;
		param->look.perp_dist_to_wall = -1;
	}
}

void			draw_wall_sprite(t_param *param, int x)
{
	int			y;
	t_mlx_par	*mlx_par;
	t_look_par	*look;

	mlx_par = &(param->mlx_par);
	look = &(param->look);
	mlx_par->da_txtr = (int*)mlx_get_data_addr(param->
	imgs_walls[look->txtr_num], &mlx_par->bpp_txtr, &mlx_par->size_line_txtr,
	&mlx_par->endian_txtr);
	y = look->draw_start;
	while (y < look->draw_end)
	{
		look->txtr_y = (int)look->txtr_pos & (TEXTURE_HEIGHT - 1);
		look->txtr_pos += look->txtr_step;
		if (look->hit_side == Y_SIDE)
			mlx_par->d_addr[y * WINDOW_WIDTH + x] = apply_fog(mlx_par->da_txtr
	[TEXTURE_WIDTH * look->txtr_y + look->txtr_x], look->perp_dist_to_wall, 1);
		else
		{
			mlx_par->d_addr[y * WINDOW_WIDTH + x] = apply_fog(mlx_par->da_txtr
	[TEXTURE_WIDTH * look->txtr_y + look->txtr_x],
		look->perp_dist_to_wall, 0);
		}
		y++;
	}
}

void			wall_casting(t_param *param)
{
	t_mlx_par	*mlx_par;

	mlx_par = &(param->mlx_par);
	param->mlx_par.d_addr = (int*)mlx_get_data_addr(param->
	mlx_par.img_ptr, &param->mlx_par.bpp, &param->mlx_par.size_line,
	&param->mlx_par.endian);
	mlx_clear_window(mlx_par->mlx_ptr, mlx_par->win_ptr);
	walk_through_stripes(param);
	sprite_casting(param);
	if (param->mmp_flag > 0)
		minimap(param);
	mlx_put_image_to_window(mlx_par->mlx_ptr, mlx_par->win_ptr,
		mlx_par->img_ptr, 0, 0);
	mlx_destroy_image(mlx_par->mlx_ptr, mlx_par->img_ptr);
	mlx_par->img_ptr = mlx_new_image(mlx_par->mlx_ptr,
		WINDOW_WIDTH, WINDOW_HEIGHT);
}
