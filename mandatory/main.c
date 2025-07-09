/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:45:16 by ybounite          #+#    #+#             */
/*   Updated: 2025/07/09 14:47:40 by ybounite         ###   ########.fr       */
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

void draw_rect(void *mlx, void *win_mlx, int x, int y, int size, int color)
{
    int i, j;

	i = 0;
    while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mlx_pixel_put(mlx, win_mlx, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void render_map(void *mlx, void *win_mlx, char **map)
{
    short x, y;
    int color;

	y = 0;
    while (map[y])
    {
		x = 0;
        while (map[y][x])
        {
            if (map[y][x] == '1')
                color = 0x444444; // dark gray wall
            else if (map[y][x] == '0')
                color = 0xCCCCCC; // light gray floor
            else
                color = 0x000000; // black for unknown

            draw_rect(mlx, win_mlx, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, color);
			x++;
        }
		y++;
    }
}

void	init_window(t_data_game *_game)
{
	_game->_mlx = mlx_init();

	_game->_win_mlx = mlx_new_window(_game->_mlx, _game->size * TILE_SIZE, _game->size * TILE_SIZE, "Cub3D");
	render_map(_game->_mlx, _game->_win_mlx, _game->map);
	mlx_hook(_game->_win_mlx, KeyPress, KeyPressMask, control_key_, &_game->_win_mlx);
	mlx_hook(_game->_win_mlx, 17, 0, _destory_window, &_game->_win_mlx);
	mlx_loop(_game->_mlx);
	// _destory_window(_game);
}

int main(int ac, char **av)
{
	t_data_game	*_game;
	// t_player	player;

	if (ac != 2)
		return (syntax_error(true), EXIT_FAILURE);
	_game = ft_malloc(sizeof(t_data_game), ALLOC);
	_game->config = ft_malloc(sizeof(t_config), ALLOC);
	ft_bzero(_game->config->textures, sizeof(char *) * TEXTURE_COUNT);
	if (!parsing(av[1], _game))
		return 1;

	for (size_t i = 0; _game->map[i]; i++)
		printf("CHECKING LINE: %s", _game->map[i]);

	for (size_t i = 0; i < TEXTURE_COUNT; i++)
	{
		if (_game->config->textures[i])
			printf("\ntype %zu: %s", i, _game->config->textures[i]);
	}
	// init_window(_game);
	// player_init(_game, &player);
	ft_malloc(CLEAR, CLEAR);
	return 0;
}
