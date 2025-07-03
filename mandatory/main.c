/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:45:16 by ybounite          #+#    #+#             */
/*   Updated: 2025/07/03 18:09:00 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

t_list	*listnew(void *content)
{
	t_list	*new;

	new = ft_malloc(sizeof(t_list), ALLOC);
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

t_list	*file_reading(short fd)
{
	char	*line;
	t_list	*_list = NULL;
	while ((line = get_next_line(fd)))
	{
		ft_lstadd_back(&_list, listnew(line));
	}
	close(fd);
	return _list;
}

void	Print_list(t_list *_list)
{
	while (_list)
	{
		printf("line : %s\n", (char *)_list->content);
		_list = _list->next;
	}
}

// bool	validate_map(t_data_game *_game)

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
    {
        fprintf(stderr, "Error: Unknown texture identifier\n");
        return false;
    }
    if (_game->config->textures[type])
    {
        fprintf(stderr, "Error: Duplicate texture definition for %d\n", type);
        return true;
    }
    // Skip the identifier (e.g., "NO ") to get the path
    path_start = line + 3;
    while (*path_start == ' ')
        path_start++;
    _game->config->textures[type] = ft_strdup(path_start);
    if (!_game->config->textures[type])
    {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return true;
    }
    return false;
}

bool	istexturs(char *line)
{
	return (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
			|| !ft_strncmp(line, "WE ", 3) || ft_strncmp(line, "EA ", 3));
}

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

void	parse_config(t_data_game *_game)
{
	t_list	*tmp;
	char	*line;

	tmp = _game->list;
	while (tmp)
	{
		line = (char *)tmp->content;
		if (is_emty_line(line))
		{
			tmp = tmp->next;
			continue ;
		}
		while (*line == ' ' || *line == '\t')
			line++;
		if (isconfig(line))
			parse_texture_line(_game, line);
		tmp = tmp->next;
	}
	
}
bool	parsing(char *filename, t_data_game *_game)
{
	check_file_name(filename);
	_game->fd = open(filename, O_RDONLY);
	if (_game->fd == -1)
		return (ft_putendl_fd("FAILDE TO OPINE FILE", STDERR) , false);
	_game->list = file_reading(_game->fd);
	if (!_game->list)
		return (ft_putendl_fd("Error\nMap is empty", STDERR), false);
	// parse_config(_game);
	return (true);
}

int main(int ac, char **av)
{
	t_data_game	*_game;
	t_config	*_config;

	if (ac != 2)
		return (syntax_error(true), EXIT_FAILURE);
	_game = ft_malloc(sizeof(t_data_game), ALLOC);
	_config = ft_malloc(sizeof(t_config), ALLOC);
	if (!parsing(av[1], _game))
		return 1;
	Print_list(_game->list);

	_config->textures[0] = ft_strdup((char*)_game->list->content);
	// config->floor_color = 1231;
	// printf("floor color is : %d\n", config->floor_color);
	printf("%s\n", _config->textures[0]);
	printf("this name is valid !\n");
	ft_malloc(CLEAR, CLEAR);
	return 0;
}
// bool validate_map(t_data_game *_game)
// {
// 	// if (!check_player_count(_game->map))
// 	//     return (ft_putendl_fd("Error: Invalid player position.", STDERR), false);
// 	// if (!check_valid_chars(_game->map))config
// 	//     return (ft_putendl_fd("Error: Invalid characters in map.", STDERR), false);
// 	// if (!check_map_closed(_game->map))
// 	//     return (ft_putendl_fd("Error: Map is not closed.", STDERR), false);
//     return true;
// }