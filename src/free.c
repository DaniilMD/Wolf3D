#include "wolf3d.h"

void	free_int_starstar(int **map, int lines)
{
	int i;

	i = 0;
	while (i < lines)
	{
		map[i] ? free(map[i]) : NULL;
		i++;
	}
	free(map);
}

void	free_everything(t_param *param)
{
	if (param->map.map)
		free_int_starstar(param->map.map, param->map.height);
	if (param->spr_par.numb_of_sprites > 0)
		free(param->spr_par.sprites);
	if (param->map.doors > 0 && param->doors)
		free(param->doors);
}

void	finish_program(t_param *param)
{
	if (param->map.map != NULL)
		free_everything(param);
	ft_putstr("Incorrect map\n");
	(void)param;
	exit(0);
}
