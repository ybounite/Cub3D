/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:45:16 by ybounite          #+#    #+#             */
/*   Updated: 2025/07/14 18:49:00 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

// bool	validate_map(t_data_game *_game)
/*
	sin(&) = opposite/hypotenuse
	cos(&) = adjacent/hypotenuse
	tan(&) = opposite/adjacent    
	hypotenuse^2 = opposite^2 + adjacent^2  
	double rad2
*/
/*
void	draw_circle(t_data_game *_game, int cx, int cy, int color)
{
	int radius = 4;
    for (int y = -radius; y <= radius; y++)
    {
        for (int x = -radius; x <= radius; x++)
        {
            if (x * x + y * y <= radius * radius)
                mlx_pixel_put(_game->_mlx, _game->_win_mlx, cx + x, cy + y, color);
        }
    }
}
void	render_map(t_data_game *_game)
{
	short	(y), (x);
	int		color;

	y = 0;
	while (_game->map[y])
	{
		x = 0;
		while (_game->map[y][x])
		{
			if (_game->map[y][x] == '1')
				color = 0x444477;
			else if (_game->map[y][x] == '0')
				color = 0xCCC666;
			else 
				color = 0x000000;
			draw_rect(_game, x * TILE_SIZE, y * TILE_SIZE, color);
			x++;
		}
		y++;
	}
	int px = (int)_game->player->_x * TILE_SIZE + TILE_SIZE / 2;
	int py = (int)_game->player->_y * TILE_SIZE + TILE_SIZE / 2;
	printf("---->px :  %d | py : %d<----\n", px, py);
	// draw_circle(_game, py, px, 0xFF0000);
}
*/
// raduis = 3;
// turndirection = 0;
// walkdirection = 0;
// rotationAngile = PI /2;
// moveSpeed = 2.0;
// rotationSpeed = 2 (PI / 180);


void	_player_move(t_data_game *_game, int key)
{
	if (key == W_KEY)
	{
		_game->player->_x += cos(_game->player->rotationAngle) * MOVE_SPEED;
		_game->player->_y += sin(_game->player->rotationAngle) * MOVE_SPEED;
	}
	else if (key == S_KEY)
	{
		_game->player->_x += cos(_game->player->rotationAngle + M_PI) * MOVE_SPEED;
		_game->player->_y += sin(_game->player->rotationAngle + M_PI) * MOVE_SPEED;
	}
	else if (key == A_KEY)
	{
		_game->player->_x += cos(_game->player->rotationAngle - M_PI_2) * MOVE_SPEED;
		_game->player->_y += sin(_game->player->rotationAngle - M_PI_2) * MOVE_SPEED;
	}
	else if (key == D_KEY)
	{
		_game->player->_x += cos(_game->player->rotationAngle + M_PI_2) * MOVE_SPEED;
		_game->player->_y += sin(_game->player->rotationAngle + M_PI_2) * MOVE_SPEED;
	}
}
void	renderPlayer(t_data_game *_game)
{
	printf("pos x : %f <--", _game->player->_x);
	printf("pos y : %f <--", _game->player->_y);
	mlx_pixel_put(_game->_mlx, _game->_win_mlx, _game->player->_y * TILE_SIZE, _game->player->_x * TILE_SIZE, 0xFF0000);
}
int		control_key_(int keycode, t_data_game *_game)
{
	// double	old_player_x = _game->player->_x;
	// double	old_player_y = _game->player->_y;

	if (keycode == ESCAPE)
	{
		mlx_destroy_window(_game->_mlx, _game->_win_mlx);
		ft_malloc(CLEAR, CLEAR);
		exit(EXIT_SUCCESS);
	}
	// _player_move(_game, keycode);
	renderPlayer(_game);
	return (true);
}

void put_pixel_img(t_data_game *_game, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
        return;  // safety check

    dst = _game->img_addr + (y * _game->line_length + x * (_game->bp_pixel / 8));
    *(unsigned int*)dst = color;
}

void	draw_rect(t_data_game *_game, int start_x, int start_y, int color)
{
    int i, j;

	i = 0;
    while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			put_pixel_img(_game, start_x + i, start_y + j, color);
			j++;
		}
		i++;
	}
}
int		render(t_data_game *_game)
{
	// draw maps
	int color;
	for (short y = 0; y < _game->size; y++){
		for (short x = 0; x < (short)ft_strlen(_game->map[y]); x++){
			if (_game->map[y][x] == '1')
				color = GRAY;
			else if (_game->map[y][x] == '0')	
				color = YELLOW;
			else 
				color = BLUE;
			//  				x				y
			draw_rect(_game, x * TILE_SIZE, y * TILE_SIZE, color);
		}
	}
	// draw player
	int px = (int)_game->player->_x * TILE_SIZE + TILE_SIZE / 2;
	int py = (int)_game->player->_y * TILE_SIZE + TILE_SIZE / 2;
	printf("pos x : %f\n", _game->player->_x);
	printf("pos y : %f\n", _game->player->_y);
	short dy = -5;
	while (dy <= 5)
	{
		short dx = -5;
		while (dx <= 5)
		{
			if (pow(dx, 2) + pow(dy, 2) <= 25)
				put_pixel_img(_game, py+dy, px+dx, RED);
			dx++;
		}
		dy++;
	}
	// 
	mlx_put_image_to_window(_game->_mlx, _game->_win_mlx, _game->img, 0, 0);
	mlx_loop(_game->_mlx);
	return 0;
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
	if (!parsing(av[1], _game))
		return (ft_malloc(CLEAR, CLEAR), EXIT_FAILURE);
	
	player_init(_game);
	for (size_t i = 0; _game->map[i]; i++)
	{
		printf("%s\n", _game->map[i]);
	}
	_mlx_init_data(_game);
	render(_game);
	// init_window(_game);
	ft_malloc(CLEAR, CLEAR);
	return EXIT_SUCCESS;
}
