/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   musics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:18:01 by abaille           #+#    #+#             */
/*   Updated: 2019/03/19 14:19:18 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	load_sounds(t_weapon *wpn, char *name, char *action)
{
	char 	*path;
	char	*file;

	if ((path = ft_strjoin("./rsrc/sound/", action))
	&& (file = ft_strljoin(path, name))
	&& (file = ft_strljoin(file, ".wav"))
	&& (wpn->shot = Mix_LoadWAV(file)))
	{
		free(file);
		return (1);
	}
	return (0);
}