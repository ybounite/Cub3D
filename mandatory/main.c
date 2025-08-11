/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:45:16 by ybounite          #+#    #+#             */
/*   Updated: 2025/08/02 11:16:18 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

void	my_mlx_pixel_put(t_imag *_img, int x, int y, int color)
{
	char	*dst;
	if (x < 0 || y < 0 || x >= _img->width || y >= _img->height)
		return ;
	dst = _img->addr + (y * _img->line_length + x * (_img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	clear_image(t_imag *img, int color)
{

    int y = 0;
    int x;
    while (y < img->height)
    {
        x = 0;
        while (x < img->width)
        {
            my_mlx_pixel_put(img, x, y, color);
            x++;
        }
        y++;
    }
}

/* --------------------------------------------------- */
/* HORIZONTAL INTERSECTION */

bool cast_horizontal(t_data_game *g, t_ray *ray, t_point *hit, double *dist)
{
    t_point step;
    t_point intercept;

    intercept.y = floor(ray->player.y / TILE_SIZE) * TILE_SIZE;
    if (is_facing_down(ray->ray_angle))
        intercept.y += TILE_SIZE;

    intercept.x = ray->player.x + (intercept.y - ray->player.y) / tan(ray->ray_angle);

    step.y = TILE_SIZE * (is_facing_up(ray->ray_angle) ? -1 : 1);
    step.x = TILE_SIZE / tan(ray->ray_angle);
    if ((is_facing_left(ray->ray_angle) && step.x > 0) ||
        (is_facing_right(ray->ray_angle) && step.x < 0))
        step.x *= -1;

    double next_x = intercept.x;
    double next_y = intercept.y;

    while (next_x >= 0 && next_y >= 0 &&
           next_x < g->map_width * TILE_SIZE &&
           next_y < g->map_height * TILE_SIZE)
    {
        int map_x = (int)(next_x / TILE_SIZE);
        int map_y = (int)((next_y + (is_facing_up(ray->ray_angle) ? -1 : 0)) / TILE_SIZE);

        if (g->map[map_y][map_x] == '1') {
            *hit = (t_point){next_x, next_y};
            *dist = hypot(next_x - ray->player.x, next_y - ray->player.y);
            return true;
        }
        next_x += step.x;
        next_y += step.y;
    }
    return false;
}

/* --------------------------------------------------- */
/* VERTICAL INTERSECTION */

bool cast_vertical(t_data_game *g, t_ray *ray, t_point *hit, double *dist)
{
    t_point step;
    t_point intercept;

    intercept.x = floor(ray->player.x / TILE_SIZE) * TILE_SIZE;
    if (is_facing_right(ray->ray_angle))
        intercept.x += TILE_SIZE;

    intercept.y = ray->player.y + (intercept.x - ray->player.x) * tan(ray->ray_angle);

    step.x = TILE_SIZE * (is_facing_left(ray->ray_angle) ? -1 : 1);
    step.y = TILE_SIZE * tan(ray->ray_angle);
    if ((is_facing_up(ray->ray_angle) && step.y > 0) ||
        (is_facing_down(ray->ray_angle) && step.y < 0))
        step.y *= -1;

    double next_x = intercept.x;
    double next_y = intercept.y;

    while (next_x >= 0 && next_y >= 0 &&
           next_x < g->map_width * TILE_SIZE &&
           next_y < g->map_height * TILE_SIZE)
    {
        int map_x = (int)((next_x + (is_facing_left(ray->ray_angle) ? -1 : 0)));
        int map_y = (int)(next_y);

        if (_hase_wall(g, map_x, map_y))
	{
            *hit = (t_point){next_x, next_y};
            *dist = hypot(next_x - ray->player.x, next_y - ray->player.y);
            return true;
        }
        next_x += step.x;
        next_y += step.y;
    }
    return false;
}

/* --------------------------------------------------- */
/* RAY CAST */

void	cast_ray(t_data_game *g, t_ray *ray)
{
    t_point h_hit, v_hit;
    double h_dist = 1e30, v_dist = 1e30;
    bool h_found = cast_horizontal(g, ray, &h_hit, &h_dist);
    bool v_found = cast_vertical(g, ray, &v_hit, &v_dist);

    if (h_found && (!v_found || h_dist < v_dist)) {
        ray->hit = h_hit;
        ray->distance = h_dist;
    }
    else if (v_found) {
        ray->hit = v_hit;
        ray->distance = v_dist;
    }
    else {
        ray->hit = ray->player; // no hit
        ray->distance = 0;
    }
}

/* --------------------------------------------------- */
/* DRAW LINE */

void	_draw_line(t_data_game *g, t_point start, t_point end, int color)
{
    double dx = end.x - start.x;
    double dy = end.y - start.y;
    double steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
    if (steps < 1) return;
    double x_inc = dx / steps;
    double y_inc = dy / steps;
    double x = start.x;
    double y = start.y;
    for (int i = 0; i <= (int)steps; i++) {
        my_mlx_pixel_put(g->_img, (int)round(x), (int)round(y), color);
        x += x_inc;
        y += y_inc;
    }
}

/* --------------------------------------------------- */
/* RENDER (Single Ray Example) */

int render(t_data_game *g)
{
    static short frame;
    if (frame == 100) {
        clear_image(g->_img, 0x000000);
	
	draw_map(g);
        t_ray ray;
        ray.player.x = g->player->_x;
        ray.player.y = g->player->_y;
        ray.ray_angle = g->player->angle; // single ray straight ahead
        normalize_angle(&ray.ray_angle);

        cast_ray(g, &ray);
        _draw_line(g, ray.player, ray.hit, 0xFFFFFF);

        mlx_put_image_to_window(g->_mlx, g->_win_mlx, g->_img->img, 0, 0);
        frame = 0;
    }
    frame++;
    return 0;
}
/*
void	sdraw_line(t_data_game *_game)
{
	double	x = _game->player->_x;
	double	y = _game->player->_y;
	double	dx = cos(_game->player->angle);
	double	dy = sin(_game->player->angle);
	int		i;
	i = 0;
	while (i < 15) // length of line
	{
		if (_game->map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] == '1')
			break ;
		my_mlx_pixel_put(_game->_img, (int)x, (int)y, 0x000000);
		x += dx;
		y += dy;
		i++;
	}
}

int render(t_data_game *_game)
{
	static short frame;

	if (frame == 100)
	{
		draw_map(_game);
		//cast_all_rays(_game);  // Draw all rays in a FOV
		sdraw_line(_game);
		//draw_ray(_game, _game->player->angle, 0x00FF00);
		mlx_put_image_to_window(_game->_mlx, _game->_win_mlx, _game->_img->img, 0, 0);
		frame = 0;
	}
	frame++;
	return 0;
}
*/

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
	if (!parsing(av[1], _game))
		return (ft_malloc(CLEAR, CLEAR), EXIT_FAILURE);
	player_init(_game);
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
