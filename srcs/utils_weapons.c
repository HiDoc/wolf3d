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
		draw_img(env, (t_edge){{W - env->player.inventory.current->sprite_shoot[frame]->w,
		H - env->player.inventory.current->sprite_shoot[frame]->h},
		{W, H}}, env->player.inventory.current->sprite_shoot[frame]);
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
		draw_img(env, (t_edge){{W - env->player.inventory.current->sprite_reload[frame]->w,
		H - env->player.inventory.current->sprite_reload[frame]->h},
		{W, H}}, env->player.inventory.current->sprite_reload[frame]);
	else
		env->player.actions.is_loading = 0;

	// 	put_img(env, weapon->sprite_reload[frame], 200, 170);
}

void	put_gun(t_env *env)
{
	int x;
	int y;

	x = W - env->player.inventory.current->sprite->w;
	y = H - env->player.inventory.current->sprite->h;
	draw_img(env, (t_edge){{x, y}, {W, H}}, env->player.inventory.current->sprite);
}