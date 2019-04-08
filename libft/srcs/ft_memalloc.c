/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 16:26:16 by abaille           #+#    #+#             */
/*   Updated: 2019/04/09 00:04:26 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*mem;

	mem = NULL;
	if (size)
	{
		if (!(mem = lt_push(malloc(size), ft_memdel)))
			doom_error_exit("Doom_nukem error, out of memory");
		ft_bzero(mem, size);
	}
	return (mem);
}
