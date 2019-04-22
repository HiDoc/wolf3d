/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_f_parser.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 20:43:23 by abaille           #+#    #+#             */
/*   Updated: 2019/04/22 14:47:27 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_F_PARSER_H
# define DOOM_F_PARSER_H

void		load_worlds(t_env *env);
void		load_map(t_engine *e, t_env *env);
void	    fill_objects_sector(t_sector *sector, t_vtx v, int ref, int is_wpn);
int			fill_enemies_sector(t_env *env, t_sector *sector, t_vtx v, int ref);
int			verify_parallelism(t_chain *chain, t_sector *sect, int mycase);

#endif
