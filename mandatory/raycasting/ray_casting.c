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

// bool	is_perpendicular_to_Yaxis(double ray_angle)
// {
// 	return (ray_angle == 0 || ray_angle == PI);
// }
// bool	is_perpendicular_to_Xaxis(double ray_angle)
// {
// 	return (ray_angle == 1.5 * PI || ray_angle == PI / 2);
// }
// bool	isfacing_up(double rotation_angle)
// {
// 	return (rotation_angle > PI && rotation_angle < 2 * PI);
// }
// bool	isfacing_down(double rotation_angle)
// {
// 	return (rotation_angle < PI && rotation_angle > 0);
// }
// bool	isfacing_left(double rotation_angle)
// {
// 	return (rotation_angle > PI / 2 && rotation_angle < 1.5 *PI);
// }
// bool	isfacing_right(double rotation_angle)
// {
// 	return (rotation_angle >= 1.5 * PI || rotation_angle <= PI / 2);
// }
// int inside_bounds(t_data_game *data, double x, double y) 
// {
//     (void)data;
//     if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
//         return 0;
//     return 1;
// }
// void    normalize_angle(double *angle)
// {
//     (*angle) = fmod(*angle, 2 * PI);
//     if (*angle < 0)
//         (*angle) += 2 * PI;
// }
// // 
// void	calculate_first_horizountal_interseaction(t_data_game *_game, t_ray *ray, double tan_value)
// {
//     if (isfacing_up(ray->ray_angle))
//         ray->first_y = floor(_game->player->_y / TILE_SIZE) * TILE_SIZE;
//     else
//         ray->first_y = (floor(_game->player->_y / TILE_SIZE) + 1) * TILE_SIZE;
//     ray->first_x = _game->player->_x + (ray->first_y - _game->player->_y) / tan_value;
// }

// void    calc_horizontal_step(t_ray *ray, double tan_val)
// {
//     if (isfacing_up(ray->ray_angle))
//         ray->step_y = -TILE_SIZE;
//     else
//         ray->step_y = TILE_SIZE;
//     ray->step_x = TILE_SIZE / fabs(tan_val);
//     if (isfacing_left(ray->ray_angle))
//         ray->step_x = -(ray->step_x);
// }

// void	check_horizontal_intersect(t_data_game *_game, t_ray *ray)
// {
// 	double	tan_value;
// 	normalize_angle(&ray->ray_angle);
// 	if (is_perpendicular_to_Yaxis(ray->ray_angle))
// 	{
// 		if (ray->ray_angle >= 1.5 * PI || ray->ray_angle <= PI / 2)
// 			ray->h_Interseaction.x = _game->player->_x + WINDOW_WIDTH;
// 		else
// 			ray->h_Interseaction.x = _game->player->_x - WINDOW_WIDTH;
// 		ray->h_Interseaction.y = _game->player->_y;
// 		return ;
// 	}
// 	tan_value = tan(ray->ray_angle);
// 	if (fabs(tan_value) <= 0.000001){
// 		if (tan_value >= 0)
//             tan_value = 0.000001;
//         else
//             tan_value = -0.000001;
// 	}
// 	calculate_first_horizountal_interseaction(_game, ray, tan_value);
// 	calc_horizontal_step(ray, tan_value);
// 	ray->h_Interseaction.x = ray->first_x;
//     ray->h_Interseaction.y = ray->first_y;
//     while (!is_wall(_game, ray->h_Interseaction.x, ray->h_Interseaction.y - isfacing_up(ray->ray_angle))
// 			&& inside_bounds(_game, ray->h_Interseaction.x, ray->h_Interseaction.y)) {
//         ray->h_Interseaction.x += ray->step_x;
//         ray->h_Interseaction.y += ray->step_y;
//     }
// }
// // vertical 
// void    calc_first_v_intersect(t_data_game *data, t_ray *ray, double tan_val)
// {
//     if (isfacing_right(ray->ray_angle))
//         ray->first_x = (floor(data->player->_x / TILE_SIZE) + 1) * TILE_SIZE;
//     else
//         ray->first_x = floor(data->player->_x / TILE_SIZE) * TILE_SIZE;
//     ray->first_y = data->player->_y + (ray->first_x - data->player->_x) * tan_val;
// }
// void    calc_vertical_step(t_data_game *data, t_ray *ray, double tan_val)
// {
//     (void)data;
//     if (isfacing_right(ray->ray_angle))
//         ray->step_x = TILE_SIZE;
//     else
//         ray->step_x = -TILE_SIZE;
//     ray->step_y = TILE_SIZE * fabs(tan_val);
//     if (isfacing_up(ray->ray_angle))
//         ray->step_y = -ray->step_y;
// }

