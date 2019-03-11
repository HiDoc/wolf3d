#include "doom.h"

void	sdl_render_game(t_env *env)
{
	dfs(env);
	loop_frames(env, &env->time.frame);
	ui_put_fps(env, env->time.fps);
	print_hud(env);
	ui_minimap(env);
	ui_draw_msg(env, &env->player.hud.is_txt, &env->time.tframe);
}

void	sdl_render_inventory(t_env *env)
{
	print_inventory(env);
	action_inventory(env, 0, 0);
}

int sdl_render(t_env *env, void (*f)(t_env *env))
{
	(void)f;
	SDL_LockSurface(env->sdl.surface);
	f(env);
	SDL_UnlockSurface(env->sdl.surface);
	SDL_UpdateTexture(env->sdl.texture,
					NULL,
					env->sdl.surface->pixels,
					env->sdl.surface->pitch);
	SDL_RenderCopy(env->sdl.renderer, env->sdl.texture, NULL, NULL);
	SDL_RenderPresent(env->sdl.renderer);
	return (1);
}

/*
** Mouse aiming !
*/
int sdl_mouse(t_engine *e, t_vision *v)
{
	int x;
	int y;

	SDL_GetRelativeMouseState(&x, &y);
	e->player.angle += x * 0.03f;
	v->yaw = clamp(v->yaw + y * 0.05f, -5, 5);
	e->player.yaw = v->yaw - e->player.velocity.z * 0.5f;
	player_moving(v, 0, e);
	return (1);
}

int	sdl_set_velocity(t_env *env, t_vision *v, const Uint8 *keycodes)
{
	t_engine	*e;
	t_vtx		move_vec;
	const int	pushing = (keycodes[SDL_SCANCODE_W]) || (keycodes[SDL_SCANCODE_S]) || (keycodes[SDL_SCANCODE_A]) || (keycodes[SDL_SCANCODE_D]);
	float		accel;
	const float	speed = env->player.actions.is_running ? SPEED_RUN : SPEED_WALK;

	move_vec = (t_vtx){0.f, 0.f};
	e = &env->engine;
	if (keycodes[SDL_SCANCODE_W])
	{
		move_vec.x += e->player.anglecos * speed;
		move_vec.y += e->player.anglesin * speed;
	}
	if (keycodes[SDL_SCANCODE_S])
	{
		move_vec.x -= e->player.anglecos * speed;
		move_vec.y -= e->player.anglesin * speed;
	}
	if (keycodes[SDL_SCANCODE_A])
	{
		move_vec.x += e->player.anglesin * speed;
		move_vec.y -= e->player.anglecos * speed;
	}
	if (keycodes[SDL_SCANCODE_D])
	{
		move_vec.x -= e->player.anglesin * speed;
		move_vec.y += e->player.anglecos * speed;
	}
	accel = pushing ? 0.4 : 0.2;
	e->player.velocity.x = e->player.velocity.x * (1 - accel) + move_vec.x * accel;
	e->player.velocity.y = e->player.velocity.y * (1 - accel) + move_vec.y * accel;
	v->moving = pushing;
	return (1);
}

int sdl_loop(t_env *env)
{
	t_vision *v;
	t_engine *e;
	const Uint8	*keycodes = (Uint8 *)SDL_GetKeyboardState(NULL);

	ft_bzero(&env->time, sizeof(t_time));

	e = &env->engine;
	v = &e->player.vision;
	v->falling = 1;
	while (1)
	{
		SDL_Event ev;
		if (keycodes[SDL_SCANCODE_Q])
			return (0);
		if ((env->time.time_a = SDL_GetTicks()) - env->time.time_b > SCREEN_TIC)
		{
			env->time.fps = 1000 / (env->time.time_a - env->time.time_b);
			env->time.time_b = env->time.time_a;
			SDL_PollEvent(&ev);
			if (!env->player.inventory.ui.is_active)
			{
				sdl_render(env, &sdl_render_game);
				player_collision(e, v, env->player.actions.is_flying);
				sdl_keyhook_game(env, ev, keycodes);
				wpn_mouse_wheel(env, ev);
				mouse_shoot(env);
				sdl_mouse(e, v);
				sdl_set_velocity(env, v, keycodes);
			}
			else
			{
				sdl_render(env, &sdl_render_inventory);
				sdl_keyhook_inventory(env, ev, keycodes);
			}
		}
	}
	return (0);
}
