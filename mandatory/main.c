/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:45:16 by ybounite          #+#    #+#             */
/*   Updated: 2025/07/21 13:25:20 by ybounite         ###   ########.fr       */
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
		_game->player->_x += cos(_game->player->angle + M_PI) * MOVE_SPEED;
		_game->player->_y += sin(_game->player->angle + M_PI) * MOVE_SPEED;
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

void	draw_ray(t_data_game *_game, double angle, int color)
{
    double rx = _game->player->_x;
    double ry = _game->player->_y;
    double dx = cos(angle);
    double dy = sin(angle);
    while (true) {
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
		// 
		draw_ray(_game, _game->player->angle, BLACK);
        mlx_put_image_to_window(_game->_mlx, _game->_win_mlx, _game->_img->img, 0, 0);

		frame = 0;
	}
	frame++;
	return 0;
}

int is_wall(t_data_game *_game, double x, double y)
{
    int grid_x = (int)(x / TILE_SIZE);
    int grid_y = (int)(y / TILE_SIZE);

    if (grid_x < 0 || grid_y < 0 || grid_y >= _game->map_height || grid_x >= _game->map_width)
        return 1;
    char c = _game->map[grid_y][grid_x];
	// printf("Postion x : %d, y : %d\n", grid_x, grid_y);
    if (c == '1')
        return 1;
    return 0;
}

int	control_key_(int keycode, t_data_game *_game)
{
	double	old_player_x = _game->player->_x;
	double	old_player_y = _game->player->_y;

	if (keycode == ESCAPE)
	{
		mlx_destroy_window(_game->_mlx, _game->_win_mlx);
		ft_malloc(CLEAR, CLEAR);
		exit(EXIT_SUCCESS);
	}
	_player_move(keycode, _game);
	if (is_wall(_game, _game->player->_x, _game->player->_y)){
		_game->player->_x = old_player_x;
	 	_game->player->_y = old_player_y;
	}
	if (keycode == LEFT_ARROW){
		_game->player->angle -= ROTATION_SPEED;
		printf("angle LEFT : %f\n", _game->player->angle);
		if (_game->player->angle < 0){
			
			_game->player->angle += 2 * PI;
			printf("updat angle LEFT : %f\n", _game->player->angle);
		}
	}
	else if (keycode == RIGHT_ARROW){
		_game->player->angle += ROTATION_SPEED;
		printf("angle RIGTH : %f\n", _game->player->angle);
		if (_game->player->angle >= 2)
			_game->player->angle -= 2 * PI; // keep angle 
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
	_game->player->_x = (_game->player->_x * TILE_SIZE) + TILE_SIZE / 2;
	_game->player->_y = (_game->player->_y * TILE_SIZE) + TILE_SIZE / 2;
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
	return EXIT_SUCCESS;
}
