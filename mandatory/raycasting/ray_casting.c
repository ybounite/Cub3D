/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:53:10 by ybounite          #+#    #+#             */
/*   Updated: 2025/07/15 17:51:11 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"


void	_player_move(t_data_game *_game, int key)
{
	if (key == S_KEY)
	{
		_game->player->_x += cos(_game->player->rotationAngle) * MOVE_SPEED;
		_game->player->_y += sin(_game->player->rotationAngle) * MOVE_SPEED;
	}
	else if (key == W_KEY)
	{
		_game->player->_x += cos(_game->player->rotationAngle + M_PI) * MOVE_SPEED;
		_game->player->_y += sin(_game->player->rotationAngle + M_PI) * MOVE_SPEED;
	}
	else if (key == D_KEY)
	{
		_game->player->_x += cos(_game->player->rotationAngle - M_PI_2) * MOVE_SPEED;
		_game->player->_y += sin(_game->player->rotationAngle - M_PI_2) * MOVE_SPEED;
	}
	else if (key == A_KEY)
	{
		_game->player->_x += cos(_game->player->rotationAngle + M_PI_2) * MOVE_SPEED;
		_game->player->_y += sin(_game->player->rotationAngle + M_PI_2) * MOVE_SPEED;
	}
}

void	put_pixel_img(t_data_game *_game, int x, int y, int color)
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
void	draw_line(t_data_game *_game, int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	// if (ads(dx) > abd(dy))
	// 	steps = abs(dx);
	// else
	// 	steps = abs(dy);
    float x_inc = dx / (float)steps;
    float y_inc = dy / (float)steps;
    float x = x0;
    float y = y0;

    for (int i = 0; i <= steps; i++)
    {
        put_pixel_img(_game, (int)x, (int)y, WHITE);
        x += x_inc;
        y += y_inc;
    }
}


int		render(t_data_game *_game)
{
	// draw maps
	int color;
	for (short y = 0; y < _game->size; y++){
		for (short x = 0; x < (short)ft_strlen(_game->map[y]); x++){
			if (_game->map[y][x] == '1')
				color = 0x444477;
			else if (_game->map[y][x] == '0')
				color = 0xCCC666;
			else 
				color = 0x000000;
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
	short dx;
	while (dy <= 5)
	{
		dx = -5;
		while (dx <= 5)
		{
			if (pow(dx, 2) + pow(dy, 2) <= 25)
				put_pixel_img(_game, px+dx, py+dy, RED);
			dx++;
		}
		dy++;
	}


	// int line_length = 30;
	// dx = cos(_game->player->rotationAngle) * line_length;
	// dy = sin(_game->player->rotationAngle) * line_length;
	// draw_line(_game, px, py, px + dx, py + dy);
	draw_line(_game, px, py, px + 25, py);
	mlx_put_image_to_window(_game->_mlx, _game->_win_mlx, _game->img, 0, 0);
	mlx_loop(_game->_mlx);
	return 0;
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
	_player_move(_game, keycode);
	render(_game);
	// renderPlayer(_game);
	return (true);
}

void	 start_simulation(t_data_game *_game)
{
	mlx_hook(_game->_win_mlx, KeyPress, KeyPressMask, control_key_, _game);
	// mlx_loop_hook(_game->_mlx, render, _game);
	render(_game);
	// render_map(_game);
	// mlx_hook(_game->_win_mlx, KeyPress, KeyPressMask, control_key_, _game);
	// mlx_hook(_game->_win_mlx, 17, 0, _destory_window, &_game->_win_mlx);
	// mlx_loop(_game->_mlx);
	// _destory_window(_game);
}
