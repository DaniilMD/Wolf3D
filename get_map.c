#include "wolf3d.h"

int			free_before_return(t_param *param, char *line, int ret_num)
{
	int	i;

	if (param->map != NULL)
	{
		i = 0;
		while (i < param->msize_y)
		{
			free(param->map[i]);
			i++;
		}
		free(param->map);
	}
	if (line != NULL)
		free(line);
	return (ret_num);
}

int			get_size_and_malloc_map(t_param *param, char *line_one)
{
	char	**x_and_y;
	int		i;
	int		xs;
	
	i = 0;
	xs = 0;
	while (line_one[i] != '\0')
	{
		if (line_one[i] == 'x')
			xs++;
		if ((line_one[i] > '9' || line_one[i] < '0') && line_one[i] != 'x')
			return (0);
		if(xs > 1)
			return (0);
		i++;
	}
	x_and_y = ft_strsplit(line_one, 'x');
	if (x_and_y[0] == NULL || x_and_y[1] == NULL || x_and_y[2] != NULL)
	{
		free_char_starstar(x_and_y);
		return (0);
	}
	///////////////////////////////////////////
	param->msize_x = ft_atoi(x_and_y[0]);
	param->msize_y = ft_atoi(x_and_y[1]);
	free_char_starstar(x_and_y);
	if (!(param->map = (int**)malloc(sizeof(int*) * (param->msize_y + 1))))
		return (0);
	param->map[param->msize_y] = EO_MAP_Y;
	/////////////////////////////////
	i = 0;
	while (i < param->msize_y)
	{
		if (!(param->map[i] = (int*)malloc(sizeof(int) * param->msize_x + 1)))
			return (0);
		param->map[i][param->msize_x] = EO_MAP_X;
		i++;
	}
	return (1);
}

int			validate_line(t_param *param, char* line)
{
	int	i;
	int	commas;

	i = 0;
	commas = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ',')
		{
			if (i == 0 || line[i + 1] == '\0')
				return (0);
			commas++;
		}
		if (line[i] > '9' && line[i] < '0' && line[i] != ',')
			return (0);
		i++;
	}
	if (commas != param->msize_x - 1)
		return (0);
	return (1);
}

void		fill_mapline(t_param *param, char *line, int lines_y)
{
	char	**splitted;
	int		i;

	splitted = ft_strsplit(line, ',');
	i = 0;
	while (i < param->msize_x)
	{
		param->map[lines_y][i] = ft_atoi(splitted[i]);
		i++;
	}
	free_char_starstar(splitted);
}




void		print_map(t_param *param)
{
	int i;
	int j;

	i = 0;
	while (i < param->msize_y)
	{
		j = 0;
		while (j < param->msize_x)
		{
			printf("%d, ",param->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}

}






int			read_map(t_param *param, char *name)
{
	char	*line;
	int		fd;
	int		lines_y;

	fd = open(name, O_RDONLY);
	if (get_next_line(fd, &line) > 0)
	{
		if (get_size_and_malloc_map(param, line) == 0)
			return (free_before_return(param, line, 0));//0);
		free(line);
	}
	else
		return (free_before_return(param, NULL, 0));//0);
	lines_y = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (validate_line(param, line) == 0)
			return (free_before_return(param, line, 0));//0);
		fill_mapline(param, line, lines_y);
		lines_y++;
		free(line);
	}
	if (lines_y != param->msize_y)
		return (free_before_return(param, NULL, 0));//0);


	print_map(param);


	return (1);//free_before_return(param, NULL, 1));//1);
}