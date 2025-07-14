/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:45:32 by ybounite          #+#    #+#             */
/*   Updated: 2025/07/14 16:03:48 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

void	_mlx_init_data(t_data_game *_game)
{
	_game->_mlx = mlx_init();
	_game->_win_mlx = mlx_new_window(_game->_mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");

	_game->img = mlx_new_image(_game->_mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	_game->img_addr = mlx_get_data_addr(_game->img, &_game->bp_pixel, &_game->line_length, &_game->endian);

}
/*
void	init_window(t_data_game *_game)
{
	// mlx_hook(_game->_win_mlx, KeyPress, KeyPressMask, control_key_, _game);
	// mlx_loop_hook(_game->_mlx, render, _game);
	// render(_game);
	// render_map(_game);
	// mlx_hook(_game->_win_mlx, KeyPress, KeyPressMask, control_key_, _game);
	// mlx_hook(_game->_win_mlx, 17, 0, _destory_window, &_game->_win_mlx);
	// mlx_loop(_game->_mlx);
	// _destory_window(_game);
}*/