/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 16:03:46 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/17 04:15:50 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		assign_vertex(t_vtx *vtx, t_env *env)
{
	env->sct_current->vtx_current = vtx;
	env->sct_current->vtx_end->next = vtx;
	env->sct_current->vtx_end = vtx;

	// stock xmin xmax ymin ymax
	(vtx->pos.x < env->sct_current->xmin)
		? env->sct_current->xmin = vtx->pos.x : 0;
	(vtx->pos.x > env->sct_current->xmax)
		? env->sct_current->xmax = vtx->pos.x : 0;
	(vtx->pos.y < env->sct_current->ymin)
		? env->sct_current->ymin = vtx->pos.y : 0;
	(vtx->pos.y > env->sct_current->ymax)
		? env->sct_current->ymax = vtx->pos.y : 0;
}

int			draw_mode(t_env *env)
{
	const t_pos			m = env->data->mouse;
	const SDL_Event 	event = env->data->sdl.event;
	const SDL_Rect  	rect = (SDL_Rect){20, 100, 850, 680};

	if (ui_mouseenter(m.x, m.y, rect))
	{
		if (event.type == SDL_MOUSEBUTTONDOWN && !env->sct_hover)
		{
			env->vtx_size = 0;
			if (!env->drawing)
			{
				env->drawing = 1;
				create_sector(env);
			}
			if (!env->vtx_hover)
			{
				create_vertex(env->mouse, env);
				return (1);
			}
			else if (env->vtx_hover == env->sct_current->vtx_start)
			{
				env->sct_current->close = 1;
				env->sct_current->vtx_current = 0;
				env->sct_current = 0;
				env->drawing = 0;
				return (1);
			}
			else if (env->vtx_hover->sector != env->sct_current)
			{
				create_vertex(env->vtx_hover->pos, env); // assign
				return (1);
			}
		}
	}
	if (m.x || m.y)
	{
		if (env->sct_current)
		{
			env->vtx_size = pythagore(
			env->sct_current->vtx_current->pos, env->mouse);
		}
		return (1);
	}
	return (0);
}
