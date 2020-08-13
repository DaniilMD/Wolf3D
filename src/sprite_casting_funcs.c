/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_casting_funcs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximka <maximka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 20:10:30 by maximka           #+#    #+#             */
/*   Updated: 2020/05/11 20:10:31 by maximka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			init_sprite_dist(t_param *param)
{
	t_spr_par	*spr_par;
	int			i;

	spr_par = &(param->spr_par);
	i = 0;
	while (i < param->spr_par.numb_of_sprites)
	{
		spr_par->sprites[i].sprite_dist = ((param->look.pos_x
	- spr_par->sprites[i].x) * ((param->look.pos_x - spr_par->sprites[i].x)))
	+ ((param->look.pos_y - spr_par->sprites[i].y)
	* ((param->look.pos_y - spr_par->sprites[i].y)));
		i++;
	}
}

void			sort_sprites(t_param *param)
{
	int			i;
	int			j;
	t_spr_par	*spr_par;
	t_sprite	spr;

	spr_par = &(param->spr_par);
	i = 0;
	while (i < param->spr_par.numb_of_sprites)
	{
		j = i;
		while (j < param->spr_par.numb_of_sprites)
		{
			if (spr_par->sprites[j].sprite_dist
				> spr_par->sprites[i].sprite_dist)
			{
				spr = spr_par->sprites[j];
				spr_par->sprites[j] = spr_par->sprites[i];
				spr_par->sprites[i] = spr;
			}
			j++;
		}
		i++;
	}
}

void			init_sprite_par(t_param *param, int i)
{
	t_spr_par	*spr_par;

	spr_par = &(param->spr_par);
	spr_par->sprite_x = spr_par->sprites[i].x - param->look.pos_x;
	spr_par->sprite_y = spr_par->sprites[i].y - param->look.pos_y;
	spr_par->inv_det = 1.0 / (param->look.plane_x * param->look.cam_dir_y
		- param->look.cam_dir_x * param->look.plane_y);
	spr_par->transformed_x = spr_par->inv_det
	* (param->look.cam_dir_y * spr_par->sprite_x
		- param->look.cam_dir_x * spr_par->sprite_y);
	spr_par->transformed_y = spr_par->inv_det
	* (-param->look.plane_y * spr_par->sprite_x
		+ param->look.plane_x * spr_par->sprite_y);
	spr_par->sprite_screen_x = (int)((WINDOW_WIDTH / 2)
		* (1 + spr_par->transformed_x / spr_par->transformed_y));
}

void			set_sprite_size_and_coef(t_param *param, int i)
{
	t_spr_par	*spr_par;

	spr_par = &(param->spr_par);
	spr_par->move_spr_y = 0;
	spr_par->width_coef = 1;
	spr_par->height_coef = 1;
	if (spr_par->sprites[i].texture == COIN)
	{
		spr_par->height_coef = 0.3;
		spr_par->width_coef = 0.3;
		spr_par->move_spr_y = (int)(300.0 / spr_par->transformed_y);
	}
	if (spr_par->sprites[i].texture == LAMP)
	{
		spr_par->height_coef = 1 / 1.5;
		spr_par->width_coef = 1 / 1.5;
		spr_par->move_spr_y = (int)(-150.0 / spr_par->transformed_y);
	}
}

void			get_sprite_size_and_pos(t_param *param, int i)
{
	t_spr_par	*spr_par;

	spr_par = &(param->spr_par);
	set_sprite_size_and_coef(param, i);
	spr_par->sprite_height = fabs((int)(WINDOW_HEIGHT / (spr_par->transformed_y))
		* spr_par->height_coef);
	spr_par->draw_start_y = WINDOW_HEIGHT / 2 - spr_par->sprite_height / 2
		+ spr_par->move_spr_y;
	if (spr_par->draw_start_y < 0)
		spr_par->draw_start_y = 0;
	spr_par->draw_end_y = WINDOW_HEIGHT / 2 + spr_par->sprite_height / 2
		+ spr_par->move_spr_y;
	if (spr_par->draw_end_y >= WINDOW_HEIGHT)
		spr_par->draw_end_y = WINDOW_HEIGHT - 1;
	spr_par->sprite_width = fabs((int)(WINDOW_HEIGHT / (spr_par->transformed_y))
		* spr_par->width_coef);
	spr_par->draw_start_x = spr_par->sprite_screen_x
		- spr_par->sprite_width / 2;
	if (spr_par->draw_start_x < 0)
		spr_par->draw_start_x = 0;
	spr_par->draw_end_x = spr_par->sprite_screen_x + spr_par->sprite_width / 2;
	if (spr_par->draw_end_x >= WINDOW_WIDTH)
		spr_par->draw_end_x = WINDOW_WIDTH - 1;
}
