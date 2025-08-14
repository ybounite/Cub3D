#include "../../includes/Cub3D.h"

bool	is_valid_cell(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

//  if any 0 is closed by space or outside map => is not valide
bool	is_valid_map(t_data_game *_game)
{
	short	i;
	short	j;
	int width;

	i = 0;
	while (i < _game->map_height)
	{
		j = 0;
		width = ft_strlen(_game->map[i]);
		while (j < width)
		{
			if (_game->map[i][j] == '0')
			{
				if ((i == 0 || i == _game->map_height - 1) ||
					(j == 0 || j == width - 1) ||
					(_game->map[i - 1][j] == ' ' || _game->map[i + 1][j] == ' ') ||
					(_game->map[i][j - 1] == ' ' || _game->map[i][j + 1] == ' '))
				{
					printf("Invalid map: '0' at (%d, %d) is not closed by walls\n", i, j);
					return false;
				}
			}
			j++;
		}
		i++;
	}
	return true;
}
