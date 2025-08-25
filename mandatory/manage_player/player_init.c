/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:41:31 by ybounite          #+#    #+#             */
/*   Updated: 2025/08/25 13:24:34 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

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
				_game->player->_x = x;
				_game->player->_y = y;
				break ;
			}
			x++;
		}
		y++;
	}
}

void	init_player_direction(t_data_game *_game, char spawn_dir)
{
	if (spawn_dir == 'N') // North ^
		_game->player->angle = (PI * 1.5); // (1.57) 90°
	else if (spawn_dir == 'S') // south 
		_game->player->angle = PI / 2; //  270°
	else if (spawn_dir == 'E') // East
		_game->player->angle = 0; // or 2PI (6.28) [0° / 360°]
	else if (spawn_dir == 'W') // west
		_game->player->angle = PI; // (3.14) 180°
}
/*   π/2 (1.57) [90°] [N]
                 ↑
				 |
[W] π (3.14) ← player → 0 or 2π (6.28) [0° / 360°] [E]
      [180°]     |
                 ↓
    3π/2 (4.71) [270°] [S]
*/
void	player_init(t_data_game *_game)
{
	player_position(_game);
	init_player_direction(_game, _game->spawm_dir);
	// convert postion player maps to window *TITL_SIZE + (TITL_SIZE / 2)
	_game->player->_x = (_game->player->_x * TILE_SIZE) + TILE_SIZE / 2.0;
	_game->player->_y = (_game->player->_y * TILE_SIZE) + TILE_SIZE / 2.0;
	// printf("postion palyer ot window --> x %f <-- and --> y %f <--\n", _game->player->_x, _game->player->_y);
}
