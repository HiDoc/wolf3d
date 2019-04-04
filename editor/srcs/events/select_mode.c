/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 16:12:22 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/04 18:06:19 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		unselect_all(t_env *env)
{
	(void)env;
}

int			select_mode(t_env *env)
{
	const SDL_Event event = env->data->sdl.event;
	const SDL_Rect  rect = (SDL_Rect){20, 100, 850, 680};

	if (event.type == SDL_MOUSEBUTTONDOWN
		&& ui_mouseenter(env->data->mouse.x, env->data->mouse.y, rect))
	{
		if (env->sct_hover)
		{
			env->sct_select = env->sct_hover;;
		}
		else if (env->vtx_hover)
		{
			env->vtx_select = env->vtx_hover;
		}
		else if (env->obj_hover)
		{
			env->obj_select = env->obj_hover;
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

	return (0);
}
