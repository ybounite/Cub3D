/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:45:16 by ybounite          #+#    #+#             */
/*   Updated: 2025/06/20 18:56:31 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

void	parsing(char *filename)
{
	check_file_name(filename);
	
}
void	syntax_error(short option)
{
	if (option == 1)
		ft_putstr_fd("Error: \nInvalid arguments\n", 2);
}
int main(int ac, char **av)
{
	// char **map;
	
	if (ac != 2)
		return (syntax_error(true), EXIT_FAILURE);
	parsing(av[1]);

	printf("this name is valid !\n");
	return 0;
}
