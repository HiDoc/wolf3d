/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txr_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 20:08:04 by abaille           #+#    #+#             */
/*   Updated: 2019/05/07 20:08:39 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	txr_del(void **ap)
{
	SDL_Texture	*texture;

	texture = (SDL_Texture *)(*ap);
	if (ap && *ap)
	{
		SDL_DestroyTexture(texture);
		texture = 0;
	}
}
