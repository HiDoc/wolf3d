/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_hud_img.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 15:02:07 by abaille           #+#    #+#             */
/*   Updated: 2019/04/21 13:46:23 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			draw_img(t_env *env, SDL_Surface *img, t_bloc *bloc)
{
	int		i;
	int		j;

	const float ratiox = img->w / (float)bloc->rect.w;
	const float ratioy = img->h / (float)bloc->rect.h;

	i = bloc->limit.v1.x;
	while (i < bloc->rect.w - bloc->limit.v2.x
	&& (ratiox > 1 ? (i * ratiox) : i) < img->w)
	{
		j = bloc->limit.v1.y;
		while (j < bloc->rect.h - bloc->limit.v2.y
		&& (ratioy > 1 ? (j * ratioy) : j) < img->h)
		{
			// Uint32 color = ;
			if (getpixel(img, (ratiox > 1 ? (i * ratiox) : i),
			(ratioy > 1 ? (j * ratioy) : j)) & img->format->Amask)
				setpixel(env->sdl.surface, i + bloc->rect.x,
				j + bloc->rect.y, getpixel(img, (ratiox > 1 ? (i * ratiox) : i),
			(ratioy > 1 ? (j * ratioy) : j)));
			j++;
		}
		i++;
	}
}

SDL_Surface		*ui_img(char *file, int i)
{
	SDL_Surface	*new;
	char		*nb;
	char		*path;
	char		*final_path;
	const char	*png = ".png";

	path = NULL;
	final_path = NULL;
	nb = ft_itoa(i + 1);
	path = ft_strjoin("./rsrc/img/", file);
	final_path = ft_strrjoin(path, nb);
	final_path = ft_strljoin(final_path, (char *)png);
	new = load_image(final_path);
	lt_release(path);
	lt_release(final_path);
	return (new);
}

