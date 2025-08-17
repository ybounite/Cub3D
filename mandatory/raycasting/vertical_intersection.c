/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:21:05 by ybounite          #+#    #+#             */
/*   Updated: 2025/08/14 15:21:08 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

bool	cast_vertical(t_data_game *g, t_ray *ray, t_point *hit, double *dist)
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
        int map_x = (int)((next_x + (is_facing_left(ray->ray_angle) ? -1 : 0)) / TILE_SIZE);
        int map_y = (int)(next_y) / TILE_SIZE;
        if (g->map[map_y][map_x] == '1')
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

