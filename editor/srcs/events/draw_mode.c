/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 16:03:46 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/25 11:56:50 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		create_sector(t_env *env)
{
	t_sct	*new;

	if (!(new = (t_sct *)ft_memalloc(sizeof(t_sct))))
		ui_error_exit_sdl("Editor: Out of memory", env->data);
	new->xmin = WIN_W + 1;
	new->xmax = -1;
	new->ymin = WIN_W + 1;
	new->ymax = -1;
	new->color = C_CYAN;
	new->next = 0;

	if (!(env->sct_start))
	{
		env->sct_current = new;
		env->sct_start = new;
		env->sct_end = new;
	}
	else
	{
		env->sct_current = new;
		env->sct_end->next = new;
		env->sct_end = new;
	}
	env->nb_sct++;
}

void		create_vertex(t_pos pos, t_env *env)
{
	t_vtx	*new;

	if (!(new = (t_vtx *)ft_memalloc(sizeof(t_vtx))))
		ui_error_exit_sdl("Editor: Out of memory", env->data);
	new->pos.x = pos.x;
	new->pos.y = pos.y;
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
	if (pos.x < env->sct_current->xmin)
		env->sct_current->xmin = pos.x;
	else if (pos.x > env->sct_current->xmax)
		env->sct_current->xmax = pos.x;

	if (pos.y < env->sct_current->ymin)
		env->sct_current->ymin = pos.y;
	else if (pos.y > env->sct_current->ymax)
		env->sct_current->ymax = pos.y;
	env->nb_vtx++;
}

void		assign_vertex(t_vtx *vtx, t_env *env)
{
	env->sct_current->vtx_current = vtx;
	env->sct_current->vtx_end->next = vtx;
	env->sct_current->vtx_end = vtx;

	// stock xmin xmax ymin ymax
	if (vtx->pos.x < env->sct_current->xmin)
		env->sct_current->xmin = vtx->pos.x;
	else if (vtx->pos.x > env->sct_current->xmax)
		env->sct_current->xmax = vtx->pos.x;

	if (vtx->pos.y < env->sct_current->ymin)
		env->sct_current->ymin = vtx->pos.y;
	else if (vtx->pos.y > env->sct_current->ymax)
		env->sct_current->ymax = vtx->pos.y;	
}

int			draw_mode(t_env *env)
{
	t_vtx	*current;

	if (!(env->drawing)) // not drawing
	{
		if (!(current = target_vertex(env))) // no dock
		{
			if (!(target_sector(env->data->mouse, env)))
			{
				env->drawing = 1;
				create_sector(env);
				create_vertex(env->data->mouse, env);
			}
		}
		else // dock
		{
			env->drawing = 1;
			create_sector(env);
			create_vertex(current->pos, env);
		}
		return (1);
	}
	else // drawing
	{
		if (!(target_sector(env->data->mouse, env)))
		{
			if ((current = target_vertex(env))) // dock
			{
				if (poscmp(current->pos,
				env->sct_current->vtx_start->pos)) // dock start
				{
					env->sct_current->close = 1;
					env->sct_current->vtx_current = 0;
					env->sct_current = 0;
					env->drawing = 0;
				}
				else // dock other
					create_vertex(current->pos, env);
			}
			else // no dock
				create_vertex(env->data->mouse, env);
		}
		return (1);
	}
	return (0);
}
