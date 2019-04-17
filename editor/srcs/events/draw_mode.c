/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 16:03:46 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/17 01:58:59 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		create_sector(t_env *env)
{
	t_sct	*new;

	if (!(new = lt_push(ft_memalloc(sizeof(t_sct)), ft_memdel)))
		ui_error_exit_sdl("Editor: Out of memory");
	new->xmin = WIN_W + 1;
	new->xmax = -1;
	new->ymin = WIN_H + 1;
	new->ymax = -1;
	new->color = C_CYAN;
	new->next = 0;

	if (!(env->sct_start))
	{
		new->id = 0;
		env->sct_current = new;
		env->sct_start = new;
		env->sct_end = new;
	}
	else
	{
		new->id = env->sct_end->id + 1;
		env->sct_current = new;
		env->sct_end->next = new;
		env->sct_end = new;
	}
	env->nb_sct++;
}

void		create_vertex(t_pos pos, t_env *env)
{
	t_vtx	*new;

	if (!(new = lt_push(ft_memalloc(sizeof(t_vtx)), ft_memdel)))
		ui_error_exit_sdl("Editor: Out of memory");
	new->pos.x = pos.x;
	new->pos.y = pos.y;
	new->sector = env->sct_current;
	new->next = 0;

	if (!(env->sct_current->vtx_start))
	{
		env->sct_current->vtx_current = new;
		env->sct_current->vtx_start = new;
		env->sct_current->vtx_end = new;
	}
	else
	{
		env->sct_current->vtx_current = new;
		env->sct_current->vtx_end->next = new;
		env->sct_current->vtx_end = new;
	}

	// stock xmin xmax ymin ymax
	(pos.x < env->sct_current->xmin) ? env->sct_current->xmin = pos.x : 0;
	(pos.x > env->sct_current->xmax) ? env->sct_current->xmax = pos.x : 0;
	(pos.y < env->sct_current->ymin) ? env->sct_current->ymin = pos.y : 0;
	(pos.y > env->sct_current->ymax) ? env->sct_current->ymax = pos.y : 0;
	env->nb_vtx++;
}

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
