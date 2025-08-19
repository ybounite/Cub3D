#include "../../includes/Cub3D.h"

void	init_textures(t_data_game *_game)
{
	_game->texture = ft_malloc(sizeof(t_texture), ALLOC);
	_game->texture->config = _game;
	_game->texture->NO = _game->config->textures[0];
	_game->texture->SO = _game->config->textures[1];
	_game->texture->WE = _game->config->textures[2];
	_game->texture->EA = _game->config->textures[3];
}

void	init_textures_data(t_data_game *_game)
{
	t_texture	*texture;

	// Use the existing texture from _game
	_game->texture->NO_img = ft_malloc(sizeof(t_imag), ALLOC);
	_game->texture->SO_img = ft_malloc(sizeof(t_imag), ALLOC);
	_game->texture->WE_img = ft_malloc(sizeof(t_imag), ALLOC);
	_game->texture->EA_img = ft_malloc(sizeof(t_imag), ALLOC);
	texture = _game->texture;
	texture->NO_img->img = mlx_xpm_file_to_image(_game->_mlx, texture->NO,
		&texture->NO_img->width, &texture->NO_img->height);
	texture->SO_img->img = mlx_xpm_file_to_image(_game->_mlx, texture->SO,
		&texture->SO_img->width, &texture->SO_img->height);
	texture->WE_img->img = mlx_xpm_file_to_image(_game->_mlx, texture->WE,
		&texture->WE_img->width, &texture->WE_img->height);
	texture->EA_img->img = mlx_xpm_file_to_image(_game->_mlx, texture->EA,
		&texture->EA_img->width, &texture->EA_img->height);
	if (!texture->NO_img->img || !texture->SO_img->img || !texture->WE_img->img
		|| !texture->EA_img->img)
	{
		ft_putendl_fd("Error: Failed to load textures.", STDERR);
		ft_malloc(CLEAR, CLEAR);
		exit(EXIT_FAILURE);
	}
}
