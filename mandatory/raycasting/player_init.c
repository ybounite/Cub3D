/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:41:31 by ybounite          #+#    #+#             */
/*   Updated: 2025/07/15 17:11:21 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"
/*
void	render_3d_view(void *mlx, void *win, char **map, t_player player, int win_width, int win_height)
{
	for (int x = 0; x < win_width; x++)
	{
		double camera_x = 2 * x / (double)win_width - 1;
		double ray_dir_x = player._dir_x + player._plane_x * camera_x;
		double ray_dir_y = player._dir_y + player._plane_y * camera_x;

		int map_x = (int)player._x;
		int map_y = (int)player._y;

		double delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
		double delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);

		double side_dist_x;
		double side_dist_y;

		int step_x;
		int step_y;

		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (player._x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - player._x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (player._y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - player._y) * delta_dist_y;
		}

		int hit = 0;
		int side;

		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (map[map_y][map_x] == '1')
				hit = 1;
		}

		double perp_wall_dist;
		if (side == 0)
			perp_wall_dist = (map_x - player._x + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - player._y + (1 - step_y) / 2) / ray_dir_y;

		int line_height = (int)(win_height / perp_wall_dist);
		int draw_start = -line_height / 2 + win_height / 2;
		if (draw_start < 0) draw_start = 0;
		int draw_end = line_height / 2 + win_height / 2;
		if (draw_end >= win_height) draw_end = win_height - 1;

		// Draw vertical line
		for (int y = draw_start; y < draw_end; y++)
			mlx_pixel_put(mlx, win, x, y, 0x444444); // red wall
	}
}
*/

bool	is_spawm_direction(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	player_position(t_data_game *_game)
{
	short	x;
	short	y;

	y = 0;
	while (_game->map[y])
	{
		x = 0;
		while (_game->map[y][x])
		{
			if (is_spawm_direction(_game->map[y][x]))
			{
				_game->spawm_dir = _game->map[y][x];
				_game->player->_x = x + 0.5;
				_game->player->_y = y + 0.5;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	init_player_direction(t_data_game *_game, char spawn_dir)
{
	if (spawn_dir == 'N') // North ^
		_game->player->rotationAngle = PI / 2;
	else if (spawn_dir == 'S') // south 
		_game->player->rotationAngle = PI * 1.5;
	else if (spawn_dir == 'E') // East
		_game->player->rotationAngle = 0;
	else if (spawn_dir == 'W') // west
		_game->player->rotationAngle = PI;
}

void	player_init(t_data_game *_game)
{
	player_position(_game);
	init_player_direction(_game, _game->spawm_dir);
}