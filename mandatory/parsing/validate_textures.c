/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 12:39:41 by ybounite          #+#    #+#             */
/*   Updated: 2025/07/12 10:02:46 by ybounite         ###   ########.fr       */
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
	return str;
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
		
		printf("-->%s\n", remove_space(_config->textures[i]));
		if (!_config->textures[i] || !check_filename_xpm(remove_space(_config->textures[i]), ".xpm"))
		{
			syntax_error(5);
			ft_malloc(CLEAR, CLEAR);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	
}
