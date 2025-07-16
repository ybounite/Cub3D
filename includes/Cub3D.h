/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:57:09 by ybounite          #+#    #+#             */
/*   Updated: 2025/07/16 10:40:34 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include  <math.h> 
# include <stdbool.h>
# include <mlx.h>
# include <X11/X.h>

# include "../libraries/getline/get_next_line.h"
# include "../libraries/libft/libft.h"

# define CLEAR	0
# define ALLOC	1
# define STDERR	2

# define WINDOW_WIDTH 1000
# define WINDOW_HEIGHT 600
# define TILE_SIZE 32
# define PI 3.141592653589793
# define FOV 60
# define MOVE_SPEED 1

// color 
#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define YELLOW 0xFFFF00
#define GRAY 0x808080
#define DARK_GRAY 0x404040

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
    LEFT_ARROW = 123,
    RIGHT_ARROW = 124
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
    double		_dir_x;
    double		_dir_y;


    double rotationAngle;
    double moveSpeed;
    double rotationSpeed;

    int walkdirection;
    int turndirection;
	double		_plane_x;
	double		_plane_y;
	short		turn_direction;
	double		rotation_andle;
}		t_player;

typedef struct	s_game
{
	short		fd;
	short		size;
	char		**map;
	char		**map_cpy;
	short		win_w;
	short		win_h;
	void		*img;
	char		*img_addr;
	int			bp_pixel;
	int			line_length;
	int			endian;
	void		*_mlx;
	void		*_win_mlx;
	short		Playr_x;
	short		Playr_y;
	char		spawm_dir;
	t_list		*list;
	t_list		*map_start;
	t_config	*config;
	t_player	*player;
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
void		_mlx_init_data(t_data_game *_game);
void		 start_simulation(t_data_game *_game);

void validate_colors(t_config *_config);

#endif