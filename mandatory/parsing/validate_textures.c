/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 12:39:41 by ybounite          #+#    #+#             */
/*   Updated: 2025/07/19 11:19:00 by bamezoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

// int file_exists(const char *filename)
// {

// }

char	*remove_space(char *str)
{
	short	i;
	bool	isother_word;

	i = 0;
	isother_word = false;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\n' && isother_word)
			return (syntax_error(3), exit(EXIT_FAILURE), NULL);
		if (str[i] == ' ' || str[i] == '\n')
		{
			str[i] = '\0';
			isother_word = true;
		}
		i++;
	}
	return (str);
}

bool	check_filename_xpm(char *file_name, char *str)
{
	int	i;

	i = 0;
	file_name = file_name + (ft_strlen(file_name) - 4);
	if (ft_strlen(file_name) == 0)
		return (false);
	while (file_name[i])
	{
		if (file_name[i] != str[i])
			return (false);
		i++;
	}
	return (true);
}

void	validate_textures(t_config *_config)
{
	short	i;

	i = 0;
	while (i < 4)
	{
		// printf("-->%s\n", remove_space(_config->textures[i]));
		if (!_config->textures[i]
			|| !check_filename_xpm(remove_space(_config->textures[i]), ".xpm"))
		{
			syntax_error(5);
			ft_malloc(CLEAR, CLEAR);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	validate_colors(t_config *_config)
{
	short	i;
	char	**split;

	i = 4;
	while (i < 6)
	{
		// printf("texture %d: %s\n", i, _config->textures[i]);
		split = ft_split(_config->textures[i], ',');
		while (*split)
		{
			if (ft_strlen(*split) == 0 || ft_atoi(*split) < 0
				|| ft_atoi(*split) > 255)
			{
				printf("Error : Invalid color range [0, 255] in texture\n");
				syntax_error(6);
				ft_malloc(CLEAR, CLEAR);
				exit(EXIT_FAILURE);
			}
			split++;
		}
		// if(i == 4)
		// {
		// 	_config->floor_color = ft_atoi(_config->textures[i]);
		// 	printf("Floor color: %d\n", _config->floor_color);
		// }
		// else if (i == 5)
		// {
		// 	_config->ceiling_color = ft_atoi(_config->textures[i]);
		// 	printf("Ceiling color: %d\n", _config->ceiling_color);
		// }
		i++;
	}
}

// void	check_left_and_right_columns(char **map, short size)
// {
// 	short	i;

// 	i = 0;
// 	while (i < size)
// 	{
// 		if (map[i][0] != '1')
// 		{
// 			ft_putendl_fd("Error\nMap is not closed on the left side ", STDERR);
// 			exit(EXIT_FAILURE);
// 		}
// 		if (map[i][ft_strlen(map[i]) - 1] != '1')
// 		{
// 			ft_putendl_fd("Error\n Map is not closed on the right side ",
// 				STDERR);
// 			exit(EXIT_FAILURE);
// 		}
// 		i++;
// 	}
// }

// void check_top_row(char **map, short size)
// {
// 	size_t	i;
// 	(void)size;

// 	i = 0;
// 	while (i < ft_strlen(map[0]))
// 	{
// 		if (map[0][i] != '1')
// 		{
// 			ft_putendl_fd("Error\nMap is not closed on the top row", STDERR);
// 			exit(EXIT_FAILURE);
// 		}
// 		i++;
// 	}
// }

// void check_bottom_row(char **map, short size)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < ft_strlen(map[size - 1]))
// 	{
// 		if (map[size - 1][i] != '1')
// 		{
// 			ft_putendl_fd("Error\nMap is not closed on the bottom row", STDERR);
// 			exit(EXIT_FAILURE);
// 		}
// 		i++;
// 	}
// }

// void	map_is_closed(char **map, short size)
// {
// 	short	i;
// 	short	j;

// 	i = 0;
// 	j = 0;
// 	check_left_and_right_columns(map, size);
// 	check_top_row(map, size);
// 	check_bottom_row(map, size);
// }
