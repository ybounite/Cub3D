/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:45:16 by ybounite          #+#    #+#             */
/*   Updated: 2025/08/02 11:16:18 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

void	_player_move(int key, t_data_game *_game)
{
	if (key == S_KEY)
	{
		_game->player->_x += cos(_game->player->angle) * MOVE_SPEED;
		_game->player->_y += sin(_game->player->angle) * MOVE_SPEED;
	}
	else if (key == W_KEY)
	{
		_game->player->_x -= cos(_game->player->angle) * MOVE_SPEED;
		_game->player->_y -= sin(_game->player->angle) * MOVE_SPEED;
	}
	else if (key == D_KEY)
	{
		_game->player->_x += cos(_game->player->angle - M_PI_2) * MOVE_SPEED;
		_game->player->_y += sin(_game->player->angle - M_PI_2) * MOVE_SPEED;
	}
	else if (key == A_KEY)
	{
		_game->player->_x += cos(_game->player->angle + M_PI_2) * MOVE_SPEED;
		_game->player->_y += sin(_game->player->angle + M_PI_2) * MOVE_SPEED;
	}
}

void	my_mlx_pixel_put(t_imag *_img, int x, int y, int color)
{
	char	*dst;
	if (x < 0 || y < 0 || x >= _img->width || y >= _img->height)
		return ;
	dst = _img->addr + (y * _img->line_length + x * (_img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	clear_image(t_imag *img, int color)
{

    int y = 0;
    int x;
    while (y < img->height)
    {
        x = 0;
        while (x < img->width)
        {
            my_mlx_pixel_put(img, x, y, color);
            x++;
        }
        y++;
    }
}

void	sdraw_line(t_data_game *_game)
{
	double	x = _game->player->_x;
	double	y = _game->player->_y;
	double	dx = cos(_game->player->angle) * -1;
	double	dy = sin(_game->player->angle) * -1;
	int		i;
	i = 0;
	while (i < 15) // length of line
	{
		if (_game->map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] == '1')
			break ;
		my_mlx_pixel_put(_game->_img, (int)x, (int)y, 0x000000);
		x += dx;
		y += dy;
		i++;
	}
}
/*
void	draw_ray(t_data_game *_game, double angle, int color)
{
	double rx = _game->player->_x;
	double ry = _game->player->_y;

	double dx = cos(angle) * -1;
	double dy = sin(angle) * -1;
	while (true)
	{
        	int map_x = (int)(rx / TILE_SIZE);
	        int map_y = (int)(ry / TILE_SIZE);
        	if (_game->map[map_y][map_x] == '1')
	            break;
	        if (rx < 0 || ry < 0 || map_x >= _game->map_width || map_y >= _game->map_height)
        	    break;
	        my_mlx_pixel_put(_game->_img, (int)rx, (int)ry, color);
	        rx += dx;
        	ry += dy;
	}
}

int	render(t_data_game *_game)
{
	static short	frame;
	if (frame == 100){
		// clear_image(_game->_img, BLACK);
		draw_map(_game);
		// cast_all_rays(_game);
		draw_ray(_game, _game->player->angle, BLACK);
		// raycasting(_game);
        mlx_put_image_to_window(_game->_mlx, _game->_win_mlx, _game->_img->img, 0, 0);
		frame = 0;
	}
	frame++;
	return 0;
}*/

// bool	is_perpendicular_to_Yaxis(double ray_angle)

// #define RAY_STEP (FOV_ANGLE / NUM_RAYS)
/*
double	cast_single_ray(t_data_game *_game, int *hit_vertical)
{
	double (x), (y), (dx), (dy);

	x = _game->player->_x;
	y = _game->player->_y;
	dx = cos(_game->player->angle) * -1;
	dy = sin(_game->player->angle) * -1;
	while (true)
	{
		if (_game->map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] == '1')
		{
			*hit_vertical = 0;
			break ;
		}
		x += dx;
		y += dy;
	}
	return (sqrt(pow((x - _game->player->_x), 2)) + pow((y - _game->player->_y), 2));
}

void	draw_3d_projection(t_data_game *_game, int column, double ray_angle, int hit_vertical)
{
    // Fisheye correction
    double corrected = _game->ray.distance * cos(ray_angle - _game->player->angle);

    // Projected wall height
    double proj_plane = (WINDOW_WIDTH / 2) / tan(FOV / 2);
    double wall_height = (TILE_SIZE / corrected) * proj_plane;

    int wall_top = (WINDOW_HEIGHT / 2) - (wall_height / 2);
    int wall_bottom = (WINDOW_HEIGHT / 2) + (wall_height / 2);

    int wall_color = hit_vertical ? 0xAAAAAA : 0xFFFFFF;

    // Draw column (vertical line)
    for (int y = 0; y < WINDOW_HEIGHT; y++)
    {
        if (y < wall_top)
            my_mlx_pixel_put(_game->_img, column, y, 0x87CEEB); // Sky
        else if (y >= wall_top && y <= wall_bottom)
            my_mlx_pixel_put(_game->_img, column, y, wall_color); // Wall
        else
            my_mlx_pixel_put(_game->_img, column, y, 0x333333); // Floor
    }
}

void	cast_all_rays(t_data_game *_game)
{
	double	start_angle;
	double	ray_angle;
	short	i;
	int hit_vertical;

	i = 0;
	start_angle = _game->player->angle - (FOV / 2);
	while (i < NUM_RAYS)
	{
		ray_angle = start_angle + i * (FOV / NUM_RAYS);
		ray_angle = config_normaliz_angle(ray_angle);
		_game->ray.distance = cast_single_ray(_game, &hit_vertical);
		//draw_3d_projection(_game, i, ray_angle, hit_vertical);
		draw_ray(_game, ray_angle, 0x00FF00); // Green color for visibility
		i++;
	}
}*/
/*
void cast_all_rays(t_data_game *_game)
{
	double start_angle = _game->player->angle - (FOV / 2);
	for (int i = 0; i < NUM_RAYS; i++)
	{
		double ray_angle = start_angle + i * (FOV / NUM_RAYS);
        	// Normalize angle between 0 and 2π
		if (ray_angle < 0)
		ray_angle += 2 * PI;
		if (ray_angle > 2 * PI)
		ray_angle -= 2 * PI;
		draw_ray(_game, ray_angle, 0x00FF00); // Green color for visibility
	}
}*/

