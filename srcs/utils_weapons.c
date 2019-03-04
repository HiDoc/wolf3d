#include "doom.h"

int	load_weapon(t_env *env, Uint8 keycode, SDL_Surface **weapon)
{
	(void)weapon;
	if (keycode == SDL_SCANCODE_R)
	{
		env->player.actions.is_loading = 1;
		SDL_FlushEvent(SDL_KEYDOWN | SDL_KEYUP);
	}
	return (0);
}

void	put_gun_shoot(t_env *env, int frame)
{
	t_weapon	*weapon;

	weapon = env->player.inventory.weapons[0];
	frame /= 2.5;
	if (frame < weapon->time_shoot)
		put_img(env, weapon->sprite_shoot[frame], 200, 170);
	else
		env->player.actions.is_shooting = 0;
}

void	put_gun_load(t_env *env, int frame)
{
	t_weapon	*weapon;

	weapon = env->player.inventory.weapons[0];
	frame /= 2.5;
	if (frame < weapon->time_reload - 1)
		put_img(env, weapon->sprite_reload[frame], 200, 170);
	else
		env->player.actions.is_loading = 0;
}

void	put_gun(t_env *env)
{
	int x;
	int y;
	SDL_Surface	*sprite;

	sprite = env->player.inventory.weapons[0]->sprite;
	x = W - sprite->w;
	y = H - sprite->h;
	put_img(env, sprite, x, y);
}