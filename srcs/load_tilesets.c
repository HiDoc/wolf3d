/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_tilesets.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 17:23:20 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/08 16:44:45 by abaille          ###   ########.fr       */
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
	if (!(surface = ui_make_surface(tiletab->tile_size, tiletab->tile_size)))
	{
		printf("Doom_nukem: tile_blit error\n");
		exit(EXIT_FAILURE); // recup error
	}
	if ((SDL_BlitScaled(surface, &srcrect, tiletab->tileset, 0)) < 0)
	{
		printf("Doom_nukem: tile_blit error\n");
		exit(EXIT_FAILURE); // recup error
	}
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
	if (!(tiletab->tileset = IMG_Load(tiletab->path)))
	{
		printf("Doom_nukem: %s\n", IMG_GetError());
		exit(EXIT_FAILURE); // recup error
	}
	if (!(tiletab->surface = (SDL_Surface **)
	ft_memalloc(sizeof(SDL_Surface *) * (tiletab->nb_tiles + 1))))
	{
		printf("Doom_nukem: Out of memory parse_tileset\n");
		exit(EXIT_FAILURE); // recup error
	}
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
