/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_skybox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 14:46:44 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/28 16:27:18 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		init_skybox(t_env *env)
{
	const t_vctr	player = env->engine.player.where;
	t_vtx			vertex[5];
	signed char		neighbors[4];

	if (!(env->engine.skybox.top = IMG_Load("rsrc/skybox/sb_top.jpg")))
	{
		printf("%s\n", IMG_GetError());
		exit(EXIT_FAILURE); // recup error
	}
	if (!(env->engine.skybox.bot = IMG_Load("rsrc/skybox/sb_bot.jpg")))
	{
		printf("%s\n", IMG_GetError());
		exit(EXIT_FAILURE); // recup error
	}
	if (!(env->engine.skybox.left = IMG_Load("rsrc/skybox/sb_left.jpg")))
	{
		printf("%s\n", IMG_GetError());
		exit(EXIT_FAILURE); // recup error
	}
	if (!(env->engine.skybox.right = IMG_Load("rsrc/skybox/sb_right.jpg")))
	{
		printf("%s\n", IMG_GetError());
		exit(EXIT_FAILURE); // recup error
	}
	if (!(env->engine.skybox.front = IMG_Load("rsrc/skybox/sb_front.jpg")))
	{
		printf("%s\n", IMG_GetError());
		exit(EXIT_FAILURE); // recup error
	}
	if (!(env->engine.skybox.back = IMG_Load("rsrc/skybox/sb_back.jpg")))
	{
		printf("%s\n", IMG_GetError());
		exit(EXIT_FAILURE); // recup error
	}

	vertex[0] = (t_vtx){player.x - 10, player.y - 10};
	vertex[1] = (t_vtx){player.x + 10, player.y - 10};
	vertex[2] = (t_vtx){player.x + 10, player.y + 10};
	vertex[3] = (t_vtx){player.x - 10, player.y + 10};
	vertex[4] = (t_vtx){player.x - 10, player.y - 10};

	ft_memset(&neighbors, -1, sizeof(signed char));

	env->engine.skybox.sector.floor = 0;
	env->engine.skybox.sector.ceil = 100;
	env->engine.skybox.sector.vertex = vertex;
	env->engine.skybox.sector.neighbors = neighbors;
	env->engine.skybox.sector.npoints = 4;
	env->engine.skybox.sector.head_object = 0;
	env->engine.skybox.sector.nb_objects = 0;
}
