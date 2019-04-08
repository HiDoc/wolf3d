/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 18:43:01 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/08 23:13:53 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		doom_release(t_env *env)
{
	lt_destroy();
	if (env->sdl.surface)
		SDL_FreeSurface(env->sdl.surface);
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