int render(t_data_game *_game)
{
	static short frame;

	if (frame == 100)
	{
		draw_map(_game);
		cast_all_rays(_game);  // Draw all rays in a FOV
		sdraw_line(_game);
		//draw_ray(_game, _game->player->angle, 0x00FF00);
		mlx_put_image_to_window(_game->_mlx, _game->_win_mlx, _game->_img->img, 0, 0);
		frame = 0;
	}
	frame++;
	return 0;
}

bool	is_wall(t_data_game *_game, double x, double y)
{
	int	grid_x;
	int	grid_y;

	grid_x = (int)(x / TILE_SIZE);
	grid_y = (int)(y / TILE_SIZE);
	if (grid_x < 0 || grid_y < 0 || grid_y >= _game->map_height || grid_x >= _game->map_width)
		return (true);
	if (_game->map[grid_y][grid_x] == '1')
		return (true);
	return (false);
}

int	control_key_(int keycode, t_data_game *_game)
{
	double	(old_player_x), (old_player_y);
	(1) && (old_player_y = _game->player->_y), (old_player_x = _game->player->_x);
	if (keycode == ESCAPE)
	{
		mlx_destroy_window(_game->_mlx, _game->_win_mlx);
		ft_malloc(CLEAR, CLEAR);
		exit(EXIT_SUCCESS);
	}
	_player_move(keycode, _game);
	if (is_wall(_game, _game->player->_x, _game->player->_y))
	{
		_game->player->_x = old_player_x;
	 	_game->player->_y = old_player_y;
	}
	if (keycode == LEFT_ARROW){
		_game->player->angle -= ROTATION_SPEED;
		printf("angle LEFT : %f\n", _game->player->angle);
		if (_game->player->angle < 0)
		{
			_game->player->angle += 2 * PI;
			printf("updat angle LEFT : %f\n", _game->player->angle);

		}
	}
	else if (keycode == RIGHT_ARROW)
	{
		_game->player->angle += ROTATION_SPEED;
		printf("angle RIGTH : %f\n", _game->player->angle);
		if (_game->player->angle >= 2){
			_game->player->angle -= 2 * PI; // keep angle
			printf("updat angle RIGTH : %f\n", _game->player->angle);
		}
	}
	return (true);
}

int main(int ac, char **av)
{
	t_data_game	*_game;

	if (ac != 2)
		return (syntax_error(true), EXIT_FAILURE);
	_game = ft_malloc(sizeof(t_data_game), ALLOC);
	_game->config = ft_malloc(sizeof(t_config), ALLOC);
	_game->player = ft_malloc(sizeof(t_player), ALLOC);
	ft_bzero(_game->config->textures, sizeof(char *) * TEXTURE_COUNT);
	_game->_img = ft_malloc(sizeof(t_imag), ALLOC);
	if (!parsing(av[1], _game))
		return (ft_malloc(CLEAR, CLEAR), EXIT_FAILURE);
	player_init(_game);
	printf("poist p_x : %f\n", _game->player->_x);
	printf("poist p_y : %f\n", _game->player->_y);

	_mlx_init_data(_game);
	mlx_hook(_game->_win_mlx, KeyPress, KeyPressMask, control_key_, _game);
	mlx_loop_hook(_game->_mlx, render, _game);
	mlx_loop(_game->_mlx);
	// _mlx_init_data(_game);
	// start_simulation(_game);
	// init_window(_game);
	ft_malloc(CLEAR, CLEAR);
	return (EXIT_SUCCESS);
}
