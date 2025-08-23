/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:00:00 by bamezoua          #+#    #+#             */
/*   Updated: 2025/08/23 10:49:49 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

static int	is_inside_circle(int x, int y, int center_x, int center_y,
		int radius)
{
	int	dx;
	int	dy;

	dx = x - center_x;
	dy = y - center_y;
	return (dx * dx + dy * dy <= radius * radius);
}

static void	draw_minimap_border(t_data_game *_game)
{
	int	border_radius;

	int x, y;
	border_radius = MINIMAP_RADIUS + 3;
	// Draw circular border
	y = MINIMAP_CENTER_Y - border_radius;
	while (y <= MINIMAP_CENTER_Y + border_radius)
	{
		x = MINIMAP_CENTER_X - border_radius;
		while (x <= MINIMAP_CENTER_X + border_radius)
		{
			if (x >= 0 && y >= 0 && x < WINDOW_WIDTH && y < WINDOW_HEIGHT)
			{
				if (is_inside_circle(x, y, MINIMAP_CENTER_X, MINIMAP_CENTER_Y,
						border_radius) && !is_inside_circle(x, y,
						MINIMAP_CENTER_X, MINIMAP_CENTER_Y, MINIMAP_RADIUS))
					my_mlx_pixel_put(_game->_img, x, y, WHITE);
			}
			x++;
		}
		y++;
	}
}

void	draw_minimap_background(t_data_game *_game)
{
	int x, y;
	// Draw circular background
	y = MINIMAP_CENTER_Y - MINIMAP_RADIUS;
	while (y <= MINIMAP_CENTER_Y + MINIMAP_RADIUS)
	{
		x = MINIMAP_CENTER_X - MINIMAP_RADIUS;
		while (x <= MINIMAP_CENTER_X + MINIMAP_RADIUS)
		{
			if (x >= 0 && y >= 0 && x < WINDOW_WIDTH && y < WINDOW_HEIGHT)
			{
				if (is_inside_circle(x, y, MINIMAP_CENTER_X, MINIMAP_CENTER_Y,
						MINIMAP_RADIUS))
					my_mlx_pixel_put(_game->_img, x, y, BLACK);
			}
			x++;
		}
		y++;
	}
}

static void	convert_screen_to_world(t_data_game *_game, int screen_x,
		int screen_y, t_point *world)
{
	double	offset_x;
	double	offset_y;

	offset_x = (screen_x - MINIMAP_CENTER_X) * MINIMAP_ZOOM;
	offset_y = (screen_y - MINIMAP_CENTER_Y) * MINIMAP_ZOOM;
	world->x = _game->player->_x + offset_x;
	world->y = _game->player->_y + offset_y;
}

static void	draw_minimap_pixel(t_data_game *_game, int screen_x, int screen_y,
		t_point world)
{
	int	map_x;
	int	map_y;

	map_x = (int)(world.x / TILE_SIZE);
	map_y = (int)(world.y / TILE_SIZE);
	if (map_x >= 0 && map_y >= 0 && map_y < _game->map_height
		&& map_x < (int)ft_strlen(_game->map[map_y]))
	{
		if (_game->map[map_y][map_x] == '1')
			my_mlx_pixel_put(_game->_img, screen_x, screen_y, GRAY);
		else if (_game->map[map_y][map_x] == 'D')
			my_mlx_pixel_put(_game->_img, screen_x, screen_y, GREEN);
		else if (_game->map[map_y][map_x] == '0'
			|| _game->map[map_y][map_x] == 'N'
			|| _game->map[map_y][map_x] == 'S'
			|| _game->map[map_y][map_x] == 'E'
			|| _game->map[map_y][map_x] == 'W')
			my_mlx_pixel_put(_game->_img, screen_x, screen_y, DARK_GRAY);
	}
}

void	draw_minimap_walls(t_data_game *_game)
{
	int		screen_x;
	int		screen_y;
	t_point	world;

	screen_y = MINIMAP_CENTER_Y - MINIMAP_RADIUS;
	while (screen_y <= MINIMAP_CENTER_Y + MINIMAP_RADIUS)
	{
		screen_x = MINIMAP_CENTER_X - MINIMAP_RADIUS;
		while (screen_x <= MINIMAP_CENTER_X + MINIMAP_RADIUS)
		{
			if (screen_x >= 0 && screen_y >= 0 && screen_x < WINDOW_WIDTH
				&& screen_y < WINDOW_HEIGHT)
			{
				if (is_inside_circle(screen_x, screen_y, MINIMAP_CENTER_X,
						MINIMAP_CENTER_Y, MINIMAP_RADIUS))
				{
					convert_screen_to_world(_game, screen_x, screen_y, &world);
					draw_minimap_pixel(_game, screen_x, screen_y, world);
				}
			}
			screen_x++;
		}
		screen_y++;
	}
}

static void	draw_player_circle(t_data_game *_game)
{
	int	dx;
	int	dy;
	int	px;
	int	py;

	dy = -3;
	while (dy <= 3)
	{
		dx = -3;
		while (dx <= 3)
		{
			if (dx * dx + dy * dy <= 9)
			{
				px = MINIMAP_CENTER_X + dx;
				py = MINIMAP_CENTER_Y + dy;
				if (px >= 0 && py >= 0 && px < WINDOW_WIDTH
					&& py < WINDOW_HEIGHT)
				{
					if (is_inside_circle(px, py, MINIMAP_CENTER_X,
							MINIMAP_CENTER_Y, MINIMAP_RADIUS))
						my_mlx_pixel_put(_game->_img, px, py, RED);
				}
			}
			dx++;
		}
		dy++;
	}
}

static void	draw_direction_line(t_data_game *_game)
{
	double	line_length;
	double	end_x;
	double	end_y;
	double	d_dx;
	double	d_dy;
	double	steps;
	int		i;
	int		lx;
	int		ly;

	line_length = 15;
	end_x = MINIMAP_CENTER_X + cos(_game->player->angle) * line_length;
	end_y = MINIMAP_CENTER_Y + sin(_game->player->angle) * line_length;
	d_dx = end_x - MINIMAP_CENTER_X;
	d_dy = end_y - MINIMAP_CENTER_Y;
	steps = fmax(fabs(d_dx), fabs(d_dy));
	if (steps > 0)
	{
		d_dx /= steps;
		d_dy /= steps;
		i = 0;
		while (i <= (int)steps)
		{
			lx = (int)(MINIMAP_CENTER_X + d_dx * i);
			ly = (int)(MINIMAP_CENTER_Y + d_dy * i);
			if (lx >= 0 && ly >= 0 && lx < WINDOW_WIDTH && ly < WINDOW_HEIGHT)
			{
				if (is_inside_circle(lx, ly, MINIMAP_CENTER_X, MINIMAP_CENTER_Y,
						MINIMAP_RADIUS))
					my_mlx_pixel_put(_game->_img, lx, ly, YELLOW);
			}
			i++;
		}
	}
}

void	draw_minimap_player(t_data_game *_game)
{
	draw_player_circle(_game);
	draw_direction_line(_game);
}

void	draw_minimap(t_data_game *_game)
{
	draw_minimap_background(_game);
	draw_minimap_walls(_game);
	draw_minimap_player(_game);
	draw_minimap_border(_game);
}