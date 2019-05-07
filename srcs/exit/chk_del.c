/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 19:45:59 by abaille           #+#    #+#             */
/*   Updated: 2019/05/07 19:46:27 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	chk_del(void **ap)
{
	Mix_Chunk	*chunk;

	chunk = (Mix_Chunk *)(*ap);
	if (ap && *ap)
	{
		Mix_FreeChunk(chunk);
		chunk = 0;
	}
}

