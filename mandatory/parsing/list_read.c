/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybounite <ybounite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 12:44:47 by ybounite          #+#    #+#             */
/*   Updated: 2025/07/11 18:33:26 by ybounite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3D.h"

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