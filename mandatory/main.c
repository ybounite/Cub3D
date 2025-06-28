/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:45:16 by ybounite          #+#    #+#             */
/*   Updated: 2025/06/28 11:09:18 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

t_list	*lstnew(void *content)
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
		ft_lstadd_back(&_list, lstnew(line));
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

bool	parsing(char *filename, t_data_game *_game)
{
	check_file_name(filename);
	_game = ft_malloc(sizeof(t_data_game), ALLOC);
	_game->fd = open(filename, O_RDONLY);
	if (_game->fd == -1)
		return (ft_putendl_fd("FAILDE TO OPINE FILE", STDERR) , false);
	_game->list = file_reading(_game->fd);
	if (!_game->list)
		return (ft_putendl_fd("Error\nMap is empty", STDERR), false);
	Print_list(_game->list);
	// if (check)
	return (true);
}

int main(int ac, char **av)
{
	t_data_game _game;
	
	if (ac != 2)
		return (syntax_error(true), EXIT_FAILURE);
	if (!parsing(av[1], &_game))
		return 1;

	printf("this name is valid !\n");
	ft_malloc(CLEAR, CLEAR);
	return 0;
}
