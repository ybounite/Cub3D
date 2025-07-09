/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 12:45:53 by ybounite          #+#    #+#             */
/*   Updated: 2025/07/09 15:27:34 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

char	**parse_map(t_data_game *_game)
{
	char	**maps;
	short	index;
	
	_game->size = ft_lstsize(_game->map_start);
	maps = ft_malloc(sizeof(char *) * ( _game->size + 1), ALLOC);
	index = 0;
	while (_game->map_start)
	{
		maps[index++] = (char *)_game->map_start->content;
		_game->map_start = _game->map_start->next;
	}
	maps[index] = NULL;
	return maps;
}

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
			if (!isplayer_position(c) && c != '1' && c != '0' && c != ' ' && c != '\n')
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

bool	parsing(char *filename, t_data_game *_game)
{
	check_file_name(filename);
	_game->fd = open(filename, O_RDONLY);
	if (_game->fd == -1)
		return (ft_putendl_fd("Error\nFAILDE TO OPINE FILE", STDERR) , false);
	_game->list = file_reading(_game->fd);
	if (!_game->list)
		return (ft_putendl_fd("Error\nMap is empty", STDERR), false);
	parse_config(_game);
	_game->map = parse_map(_game);
	if (!check_allowed_characters(_game))
		return false;
	return (true);
}
// valid_characters(_game);