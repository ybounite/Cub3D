/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 12:45:53 by ybounite          #+#    #+#             */
/*   Updated: 2025/07/14 15:29:25 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

char	*remove_newline(char *line)
{
	if (!line)
		return NULL;
	short	i;

	i = ft_strlen(line) - 1;
	if (line[i] == '\n')
		line[i] = '\0';
	return line;
}

char	**parse_map(t_data_game *_game)
{
	char	**maps;
	short	index;
	
	_game->size = ft_lstsize(_game->map_start);
	maps = ft_malloc(sizeof(char *) * ( _game->size + 1), ALLOC);
	index = 0;
	while (_game->map_start)
	{
		maps[index++] = remove_newline(_game->map_start->content);
		_game->map_start = _game->map_start->next;
	}
	maps[index] = NULL;
	return maps;
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
	validate_textures(_game->config);
	// // check this texter in valide ?
	_game->map = parse_map(_game);
	if (!check_allowed_characters(_game))
		return false;
	// check is all map is close in wall ?
	// 
	return (true);
}
