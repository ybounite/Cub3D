/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_direction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:21:21 by ybounite          #+#    #+#             */
/*   Updated: 2025/08/14 15:21:27 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

void    normalize_angle(double *angle)
{
	*angle = fmod(*angle, 2 * PI);
	if (*angle < 0)
		*angle += 2 * PI;
}

bool	is_facing_down(double angle)
{
	return (angle > 0 && angle < PI);
}

bool	is_facing_up(double angle)
{
	return !is_facing_down(angle);
}

bool	is_facing_right(double angle)
{
	return (angle < PI/2 || angle > 3*PI/2);
}

bool	is_facing_left(double angle)
{
	return !is_facing_right(angle);
}

