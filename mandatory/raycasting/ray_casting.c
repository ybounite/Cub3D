/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:53:10 by ybounite          #+#    #+#             */
/*   Updated: 2025/07/31 14:11:34 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

void	cast_ray(t_data_game *g, t_ray *ray)
{
	t_point h_hit, v_hit;
	double h_dist = 1e30, v_dist = 1e30;
	bool h_found = cast_horizontal(g, ray, &h_hit, &h_dist);
	bool v_found = cast_vertical(g, ray, &v_hit, &v_dist);

	if (h_found && (!v_found || h_dist < v_dist))
	{
		ray->hit = h_hit;
		ray->distance = h_dist;
	}
	else if (v_found)
	{
		ray->hit = v_hit;
		ray->distance = v_dist;
	}
	else{
		ray->hit = ray->player; // no hit
		ray->distance = 0;
	}
}

void _cast_all_rays(t_data_game *g)
{
	t_ray ray;
	short i;

	ray.ray_angle = g->player->angle - FOV / 2;
	ray.step_angle = FOV / WINDOW_WIDTH;
	ray.player.x = g->player->_x;
	ray.player.y = g->player->_y;

    // Distance from player to projection plane (in pixels)
	double dist_proj_plane = (WINDOW_HEIGHT / 2) / tan(FOV / 2);
	for (i = 0; i < WINDOW_WIDTH; i++)
	{
		normalize_angle(&ray.ray_angle);
		cast_ray(g, &ray);
        // Correct fish-eye
		double perp_dist = ray.distance * cos(ray.ray_angle - g->player->angle);
        // Wall height based on projection
		double wall_height = (TILE_SIZE / perp_dist) * dist_proj_plane;
        // Top & bottom Y positions
		int wall_top = (WINDOW_HEIGHT / 2) - wall_height / 2;
		if (wall_top < 0)
			wall_top = 0;
		int wall_bottom = (WINDOW_HEIGHT / 2) + wall_height / 2;
		if (wall_bottom > WINDOW_HEIGHT)
			wall_bottom = WINDOW_HEIGHT;
        // Draw wall stripe (centered vertically)
		for (int y = wall_top; y < wall_bottom; y++)
			my_mlx_pixel_put(g->_img, i, y, 0xBBBBBB);
		ray.ray_angle += ray.step_angle;
	}
}

/*
double	normaliz_angle(double ray_angle)
{
	if (ray_angle < 0) // Normalize angle between 0 and 2π
		ray_angle += 2 * PI;
	if (ray_angle > 2 * PI)
		ray_angle -= 2 * PI;
	return (ray_angle);
}

void init_ray(t_ray *ray, t_data_game *data)
{
	ray->ray_angle = data->player->angle - (FOV / 2);
	ray->angle_step = FOV / NUM_RAYS;
}
/ hhhhh
double	cast_single_ray(t_data_game *_game, int *hit_vertical)
{
	double (x), (y), (dx), (dy);

	x = _game->player->_x;
	y = _game->player->_y;
	dx = cos(_game->player->angle) * -1;
	dy = sin(_game->player->angle) * -1;
	while (true)
	{
		if (_game->map[(int)(y / TILE_SIZE)][(int)(x / TILE_SIZE)] == '1')
		{
			*hit_vertical = 0;
			break ;
		}
		x += dx;
		y += dy;
	}
	return (sqrt(pow((x - _game->player->_x), 2)) + pow((y - _game->player->_y), 2));
}

void	draw_3d_projection(t_data_game *_game, int column, double ray_angle, int hit_vertical)
{
    // Fisheye correction
    double corrected = _game->ray.distance * cos(ray_angle - _game->player->angle);

    // Projected wall height
    double proj_plane = (WINDOW_WIDTH / 2) / tan(FOV / 2);
    double wall_height = (TILE_SIZE / corrected) * proj_plane;

    int wall_top = (WINDOW_HEIGHT / 2) - (wall_height / 2);
    int wall_bottom = (WINDOW_HEIGHT / 2) + (wall_height / 2);

    int wall_color = hit_vertical ? 0xAAAAAA : 0xFFFFFF;

    // Draw column (vertical line)
    for (int y = 0; y < WINDOW_HEIGHT; y++)
    {
        if (y < wall_top)
            my_mlx_pixel_put(_game->_img, column, y, 0x87CEEB); // Sky
        else if (y >= wall_top && y <= wall_bottom)
            my_mlx_pixel_put(_game->_img, column, y, wall_color); // Wall
        else
            my_mlx_pixel_put(_game->_img, column, y, 0x333333); // Floor
    }
}

void	draw_ray(t_data_game *_game, double angle, int color)
{
	double rx = _game->player->_x;
	double ry = _game->player->_y;

	double dx = cos(angle) * -1;
	double dy = sin(angle) * -1;
	while (true)
	{
        	int map_x = (int)(rx / TILE_SIZE);
	        int map_y = (int)(ry / TILE_SIZE);
        	if (_game->map[map_y][map_x] == '1')
	            break;
	        if (rx < 0 || ry < 0 || map_x >= _game->map_width || map_y >= _game->map_height)
        	    break;
	        my_mlx_pixel_put(_game->_img, (int)rx, (int)ry, color);
	        rx += dx;
        	ry += dy;
	}
}

void	cast_all_rays(t_data_game *_game)
{
	double	start_angle;
	double	ray_angle;
	short	i;
	int hit_vertical;

	i = 0;
	start_angle = _game->player->angle - (FOV / 2);
	while (i < NUM_RAYS)
	{
		ray_angle = start_angle + i * (FOV / NUM_RAYS);
		ray_angle = config_normaliz_angle(ray_angle);
		_game->ray.distance = cast_single_ray(_game, &hit_vertical);
		draw_3d_projection(_game, i, ray_angle, hit_vertical);
		//draw_ray(_game, ray_angle, 0x00FF00); // Green color for visibility
		i++;
	}
}

// Horizontal intersection (DDA simplification)
void check_horizontal_intersect(t_data_game *data, t_ray *ray)
{
	double x = data->player->_x;
	double y = data->player->_y;
	double dx = cos(ray->ray_angle);
	double dy = sin(ray->ray_angle);

	while (true)
	{
		int map_x = (int)(x / TILE_SIZE);
		int map_y = (int)(y / TILE_SIZE);
		if (map_x < 0 || map_x >= WINDOW_WIDTH || map_y < 0 || map_y >= WINDOW_HEIGHT)
			break;
		if (data->map[map_y][map_x] == '1')
		{
			ray->wall_hit_x = x;
			ray->wall_hit_y = y;
			ray->distance = sqrt(pow(x - data->player->_x, 2) + pow(y - data->player->_y, 2));
			ray->wall_type = HORIZONTAL;
			break;
		}
		x += dx;
		y += dy;
	}
}

// Vertical intersection (same as above for now, can be optimized separately)
void check_vertical_intersect(t_data_game *data, t_ray *ray)
{
	double x = data->player->_x;
	double y = data->player->_y;
	double dx = cos(ray->ray_angle);
	double dy = sin(ray->ray_angle);

	while (true)
	{
		int map_x = (int)(x / TILE_SIZE);
		int map_y = (int)(y / TILE_SIZE);
		if (map_x < 0 || map_x >= WINDOW_WIDTH || map_y < 0 || map_y >= WINDOW_HEIGHT)
			break;
		if (data->map[map_y][map_x] == '1')
		{
			double distance = sqrt(pow(x - data->player->_x, 2) + pow(y - data->player->_y, 2));
			if (distance < ray->distance || ray->wall_type == NONE)
			{
				ray->wall_hit_x = x;
				ray->wall_hit_y = y;
				ray->distance = distance;
				ray->wall_type = VERTICAL;
			}
			break;
		}
		x += dx;
		y += dy;
	}
}

// Calculate distance and color
void calc_distance(t_data_game *data, t_ray *ray, int *color)
{
	double angle_diff = normaliz_angle(ray->ray_angle - data->player->angle);
	ray->distance *= cos(angle_diff);
	if (ray->wall_type == VERTICAL)
		*color = DARK_GRAY;
	else
		*color = WHITE;
}

// Project wall on screen
void wall_projection(t_data_game *data, t_ray *ray, int *color, int col)
{
	double dist_to_proj_plane = (WINDOW_WIDTH / 2) / tan(FOV / 2);
	double wall_height = (TILE_SIZE / ray->distance) * dist_to_proj_plane;

	int wall_top = (WINDOW_HEIGHT / 2) - (wall_height / 2);
	int wall_bottom = (WINDOW_HEIGHT / 2) + (wall_height / 2);
	if (wall_top < 0) wall_top = 0;
	if (wall_bottom > WINDOW_HEIGHT) wall_bottom = WINDOW_HEIGHT;

	for (int y = 0; y < WINDOW_HEIGHT; y++)
	{
		if (y < wall_top)
			my_mlx_pixel_put(data->_img, col, y, 0x87CEEB); // Sky
		else if (y >= wall_top && y <= wall_bottom)
			my_mlx_pixel_put(data->_img, col, y, *color);   // Wall
		else
			my_mlx_pixel_put(data->_img, col, y, 0x333333); // Floor
	}
}

// Raycasting and rendering
void cast_all_rays(t_data_game *data)
{
	t_ray ray;
	int i = 0;
	int color;

	init_ray(&ray, data);

	while (i < NUM_RAYS)
	{
		ray.wall_type = NONE;
		ray.distance = 0;
		check_horizontal_intersect(data, &ray);
		check_vertical_intersect(data, &ray);
		calc_distance(data, &ray, &color);
		wall_projection(data, &ray, &color, i);
		ray.ray_angle += ray.angle_step;
		ray.ray_angle = normaliz_angle(ray.ray_angle);
		i++;
	}
}
*/
