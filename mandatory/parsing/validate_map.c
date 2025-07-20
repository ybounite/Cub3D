#include "../../includes/Cub3D.h"

bool	is_valid_cell(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

bool	flood_fill_check(char **map, int **visited, int x, int y, int height)
{
	int	width;

	if (y < 0 || y >= height || !map[y])
		return (false);
	width = ft_strlen(map[y]);
	if (x < 0 || x >= width)
		return (false);
	// hit a space (enclosed)
	if (map[y][x] == ' ')
		return (false);
	// hit a wall || already visited
	if (map[y][x] == '1' || visited[y][x])
		return (true);
	if (!is_valid_cell(map[y][x]))
		return (false);
	// Mark as visited
	visited[y][x] = 1;
	// Check all 4 directions
	if (!flood_fill_check(map, visited, x + 1, y, height)
		|| !flood_fill_check(map, visited, x - 1, y, height)
		|| !flood_fill_check(map, visited, x, y + 1, height)
		|| !flood_fill_check(map, visited, x, y - 1, height))
		return (false);
	return (true);
}

int	**create_visited_array(char **map, int height)
{
	int	**visited;

	int i, j;
	visited = ft_malloc(sizeof(int *) * height, ALLOC);
	i = 0;
	while (i < height)
	{
		visited[i] = ft_malloc(sizeof(int) * ft_strlen(map[i]), ALLOC);
		j = 0;
		while (j < (int)ft_strlen(map[i]))
		{
			visited[i][j] = 0;
			j++;
		}
		i++;
	}
	return (visited);
}

void	find_player_position(char **map, int height, int *px, int *py)
{
	int y, x;
	*px = -1;
	*py = -1;
	y = 0;
	while (y < height && map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (isplayer_position(map[y][x]))
			{
				*px = x;
				*py = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

bool	validate_map(char **map, int height)
{
	int		**visited;
	bool	is_valid;

	int player_x, player_y;
	find_player_position(map, height, &player_x, &player_y);
	if (player_x == -1 || player_y == -1)
		return (ft_putendl_fd("Error\nPlayer not found", STDERR), false);
	visited = create_visited_array(map, height);
	is_valid = flood_fill_check(map, visited, player_x, player_y, height);
	if (!is_valid)
		ft_putendl_fd("Error\nMap is not properly enclosed", STDERR);
	return (is_valid);
}