// void check_vertical_intersect(t_data_game *data, t_ray *ray)
// {
//     double tan_val;
//     normalize_angle(&ray->ray_angle);
//     if (is_perpendicular_to_Xaxis(ray->ray_angle))
//     {
//         ray->v_intersect.x = data->player->_x;
//         if (isfacing_up(ray->ray_angle))
//             ray->v_intersect.y = data->player->_y + WINDOW_WIDTH;
//         else
//             ray->v_intersect.y = data->player->_y - WINDOW_WIDTH;
//         return ;
//     }
//     tan_val = tan(ray->ray_angle);
//     calc_first_v_intersect(data, ray, tan_val);
//     calc_vertical_step(data, ray, tan_val);
//     ray->v_intersect.x = ray->first_x;
//     ray->v_intersect.y = ray->first_y;
//     while (!is_wall(data, ray->v_intersect.x - isfacing_left(ray->ray_angle), ray->v_intersect.y) 
// 		&& inside_bounds(data, ray->v_intersect.x, ray->v_intersect.y)) {
//         ray->v_intersect.x += ray->step_x;
//         ray->v_intersect.y += ray->step_y;
//     }
// }
// void    calc_distance(t_data_game *data, t_ray *ray, int *color)
// {
//     ray->h_dist = (ray->h_Interseaction.x - data->player->_x) * (ray->h_Interseaction.x - data->player->_x) + (ray->h_Interseaction.y - data->player->_y) * (ray->h_Interseaction.y - data->player->_y);
//     ray->v_dist = (ray->v_intersect.x - data->player->_x) * (ray->v_intersect.x - data->player->_x) + (ray->v_intersect.y - data->player->_y) * (ray->v_intersect.y - data->player->_y);

//     if (ray->h_dist < ray->v_dist)
//     {
//         *color = 0xaa0000;
//         ray->distance = sqrt(ray->h_dist);
//         ray->ray_end.x = ray->h_Interseaction.x;
//         ray->ray_end.y = ray->h_Interseaction.y;
//     } else 
//     {
//         *color = 0xff0000;
//         ray->distance = sqrt(ray->v_dist);
//         ray->ray_end.x = ray->v_intersect.x;
//         ray->ray_end.y = ray->v_intersect.y;
//     }
//     ray->distance *= cos(ray->ray_angle - data->player->angle);
// 	draw_line(data, ray->player, ray->ray_end, BLUE);
//     // draw_line(data, ray->player, ray->ray_end, BLUE, 2);
// }
// void	raycasting(t_data_game *_game)
// {
// 	t_ray	ray;
// 	short	i = 0;
//     int     color;

// 	// init data ray
// 	ray.ray_angle = _game->player->angle - (FOV / 2);
// 	ray.step_angle = FOV / NUM_RAYS;
// 	ray.distance = 0;
// 	ray.player.x = _game->player->_x;
// 	ray.player.y = _game->player->_y;

// 	while (i < NUM_RAYS)
// 	{
//         check_horizontal_intersect(_game, &ray);
// 		check_horizontal_intersect(_game, &ray);
//         calc_distance(_game, &ray, &color);
// 		i++;
// 	}		
// }
