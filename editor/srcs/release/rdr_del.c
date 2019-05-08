/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 20:46:28 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/07 20:46:37 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		rdr_del(void **ap)
{
	SDL_Renderer		*renderer;

	renderer = (SDL_Renderer *)(*ap);
	if (ap && *ap)
	{
		SDL_DestroyRenderer(renderer);
		renderer = 0;
	}
}
