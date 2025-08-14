/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:37:09 by ybounite          #+#    #+#             */
/*   Updated: 2025/08/14 15:38:04 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

void	my_mlx_pixel_put(t_imag *_img, int x, int y, int color)
{
	char	*dst;
	if (x < 0 || y < 0 || x >= _img->width || y >= _img->height)
		return ;
	dst = _img->addr + (y * _img->line_len + x * (_img->bit_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	clear_image(t_imag *img, int color)
{
	int (y), (x);

	y = 0;
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

