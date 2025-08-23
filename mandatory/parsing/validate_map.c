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

int	ft_count(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i] != '\0')
		i++;
	return (i);
}

//  if any 0 is closed by space or outside map => is not valide
static bool	validate_door_placement(t_data_game *_game, int i, int j, int width)
{
	if (j > 0 && j < width - 1 && i > 0 && i < _game->map_height - 1)
	{
		if (!(_game->map[i][j - 1] == '1' && _game->map[i][j + 1] == '1')
			&& !(_game->map[i - 1][j] == '1' && _game->map[i + 1][j] == '1'))
		{
			printf("Error\nDoor must be enclosed by walls on opposite sides\n");
			return (false);
		}
	}
	else
	{
		printf("Error\nDoor cannot be at map boundary\n");
		return (false);
	}
	return (true);
}

static bool	check_adjacent_cells(t_data_game *_game, int i, int j, int width)
{
	bool	invalid;

	invalid = false;
	if (i > 0 && (j >= ft_count(_game->map[i - 1]) || _game->map[i
			- 1][j] == ' '))
		invalid = true;
	if (i < _game->map_height - 1 && (j >= ft_count(_game->map[i + 1])
			|| _game->map[i + 1][j] == ' '))
		invalid = true;
	if (j > 0 && _game->map[i][j - 1] == ' ')
		invalid = true;
	if (j < width - 1 && _game->map[i][j + 1] == ' ')
		invalid = true;
	if (invalid)
	{
		printf("Error\nInvalid map- valid cell adjacent to space or outside boundary\n");
		return (false);
	}
	return (true);
}

static bool	validate_cell(t_data_game *_game, int i, int j, int width)
{
	if (_game->map[i][j] == 'D')
	{
		if (!validate_door_placement(_game, i, j, width))
			return (false);
	}
	if (is_valid_cell(_game->map[i][j]))
	{
		if (i == 0 || i == _game->map_height - 1 || j == 0 || j == width - 1)
		{
			printf("Error\nValid cells cannot be at map boundary\n");
			return (false);
		}
		if (!check_adjacent_cells(_game, i, j, width))
			return (false);
	}
	return (true);
}

bool	is_valid_map(t_data_game *_game)
{
	int i;
	int j;
	int width;

	if (check_map_if_closed(_game) == false)
		return (false);
	i = 0;
	while (i < _game->map_height)
	{
		j = 0;
		width = ft_count(_game->map[i]);
		while (j < width)
		{
			if (!validate_cell(_game, i, j, width))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}