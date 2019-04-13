/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 14:14:41 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/13 22:33:45 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void     create_object(int category, t_env *env)
{
	t_object   *new;

	if (!(new = (t_object *)ft_memalloc(sizeof(t_object))))
		ui_error_exit_sdl("Editor: create object, out of memory", env->data);
	//new->ref = /**/;
	//new->sct = /**/;
	//...
	new->pos = env->mouse;
	new->category = category;
	if (!(env->objects))
	{
		env->objects = new;
		env->objects->next = 0;
	}
	else
	{
		new->next = env->objects;
		env->objects = new;
	}
}

int			elem_mode(t_env *env)
{
	const int		tab[5] = {
		E_B_ELM_OBWL, E_B_ELM_CONS, E_B_ELM_NTTY, E_B_ELM_PRFB, E_B_ELM_SPEC};
	const SDL_Event event = env->data->sdl.event;
	const SDL_Rect	rect = (SDL_Rect){20, 100, 850, 680};
	t_elem			*obj_btn;
	int				i;

	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y, rect)
				&& env->obj_type > -1)
		{
			if (env->sct_hover)
				create_object(env->obj_type, env);
			return (1);
		}

		i = 0;
		while (i < 5)
		{
			if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y,
						get_element(tab[i], env)->rect))
			{
				env->obj_mode = i;
				return (1);
			}
			i++;
		}
		// click on object button
		obj_btn = env->btn_objs;
		while (obj_btn)
		{
			if (ui_mouseenter(
						env->data->mouse.x, env->data->mouse.y, obj_btn->rect)
					&& obj_btn->type == env->obj_mode)
				env->obj_type = obj_btn->type; // replace by ref
			obj_btn = obj_btn->next;
		}
	}
	return (0);
}
