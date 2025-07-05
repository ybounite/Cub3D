/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:45:16 by ybounite          #+#    #+#             */
/*   Updated: 2025/07/05 12:37:43 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

// bool	validate_map(t_data_game *_game)

int main(int ac, char **av)
{
	t_data_game	*_game;

	if (ac != 2)
		return (syntax_error(true), EXIT_FAILURE);
	_game = ft_malloc(sizeof(t_data_game), ALLOC);
	_game->config = ft_malloc(sizeof(t_config), ALLOC);
	if (!parsing(av[1], _game))
		return 1;

	for (size_t i = 0; _game->map[i]; i++)
	{
		printf("CHECKING LINE: %s", _game->map[i]);
	}
	
	ft_malloc(CLEAR, CLEAR);
	return 0;
}
