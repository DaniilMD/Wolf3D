/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_casting_core.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximka <maximka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 20:10:25 by maximka           #+#    #+#             */
/*   Updated: 2020/05/11 20:10:26 by maximka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			sprite_txtr_work(t_param *param, int y, int stripe)
{
	t_spr_par	*spr_par;

	spr_par = &(param->spr_par);
	spr_par->d = (y - spr_par->move_spr_y) * 2
		- WINDOW_HEIGHT + spr_par->sprite_height;
	spr_par->tex_y = ((spr_par->d * TEXTURE_HEIGHT)
		/ spr_par->sprite_height) / 2;
	if ((param->mlx_par.d_addr_sprites[TEXTURE_WIDTH * spr_par->tex_y
	+ spr_par->tex_x] & 0x00FFFFFF) != 0)
		param->mlx_par.d_addr[y * WINDOW_WIDTH + stripe] =
			apply_fog(param->mlx_par.d_addr_sprites[TEXTURE_WIDTH
			* spr_par->tex_y + spr_par->tex_x],
	spr_par->transformed_y, 0);
}

void			sprite_drawer(t_param *param)
{
	int			stripe;
	int			y;
	t_spr_par	*spr_par;

	spr_par = &(param->spr_par);
	stripe = spr_par->draw_start_x;
	while (stripe < spr_par->draw_end_x)
	{
		spr_par->tex_x = (int)(2 * (stripe - (-spr_par->sprite_width / 2
	+ spr_par->sprite_screen_x)) * TEXTURE_WIDTH / spr_par->sprite_width) / 2;
		if (spr_par->transformed_y > 0 && stripe > 0 && stripe < WINDOW_WIDTH
			&& spr_par->transformed_y < spr_par->z_for_stripes[stripe])
		{
			y = spr_par->draw_start_y;
			while (y < spr_par->draw_end_y)
			{
				sprite_txtr_work(param, y, stripe);
				y++;
			}
		}
		stripe++;
	}
}

void			sprite_casting(t_param *param)
{
	int			i;
	t_spr_par	*spr_par;

	if (param->spr_par.numb_of_sprites == 0)
		return ;
	spr_par = &(param->spr_par);
	init_sprite_dist(param);
	sort_sprites(param);
	i = 0;
	while (i < param->spr_par.numb_of_sprites)
	{
		if (spr_par->sprites[i].texture == -1)
		{
			i++;
			continue;
		}
		param->mlx_par.d_addr_sprites = (int*)mlx_get_data_addr(param->
	imgs_sprites[spr_par->sprites[i].texture], &param->mlx_par.bpp_sprites,
	&param->mlx_par.size_line_sprites, &param->mlx_par.endian_sprites);
		init_sprite_par(param, i);
		get_sprite_size_and_pos(param, i);
		sprite_drawer(param);
		i++;
	}
}
