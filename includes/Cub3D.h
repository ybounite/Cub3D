/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:57:09 by ybounite          #+#    #+#             */
/*   Updated: 2025/08/14 09:54:28 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include  <math.h> 
# include <stdbool.h>
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>

# include "../libraries/getline/get_next_line.h"
# include "../libraries/libft/libft.h"

# define CLEAR	0
# define ALLOC	1
# define STDERR	2

# define WINDOW_WIDTH 1000 // cols
# define WINDOW_HEIGHT 600 //rows
# define TILE_SIZE 32
# define PI 3.141592653589793
# define FOV 60 * (PI /180) // <- convert in radin (degree * 180/PI)
# define MOVE_SPEED 2
# define ROTATION_SPEED 0.2618
# define NUM_RAYS 200
// color 
#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define YELLOW 0xFFFF00
#define GRAY 0x808080
#define DARK_GRAY 0x404040

# define NONE 0
# define HORIZONTAL 1
# define VERTICAL 2
typedef enum 
{
	NO_TEXTURE,  // North
	SO_TEXTURE,  // South
	WE_TEXTURE,  // West
	EA_TEXTURE,  // East
	C_COLOR,
	F_COLOR,
	IDNTIFIER_TEXTURE,
	TEXTURE_COUNT
}	t_texture_type;

enum e_keycodes
{
    W_KEY = 'w',
    A_KEY = 'a',
    S_KEY = 's',
    D_KEY = 'd',
    ESCAPE = 65307,
    LEFT_ARROW = 65361,
    RIGHT_ARROW = 65363
};

typedef	enum	s_spawm_direction
{
	NORTH,
	SOUTH,
	EAST,
	WEST
	// ESCAPE = 65307
}	t_spawm_dir;

typedef struct s_config
{
	char	*textures[TEXTURE_COUNT]; 
	int		floor_color;
	int		ceiling_color;
}				t_config;

typedef struct s_player
{
	double		_x;
	double		_y;
	double		angle;
}				t_player;

typedef struct s_point
{
	double		x;
	double		y;
}				t_point;

typedef struct	s_imag
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_imag;

typedef	struct s_ray
{
	double		ray_angle;//
	double		step_angle;
	double		distance;//
	double		h_distance;
	double		v_distance;
	int		wall_type;
	t_point		player;
	t_point		first_inters_h;
	t_point		first_inters_v;
	t_point		step_h;
	t_point		step_v;
	t_point		hit;
	t_point		v_inters;
	t_point		h_inters; // this forst point this 
}	t_ray;

typedef struct	s_game
{
	short		fd;
	short		size;
	char		**map;
	char		**map_cpy;
	void		*_mlx;
	void		*_win_mlx;
	char		spawm_dir;
	int		map_width;
	int		map_height;
	t_imag		*_img;
	t_list		*list;
	t_list		*map_start;
	t_config	*config;
	t_player	*player;
	t_ray		ray;
}				t_data_game;

/* -------------------------------------------------------------------------- */
/*                             check_file_name.c                              */
/* -------------------------------------------------------------------------- */
bool			check_filename(char *file_name, char *str);
void			check_file_name(char *file_name);

/* -------------------------------------------------------------------------- */
/*                             syntax_error.c                                 */
/* -------------------------------------------------------------------------- */
void			syntax_error(short option);

// parse_maps.c 
void	        parse_config(t_data_game *_game);
char	        **parse_map(t_data_game *_game);
bool        	parsing(char *filename, t_data_game *_game);

// file_reading.c
t_list	        *listnew(void *content);
t_list      	*file_reading(short fd);
void	        Print_list(t_list *_list);

/* -------------------------------------------------------------------------- */
/*                             angle_direction.c                              */
/* -------------------------------------------------------------------------- */
void			normalize_angle(double *angle);
bool			is_facing_down(double angle);
bool			is_facing_up(double angle);
bool			is_facing_right(double angle);
bool			is_facing_left(double angle);

/* -------------------------------------------------------------------------- */
/*                            horizontal_intersection.c                       */
/* -------------------------------------------------------------------------- */
/* 			HORIZONTAL INTERSECTION */
bool			cast_horizontal(t_data_game *g, t_ray *ray,
			       t_point *hit, double *dist);

/* -------------------------------------------------------------------------- */
/*                            vertical_intersection.c                         */
/* -------------------------------------------------------------------------- */
/* VERTICAL INTERSECTION */
bool			cast_vertical(t_data_game *g, t_ray *ray,
				t_point *hit, double *dist);

/* -------------------------------------------------------------------------- */
/*                          collision_check.c 		                      */
/* -------------------------------------------------------------------------- */
bool			_hase_wall(t_data_game *_game, double dx, double dy);
bool			is_wall(t_data_game *_game, double x, double y);

/* -------------------------------------------------------------------------- */
/*                          player_control.c 		                      */
/* -------------------------------------------------------------------------- */
int			control_key_(int keycode, t_data_game *_game);
void			_player_move(int key, t_data_game *_game);

// init player
void			player_position(t_data_game *_game);
void			init_player_direction(t_data_game *_game, char spawn_dir);
void			player_init(t_data_game *_game);

// check_allowed_characters.c
bool			check_allowed_characters(t_data_game *_game);
bool			isplayer_position(char c);


bool			parse_texture_line(t_data_game *_game, char *line);
t_texture_type	get_texturs_type(char *line);

// control keypriss
int				_destory_window(t_data_game *_game);
int				control_key_(int keycode, t_data_game *_game);
void			render_map(t_data_game *_game);
// check_filename
void			validate_textures(t_config *_config);

// _mlx_init
bool			_mlx_init_data(t_data_game *_game);
void			 start_simulation(t_data_game *_game);

/* -------------------------------------------------------------------------- */
/*                             map_renderer.c                                 */
/* -------------------------------------------------------------------------- */
void					draw_map(t_data_game *_game);
void					my_mlx_pixel_put(t_imag *_img, int x, int y, int color);

void validate_colors(t_config *_config);
void map_is_closed(char **map, short size);
bool is_valid_map(t_data_game *_game);

void		raycasting(t_data_game *_game);
void		draw_line(t_data_game *_game, t_point start_p, t_point end_p, int color);
bool		is_wall(t_data_game *_game, double x, double y);

void	cast_all_rays(t_data_game *_game);
#endif
