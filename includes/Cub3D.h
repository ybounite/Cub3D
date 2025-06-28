/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:57:09 by ybounite          #+#    #+#             */
/*   Updated: 2025/06/28 10:52:11 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <stdbool.h>

# include "../libraries/getline/get_next_line.h"
# include "../libraries/libft/libft.h"

# define CLEAR	0
# define ALLOC	1
# define STDERR	2

typedef struct s_config
{
    char *no_texture;
    char *so_texture;
    char *we_texture;
    char *ea_texture;
    int floor_color;
    int ceiling_color;
} t_config;

typedef struct	s_game
{
	short		fd;
	char		**map;
	char		**map_cpy;
	t_list		*list;
	t_config	config;
}				t_data_game;

/* -------------------------------------------------------------------------- */
/*                             check_file_name.c                              */
/* -------------------------------------------------------------------------- */
bool			check_filename_cub(char *file_name, char *str);
void			check_file_name(char *file_name);

/* -------------------------------------------------------------------------- */
/*                             syntax_error.c                                 */
/* -------------------------------------------------------------------------- */
void	        syntax_error(short option);

#endif