/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:18:42 by ybounite          #+#    #+#             */
/*   Updated: 2025/08/25 13:19:59 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/Cub3D.h"

void	init_textures(t_data_game *_game)
{
	_game->texture = ft_malloc(sizeof(t_texture), ALLOC);
	_game->texture->no = _game->config->textures[NO_TEXTURE];
	_game->texture->so = _game->config->textures[SO_TEXTURE];
	_game->texture->we = _game->config->textures[WE_TEXTURE];
	_game->texture->ea = _game->config->textures[EA_TEXTURE];
	_game->texture->door = "./textures/open-door.xpm";
}

void	init_textures_address(t_texture *texture)
{
	texture->no_img->addr = mlx_get_data_addr(texture->no_img->img,
			&texture->no_img->bit_per_pixel, &texture->no_img->line_len,
			&texture->no_img->endian);
	texture->ea_img->addr = mlx_get_data_addr(texture->ea_img->img,
			&texture->ea_img->bit_per_pixel, &texture->ea_img->line_len,
			&texture->ea_img->endian);
	texture->we_img->addr = mlx_get_data_addr(texture->we_img->img,
			&texture->we_img->bit_per_pixel, &texture->we_img->line_len,
			&texture->we_img->endian);
	texture->so_img->addr = mlx_get_data_addr(texture->so_img->img,
			&texture->so_img->bit_per_pixel,
			&texture->so_img->line_len, &texture->so_img->endian);
	texture->dr_img->addr = mlx_get_data_addr(texture->dr_img->img,
			&texture->dr_img->bit_per_pixel,
			&texture->dr_img->line_len, &texture->dr_img->endian);

	if (!texture->no_img->addr || !texture->so_img->addr || !texture->dr_img->addr
		|| !texture->we_img->addr || !texture->ea_img->addr)
	{
		ft_putendl_fd("Error: Address Failed to load textures.", STDERR);
		ft_malloc(CLEAR, CLEAR);
		exit(EXIT_FAILURE);
	}
}

void	init_textures_data(t_data_game *_game)
{
	t_texture	*texture;

	_game->texture->no_img = ft_malloc(sizeof(t_imag), ALLOC);
	_game->texture->so_img = ft_malloc(sizeof(t_imag), ALLOC);
	_game->texture->we_img = ft_malloc(sizeof(t_imag), ALLOC);
	_game->texture->ea_img = ft_malloc(sizeof(t_imag), ALLOC);
	_game->texture->dr_img = ft_malloc(sizeof(t_imag), ALLOC);
	texture = _game->texture;
	texture->no_img->img = mlx_xpm_file_to_image(_game->_mlx, texture->no,
			&texture->no_img->width, &texture->no_img->height);
	texture->so_img->img = mlx_xpm_file_to_image(_game->_mlx, texture->so,
			&texture->so_img->width, &texture->so_img->height);
	texture->we_img->img = mlx_xpm_file_to_image(_game->_mlx, texture->we,
			&texture->we_img->width, &texture->we_img->height);
	texture->ea_img->img = mlx_xpm_file_to_image(_game->_mlx, texture->ea,
			&texture->ea_img->width, &texture->ea_img->height);
	texture->dr_img->img = mlx_xpm_file_to_image(_game->_mlx, "textures/door2.xpm",
			&texture->dr_img->width, &texture->dr_img->height);
	if (!texture->no_img->img || !texture->so_img->img || !texture->dr_img->img
		|| !texture->we_img->img || !texture->ea_img->img)
	{
		ft_putendl_fd("Error: Failed to load textures.", STDERR);
		ft_malloc(CLEAR, CLEAR);
		exit(EXIT_FAILURE);
	}
	init_textures_address(texture);
	_game->texture = texture;
}
