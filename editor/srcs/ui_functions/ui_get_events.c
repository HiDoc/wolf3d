/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_get_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 14:40:45 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/25 11:56:04 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int			ui_get_events(int (*event)(t_env *env), t_env *env)
{
	int		change;

	change = 0;

	SDL_WaitEvent(&(env->data->sdl.event));
	env->data->state = SDL_GetKeyboardState(0);
	SDL_GetMouseState(&(env->data->mouse_x), &(env->data->mouse_y));

	env->data->mouse = (t_pos){
	(float)env->data->mouse_x,
	(float)env->data->mouse_y};

	change = event(env);

	return (change);	
}
