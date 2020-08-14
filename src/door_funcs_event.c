#include "wolf3d.h"

void	create_thr_door(t_param *param, int x, int y)
{
	int	i;

	i = 0;
	while (i < param->map.doors)
	{
		if (x == param->doors[i].door_x &&
			y == param->doors[i].door_y)
			return ;
		i++;
	}
	i = 0;
	while (i < param->map.doors)
	{
		if (param->doors[i].door_x == -1 && param->doors[i].door_y == -1)
		{
			param->doors[i].door_x = x;
			param->doors[i].door_y = y;
			param->doors[i].k = 0;
			pthread_create(&param->doors[i].thr, NULL,
				door_shift, (void*)&param->doors[i]);
			break ;
		}
		i++;
	}
}

void	*door_shift(void *curr_door)
{
	int		x;
	int		y;
	double	delay;
	int		i;
	t_door	*door;

	door = (t_door*)curr_door;
	delay = DELAY_VAL;
	x = door->door_x;
	y = door->door_y;
	i = -1;
	while (++i < delay)
		door->k = i / delay;
	door_sleep(door, x, y);
	i = -1;
	while (++i < delay)
		door->k = (delay - i) / delay;
	door->door_x = -1;
	door->door_y = -1;
	door->k = 0;
	pthread_exit(NULL);
	return (NULL);
}

void	door_sleep(t_door *door, int x, int y)
{
	door->map[door->door_y][door->door_x] = 0;
	door->door_y = -2;
	door->door_x = -2;
	sleep(3);
	door->door_y = y;
	door->door_x = x;
	door->map[door->door_y][door->door_x] = DOOR;
}
