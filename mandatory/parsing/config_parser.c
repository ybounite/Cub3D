		/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 12:47:32 by ybounite          #+#    #+#             */
/*   Updated: 2025/07/05 15:15:53 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

t_texture_type	get_texturs_type(char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
		return NO_TEXTURE;
	else if (!ft_strncmp(line, "SO ", 3))
		return SO_TEXTURE;
	else if (!ft_strncmp(line, "WE ", 3))
		return WE_TEXTURE;
	else if (!ft_strncmp(line, "EA ", 3))
		return EA_TEXTURE;
	else if (!ft_strncmp(line , "F ", 2))
		return F_COLOR;
	else if (!ft_strncmp(line, "C ", 2))
		return C_COLOR;
	return IDNTIFIER_TEXTURE;
}

bool	parse_texture_line(t_data_game *_game, char *line)
{
	t_texture_type	type;
	char			*path_start;

	type = get_texturs_type(line);
	if (type == IDNTIFIER_TEXTURE)
		return (syntax_error(3), true);
	if (_game->config->textures[type])
		return (syntax_error(2), true);
	path_start = line + 2;
	if (type <= EA_TEXTURE)
		path_start++; // Skip 3 characters for "NO ", "SO " ...
	while (*path_start == ' ')
		path_start++;
	_game->config->textures[type] = ft_strdup(path_start);
	if (!_game->config->textures[type])
		return (syntax_error(4), true);
	return false;
}

// bool	istexturs(char *line)
// {
// 	return (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
// 			|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3));
// }

bool	isconfig(char *line)
{
	return (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3)
		||	!ft_strncmp(line, "C ", 2) || !ft_strncmp(line, "F ", 2));
}

bool	is_emty_line(char *str)
{
	short	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\n')
		return (true);
	return false;
}

bool	is_map_line(char *line)
{
	while (*line)
	{
		if (*line == '\n')
		{
			line++;
			continue ;
		}
		if (*line != ' ' && *line != '0' && *line != '1'
			&& *line != 'N' && *line != 'S' && *line != 'E' && *line != 'W')
			return false;
		line++;
	}
	return true;
}

void	parse_config(t_data_game *_game)
{
	t_list	*tmp;
	char	*line;

	tmp = _game->list;
	while (tmp)
	{
		line = (char *)tmp->content;
		while (*line == ' ' || *line == '\t')
			line++;
		if (is_emty_line(line))
		{
			tmp = tmp->next;
			continue ;
		}
		if (is_map_line(line)){
			_game->map_start = tmp;
			break ;
		}
		if (isconfig(line))
			parse_texture_line(_game, line);
		else
		{
			syntax_error(3);
			ft_malloc(CLEAR, CLEAR);
			exit(EXIT_FAILURE);
		}
		tmp = tmp->next;
	}
}
