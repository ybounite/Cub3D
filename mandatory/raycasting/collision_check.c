/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:19:47 by ybounite          #+#    #+#             */
/*   Updated: 2025/08/23 10:54:35 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

bool	_hase_wall(t_data_game *_game, double dx, double dy)
{
	return (is_wall(_game, dx, dy)
		|| is_wall(_game, dx + 1, dy + 1)
		|| is_wall(_game, dx - 1, dy + 1)
	 	|| is_wall(_game, dx + 1, dy - 1)
	 	|| is_wall(_game, dx - 1, dy - 1));
}

bool	is_wall(t_data_game *_game, double x, double y)
{
	int	grid_x;
	int	grid_y;

	_game->is_door = false;
	grid_x = (int)(x / TILE_SIZE);
	grid_y = (int)(y / TILE_SIZE);
	if (grid_x < 0 || grid_y < 0 || grid_y >= _game->map_height || grid_x >= _game->map_width)
		return (true);
	if (_game->map[grid_y][grid_x] == '1')
		return (true);
	if ( _game->map[grid_y][grid_x] == 'D')
		return (printf("door\n"),_game->is_door = true, true);
	return (false);
}

