/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:45:16 by ybounite          #+#    #+#             */
/*   Updated: 2025/07/15 15:01:08 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

// bool	validate_map(t_data_game *_game)
/*
	sin(&) = opposite/hypotenuse
	cos(&) = adjacent/hypotenuse
	tan(&) = opposite/adjacent    
	hypotenuse^2 = opposite^2 + adjacent^2  
	double rad2
*/
/*
void	draw_circle(t_data_game *_game, int cx, int cy, int color)
{
	int radius = 4;
    for (int y = -radius; y <= radius; y++)
    {
        for (int x = -radius; x <= radius; x++)
        {
            if (x * x + y * y <= radius * radius)
                mlx_pixel_put(_game->_mlx, _game->_win_mlx, cx + x, cy + y, color);
        }
    }
}
void	render_map(t_data_game *_game)
{
	short	(y), (x);
	int		color;

	y = 0;
	while (_game->map[y])
	{
		x = 0;
		while (_game->map[y][x])
		{
			if (_game->map[y][x] == '1')
				color = 0x444477;
			else if (_game->map[y][x] == '0')
				color = 0xCCC666;
			else 
				color = 0x000000;
			draw_rect(_game, x * TILE_SIZE, y * TILE_SIZE, color);
			x++;
		}
		y++;
	}
	int px = (int)_game->player->_x * TILE_SIZE + TILE_SIZE / 2;
	int py = (int)_game->player->_y * TILE_SIZE + TILE_SIZE / 2;
	printf("---->px :  %d | py : %d<----\n", px, py);
	// draw_circle(_game, py, px, 0xFF0000);
}
*/
// raduis = 3;
// turndirection = 0;
// walkdirection = 0;
// rotationAngile = PI /2;
// moveSpeed = 2.0;
// rotationSpeed = 2 (PI / 180);


int main(int ac, char **av)
{
	t_data_game	*_game;

	if (ac != 2)
		return (syntax_error(true), EXIT_FAILURE);
	_game = ft_malloc(sizeof(t_data_game), ALLOC);
	_game->config = ft_malloc(sizeof(t_config), ALLOC);
	_game->player = ft_malloc(sizeof(t_player), ALLOC);
	ft_bzero(_game->config->textures, sizeof(char *) * TEXTURE_COUNT);
	if (!parsing(av[1], _game))
		return (ft_malloc(CLEAR, CLEAR), EXIT_FAILURE);
	
	player_init(_game);
	for (size_t i = 0; _game->map[i]; i++)
	{
		printf("%s\n", _game->map[i]);
	}
	_mlx_init_data(_game);
	start_simulation(_game);
	// init_window(_game);
	ft_malloc(CLEAR, CLEAR);
	return EXIT_SUCCESS;
}
