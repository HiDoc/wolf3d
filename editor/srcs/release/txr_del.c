/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txr_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 20:47:23 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/07 20:47:29 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		txr_del(void **ap)
{
	SDL_Texture		*texture;

	texture = (SDL_Texture *)(*ap);
	if (ap && *ap)
	{
		SDL_DestroyTexture(texture);
		texture = 0;
	}
}
