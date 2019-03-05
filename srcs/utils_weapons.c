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

	weapon = env->player.inventory.current;
	frame /= 2.5;
	if (frame < weapon->time_shoot)
		put_gun(env, weapon->sprite_shoot[frame]);
	else
		env->player.actions.is_shooting = 0;
	// 	put_img(env, weapon->sprite_shoot[frame], 200, 170);
}

void	put_gun_load(t_env *env, int frame)
{
	t_weapon	*weapon;

	weapon = env->player.inventory.current;
	frame /= 2.5;
	if (frame < weapon->time_reload - 1)
		put_gun(env, weapon->sprite_reload[frame]);
	else
		env->player.actions.is_loading = 0;

	// 	put_img(env, weapon->sprite_reload[frame], 200, 170);
}

void	put_gun(t_env *env, SDL_Surface *sprite)
{
	int x;
	int y;

	x = W - sprite->w;
	y = H - sprite->h;
	if (x < 0 || y < 0)
		draw_img(env, (t_edge){{0, 0}, {W, H}},
		sprite,
		(t_ixy){x < 0 ? -x : x, y < 0 ? -y : y});
	else
		draw_img(env, (t_edge){{x, y}, {W, H}},
		sprite,
		(t_ixy){0, 0});
}