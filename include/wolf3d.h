/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximka <maximka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 20:09:27 by maximka           #+#    #+#             */
/*   Updated: 2020/06/12 16:19:19 by maximka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <math.h>
# include <time.h>
# include <pthread.h>
# include "keys.h"
# include "linux_keys.h"
# include "../minilibx-master/mlx.h"

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 800

# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64

# define EO_MAP_Y NULL
# define EO_MAP_X -1

# define WALL_TEXTURES_NUM 11
# define SPRITE_TEXTURES_NUM 4

# define X_SIDE 0
# define Y_SIDE 1

# define DOOR 20
# define PORTAL 32
# define DOOR_TXTR 8
# define NO_DOOR -1
# define DELAY_VAL 100000000.0;

# define PORTAL 32

# define LAMP 0
# define PILLAR 1
# define BARREL 2
# define COIN 3

# define NO_COIN_HIT -1
# define HIT_OBJ -1
# define NO_OBJ_HIT -2

# define ROTATION_SPEED 0.15
# define MOVEMENT_SPEED 0.25

# define FOG_R 0
# define FOG_G 0
# define FOG_B 0
# define SIGHT_DIST 10

# define CROSSES "maps/crosses"
# define JOJO "maps/jojo"
# define LABIRYNTH "maps/labirynth"

# define P_TEXTRURE 10

# define SEC_BETW_FPS 3

typedef struct	s_parse
{
	int			x;
	int			y;
	int			fd;
	int			**map;
}				t_parse;

typedef struct	s_img
{
	int			bpp;
	int			stride;
	int			endian;
	int			*addr;
	int			w;
	int			h;
}				t_img;

typedef struct	s_mlx_par
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	int			*d_addr;
	int			bpp;
	int			size_line;
	int			endian;
	int			im_count;
	int			*da_txtr;
	int			bpp_txtr;
	int			size_line_txtr;
	int			endian_txtr;
	int			im_count_txtr;
	int			*d_addr_sprites;
	int			bpp_sprites;
	int			size_line_sprites;
	int			endian_sprites;
	int			im_count_sprites;
}				t_mlx_par;

typedef struct	s_look_par
{
	double		pos_x;
	double		pos_y;
	double		cam_dir_x;
	double		cam_dir_y;
	double		plane_x;
	double		plane_y;
	double		dir_x;
	double		dir_y;
	int			real_map_x;
	int			real_map_y;
	double		dist_to_side_x;
	double		dist_to_side_y;
	double		d_dist_x;
	double		d_dist_y;
	double		perp_dist_to_wall;
	int			step_x;
	int			step_y;
	int			hit;
	int			hit_side;
	int			line_h;
	int			draw_start;
	int			draw_end;
	double		wall_x;
	int			txtr_num;
	int			txtr_x;
	int			txtr_y;
	double		txtr_step;
	double		txtr_pos;
}				t_look_par;

typedef struct	s_map
{
	int			doors;
	int			sprites;
	int			level;
	int			length;
	int			height;
	int			**map;
}				t_map;

typedef struct	s_fc_par
{
	t_img		floor;
	t_img		ceil;
	double		dir_x_left;
	double		dir_y_left;
	double		dir_x_right;
	double		dir_y_right;
	int			p;
	double		row_dist;
	double		floor_step_x;
	double		floor_step_y;
	double		floor_x;
	double		floor_y;
	int			cell_x;
	int			cell_y;
	int			txtr_x;
	int			txtr_y;
}				t_fc_par;

typedef struct	s_sprite
{
	double		x;
	double		y;
	int			texture;
	double		sprite_dist;
}				t_sprite;

typedef struct	s_spr_par
{
	int			numb_of_sprites;
	t_sprite	*sprites;
	double		z_for_stripes[WINDOW_WIDTH];

	double		sprite_x;
	double		sprite_y;

	double		inv_det;
	double		transformed_x;
	double		transformed_y;

	int			sprite_screen_x;

	int			sprite_height;
	int			draw_start_y;
	int			draw_end_y;

	int			sprite_width;
	int			draw_start_x;
	int			draw_end_x;

	int			tex_x;
	int			tex_y;

	int			d;

	int			move_spr_y;
	double		width_coef;
	double		height_coef;
}				t_spr_par;

typedef struct	s_door
{
	pthread_t	thr;
	int			**map;
	int			door_x;
	int			door_y;
	double		k;
}				t_door;

typedef struct	s_minimap_par
{
	int			x;
	int			y;
	int			x_sq;
	int			y_sq;
	int			sq_w;
	int			sq_h;
}				t_minimap_par;

typedef struct	s_param
{
	t_map		map;
	t_look_par	look;
	double		time;
	double		time_old;
	double		frame_time;
	int			sec_rmmbr;
	double		ms;
	double		rot_speed;
	t_mlx_par	mlx_par;
	void		*imgs_walls[WALL_TEXTURES_NUM];
	void		*imgs_sprites[SPRITE_TEXTURES_NUM];
	t_fc_par	fc_par;
	t_spr_par	spr_par;
	int			coin_hit;
	int			points;
	t_door		*doors;
	int			mmp_flag;
}				t_param;

/*
** main.c
*/

