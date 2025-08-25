/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:53:10 by ybounite          #+#    #+#             */
/*   Updated: 2025/08/25 14:23:20 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

void        cast_ray(t_data_game *g, t_ray *ray)
{
        t_point (h_hit), (v_hit);
        double h_dist = 1e30, v_dist = 1e30;
	g->is_door_h = false, g->is_door_v = false;
        bool h_found = cast_horizontal(g, ray, &h_hit, &h_dist);
        bool v_found = cast_vertical(g, ray, &v_hit, &v_dist);

        if (h_found && (!v_found || h_dist < v_dist))
        {
                ray->hit = h_hit;
                ray->distance = h_dist; 
                ray->was_hit_vertical = 0;
        }
        else if (v_found)
        {
                ray->hit = v_hit;
                ray->distance = v_dist;
                ray->was_hit_vertical = 1;
        }
        else{
                ray->hit = ray->player; // no hit
                ray->distance = 0;
                ray->was_hit_vertical = -1;
        }
}

unsigned int        get_pixel(t_imag *tex, int x, int y)
{
        char        *dst;

        if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
                return (0xFF00FF);
        dst = tex->addr + (y * tex->line_len + x * (tex->bit_per_pixel / 8));
        return (*(unsigned int *)dst);
}

t_imag        *choose_texture(t_data_game *g, t_ray *ray)
{
        if (ray->was_hit_vertical == 1)
        {
	        if (g->is_door_v)
	                return (g->texture->dr_img);
                if (is_facing_left(ray->ray_angle))

                        return (g->texture->we_img);
                else
                        return (g->texture->ea_img);
        }
        else
        {
		if (g->is_door_h)
                	return (g->texture->dr_img);
                if (is_facing_down(ray->ray_angle))
                        return (g->texture->no_img);
                else
                        return (g->texture->so_img);
        }
}

void        init_ray(t_ray *ray, t_data_game *_game)
{
        ray->ray_angle = _game->player->angle - (FOV / 2.0);
        ray->step_angle = FOV / WINDOW_WIDTH;
        ray->player.x = _game->player->_x;
        ray->player.y = _game->player->_y;
        ray->dist_proj_plane = (WINDOW_HEIGHT / 2.0) / tan(FOV / 2.0);
}

unsigned int        blend_color(unsigned int src, unsigned int bg, double alpha)
{
        int r1 = (src >> 16) & 0xFF;
        int g1 = (src >> 8) & 0xFF;
        int b1 = src & 0xFF;

        int r2 = (bg >> 16) & 0xFF;
        int g2 = (bg >> 8) & 0xFF;
        int b2 = bg & 0xFF;

        int r = (int)(r1 * alpha + r2 * (1 - alpha));
        int g = (int)(g1 * alpha + g2 * (1 - alpha));
        int b = (int)(b1 * alpha + b2 * (1 - alpha));

        return (r << 16) | (g << 8) | b;
}

int        get_tex_x(t_ray *ray, t_imag *textuer)
{
        int        tex_x;

        // find textures x
        if (ray->was_hit_vertical)
                tex_x = (int)fmod(ray->hit.y, TILE_SIZE);
        else
                tex_x = (int)fmod(ray->hit.x, TILE_SIZE);
        return (tex_x * textuer->width / TILE_SIZE);
}

void        draw_wall_strip(t_data_game *_g, t_ray *ray, t_imag *tex, t_data_slice sd)
{
        int                y;
        int                d;
        unsigned int       color;
        unsigned int       final_color;

        y = sd.wall_top;
        while (y < sd.wall_bottome)
        {
                d = (y + (sd.wall_height / 2.0)) - WINDOW_HEIGHT / 2.0;
                d *= tex->height;
                sd.tex_y = d / sd.wall_height;
                sd.alpha = 1.0 - (ray->distance / 2000);
                color = get_pixel(tex, sd.tex_x, sd.tex_y); 
                if (sd.alpha < 0)
                        sd.alpha = 0;
                if (sd.alpha > 1)
                        sd.alpha = 1;
                final_color = blend_color(color, BLACK, sd.alpha);
                my_mlx_pixel_put(_g->_img, sd.i, y++, final_color);
        }
}

void        _render_wall_slice(t_data_game *_g, t_ray *ray, int i)
{
        t_data_slice        slic;
        t_imag                *tex;
        // CORRECT FISH-EYE
        slic.perp_dist = ray->distance * cos(ray->ray_angle - _g->player->angle);
        slic.wall_height = (TILE_SIZE / slic.perp_dist)  * ray->dist_proj_plane;
        slic.wall_top = (WINDOW_HEIGHT / 2.0) - slic.wall_height / 2.0;
        slic.wall_bottome = (WINDOW_HEIGHT / 2.0) + slic.wall_height / 2.0;
        if (slic.wall_top < 0)
                slic.wall_top = 0;
        if (slic.wall_bottome > WINDOW_HEIGHT)
                slic.wall_bottome = WINDOW_HEIGHT;
        tex = choose_texture(_g, ray);
        slic.tex_x = get_tex_x(ray, tex);
        slic.i = i;
        draw_wall_strip(_g, ray, tex, slic);
}

void        _cast_all_rays(t_data_game *_game)
{
        t_ray        ray;
        short        i;

        init_ray(&ray, _game);
        i = 0;
        while (i < WINDOW_WIDTH)
        {
                normalize_angle(&ray.ray_angle);
                cast_ray(_game, &ray);
		_render_wall_slice(_game, &ray, i);
                ray.ray_angle += ray.step_angle;
                i++;
        }
}
/*
void        _render_wall_slice(t_data_game *_game, t_ray *ray, int i)
{
        double        perp_dist;
        double        wall_height;
        int        wall_top;
        int        wall_bottom;

        // correct fish-ey
        perp_dist = ray->distance * cos(ray->ray_angle - _game->player->angle);
        wall_height = (TILE_SIZE / perp_dist) * ray->dist_proj_plane;
        wall_top = (WINDOW_HEIGHT / 2.0) - wall_height / 2.0;
        if (wall_top < 0)
                wall_top = 0;
        wall_bottom = (WINDOW_HEIGHT / 2.0) + wall_height / 2.0;
        if (wall_bottom > WINDOW_HEIGHT)
                wall_bottom = WINDOW_HEIGHT;

        t_imag *tex = choose_texture(_game, ray);

        // find texture X
        int tex_x;
        if (ray->was_hit_vertical)
                tex_x = (int)fmod(ray->hit.y, TILE_SIZE);
        else
                tex_x = (int)fmod(ray->hit.x, TILE_SIZE);
        tex_x = (tex_x * tex->width) / TILE_SIZE;
        // draw vertical stripe
        for (int y = wall_top; y < wall_bottom; y++)
        {
                int destanceFromTop = y + (wall_height/2.0) - (WINDOW_HEIGHT/2.0);
                int d= destanceFromTop * tex->height;
                int tex_y = d / wall_height;
                unsigned int color = get_pixel(tex, tex_x, tex_y);
                // transparency effect based on distance
                double max_dist = 800.0; // adjust fog distance
                double alpha = 1.0 - (ray->distance / max_dist);
                if (alpha < 0)
                        alpha = 0;
                if (alpha > 1)
                        alpha = 1;
                // fade into black (or could use floor/sky colors)
                unsigned int bg_color = BLACK;
                unsigned int final_color = blend_color(color, bg_color, alpha);
                my_mlx_pixel_put(_game->_img, i, y, final_color);
        }
}
void        _cast_all_rays(t_data_game *g)
{
        t_ray        ray;
        short        i;

        init_ray(&ray, g);
        //ray.ray_angle = g->player->angle - (FOV / 2);
        //ray.step_angle = FOV / WINDOW_WIDTH;
        //ray.player.x = g->player->_x;
        //ray.player.y = g->player->_y;

        // distance from player to projection plane
        double dist_proj_plane = (WINDOW_HEIGHT / 2) / tan(FOV / 2);

        for (i = 0; i < WINDOW_WIDTH; i++)
        {
                normalize_angle(&ray.ray_angle);
                cast_ray(g, &ray);

                // correct fish-eye
                double perp_dist = ray.distance * cos(ray.ray_angle - g->player->angle);
                if (perp_dist < 0.0001) perp_dist = 0.0001; // avoid div by 0

                // wall projected height
                double wall_height = (TILE_SIZE / perp_dist) * dist_proj_plane;

                // top & bottom Y
                int wall_top = (WINDOW_HEIGHT / 2) - (wall_height / 2);
                if (wall_top < 0)
                        wall_top = 0;
                int wall_bottom = (WINDOW_HEIGHT / 2) + (wall_height / 2);
                if (wall_bottom > WINDOW_HEIGHT)
                        wall_bottom = WINDOW_HEIGHT;

                // pick texture
                t_imag *tex = choose_texture(g, &ray);

                // find X coordinate in texture
                int tex_x;
                if (ray.was_hit_vertical)
                        tex_x = (int)fmod(ray.hit.y, TILE_SIZE);
                else
                        tex_x = (int)fmod(ray.hit.x, TILE_SIZE);
                tex_x = (tex_x * tex->width) / TILE_SIZE;

                // draw vertical stripe
                for (int y = wall_top; y < wall_bottom; y++)
                {
                        int d = (y - wall_top) * tex->height;
                        int tex_y = d / wall_height;
                        unsigned int color = get_pixel(tex, tex_x, tex_y);
                        my_mlx_pixel_put(g->_img, i, y, color);
                }
                ray.ray_angle += ray.step_angle;
        }
}*/
