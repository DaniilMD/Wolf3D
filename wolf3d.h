#ifndef WOLF3D_H
# define WOLF3D_H
# include "libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <math.h>



# include <mlx.h>
# include <pthread.h>


#include <time.h>


# include "/Users/openelop/.brew/Cellar/glew/2.1.0_1/include/GL/glew.h"
// #define GLFW_DLL
# include "/Users/openelop/.brew/Cellar/glfw/3.3.2/include/GLFW/glfw3.h"


///////////////          !!!УДОЛИ!!!

#include <stdio.h>

///////////////          !!!УДОЛИ!!!




# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 1080

# define X_SIDE 0
# define Y_SIDE 1


// # define THREADS_NUM 10


# define EO_MAP_Y NULL
# define EO_MAP_X -1

typedef struct	s_mlx_par
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*mlx_data_addr;
	int			bpp;
	int			size_line;
	int			endian;
	int			im_count;
}				t_mlx_par;

typedef struct	s_look_par
{
	/*
	**			My position and look.
	*/
	double		pos_x;
	double		pos_y;

	double		cam_dir_x;
	double		cam_dir_y;

	double		plane_x;
	double		plane_y;

	double		dir_x;
	double		dir_y;


	/*
	**			Different look params.
	*/

	int			real_map_x;
	int			real_map_y;

	//length of ray from current position to next x or y-side
	double 		dist_to_side_x;
    double		dist_to_side_y;

	double 		d_dist_x;
    double		d_dist_y;




	double		perp_dist_to_wall;




	//what direction to step in x or y-direction (either +1 or -1)
	int			step_x;
	int			step_y;

	//was there a wall hit?
	int			hit;

	//was a NS or a EW wall hit?
	int			hit_side;



	int			line_h;
	int			draw_start;
	int			draw_end;


	int			colour;

}				t_look_par;

typedef struct	s_param
{
	int			msize_x;
	int			msize_y;
	int			**map;
	
	t_look_par	look;

	double		time;
	double		time_old;


	double		frame_time;

	//speed modifiers
   
	//the constant value is in squares/second
	double		ms;
	//the constant value is in radians/second
	double		rot_speed;










	t_mlx_par	mlx_par;
	// void		*imgs[10];
}				t_param;

// typedef struct	s_for_threads
// {
// 	t_param		param;
// 	int			thread_num;
// 	int			*iters;
// }				t_for_threads;









/*
** main.c
*/

/*
** get_map.c
*/

int				get_size_and_malloc_map(t_param *param, char *line_one);
int				validate_line(t_param *param, char* line);
void			fill_mapline(t_param *param, char *line, int lines_y);
int				read_map(t_param *param, char *name);










void		print_map(t_param *param);



/*
** init_and_usage.c
*/

int				wrong_num_of_args(void);
void			initialize(t_param *param);


/*
** events.c
*/

void			close_window(t_param *param);
void			move(int key, t_param *param);
int				key_press_down(int key, void *void_param);

#endif
