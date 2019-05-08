/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_other.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 17:57:50 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/05 18:01:18 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		no_op_ft(t_env *env, t_parseline *line, t_vtx *vtx)
{
	(void)env;
	(void)line;
	(void)vtx;
}

void		load_comment(t_env *e, t_parseline *line, t_vtx *vert)
{
	no_op_ft(e, line, vert);
}

void		load_music(t_env *e, t_parseline *line, t_vtx *vert)
{
	no_op_ft(e, line, vert);
}

void		load_skybox(t_env *e, t_parseline *line, t_vtx *vert)
{
	no_op_ft(e, line, vert);
}

void		load_texture(t_env *e, t_parseline *line, t_vtx *vert)
{
	no_op_ft(e, line, vert);
}
