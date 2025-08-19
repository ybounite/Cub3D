/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:00:00 by bamezoua          #+#    #+#             */
/*   Updated: 2025/08/19 10:11:45 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

static void	draw_minimap_border(t_data_game *_game)
{
	int x, y;
	// Draw border
	y = MINIMAP_Y - MINIMAP_BORDER;
	while (y < MINIMAP_Y + MINIMAP_SIZE + MINIMAP_BORDER)
	{
		x = MINIMAP_X - MINIMAP_BORDER;
		while (x < MINIMAP_X + MINIMAP_SIZE + MINIMAP_BORDER)
		{
			if (x >= 0 && y >= 0 && x < WINDOW_WIDTH && y < WINDOW_HEIGHT)
				my_mlx_pixel_put(_game->_img, x, y, WHITE);
			x++;
		}
		y++;
	}
}

void	draw_minimap_background(t_data_game *_game)
{
	int x, y;
	// Draw background
	y = MINIMAP_Y;
	while (y < MINIMAP_Y + MINIMAP_SIZE)
	{
		x = MINIMAP_X;
		while (x < MINIMAP_X + MINIMAP_SIZE)
		{
			if (x >= 0 && y >= 0 && x < WINDOW_WIDTH && y < WINDOW_HEIGHT)
				my_mlx_pixel_put(_game->_img, x, y, BLACK);
			x++;
		}
		y++;
	}
}

void	draw_minimap_walls(t_data_game *_game)
{
	int	scale;

	int map_x, map_y;
	int mini_x, mini_y;
	scale = MINIMAP_SCALE;
	int dx, dy, pixel_x, pixel_y;
	map_y = 0;
	while (map_y < _game->map_height)
	{
		map_x = 0;
		while (map_x < (int)ft_strlen(_game->map[map_y]))
		{
			mini_x = MINIMAP_X + (map_x * MINIMAP_SIZE) / (_game->map_width);
			mini_y = MINIMAP_Y + (map_y * MINIMAP_SIZE) / (_game->map_height);
			// Draw a small square for each map cell
			dy = 0;
			while (dy < scale && mini_y + dy < MINIMAP_Y + MINIMAP_SIZE)
			{
				dx = 0;
				while (dx < scale && mini_x + dx < MINIMAP_X + MINIMAP_SIZE)
				{
					pixel_x = mini_x + dx;
					pixel_y = mini_y + dy;
					if (pixel_x >= MINIMAP_X && pixel_y >= MINIMAP_Y
						&& pixel_x < MINIMAP_X + MINIMAP_SIZE
						&& pixel_y < MINIMAP_Y + MINIMAP_SIZE)
					{
						if (_game->map[map_y][map_x] == '1')
							my_mlx_pixel_put(_game->_img, pixel_x, pixel_y,
								GRAY);
						else if (_game->map[map_y][map_x] == '0'
							|| _game->map[map_y][map_x] == 'N'
							|| _game->map[map_y][map_x] == 'S'
							|| _game->map[map_y][map_x] == 'E'
							|| _game->map[map_y][map_x] == 'W')
							my_mlx_pixel_put(_game->_img, pixel_x, pixel_y,
								DARK_GRAY);
					}
					dx++;
				}
				dy++;
			}
			map_x++;
		}
		map_y++;
	}
}

void	draw_minimap_player(t_data_game *_game)
{
	int		player_mini_x;
	int		player_mini_y;
	double	line_length;
	double	end_x;
	double	end_y;
	double	d_dx;
	double	d_dy;
	double	steps;
	int		i;
	int		lx;
	int		ly;

	// Calculate player position on minimap
	player_mini_x = MINIMAP_X + (int)((_game->player->_x / TILE_SIZE)
			* MINIMAP_SIZE) / _game->map_width;
	player_mini_y = MINIMAP_Y + (int)((_game->player->_y / TILE_SIZE)
			* MINIMAP_SIZE) / _game->map_height;
	int dx, dy, px, py;
	// Draw player as a small red circle
	dy = -2;
	while (dy <= 2)
	{
		dx = -2;
		while (dx <= 2)
		{
			if (dx * dx + dy * dy <= 4) // Circle radius 2
			{
				px = player_mini_x + dx;
				py = player_mini_y + dy;
				if (px >= MINIMAP_X && py >= MINIMAP_Y && px < MINIMAP_X
					+ MINIMAP_SIZE && py < MINIMAP_Y + MINIMAP_SIZE)
					my_mlx_pixel_put(_game->_img, px, py, RED);
			}
			dx++;
		}
		dy++;
	}
	// Draw player direction line
	line_length = 8;
	end_x = player_mini_x + cos(_game->player->angle) * line_length;
	end_y = player_mini_y + sin(_game->player->angle) * line_length;
	// Simple line drawing
	d_dx = end_x - player_mini_x;
	d_dy = end_y - player_mini_y;
	steps = fmax(fabs(d_dx), fabs(d_dy));
	if (steps > 0)
	{
		d_dx /= steps;
		d_dy /= steps;
		i = 0;
		while (i <= (int)steps)
		{
			lx = (int)(player_mini_x + d_dx * i);
			ly = (int)(player_mini_y + d_dy * i);
			if (lx >= MINIMAP_X && ly >= MINIMAP_Y && lx < MINIMAP_X
				+ MINIMAP_SIZE && ly < MINIMAP_Y + MINIMAP_SIZE)
				my_mlx_pixel_put(_game->_img, lx, ly, YELLOW);
			i++;
		}
	}
	
}

void	draw_minimap(t_data_game *_game)
{
	draw_minimap_border(_game);
	draw_minimap_background(_game);
	draw_minimap_walls(_game);
	draw_minimap_player(_game);
}