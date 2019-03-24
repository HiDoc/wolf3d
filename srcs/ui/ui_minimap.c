/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 16:07:41 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/24 20:48:54 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*static*/ t_edge	translate_edge(t_vctr player_position, t_vtx v1, t_vtx v2)
{
	t_edge      edge;

	edge.v1 = (t_vtx){v1.x - player_position.x, v1.y - player_position.y};
	edge.v2 = (t_vtx){v2.x - player_position.x, v2.y - player_position.y};
	return (edge);
}

/*static*/ t_edge	rotate_edge(t_player player, t_edge v)
{
	const float pcos = -player.anglecos;
	const float psin = -player.anglesin;
	t_edge      edge;

	edge.v1 = (t_vtx){
		v.v1.x * psin - v.v1.y * pcos,
			v.v1.x * pcos + v.v1.y * psin};

	edge.v2 = (t_vtx){
		v.v2.x * psin - v.v2.y * pcos,
			v.v2.x * pcos + v.v2.y * psin};

	return (edge);
}

/*static*/ void		draw_objects(SDL_Surface *surface, t_minimap *minimap,
		t_engine *engine)
{
	t_wrap_sect		*obj;
	SDL_Rect		rect;
	t_edge			edge;
	unsigned int	i;

	i = 0;
	while (i < engine->nsectors)
	{
		obj = engine->sectors[i].head_object;
		while (obj)
		{
			// translation
			edge = translate_edge(engine->player.where, obj->vertex, obj->vertex);

			// rotation
			edge = rotate_edge(engine->player, edge);

			// scale
			rect = (SDL_Rect){
				edge.v1.x * COEF_MINIMAP, 
					edge.v1.y * COEF_MINIMAP,
					10, 10};

			// origin
			rect = (SDL_Rect){
				rect.x + minimap->origin.x + MINIMAP_SIZE / 2 - 5,
					rect.y + minimap->origin.y + MINIMAP_SIZE / 2 - 5,
					10, 10};

			ui_draw_rect(surface, rect, C_GREEN);
			obj = obj->next;
		}
		i++;
	}
}

void		ui_minimap(t_env *env)
{
	t_minimap			*minimap = &(env->engine.minimap);

	// blit
	SDL_Rect src_rect = (SDL_Rect){
	(env->engine.player.where.x * COEF_MINIMAP),
	(env->engine.player.where.y * COEF_MINIMAP),
	MINIMAP_SIZE, MINIMAP_SIZE};

	SDL_UnlockSurface(env->sdl.surface);

	SDL_BlitScaled(minimap->background, 0, env->sdl.surface,
	&((SDL_Rect){minimap->origin.x, minimap->origin.y,
	MINIMAP_SIZE, MINIMAP_SIZE}));

	env->sdl.surface = rotate_surface(src_rect,
	minimap->surface, env->sdl.surface, minimap->origin, env);

	SDL_LockSurface(env->sdl.surface);

	// draw objects && bots
	draw_objects(env->sdl.surface, minimap, &(env->engine));
	// draw_bots();
}
