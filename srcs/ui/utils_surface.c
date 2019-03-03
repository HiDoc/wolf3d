/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_surface.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 16:17:46 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/03 16:34:37 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

SDL_Surface		*new_surface(char *filename)
{
	SDL_Surface	*new;
	char		*path;
	const char	*png = ".png";

	path = ft_strjoin("./rsrc/img/", filename);
	path = ft_strljoin(path, (char *)png);
	new = IMG_Load(path);
	free(path);
	path = NULL;
	return (new);
}