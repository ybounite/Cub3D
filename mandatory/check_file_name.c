/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_name.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:41:44 by ybounite          #+#    #+#             */
/*   Updated: 2025/06/20 18:55:28 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

bool	check_filename_cub(char *file_name, char *str)
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

void	check_file_name(char *file_name)
{
	if (!file_name || !check_filename_cub(file_name, ".cub"))
	{
		ft_putstr_fd("Erroe:\nfile name is incorrect!\n", 2);
		exit(EXIT_FAILURE);
	}
}
