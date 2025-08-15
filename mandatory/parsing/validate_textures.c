/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamezoua <bamezoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 12:39:41 by ybounite          #+#    #+#             */
/*   Updated: 2025/08/15 11:13:46 by bamezoua         ###   ########.fr       */
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

int	shift_color(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		printf("Error : Invalid color range [0, 255] in texture\n");
		syntax_error(6);
		ft_malloc(CLEAR, CLEAR);
		exit(1);
	}
	return (r << 16 | g << 8 | b);
}

void	validate_colors(t_config *_config, t_data_game *_game)
{
	short	i;
	char	**split;

	int r, g, b;
	i = 4;
	while (i < 6)
	{
		split = ft_split(_config->textures[i], ',');
		if (!split || ft_strlen(_config->textures[i]) == 0)
		{
			printf("Error : Invalid color format in texture\n");
			ft_malloc(CLEAR, CLEAR);
			exit(1);
		}
		if (!split[0] || !split[1] || !split[2] || split[3])
		{
			printf("Error : Color must be R,G,B format\n");
			ft_malloc(CLEAR, CLEAR);
			exit(1);
		}
		r = ft_atoi(split[0]);
		g = ft_atoi(split[1]);
		b = ft_atoi(split[2]);
		if (i == 4)
		{
			_config->floor_color = mlx_get_color_value(_game->_mlx,
					shift_color(r, g, b));
			printf("floor color: %d\n", _config->floor_color);
		}
		else if (i == 5)
		{
			_config->ceiling_color = mlx_get_color_value(_game->_mlx,
					shift_color(r, g, b));
			printf("ceiling color: %d\n", _config->ceiling_color);
		}
		i++;
	}
}
