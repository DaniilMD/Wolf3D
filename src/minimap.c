#include "wolf3d.h"

void		choose_txtr_for_minimap_sqr(t_param *param, int y, int x)
{
	t_mlx_par *mlx_par;

	mlx_par = &(param->mlx_par);
	if (y == (int)(param->look.pos_y) && x == (int)(param->look.pos_x))
		mlx_par->da_txtr = (int*)mlx_get_data_addr(param->
	imgs_walls[P_TEXTRURE], &mlx_par->bpp_txtr,
	&mlx_par->size_line_txtr, &mlx_par->endian_txtr);
	else if (param->map.map[y][x] >= 1 && param->map.map[y][x] <= 8)
		mlx_par->da_txtr = (int*)mlx_get_data_addr(param->
	imgs_walls[param->map.map[y][x] - 1], &mlx_par->bpp_txtr,
	&mlx_par->size_line_txtr, &mlx_par->endian_txtr);
	else if (param->map.map[y][x] == 20)
		mlx_par->da_txtr = (int*)mlx_get_data_addr(param->
	imgs_walls[8], &mlx_par->bpp_txtr,
	&mlx_par->size_line_txtr, &mlx_par->endian_txtr);
	else if (param->map.map[y][x] == 32)
		mlx_par->da_txtr = (int*)mlx_get_data_addr(param->
	imgs_walls[9], &mlx_par->bpp_txtr,
	&mlx_par->size_line_txtr, &mlx_par->endian_txtr);
	else if (param->map.map[y][x] >= 'a' && param->map.map[y][x] <= 'h')
		mlx_par->da_txtr = (int*)mlx_get_data_addr(param->
	imgs_walls[param->map.map[y][x] - 'a'], &mlx_par->bpp_txtr,
	&mlx_par->size_line_txtr, &mlx_par->endian_txtr);
}

void		set_color_on_minimap(t_param *param, t_minimap_par *mmp)
{
	if (mmp->y == (int)param->look.pos_y && mmp->x == (int)param->look.pos_x)
		param->mlx_par.d_addr[(int)(((double)WINDOW_WIDTH * (mmp->y_sq +
	mmp->y * mmp->sq_h + WINDOW_HEIGHT / 10)) +
	(mmp->x_sq + mmp->x * mmp->sq_w + WINDOW_WIDTH / 10))] =
		param->mlx_par.da_txtr[(mmp->y_sq * TEXTURE_HEIGHT) / mmp->sq_h
	* TEXTURE_WIDTH + (mmp->x_sq * TEXTURE_WIDTH) / mmp->sq_w];
	else if (param->map.map[mmp->y][mmp->x] == 0)
		param->mlx_par.d_addr[(int)(((double)WINDOW_WIDTH * (mmp->y_sq +
	mmp->y * mmp->sq_h + WINDOW_HEIGHT / 10)) + (mmp->x_sq + mmp->x *
	mmp->sq_w + WINDOW_WIDTH / 10))] = 0xFFFFFF;
	else if (param->map.map[mmp->y][mmp->x] == -1)
		param->mlx_par.d_addr[(int)(((double)WINDOW_WIDTH * (mmp->y_sq + mmp->y
	* mmp->sq_h + WINDOW_HEIGHT / 10)) + (mmp->x_sq + mmp->x *
	mmp->sq_w + WINDOW_WIDTH / 10))] = 0x000000;
	else
	{
		param->mlx_par.d_addr[(int)(((double)WINDOW_WIDTH * (mmp->y_sq + mmp->y
	* mmp->sq_h + WINDOW_HEIGHT / 10)) + (mmp->x_sq + mmp->x *
	mmp->sq_w + WINDOW_WIDTH / 10))] =
		param->mlx_par.da_txtr[(mmp->y_sq * TEXTURE_HEIGHT) / mmp->sq_h *
	TEXTURE_WIDTH + (mmp->x_sq * TEXTURE_WIDTH) / mmp->sq_w];
	}
}

void		print_txtred_square(t_param *param, int y, int x)
{
	t_minimap_par mmp;

	mmp.x = x;
	mmp.y = y;
	mmp.sq_h = (int)((double)WINDOW_HEIGHT * 0.8 / param->map.height);
	mmp.sq_w = (int)((double)WINDOW_WIDTH * 0.8 / param->map.length);
	choose_txtr_for_minimap_sqr(param, y, x);
	mmp.y_sq = 0;
	while (mmp.y_sq < mmp.sq_h)
	{
		mmp.x_sq = 0;
		while (mmp.x_sq < mmp.sq_w)
		{
			set_color_on_minimap(param, &mmp);
			mmp.x_sq++;
		}
		mmp.y_sq++;
	}
}

void		minimap(t_param *param)
{
	int x;
	int y;

	y = 0;
	while (y < param->map.height)
	{
		x = 0;
		while (x < param->map.length)
		{
			print_txtred_square(param, y, x);
			x++;
		}
		y++;
	}
}
