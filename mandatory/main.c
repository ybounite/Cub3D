/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:45:16 by ybounite          #+#    #+#             */
/*   Updated: 2025/08/18 09:29:48 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

void	_draw_line(t_data_game *g, t_point start, t_point end, int color)
{
	double	dx;
	double	dy;
	double	steps;
	double	x_inc;
	double	y_inc;
	double	x;
	double	y;

	dx = end.x - start.x;
	dy = end.y - start.y;
	steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
	if (steps < 1)
		return ;
	x_inc = dx / steps;
	y_inc = dy / steps;
	x = start.x;
	y = start.y;
	for (int i = 0; i <= (int)steps; i++)
	{
		my_mlx_pixel_put(g->_img, (int)round(x), (int)round(y), color);
		x += x_inc;
		y += y_inc;
	}
}

void	sdraw_line(t_data_game *_game)
{
	t_point	inters;
	t_point	step;
	short	i;

	inters.x = _game->player->_x;
	inters.y = _game->player->_y;
	step.x = cos(_game->player->angle);
	step.y = sin(_game->player->angle);
	i = 0;
	while (i < 15) // length of line
	{
		if (is_wall(_game, inters.x, inters.y))
			break ;
		my_mlx_pixel_put(_game->_img, (int)inters.x, (int)inters.y
		   , 0x000000);
		inters.x += step.x;
		inters.y += step.y;
		i++;
	}
}

int	render(t_data_game *g)
{
	static short	frame;

	if (frame == 100)
	{
		clear_image(g->_img, 0x000000);
		draw_sky_and_floor(g);
		//>draw_map(g);
		_cast_all_rays(g);
		//>sdraw_line(g);
	        //cast_ray(g, &ray);
		//_draw_line(g, ray.player, ray.hit, 0xFFFFFF);
		mlx_put_image_to_window(g->_mlx, g->_win_mlx, g->_img->img, 0, 0);
		frame = 0;
	}
	frame++;
	return (0);
}

int main(int ac, char **av)
{
	t_data_game	*_game;

	if (ac != 2)
		return (syntax_error(true), EXIT_FAILURE);
	_game = ft_malloc(sizeof(t_data_game), ALLOC);
	_game->config = ft_malloc(sizeof(t_config), ALLOC);
	_game->player = ft_malloc(sizeof(t_player), ALLOC);
	ft_bzero(_game->config->textures, sizeof(char *) * TEXTURE_COUNT);
	_game->_img = ft_malloc(sizeof(t_imag), ALLOC);
	_game->_mlx = mlx_init();
	if (!_game->_mlx)
		return (ft_putendl_fd("Error:\nmlx_init failed.", STDERR), false);
	if (!parsing(av[1], _game))
		return (ft_malloc(CLEAR, CLEAR), EXIT_FAILURE);
	player_init(_game);
	init_textures(_game);
	printf("poist p_x : %f\n", _game->player->_x);
	printf("poist p_y : %f\n", _game->player->_y);
	
	_mlx_init_data(_game);
	mlx_hook(_game->_win_mlx, KeyPress, KeyPressMask, control_key_, _game);
	mlx_loop_hook(_game->_mlx, render, _game);
	mlx_loop(_game->_mlx);
	// _mlx_init_data(_game);
	// start_simulation(_game);
	// init_window(_game);
	ft_malloc(CLEAR, CLEAR);
	return (EXIT_SUCCESS);
}
