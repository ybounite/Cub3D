/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:01:09 by ybounite          #+#    #+#             */
/*   Updated: 2025/08/22 16:13:56 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

void	_player_move(int key, t_data_game *_g)
{
	if (key == S_KEY)
	{
		_g->player->_x -= cos(_g->player->angle) * MOVE_SPEED;
		_g->player->_y -= sin(_g->player->angle) * MOVE_SPEED;
	}
	else if (key == W_KEY)
	{
		_g->player->_x += cos(_g->player->angle) * MOVE_SPEED;
		_g->player->_y += sin(_g->player->angle) * MOVE_SPEED;
	}
	else if (key == A_KEY)
	{
		_g->player->_x += cos(_g->player->angle - M_PI_2) * MOVE_SPEED;
		_g->player->_y += sin(_g->player->angle - M_PI_2) * MOVE_SPEED;
	}
	else if (key == D_KEY)
	{
		_g->player->_x += cos(_g->player->angle + M_PI_2) * MOVE_SPEED;
		_g->player->_y += sin(_g->player->angle + M_PI_2) * MOVE_SPEED;
	}
}

bool	wall_collisions(t_data_game *_game, t_point old_player)
{
	if (_hase_wall(_game, _game->player->_x, old_player.y))
		_game->player->_x = old_player.x;
	if (_hase_wall(_game, old_player.x, _game->player->_y))
		_game->player->_y = old_player.y;
	return (true);
}

int	control_key_(int keycode, t_data_game *_g)
{
	t_point	old_player;

	(1) && (old_player.y = _g->player->_y), (old_player.x = _g->player->_x);
	if (keycode == ESCAPE)
	{
		mlx_destroy_window(_g->_mlx, _g->_win_mlx);
		ft_malloc(CLEAR, CLEAR);
		exit(EXIT_SUCCESS);
	}
	_player_move(keycode, _g);
	wall_collisions(_g, old_player);
	if (keycode == LEFT_ARROW)
	{
		_g->player->angle -= ROTATION_SPEED;
		if (_g->player->angle < 0)
			_g->player->angle += 2 * PI;
	}
	else if (keycode == RIGHT_ARROW)
	{
		_g->player->angle += ROTATION_SPEED;
		if (_g->player->angle >= 2)
			_g->player->angle -= 2 * PI;
	}
	return (true);
}
