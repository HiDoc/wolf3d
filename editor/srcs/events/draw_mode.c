/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 16:03:46 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/30 22:53:11 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static int	vertex_of_sector(t_vtx *vtx, t_sct *sct)
{
	t_w_vtx		*ptr;

	ptr = sct->w_vtx_start;
	while (ptr)
	{
		if (ptr->vtx == vtx)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

int			draw_mode(t_env *env)
{
	SDL_Rect			rect = get_element(E_R_RECT, env)->rect;
	const t_pos			m = env->data->mouse;
	const SDL_Event 	event = env->data->sdl.event;
	t_elem				*wall_txtr;

	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (ui_mouseenter(m.x, m.y, get_element(E_B_DRW_UP, env)->rect))
		{
			(env->editor.dropdown[DD_WALLTX].idx_element < 0)
				? env->editor.dropdown[DD_WALLTX].idx_element++ : 0;
		}
		else if (ui_mouseenter(m.x, m.y, get_element(E_B_DRW_DOWN, env)->rect))
		{
			(env->editor.dropdown[DD_WALLTX].idx_element
			> -env->editor.dropdown[DD_WALLTX].nb_element + 1)
				? env->editor.dropdown[DD_WALLTX].idx_element-- : 0;
		}
		else if (ui_mouseenter(m.x, m.y, rect))
		{
			if (!env->editor.sct_hover)
			{
				if (!env->editor.drawing)
				{
					env->editor.drawing = 1;
					create_sector(env);
				}
				if (!env->editor.vtx_hover)
				{
					create_vertex(env->mouse, env);
					create_w_vertex(env->vertex, env);
				}
				else if (env->sct_current->w_vtx_start
				&& env->editor.vtx_hover == w_vtx_lst_end(
				env->sct_current->w_vtx_start)->vtx
				&& env->sct_current->nb_w_vtx > 2)
				{
					env->sct_current->close = 1;
					env->sct_current->w_vtx_current = 0;
					env->sct_current = 0;
					env->editor.drawing = 0;
				}
				else if (!vertex_of_sector(
				env->editor.vtx_hover, env->sct_current))
				{
					create_w_vertex(env->editor.vtx_hover, env);
				}
			}
		}

		// click on object button
		wall_txtr = env->editor.dropdown[DD_WALLTX].start;
		while (wall_txtr)
		{
			if (ui_mouseenter(m.x, m.y, wall_txtr->rect))
			{
				env->editor.dropdown[DD_WALLTX].current->clicked = 0;
				env->editor.dropdown[DD_WALLTX].current = wall_txtr;
				wall_txtr->clicked = 1;
			}
			wall_txtr = wall_txtr->next;
		}
		return (1);
	}
	if (env->sct_current)
	{
		env->sct_current->w_vtx_current->size =
			pythagore(env->sct_current->w_vtx_current->vtx->pos, env->mouse);
	}
	return (ui_mouseenter(m.x, m.y, rect) && (m.x || m.y));
}
