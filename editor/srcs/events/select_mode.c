/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 16:12:22 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/14 13:40:01 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		unselect_all(t_env *env)
{
	env->obj_select = 0;
	env->vtx_select = 0;
	env->sct_select = 0;
}

int			select_mode(t_env *env)
{
	const SDL_Event event = env->data->sdl.event;
	const SDL_Rect  rect = (SDL_Rect){20, 100, 850, 680};

	if (event.type == SDL_MOUSEBUTTONDOWN
		&& ui_mouseenter(env->data->mouse.x, env->data->mouse.y, rect))
	{
		unselect_all(env);
		if (env->vtx_hover)
		{
			env->vtx_select = env->vtx_hover;
		}
		else if (env->obj_hover)
		{
			env->obj_select = env->obj_hover;
		}
		else if (env->sct_hover)
		{
			env->sct_select = env->sct_hover;
		}
		return (1);
	}

	// sector
	// 	- ceil
	// 	- floor
	// 	- gravity
	//  [] delete

	// edge
	//	* sector
	//	[] portal
	//	- texture
	//	[] delete

	// vertex
	//	* sector
	//	[] delete

	// wall_object
	//	* sector
	//	[] delete

	// comsumable
	//	* sector
	//	[] delete

	// entity
	//	* sector
	//	[] delete

	// prefab
	//	* sector
	//	[] delete

	// special
	//	* sector
	//	[] delete

	if (env->data->mouse.x || env->data->mouse.y)
		return (1);
	return (0);
}