int				stuck_in_door(t_param *param);
int				render(t_param *param);
int				choose_level(t_param *param, char *name);

/*
** define_map.c
*/

double			ft_atoi_for_double(char *line, int *i_now);
int				sprite(int fd, t_param *param, char *name);
int				validate_map(t_map *map);
int				validate_file(char *name);
int				**define_map(char *name, t_map *m, t_param *param);

/*
** init_and_usage.c
*/

int				usage(void);
int				free_space(t_look_par *look, t_map *map);
void			initialize(t_param *param);
void			create_images_walls(t_param *param);
void			create_images_sprites(t_param *param);

/*
** wall_casting_funcs.c
*/

void			initialize_look_vert_line(t_param *param, int x);
void			get_steps_and_d_distances(t_param *param);
void			dda_alg(t_param *param);
void			get_perp_dist_and_line_prop(t_param *param);
void			get_txtr_par(t_param *param);

/*
** wall_casting_core.c
*/

int				choose_wall(int	a);
void			walk_through_stripes(t_param *param);
void			draw_wall_sprite(t_param *param, int x);
void			wall_casting(t_param *param);

/*
** door_funcs_check_hit.c
*/

int				check_door(t_param *param);
void			wall_x_and_per_dist_for_door(t_look_par *look);
int				check_hit(t_param *param);
int				door_animation(t_param *param);

/*
** door_funcs_event.c
*/

void			create_thr_door(t_param *param, int x, int y);
void			*door_shift(void *p);
void			door_sleep(t_door *door, int x, int y);

/*
** floor_and_ceiling_casting.c
*/

void			get_floor_and_ceil_params(t_param *param, int y);
void			fill_horizontal_line(t_param *param, int y);
void			floor_and_ceiling_casting(t_param *param);

/*
** sprite_casting_funcs.c
*/

void			init_sprite_dist(t_param *param);
void			sort_sprites(t_param *param);
void			init_sprite_par(t_param *param, int i);
void			set_sprite_size_and_coef(t_param *param, int i);
void			get_sprite_size_and_pos(t_param *param, int i);

/*
** sprite_casting_core.c
*/
void			sprite_txtr_work(t_param *param, int y, int stripe);
void			sprite_drawer(t_param *param);
void			sprite_casting(t_param *param);

/*
** events.c
*/

void			close_window(t_param *param);
void			free_map(t_param *param);
int				red_cross(t_param *param);
int				key_press_down(int key, void *void_param);
void			press_f(t_param *param);

/*
** movement.c
*/

int				check_object_collision(t_param *param,
	double pos_x, double pos_y);
int				check_collisions(t_param *param, double pos_x,
	double pos_y, char f);
void			move_forw_back(int key, t_param *param);
void			move_left_right(int key, t_param *param);

/*
** rotation.c
*/

void			rotate(int key, t_param *param);
void			rotation_q(t_param *param);
void			rotation_e(t_param *param);

/*
** fog.c
*/

void			mult_rgb(int *r, int *g, int *b);
int				apply_fog(int curr_col, double dist, int mult_on_half);

/*
** free.c
*/

void			free_int_starstar(int **map, int lines);
void			free_everything(t_param *param);
void			finish_program(t_param *param);

/*
** minimap.c
*/

void			choose_txtr_for_minimap_sqr(t_param *param, int y, int x);
void			set_color_on_minimap(t_param *param, t_minimap_par *mmp);
void			print_txtred_square(t_param *param, int y, int x);
void			minimap(t_param *param);

/*
** norm.c
*/

int				valid_norm(t_map *map, int i, int j);
int				**valid_define(char *name, int **map, t_param *param);
int				column(int fd);
int				line(int fd, t_map *map);
void			init_p(t_parse *p);

/*
** norm2.c
*/

int				fill(int fd, int ***map);
void			fill2(t_map *m);
int				count_of_sprites(int fd);
int				check_available_wall(char c);
int				**create_map(int y);

/*
**norm3.c
*/

int				foo(char *p, int *cnt_comma, int *cnt_dot, int *i);
int				norm_val_spr_par(char *spr_p, int *cnt_comma,
				int *cnt_dot, int *i);
int				validate_sprite_par(char *spr_p);
int				norm_valid_file(char c, char prev, int *dog_cnt);
int				walls(int a);

/*
**norm4.c
*/

int				norm_sprite(int fd, char *line, int *n);
int				norm_sprite2(int fd, char *line, int *i_now, t_param *param);
void			print_map(t_map *map);

#endif
