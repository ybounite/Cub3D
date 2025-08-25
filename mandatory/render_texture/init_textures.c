/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:53:10 by ybounite          #+#    #+#             */
/*   Updated: 2025/08/20 15:55:38 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

void	init_textures(t_data_game *_game)
{
	_game->texture = ft_malloc(sizeof(t_texture), ALLOC);
	_game->texture->NO = _game->config->textures[NO_TEXTURE];
	_game->texture->SO = _game->config->textures[SO_TEXTURE];
	_game->texture->WE = _game->config->textures[WE_TEXTURE];
	_game->texture->EA = _game->config->textures[EA_TEXTURE];
}

void	init_textures_address(t_texture *texture, t_data_game *_game)
{
	(void)_game;
	texture->NO_img->addr = mlx_get_data_addr(texture->NO_img->img,
			&texture->NO_img->bit_per_pixel,
			&texture->NO_img->line_len, &texture->NO_img->endian);
	texture->EA_img->addr = mlx_get_data_addr(texture->EA_img->img,
			&texture->EA_img->bit_per_pixel,
			&texture->EA_img->line_len, &texture->EA_img->endian);
	texture->WE_img->addr = mlx_get_data_addr(texture->WE_img->img,
			&texture->WE_img->bit_per_pixel,
			&texture->WE_img->line_len, &texture->WE_img->endian);
	texture->SO_img->addr = mlx_get_data_addr(texture->SO_img->img,
			&texture->SO_img->bit_per_pixel,
			&texture->SO_img->line_len, &texture->SO_img->endian);
	texture->dr_img->addr = mlx_get_data_addr(texture->dr_img->img,
			&texture->dr_img->bit_per_pixel,
			&texture->dr_img->line_len, &texture->dr_img->endian);

	if (!texture->NO_img->addr || !texture->SO_img->addr || !texture->dr_img->addr
		|| !texture->WE_img->addr || !texture->EA_img->addr)
	{
		ft_putendl_fd("Error: Address Failed to load textures.", STDERR);
		ft_malloc(CLEAR, CLEAR);
		exit(EXIT_FAILURE);
	}
}

void	init_textures_data(t_data_game *_game)
{
	t_texture	*texture;

	_game->texture->NO_img = ft_malloc(sizeof(t_imag), ALLOC);
	_game->texture->SO_img = ft_malloc(sizeof(t_imag), ALLOC);
	_game->texture->WE_img = ft_malloc(sizeof(t_imag), ALLOC);
	_game->texture->EA_img = ft_malloc(sizeof(t_imag), ALLOC);
	_game->texture->dr_img = ft_malloc(sizeof(t_imag), ALLOC);
	texture = _game->texture;
	texture->NO_img->img = mlx_xpm_file_to_image(_game->_mlx, texture->NO,
			&texture->NO_img->width, &texture->NO_img->height);
	texture->SO_img->img = mlx_xpm_file_to_image(_game->_mlx, texture->SO,
			&texture->SO_img->width, &texture->SO_img->height);
	texture->WE_img->img = mlx_xpm_file_to_image(_game->_mlx, texture->WE,
			&texture->WE_img->width, &texture->WE_img->height);
	texture->EA_img->img = mlx_xpm_file_to_image(_game->_mlx, texture->EA,
			&texture->EA_img->width, &texture->EA_img->height);
	texture->dr_img->img = mlx_xpm_file_to_image(_game->_mlx, "textures/door2.xpm",
			&texture->dr_img->width, &texture->dr_img->height);
	if (!texture->NO_img->img || !texture->SO_img->img || !texture->dr_img->img
		|| !texture->WE_img->img || !texture->EA_img->img)
	{
		ft_putendl_fd("Error: Failed to load textures.", STDERR);
		ft_malloc(CLEAR, CLEAR);
		exit(EXIT_FAILURE);
	}
	init_textures_address(texture, _game);
	_game->texture = texture;
}
