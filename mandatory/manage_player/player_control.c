
#include "../../includes/Cub3D.h"



void	_player_move(int key, t_data_game *_game)
{
	if (key == S_KEY)
	{
		_game->player->_x -= cos(_game->player->angle) * MOVE_SPEED;
		_game->player->_y -= sin(_game->player->angle) * MOVE_SPEED;
	}
	else if (key == W_KEY)
	{
		_game->player->_x += cos(_game->player->angle) * MOVE_SPEED;
		_game->player->_y += sin(_game->player->angle) * MOVE_SPEED;
	}
	else if (key == A_KEY)
	{
		_game->player->_x += cos(_game->player->angle - M_PI_2) * MOVE_SPEED;
		_game->player->_y += sin(_game->player->angle - M_PI_2) * MOVE_SPEED;
	}
	else if (key == D_KEY)
	{
		_game->player->_x += cos(_game->player->angle + M_PI_2) * MOVE_SPEED;
		_game->player->_y += sin(_game->player->angle + M_PI_2) * MOVE_SPEED;
	}
}

int	control_key_(int keycode, t_data_game *_game)
{
	double	(old_player_x), (old_player_y);
	(1) && (old_player_y = _game->player->_y), (old_player_x = _game->player->_x);
	if (keycode == ESCAPE)
	{
		mlx_destroy_window(_game->_mlx, _game->_win_mlx);
		ft_malloc(CLEAR, CLEAR);
		exit(EXIT_SUCCESS);
	}
	_player_move(keycode, _game);
	if (_hase_wall(_game, _game->player->_x, _game->player->_y))
	{
		_game->player->_x = old_player_x;
	 	_game->player->_y = old_player_y;
	}
	if (keycode == LEFT_ARROW){
		_game->player->angle -= ROTATION_SPEED;
		printf("angle LEFT : %f\n", _game->player->angle);
		if (_game->player->angle < 0)
		{
			_game->player->angle += 2 * PI;
			printf("updat angle LEFT : %f\n", _game->player->angle);

		}
	}
	else if (keycode == RIGHT_ARROW)
	{
		_game->player->angle += ROTATION_SPEED;
		printf("angle RIGTH : %f\n", _game->player->angle);
		if (_game->player->angle >= 2){
			_game->player->angle -= 2 * PI; // keep angle
			printf("updat angle RIGTH : %f\n", _game->player->angle);
		}
	}
	return (true);
}

