#include "../../includes/Cub3D.h"

bool	is_valid_cell(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == 'D');
}

bool	check_top_and_bottum(t_data_game *_game)
{
	int	i;
	int	j;

	i = 0;
	while (i < _game->map_height)
	{
		j = 0;
		if (i == 0 || i == _game->map_height - 1)
		{
			while (_game->map[i][j])
			{
				if (_game->map[i][j] == 'N' || _game->map[i][j] == 'S'
					|| _game->map[i][j] == 'E' || _game->map[i][j] == 'W')
				{
					printf("Invalid map: top or bottom row must be all walls\n");
					return (false);
				}
				j++;
			}
		}
		i++;
	}
	return (true);
}

bool	check_right_and_left(t_data_game *_game)
{
	int	i;
	int	j;

	i = 0;
	while (i < _game->map_height)
	{
		j = 0;
		if (_game->map[i][j] == 'N' || _game->map[i][j] == 'S'
			|| _game->map[i][j] == 'E' || _game->map[i][j] == 'W'
			|| _game->map[i][ft_strlen(_game->map[i]) - 1] == 'N')
		{
			printf("Invalid map: left or right column must be all walls\n");
			return (false);
		}
		i++;
	}
	return (true);
}

bool	check_map_if_closed(t_data_game *_game)
{
	if (check_top_and_bottum(_game) == false)
		return (false);
	if (check_right_and_left(_game) == false)
		return (false);
	return (true);
}

//  if any 0 is closed by space or outside map => is not valide
bool	is_valid_map(t_data_game *_game)
{
	short	i;
	short	j;
	int		width;

	i = 0;
	if (check_map_if_closed(_game) == false)
		return (false);
	while (i < _game->map_height)
	{
		j = 0;
		width = ft_strlen(_game->map[i]);
		while (j < width)
		{
			if (_game->map[i][j] == 'D')
			{
				if (!(_game->map[i][j - 1] == '1' && _game->map[i][j
						+ 1] == '1') && !(_game->map[i - 1][j] == '1'
						&& _game->map[i + 1][j] == '1'))
				{
					printf("Error\nDoor must be enclosed by walls on opposite sides\n");
					return (false);
				}
			}
			if (is_valid_cell(_game->map[i][j]))
			{
				if ((i == 0 || i == _game->map_height - 1) || (j == 0
						|| j == width - 1) || (_game->map[i - 1][j] == ' '
						|| _game->map[i + 1][j] == ' ') || (_game->map[i][j
						- 1] == ' ' || _game->map[i][j + 1] == ' '))
				{
					printf("Error\n Invalid map\n");
					return (false);
				}
			}
			j++;
		}
		i++;
	}
	return (true);
}
