/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_allowed_characters.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:44:57 by ybounite          #+#    #+#             */
/*   Updated: 2025/07/11 16:53:07 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

bool	isplayer_position(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

bool	check_allowed_characters(t_data_game *_game)
{
	short	player_count;
	short	y;
	short	x;
	char	c;

	(1) && (player_count = 0), (y = 0);
	while (_game->map[y])
	{
		x = 0;
		while (_game->map[y][x])
		{
			c = _game->map[y][x];
			if (!isplayer_position(c) && c != '1'
				&& c != '0' && c != ' ' && c != '\n')
				return (ft_putendl_fd("Error\nInvalid character", STDERR), false);
			if (isplayer_position(c))
				player_count++;
			x++;
		}
		y++;
	}
	if (player_count != 1)
		return (ft_putendl_fd("Error\nJest one player position", STDERR), false);
	return true;
}
