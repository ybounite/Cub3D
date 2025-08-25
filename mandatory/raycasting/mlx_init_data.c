/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:22:09 by ybounite          #+#    #+#             */
/*   Updated: 2025/08/25 13:23:16 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

bool	_mlx_init_data(t_data_game *_game)
{
	_game->_win_mlx = mlx_new_window(_game->_mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	if (!_game->_win_mlx)
		return (ft_putendl_fd("Error:\nmlx_new_window failed.", STDERR), false);
	_game->_img->img = mlx_new_image(_game->_mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!_game->_img->img)
		return (ft_putendl_fd("Error:\nmlx_new_image failed.", STDERR), false);
	_game->_img->addr = mlx_get_data_addr(_game->_img->img, &_game->_img->bit_per_pixel,
			&_game->_img->line_len, &_game->_img->endian);
	_game->_img->width = WINDOW_WIDTH;
	_game->_img->height = WINDOW_HEIGHT;
	return (true);
}
