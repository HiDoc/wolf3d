/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 18:43:01 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/07 20:00:14 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		free_env_audio(t_env *env)
{
	Mix_FreeMusic(env->sounds.load);
}

void		free_env_player(t_env *env)
{
	// free env->player.inventory
	// free env->player.actions
	// free env->player.shot
}

void		free_env_world(t_env *env)
{
	// RENDU ICI
}

void		free_env_content(t_env *env)
{
	free_env_audio(env);
	free_env_player(env);
	free_env_world(env);
	//	free_content(env->sdl) // except texture/renderer/window
	//	free_content(env->engine)
	//	free_content(env->hud)
	//	free_content(env->tiletab)
}

void		doom_release(t_env *env)
{
	free_env_content(env);
	if (env->sdl.texture)
		SDL_DestroyTexture(env->sdl.texture);
	if (env->sdl.renderer)
		SDL_DestroyRenderer(env->sdl.renderer);
	if (env->sdl.window)
		SDL_DestroyWindow(env->sdl.window);
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
}

void		doom_error_exit(char *str, t_env *env)
{
	ft_putendl_fd(str, 2);
	doom_release(env);
	exit(EXIT_FAILURE);
}

void		doom_exit(t_env *env)
{
	doom_release(env);
	exit(EXIT_SUCCESS);
}
