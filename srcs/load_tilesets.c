/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_tilesets.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 17:23:20 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/21 14:36:01 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

SDL_Surface		*tile_blit(t_tiletab *tiletab, int index)
{
	SDL_Surface		*surface;
	SDL_Rect		srcrect;

	srcrect = (SDL_Rect){
	index % tiletab->tile_size, index % tiletab->nb_column,
	tiletab->tile_size, tiletab->tile_size};
	surface = make_surface(tiletab->tile_size, tiletab->tile_size);
	if ((SDL_BlitScaled(surface, &srcrect, tiletab->tileset, 0)) < 0)
		doom_error_exit("Doom_nukem error on tile_blit");
	SDL_FreeSurface(surface);
	return (surface);
}

/*
** path		: tileset path
** nb		: nb of tiles
** size		: w/h of a tile
*/
void			parse_tileset(t_tiletab *tiletab)
{
	int				i;

	i = 0;
	tiletab->tileset = load_image(tiletab->path);
	tiletab->surface =
	(SDL_Surface **)ft_memalloc(sizeof(SDL_Surface *) * (tiletab->nb_tiles + 1));
	while (i < tiletab->nb_tiles)
	{
		tiletab->surface[i] = tile_blit(tiletab, i);
		i++;
	}
}

void		load_tilesets(t_env *env)
{
	env->tiletab = (t_tiletab){"rsrc/tilesets/tileset.png", 0, 23, 20, 32, 0};
	parse_tileset(&(env->tiletab));
}
