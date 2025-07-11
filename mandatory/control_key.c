/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 09:55:32 by ybounite          #+#    #+#             */
/*   Updated: 2025/07/11 10:11:29 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

int	_destory_window(t_data_game *_game)
{
	mlx_clear_window(_game->_mlx, _game->_win_mlx);
	if (_game->_win_mlx)
	{
		mlx_destroy_window(_game->_mlx, _game->_win_mlx);
		_game->_win_mlx = NULL;
	}
	if (_game->_mlx)
	{
		mlx_destroy_display(_game->_mlx);
		free(_game->_mlx);
		_game->_mlx = NULL;
	}
	ft_malloc(CLEAR, CLEAR);
	exit(EXIT_SUCCESS);
	return true;
}

void	control_handle_key_press(int keycode, t_data_game *_game)
{
	if (keycode == A_KEY)
	{
		_game->player->_x += _game->player->_dir_x * MOVE_SPEED;
		_game->player->_y += _game->player->_dir_y * MOVE_SPEED;
	}
	else if (keycode == D_KEY)
	{
		_game->player->_x -= _game->player->_dir_x * MOVE_SPEED;
		_game->player->_y -= _game->player->_dir_y * MOVE_SPEED;
	}
	else if (keycode == W_KEY)
	{
		_game->player->_x += _game->player->_dir_y * MOVE_SPEED;
		_game->player->_y -= _game->player->_dir_x * MOVE_SPEED;
	}
	else if (keycode == S_KEY)
	{
		_game->player->_x -= _game->player->_dir_y * MOVE_SPEED;
		_game->player->_y += _game->player->_dir_x * MOVE_SPEED;
	}

}

int	control_key_(int keycode, t_data_game	*_game)
{
	// double	(old_position_x), (old_position_y);
	if (keycode == ESCAPE)
		_destory_window(_game);
	// old_position_x = _game->player._x;
	// old_position_y = _game->player._y;
	control_handle_key_press(keycode, _game);
	printf("updat pos x : %f\n", _game->player->_x);
	printf("updat pos y : %f\n", _game->player->_y);
	printf("%f\n", _game->player->_dir_x);
	render_map(_game);
	// update_player_animation(_game);
	return (1);
}
