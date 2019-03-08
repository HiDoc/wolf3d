#include "doom.h"

int	load_weapon(t_env *env, Uint8 keycode)
{
	if (keycode == SDL_SCANCODE_R)
	{
		env->player.actions.is_loading = 1;
		SDL_FlushEvent(SDL_KEYDOWN | SDL_KEYUP);
	}
	return (0);
}

int	put_gun_shoot(t_env *env, int frame)
{
	t_weapon	*weapon;

	weapon = env->player.inventory.current;
	frame /= 2.5;
	if (frame < weapon->time_shoot)
		put_gun(env, weapon->sprite_shoot[frame]);
	else
		env->player.actions.is_shooting = 0;
	return (1);
}

int	put_gun_load(t_env *env, int frame)
{
	t_weapon	*weapon;

	weapon = env->player.inventory.current;
	frame /= 2.5;
	if (frame < weapon->time_reload - 1)
		put_gun(env, weapon->sprite_reload[frame]);
	else
		env->player.actions.is_loading = 0;
	return (1);
}

int	put_gun(t_env *env, SDL_Surface *sprite)
{
	int x;
	int y;

	x = W - sprite->w;
	y = H - sprite->h;
	if (x < 0 || y < 0)
		put_img_inv(env, sprite, (t_edge){{0, 0}, {W - W / 16, H}}, (t_edge){{0, 0}, {0, 0}});
	else
		draw_img(env, (t_edge){{x, y}, {W, H}},
		sprite,
		(t_ixy){100, 0});
	return (1);
}