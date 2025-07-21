/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_renderer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:21:02 by ybounite          #+#    #+#             */
/*   Updated: 2025/07/21 10:24:00 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

void	draw_square(t_data_game *_game, int start_x, int start_y, int color)
{
	short	(x), (y);
	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			my_mlx_pixel_put(_game->_img, x + start_x, y +start_y, color);
			x++;
		}
		y++;
	}
	
}

void	draw_walls(t_data_game *_game)
{
	int	(x), (y), (color);
	y = 0;
	while (_game->map[y])
	{
		x = 0;
		while (_game->map[y][x])
		{
			if (_game->map[y][x] == '1')
				color = 0x444477;
			else if (_game->map[y][x] == '0' || _game->map[y][x] == 'N')
				color = 0xCCC666;
			else
				color = 0x000000;
			draw_square(_game, x * TILE_SIZE, y * TILE_SIZE, color);
			x++;
		}
		y++;
	}
	
}

void	draw_line(t_data_game *_game, t_point start_p, t_point end_p, int color)
{
	double	dx;
	double	dy;
	double	steps;
	int		i;

	i = 0;
	dx = end_p.x - start_p.x;
	dy = end_p.y - start_p.y;
	steps = fmax(fabs(dx), fabs(dy));

	while (i < steps)
	{
		my_mlx_pixel_put(_game->_img, start_p.x, start_p.y, color);
		start_p.x += dx/steps;
		start_p.y += dy/steps;
		i++;
	}
}

void	draw_grid_lines(t_data_game *_game)
{
	int y = 0;
    int x = 0;
    t_point point1;
    t_point point2;

    while (x < _game->map_width)
    {
        point1.x = x * TILE_SIZE;
        point1.y = 0;
        point2.x = x * TILE_SIZE;
        point2.y = _game->map_height * TILE_SIZE;
        draw_line(_game, point1, point2, GRAY);
        x++;
    }
    while (y < _game->map_height)
    {
        point1.x = 0;
        point1.y = y * TILE_SIZE;
        point2.x = _game->map_width * TILE_SIZE;
        point2.y = y * TILE_SIZE;
        draw_line(_game, point1, point2, GRAY);
        y++;
    }
}

void	draw_player(t_data_game *_game)
{
	int px = (int)_game->player->_x;
	int py = (int)_game->player->_y;
	int dy = -5;

	while (dy <= 5)
	{
		int dx = -5;
		while (dx <= 5)
		{
			if (dx*dx + dy*dy <= 25)
				my_mlx_pixel_put(_game->_img, px+dx, py+dy, RED);
			dx++;
		}
		dy++;
	}
}
void	draw_map(t_data_game *_game)
{
	draw_walls(_game);
	draw_grid_lines(_game);
	draw_player(_game);
}
