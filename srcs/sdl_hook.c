#include "wolf.h"

int			sdl_exit_wolf(t_env *env, Uint8 keycode)
{
	if (keycode == SDL_SCANCODE_ESCAPE)
	{
		env_free(env);
		exit(0);
	}
	return (0);
}

static int	sdl_check_pos(t_env *env, t_point mult, float check)
{
	int x;
	int y;

	x = env->player.pos.x + mult.x * check;
	y = env->player.pos.y;
	env->w_map[x][y] == 0 ? env->player.pos.x += mult.x * check : 0;
	x = env->player.pos.x;
	y = env->player.pos.y + mult.y * check;
	env->w_map[x][y] == 0 ? env->player.pos.y += mult.y * check : 0;
	return (1);
}

int			sdl_move(t_env *env, Uint8 *keycodes)
{
	if (keycodes[SDL_SCANCODE_W])
		sdl_check_pos(env, env->player.dir, 0.1);
	if (keycodes[SDL_SCANCODE_S])
		sdl_check_pos(env, env->player.dir, -0.1);
	if (keycodes[SDL_SCANCODE_D])
		sdl_check_pos(env, env->player.plane, 0.1);
	if (keycodes[SDL_SCANCODE_A])
		sdl_check_pos(env, env->player.plane, -0.1);
	return (0);
}

int			sdl_motion_mouse(t_env *env, int x, int y)
{
	double	mult;

	mult = x < 0 ? 4.0 : -4.0;
	env->player.dir = point_rotate(env->player.dir, mult);
	env->player.plane = point_rotate(env->player.plane, mult);
	env->angle_d += mult;
	env->angle_d > 358.0 ? env->angle_d = 0.0 : 0;
	env->angle_d < 0.0 ? env->angle_d = 358.0 : 0;
	if (y > 10)
	{
		if (env->is_updn > -400)
			env->is_updn -= 20;
	}
	else if (y < -10)
	{
		if (env->is_updn < 400)
			env->is_updn += 20;
	}
	return (0);
}

int			player_jump(t_env *env)
{
	if (env->player.actions.is_jumping == 1)
	{
		env->is_updn += 20;
		env->hratio += 0.1;
	}
	else
	{
		env->is_updn -= 20;
		env->hratio -= 0.1;
	}
	if (env->hratio >= 2 && env->player.actions.is_jumping == 1)
		env->player.actions.is_jumping = 0;
	return (0);
}

int			jumping(t_env *env, Uint8 keycode)
{
	if (keycode == SDL_SCANCODE_SPACE)
	{
		env->player.actions.is_jumping = 1;
		SDL_FlushEvent(SDL_KEYDOWN | SDL_KEYUP);
	}
	return (0);
}

int			sdl_keyhook(t_env *env, SDL_Event event)
{
	Uint8	keycode;
	Uint8	*keycodes;

	keycodes = (Uint8 *)SDL_GetKeyboardState(NULL);
	keycode = event.key.keysym.scancode;
	sdl_move(env, (Uint8 *)keycodes);
	if (keycodes[SDL_SCANCODE_R])
		load_weapon(env, SDL_SCANCODE_R, env->ak_frms);
	if (keycodes[SDL_SCANCODE_SPACE])
		jumping(env, SDL_SCANCODE_SPACE);
	sdl_exit_wolf(env, keycode);
	return (0);
}
