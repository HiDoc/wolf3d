/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 16:12:22 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/14 17:22:23 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		unselect_all(t_env *env)
{
	env->obj_select = 0;
	env->vtx_select = 0;
	env->sct_select = 0;
}

static void     delete_object(t_object *obj, t_env *env)
{
	t_object	*ptr;

	ptr = env->objects;
	if (ptr == obj)
	{
		env->objects = ptr->next;
		free(obj->name);
		free(obj);
		return ;
	}
	while (ptr && ptr->next)
	{
		if (ptr->next == obj)
		{
			ptr->next = ptr->next->next;
			free(obj->name);
			free(obj);
		}
		ptr = ptr->next;
	}
}

int			select_mode(t_env *env)
{
	const t_pos		m = env->data->mouse;
	const SDL_Event event = env->data->sdl.event;
	const SDL_Rect  rect = (SDL_Rect){20, 100, 850, 680};

	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y, rect))
		{
			unselect_all(env);
			if (env->vtx_hover)
				env->vtx_select = env->vtx_hover;
			else if (env->obj_hover)
				env->obj_select = env->obj_hover;
			else if (env->sct_hover)
				env->sct_select = env->sct_hover;
			return (1);
		}
		else if (ui_mouseenter(m.x, m.y, get_element(E_B_SELEC_DEL, env)->rect))
		{
			//if (env->vtx_select)
			/*else */if (env->obj_select)
				delete_object(env->obj_select, env);
			//else if (env->sct_select)
			unselect_all(env);
			return (1);	
		}
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
