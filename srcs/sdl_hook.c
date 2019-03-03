#include "doom.h"

int			sdl_keyhook(t_env *env, SDL_Event event)
{
	Uint8	keycode;
	Uint8	*keycodes;

	keycodes = (Uint8 *)SDL_GetKeyboardState(NULL);
	keycode = event.key.keysym.scancode;

	if (event.type == SDL_KEYDOWN)
	{
		if (keycodes[SDL_SCANCODE_C])
			pick_object(env, env->engine.sectors[0].head_object);
		if (keycodes[SDL_SCANCODE_V])
			pick_object(env, env->engine.sectors[0].head_object->next);
		if (keycodes[SDL_SCANCODE_O])
			give_health(env, &env->player.inventory.objects[0]);
		if (keycodes[SDL_SCANCODE_P])
			give_shield(env, &env->player.inventory.objects[1]);
		if (keycodes[SDL_SCANCODE_TAB])
			env->player.inventory.is_active = 1;
		if (keycodes[SDL_SCANCODE_U])
			env->player.inventory.is_active = 0;
	}
	return (1);
}
