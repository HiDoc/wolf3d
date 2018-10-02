/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sdl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 15:55:08 by fmadura           #+#    #+#             */
/*   Updated: 2018/10/02 15:56:39 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

SDL_Surface	*create_surface(char *path)
{
	SDL_Surface* image = IMG_Load(path);
	if(!image)
	{
		printf("Erreur de chargement de l'image : %s", SDL_GetError());
		return NULL;
	}
	return (image);
}
