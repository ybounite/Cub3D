/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:45:32 by ybounite          #+#    #+#             */
/*   Updated: 2025/07/21 09:51:52 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

bool	_mlx_init_data(t_data_game *_game)
{
	_game->_mlx = mlx_init();
	// 														cols               rows
	_game->_win_mlx = mlx_new_window(_game->_mlx, _game->map_width * TILE_SIZE, _game->map_height * TILE_SIZE, "Cub3D");
	if (!_game->_win_mlx)
		return (ft_putendl_fd("Error:\nmlx_new_window failed.", STDERR), false);

	_game->_img->img = mlx_new_image(_game->_mlx, _game->map_width * TILE_SIZE, _game->map_height * TILE_SIZE);
	if (!_game->_img->img)	
		return (ft_putendl_fd("Error:\nmlx_new_image failed.", STDERR), false);

	printf("img ptr: %p\n", _game->_img->img);

	_game->_img->addr = mlx_get_data_addr(_game->_img->img, &_game->_img->bits_per_pixel,
							&_game->_img->line_length, &_game->_img->endian);
	_game->_img->width = _game->map_width * TILE_SIZE;
	_game->_img->height = _game->map_height * TILE_SIZE;
	return true;
}
