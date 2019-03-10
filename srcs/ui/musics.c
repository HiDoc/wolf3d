#include "doom.h"

void	load_sounds(t_env *env)
{
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	env->sounds.shot = Mix_LoadWAV("rsrc/sound/shot.wav");
}