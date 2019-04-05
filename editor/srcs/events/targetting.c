/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   targetting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:57:49 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/05 19:21:03 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

/*t_pos   diff_vertex(t_pos p1, t_pos p2)
  {
  t_pos	pos;

  pos = (t_pos){p1.x - p2.x, p1.y - p2.y};
  return (pos);
  }

  float		cross_product(t_pos p1, t_pos p2)
  {
  return (p1.x * p2.y - p2.x * p1.y); 
  }

// intersect vrx/edg
float		pointside(t_pos p, t_vrx v0, t_vrx v1)
{
t_pos	p0;
t_pos	p1;

p0 = (t_pos){v0.pos.x, v0.pos.y};
p1 = (t_pos){v1.pos.x, v1.pos.y};
return (cross_product(diff_vertex(p1, p0), diff_vertex(p, p0)));
}*/

/*// intersect vrx/vrx return vrx on intersect or -1/-1
  t_pos		intersect_vrx(t_vrx v1, t_vrx v2, t_vrx v3, t_vrx v4)
  {
  t_pos	p1 = (t_pos){v1.pos.x, v1.pos.y};
  t_pos	p2 = (t_pos){v2.pos.x, v2.pos.y};
  t_pos	p3 = (t_pos){v3.pos.x, v3.pos.y};
  t_pos	p4 = (t_pos){v4.pos.x, v4.pos.y};
  t_pos   v;
  float   div;
  float   xs1;
  float   xs2;
  float   (*f)(t_pos, t_pos);

  f = &cross_product;
  xs1 = f(p1, p2);
  xs2 = f(p3, p4);
  div = f((t_pos){p1.x - p2.x, p1.y - p2.y},
  (t_pos){p3.x - p4.x, p3.y - p4.y});
  v.x = f((t_pos){xs1, p1.x - p2.x}, (t_pos){xs2, p3.x - p4.x}) / div;
  v.y = f((t_pos){xs1, p1.y - p2.y}, (t_pos){xs2, p3.y - p4.y}) / div;
  return (v);
  }*/

t_sct       *target_sector(t_pos pos, t_env *env)
{
	t_sct   *sector;
	t_sct   *target;

	target = 0;
	sector = env->sct_start;
	while (sector && sector->close == 1) // for each sectors
	{
		sector->color = 0xFFFFFFFF;
		if (!(env->vtx_hover) && vertex_in_sector(sector, pos))
		{
			sector->color = (env->mouse_mode == 0) ? 0xFF00FF00 : 0xFF0000FF;
			target = sector;
		}
		sector = sector->next;
	}
	return (target);
}

t_vtx		*target_vertex(t_env *env)
{
	t_sct	*sct;
	t_vtx	*vtx;
	t_pos	pos;

	env->vtx_hover = 0;
	sct = env->sct_start;
	while (sct)
	{
		vtx = sct->vtx_start;
		while (vtx)
		{
			pos = (t_pos){
			20 + vtx->pos.x * env->pixel_value,
			100 + vtx->pos.y * env->pixel_value};
			if (ui_close_to(env->data->mouse, pos, 10))
			{
				env->vtx_hover = vtx;
				return (vtx);
			}
			vtx = vtx->next;
		}
		sct = sct->next;
	}
	return (0);
}

t_object	*target_object(t_pos pos, t_env *env)
{
	t_object	*obj;
	t_pos		calcpos;

	env->obj_hover = 0;
	obj = env->objects;
	while (obj)
	{
		calcpos = (t_pos){
		20 + obj->pos.x * env->pixel_value,
		100 + obj->pos.y * env->pixel_value};
		if (ui_close_to(pos, calcpos, 10))
		{
			env->obj_hover = obj;
			return (obj);
		}
		obj = obj->next;
	}
	return (0);
}
