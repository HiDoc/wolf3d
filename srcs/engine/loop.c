#include "doom.h"

int sdl_render(t_env *env, void (*f)(t_env *env), int *frame, int *tframe)
{
	SDL_LockSurface(env->sdl.surface);
	f(env);
	loop_frames(env, frame);
	print_hud(env);
	ui_minimap(env);
	ui_draw_msg(env, &env->player.hud.is_txt, tframe);
	if (env->player.inventory.ui.is_active)
	{
		print_inventory(env);
		action_inventory(env, 0, 0);
	}
	SDL_UnlockSurface(env->sdl.surface);
	if (env->sdl.texture == NULL)
		env->sdl.texture = SDL_CreateTextureFromSurface(env->sdl.renderer, env->sdl.surface);
	else
	{
		SDL_DestroyTexture(env->sdl.texture);
		env->sdl.texture = SDL_CreateTextureFromSurface(env->sdl.renderer, env->sdl.surface);
	}
	SDL_RenderClear(env->sdl.renderer);
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

int	sdl_set_velocity(t_env *env, t_vision *v, const int wsad[4])
{
	t_engine	*e;
	t_vtx		move_vec;
	const int	pushing = wsad[0] || wsad[1] || wsad[2] || wsad[3];
	float		accel;
	const float	speed = env->player.actions.is_running ? SPEED_RUN : SPEED_WALK;

	move_vec = (t_vtx){0.f, 0.f};
	e = &env->engine;
	if (wsad[0])
	{
		move_vec.x += e->player.anglecos * speed;
		move_vec.y += e->player.anglesin * speed;
	}
	if (wsad[1])
	{
		move_vec.x -= e->player.anglecos * speed;
		move_vec.y -= e->player.anglesin * speed;
	}
	if (wsad[2])
	{
		move_vec.x += e->player.anglesin * speed;
		move_vec.y -= e->player.anglecos * speed;
	}
	if (wsad[3])
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

	int wsad[4] = {0, 0, 0, 0};
	t_vision v;
	t_engine *e;
	int fps;
	Uint32 time_a;
	Uint32 time_b;
	int frame;
	int tframe;
	const Uint8	*keycodes = (Uint8 *)SDL_GetKeyboardState(NULL);

	time_b = 0;
	fps = 0;
	e = &env->engine;
	v = (t_vision){0, 1, 0, 0, 0, 0};
	while (1)
	{
		SDL_Event ev;
		if ((time_a = SDL_GetTicks()) - time_b > SCREEN_TIC)
		{
			fps = 1000 / (time_a - time_b);
			time_b = time_a;
			sdl_render(env, &dfs, &frame, &tframe);
			player_collision(e, &v, env->player.actions.is_flying);
			SDL_PollEvent(&ev);
			v.moving = 0;
			if (ev.type == SDL_KEYDOWN)
			{
				wsad[0] = (keycodes[SDL_SCANCODE_W]);
				wsad[1] = (keycodes[SDL_SCANCODE_S]);
				wsad[2] = (keycodes[SDL_SCANCODE_A]);
				wsad[3] = (keycodes[SDL_SCANCODE_D]);
				if (keycodes[SDL_SCANCODE_SPACE])
				{
					if (v.ground)
					{
						e->player.velocity.z += env->player.actions.is_flying ? 0.7 : 0.5;
						if (!env->player.actions.is_flying)
							v.falling = 1;
					}
				}
				if (keycodes[SDL_SCANCODE_LCTRL] || keycodes[SDL_SCANCODE_RCTRL])
				{
					v.ducking = 1;
					v.falling = 1;
				}
				if (keycodes[SDL_SCANCODE_Q])
					return (0);
			}
			sdl_keyhook(env, ev);
			wpn_mouse_wheel(env, ev);
			mouse_shoot(env);
		}
		if (!env->player.inventory.ui.is_active)
			sdl_mouse(e, &v);
		if (v.moving)
			sdl_set_velocity(env, &v, (const int *)wsad);
		// SDL_Delay(10);
	}
	return (0);
}
